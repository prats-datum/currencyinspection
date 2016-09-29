using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using HalconDotNet;

namespace CameraSetupTool
{
    public partial class HalconWindowControl : HWindowControl
    {
        public HalconWindowControl()
        {
            this.Dock = DockStyle.Fill;
            Resize += ResizedEvent;
            SetEventHandlers();
            resetTimer = new Timer { Interval = SystemInformation.DoubleClickTime };
            resetTimer.Tick += ResetTimer_Tick;
        }

        public enum ZoomPanType
        {
            ZoomOnly,
            PanOnly,
            ZoomAndPan,
            DisableAll
        }

        public enum ImageFitType
        {
            Auto,
            XAxis,
            YAxis
        }

        public delegate void RepaintEventHandler(object sender);
        public event RepaintEventHandler WindowRepainted;

        public delegate void ImageZoomedEventHandler(object sender, double Ratio);
        public event ImageZoomedEventHandler ImageZoomed;

        public delegate void ImageChangedEventHandler(object sender);
        public event ImageChangedEventHandler ImageChanged;

        private HImage imageUsed;
        private readonly Timer resetTimer;
        private int imageWidth;
        private int imageHeight;

        private double imgRow1;
        private double imgColumn1;
        private double imgRow2;
        private double imgColumn2;

        private double startX;
        private double startY;
        private ZoomPanType zoomData = ZoomPanType.ZoomAndPan;
        private int clickTrigger;
        private double ratioValue;
        private Cursor CursorUsed = Cursors.Default;

        public double Row1 { get { return imgRow1; } }

        public double Row2 { get { return imgRow2; } }

        public double Column1 { get { return imgColumn1; } }

        public double Column2 { get { return imgColumn2; } }

        public double ImageWidth { get { return imageWidth; } }

        public double ImageHeight { get { return imageHeight; } }

        public double RatioValue { get { return ratioValue; } }

        public HImage ImageData { get { return imageUsed; } }

        public bool DisplayBorder { get; set; }

        public ZoomPanType PanZoomType
        {
            get { return zoomData; }
            set
            {
                zoomData = value;
                SetEventHandlers();
            }
        }

        private ImageFitType imgFit = ImageFitType.Auto;
        public ImageFitType ImageFit
        {
            get { return imgFit; }
            set
            {
                imgFit = value;
                ZoomImage(0, 0, 1);
            }
        }

        void ResetTimer_Tick(object sender, EventArgs e)
        {
            if (clickTrigger == 2)
                Reset();
            clickTrigger = 0;
            resetTimer.Stop();
        }

        private void SetEventHandlers()
        {
            HMouseUp -= MouseUpEvent;
            HMouseDown -= MouseDownEvent;
            HMouseMove -= MouseMovedEvent;
            HMouseWheel -= MouseWheelEvent;

            if (zoomData == ZoomPanType.PanOnly || zoomData == ZoomPanType.ZoomAndPan)
            {
                HMouseDown += MouseDownEvent;
                HMouseMove += MouseMovedEvent;
            }
            if (zoomData == ZoomPanType.ZoomOnly || zoomData == ZoomPanType.ZoomAndPan)
            {
                HMouseWheel += MouseWheelEvent;
            }
            if (zoomData == ZoomPanType.ZoomAndPan || zoomData == ZoomPanType.ZoomOnly || zoomData == ZoomPanType.PanOnly)
            {
                HMouseUp += MouseUpEvent;
            }
        }

        public void DisplayImage(HObject imageObj)
        {
            if (imageObj == null) return;

            HImage obj = imageObj as HImage;
            if (obj != null)
            {
                bool isImageValid = false;
                try
                {
                    int channelCount = obj.CountChannels();
                    isImageValid = channelCount > 0;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                if (isImageValid)
                {
                    int h;
                    int w;
                    string s;
                    obj.GetImagePointer1(out s, out w, out h);
                    imageUsed = obj;
                    if (imageHeight == h && imageWidth == w)
                    {
                        Repaint();
                        if (ImageChanged != null)
                            ImageChanged(this);
                        return;
                    }
                    HRegion domain = obj.GetDomain();
                    HTuple r;
                    HTuple c;
                    int area = domain.AreaCenter(out r, out c);


                    if (area == (w * h))
                    {
                        if ((h != imageHeight) || (w != imageWidth))
                        {
                            imageHeight = h;
                            imageWidth = w;
                            SetImagePart(0, 0, h, w);
                            ZoomImage(0, 0, 1);
                        }
                    }
                }
            }
            Repaint();
            if (ImageChanged != null)
                ImageChanged(this);
        }

        private void SetImagePart(int row1, int column1, int row2, int column2)
        {
            imgRow1 = row1;
            imgColumn1 = column1;
            imgRow2 = imageHeight = row2;
            imgColumn2 = imageWidth = column2;

            System.Drawing.Rectangle rect = ImagePart;
            rect.X = (int)imgColumn1;
            rect.Y = (int)imgRow1;
            rect.Height = imageHeight;
            rect.Width = imageWidth;

            double ratio = (double)rect.Width / Width;
            rect.Height = (int)(rect.Height * ratio);
            ImagePart = rect;
        }

        private bool ZoomImage(double x, double y, double scale)
        {
            try
            {
                double lengthC = (imgColumn2 - imgColumn1) * scale;
                double lengthR = (imgRow2 - imgRow1) * scale;
                double percentC = (x - imgColumn1) / (imgColumn2 - imgColumn1);
                double percentR = (y - imgRow1) / (imgRow2 - imgRow1);

                if ((lengthC > 5 && lengthC < 50000) && (lengthR > 5 && lengthR < 35000))
                {
                    imgColumn1 = x - lengthC * percentC;
                    imgColumn2 = x + lengthC * (1 - percentC);

                    imgRow1 = y - lengthR * percentR;
                    imgRow2 = y + lengthR * (1 - percentR);

                    System.Drawing.Rectangle rect = ImagePart;
                    rect.X = (int)Math.Round(imgColumn1);
                    rect.Y = (int)Math.Round(imgRow1);
                    rect.Width = (int)Math.Round(lengthC);
                    rect.Height = (int)Math.Round(lengthR);


                    double ratioVal1 = (double)rect.Width / Width;
                    double ratioVal2 = (double)rect.Height / Height;
                    if (ImageFit == ImageFitType.XAxis)
                        ratioValue = ratioVal1;
                    else if (ImageFit == ImageFitType.YAxis)
                        ratioValue = ratioVal2;
                    else
                        ratioValue = ratioVal1 > ratioVal2 ? ratioVal1 : ratioVal2;
                    rect.Width = (int)(Width * ratioValue);
                    rect.Height = (int)(Height * ratioValue);

                    if (rect.Height > 0 && rect.Width > 0)
                    {
                        ImagePart = rect;
                    }
                    ratioValue = Convert.ToDouble(imageWidth) / Convert.ToDouble(Column2 - Column1);
                    if (ImageZoomed != null)
                        ImageZoomed(this, ratioValue);
                    Repaint();
                    return true;
                }
            }
            catch (Exception exMsg)
            {
                MessageBox.Show(@"Error: " + exMsg.Message);
            }
            return false;
        }

        private void MouseWheelEvent(object sender, HMouseEventArgs eventArgsList)
        {
            double scale;
            if (eventArgsList.Delta > 0)
            {
                scale = 0.9;            // Zoom in
            }
            else
            {
                scale = 1 / 0.9;        // Zoom out
            }

            if (ZoomImage(eventArgsList.X, eventArgsList.Y, scale))
            {
                if (WindowRepainted != null)
                {
                    WindowRepainted(this);
                }
            }
        }

        private void MouseDownEvent(object sender, HMouseEventArgs eventArgsList)
        {
            if (eventArgsList.Button == MouseButtons.Middle)
            {
                startX = eventArgsList.X;
                startY = eventArgsList.Y;
                CursorUsed = Cursor;
                Cursor = Cursors.NoMove2D;
            }
        }

        private void MouseUpEvent(object sender, HMouseEventArgs eventArgsList)
        {
            if (eventArgsList.Button == MouseButtons.Middle)
            {
                if (clickTrigger == 0)
                    resetTimer.Start();
                clickTrigger++;
                Cursor = CursorUsed;
            }
        }

        private void MouseMovedEvent(object sender, HMouseEventArgs eventArgsList)
        {
            if (eventArgsList.Button == MouseButtons.Middle)
            {
                double motionX = ((eventArgsList.X - startX));
                double motionY = ((eventArgsList.Y - startY));

                if (((int)motionX != 0) || ((int)motionY != 0))
                {
                    MoveImage(motionX, motionY);
                    if (WindowRepainted != null)
                    {
                        WindowRepainted(this);
                    }
                    startX = eventArgsList.X - motionX;
                    startY = eventArgsList.Y - motionY;
                }
            }
        }

        private void MoveImage(double motionX, double motionY)
        {
            imgRow1 += -motionY;
            imgRow2 += -motionY;

            imgColumn1 += -motionX;
            imgColumn2 += -motionX;

            System.Drawing.Rectangle rect = ImagePart;
            rect.X = (int)Math.Round(imgColumn1);
            rect.Y = (int)Math.Round(imgRow1);
            ImagePart = rect;

            Repaint();
        }

        public void Repaint()
        {
            HSystem.SetSystem("flush_graphic", "false");
            RepaintWithoutGraphics();
            HSystem.SetSystem("flush_graphic", "true");
            HalconWindow.SetColor("black");
            HalconWindow.DispLine(-100.0, -100.0, -101.0, -101.0);
        }

        public void ClearWindow()
        {
            imageUsed = null;
            imageWidth = 0;
            imageHeight = 0;
            ratioValue = 1;
            imgRow1 = 0;
            imgRow2 = 0;
            imgColumn1 = 0;
            imgColumn2 = 0;
            HalconWindow.ClearWindow();
        }

        public void RepaintWithoutGraphics()
        {
            HalconWindow.ClearWindow();
            if (imageUsed == null) return;
            HalconWindow.DispObj(imageUsed);
            if (DisplayBorder)
            {
                HalconWindow.SetColor("red");
                HalconWindow.SetDraw("margin");
                HalconWindow.DispRectangle1(0.0, 0.0, imageHeight, imageWidth);
            }
        }

        public void Repaint(bool flushGraphics)
        {
            if (flushGraphics)
                Repaint();
            else
                RepaintWithoutGraphics();
        }

        public void Reset()
        {
            imgRow1 = 0;
            imgColumn1 = 0;
            imgRow2 = imageHeight;
            imgColumn2 = imageWidth;
            SetImagePart(0, 0, (int)imgRow2, (int)imgColumn2);
            Repaint();
            ZoomImage(0, 0, 1);
            if (WindowRepainted != null)
            {
                WindowRepainted(this);
            }
        }

        private void ResizedEvent(object sender, EventArgs e)
        {
            ZoomImage(0, 0, 1);
        }
    }
}
