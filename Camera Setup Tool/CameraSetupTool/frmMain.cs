using HalconDotNet;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ChartDirector;

namespace CameraSetupTool
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();

            currentImage = new HImage();

            this.btnFocusSetting.Tag = CameraSettingSteps.FocusSetting;
            this.btnLightIntensityCheck.Tag = CameraSettingSteps.LightIntensityCheck;
            this.btnWhiteBalancing.Tag = CameraSettingSteps.WhiteBalancing;
            this.btnFFC.Tag = CameraSettingSteps.FFC;

            cameraSteps = new iCameraSettingSteps[TOTALNUMBEROFSTEPS];
            cameraSteps[(int)CameraSettingSteps.FocusSetting] = new UserControls.FocusSetting();
            cameraSteps[(int)CameraSettingSteps.LightIntensityCheck] = new UserControls.LightIntensityCheck();
            cameraSteps[(int)CameraSettingSteps.WhiteBalancing] = new UserControls.WhiteBalancing();
            cameraSteps[(int)CameraSettingSteps.FFC] = new UserControls.OnCameraFFC();
            cameraSteps[(int)CameraSettingSteps.ImageViewer] = new UserControls.ImageViewer();
        }

        public CameraAcquisition cameraAcq;

        HImage currentImage;

        /// <summary>
        /// Denotes the coordinate of mouse pointer in the image window
        /// </summary>
        private double oldRow;
        /// <summary>
        /// Denotes the coordinate of mouse pointer in the image window
        /// </summary>
        private double oldCol;

        public enum CameraSettingSteps
        {
            FocusSetting,
            LightIntensityCheck,
            WhiteBalancing,
            FFC,
            ImageViewer
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            btnFocusSetting.Checked = true;
            
        }

        const int TOTALNUMBEROFSTEPS = 5;

        iCameraSettingSteps currentCameraStep;

        iCameraSettingSteps[] cameraSteps;

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void OnCameraSetupStepChanged(object sender, EventArgs e)
        {
            RadioButton b = sender as RadioButton;
            if (b.Checked)
            {
                CameraSettingSteps selectedStep = (CameraSettingSteps)Enum.Parse(typeof(CameraSettingSteps), b.Tag.ToString());
                OnStepChanged((int)selectedStep);
            }
        }

        private void OnStepChanged(int currentStep)
        {
            currentCameraStep = cameraSteps[currentStep];
            cameraAcq.RemoveImageGrabbedHandlers();
            this.SuspendLayout();
            this.pnlControls.Controls.Clear();
            this.pnlControls.Controls.Add((Control)currentCameraStep);
            this.ResumeLayout();
            currentCameraStep.CameraAcquisition = this.cameraAcq;
            currentCameraStep.CameraAcquisition.ImageGrabbed += new ImageGrabbedHandler(UpdateUIAfterProcessingStep);
            currentCameraStep.RefreshImageWindow += new CameraSetupTool.RefreshImageWindowEventHandler(UpdateUIAfterProcessingStep);
            StepDescriptor desc = currentCameraStep.GetStepDescriptor();

            lblInstruction.Text = desc.StepDescription;
        }

        private void UpdateUIAfterProcessingStep(HImage grabbedImage)
        {
            if (this.currentImage == null)
            {
                return;
            }
            currentImage = grabbedImage.CopyImage();
            currentCameraStep.ProcessStep(currentImage);
            UpdateImageWindow(currentImage);
            UpdateChartUI(currentCameraStep);
        }

        private void UpdateImageWindow(HImage image)
        {
            if (this.currentImage == null) return;
            if (this.InvokeRequired)
            {
                Action<HImage> a = new Action<HImage>(UpdateImageWindow);
                this.BeginInvoke(a, image);
            }
            HImage rgbImage = null;
            HImage rImage = null;
            HImage gImage = null;
            HImage bImage = null;
            HImage irImage = null;
            if(image.CountChannels() > Properties.Settings.Default.NumberOfChannelsInColorImage)
            {
                rImage = image.Decompose4(out gImage, out bImage, out irImage);
                rgbImage = rImage.Compose3(gImage, bImage);

                if (rgbImage != null)
                    this.hwcRGBImage.DisplayImage(rgbImage);

                if (irImage != null)
                    this.hwcIRImage.DisplayImage(irImage);

            }
        }

        void UpdateChartUI(iCameraSettingSteps step)
        {
            if (this.currentImage == null)
            {
                return;
            }
            if (this.InvokeRequired)
            {
                Action<iCameraSettingSteps> a = new Action<iCameraSettingSteps>(UpdateChartUI);
                this.BeginInvoke(a, step);
            }
            else
            {
                step.UpdateChartUI(this.winChart);
            }
        }

        /// <summary>
        /// Handles the "Mouse Move" event in the Image Window
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="HalconDotNet.HMouseEventArgs"/> instance containing the event data.</param>
        private void OnImageWindowMouseMove(object sender, HMouseEventArgs e)
        {
            HalconWindowControl window = sender as HalconWindowControl;
            UpdatePointAndGrayValLabels(window, e.Y, e.X);
        }

        private void OnImageWindowImageChanged(object sender)
        {
            HalconWindowControl window = sender as HalconWindowControl;
            UpdatePointAndGrayValLabels(window as HalconWindowControl, oldRow, oldCol);
            RefreshRegionsInHalconWindow(window);
        }

        private void OnImageWindowRepainted(object sender)
        {
            HalconWindowControl window = sender as HalconWindowControl;
            RefreshRegionsInHalconWindow(window);
        }

        /// <summary>
        /// Updates the coordinate and gray value labels according to the mouse movement
        /// </summary>
        /// <param name="window">The window.</param>
        /// <param name="row">The row.</param>
        /// <param name="column">The column.</param>
        private void UpdatePointAndGrayValLabels(HalconWindowControl window, double row, double column)
        {
            if (this.InvokeRequired)
            {
                Action<HalconWindowControl, double, double> a = new Action<HalconWindowControl,double,double>(UpdatePointAndGrayValLabels);
                this.BeginInvoke(a, window,row,column);
            }
            else
            {
            if (window == null) return;
            lblRowColData.Text = Convert.ToInt32(row) + @"," + Convert.ToInt32(column);
            oldRow = row;
            oldCol = column;
            try
            {
                if (window.ImageData == null || column < 0 || row < 0 || window.ImageWidth < column || window.ImageHeight < row)
                {
                    lblRowColData.Text = "0,0";
                    lblColorValue.Text = "0,0,0";
                    return;
                }
                    string pixelString = "";
                HTuple pixelVal = window.ImageData.GetGrayval((int)row, (int)column);
                if (pixelVal.Length > 1)
                {
                    for (int i = 0; i < pixelVal.Length; i++)
                    {
                        pixelString = pixelString + pixelVal[i].D;
                        if (i != pixelVal.Length - 1)
                        {
                            pixelString = pixelString + ",";
                        }
                    }
                }
                else
                {
                        int channels = window.ImageData.CountChannels();
                    if (channels == 1)
                    {
                        HTuple pixelVals = window.ImageData.GetGrayval((int)row, (int)column);
                        pixelString = Convert.ToInt32(pixelVals.D).ToString();
                    }
                    else if (channels == 3)
                    {
                        HImage r, g, b;
                        r = window.ImageData.Decompose3(out g, out b);
                        HTuple pixelVals = r.GetGrayval((int)row, (int)column);
                        pixelString = Convert.ToInt32(pixelVals.D).ToString();
                        pixelVals = g.GetGrayval((int)row, (int)column);
                        pixelString = pixelString + "," + Convert.ToInt32(pixelVals.D);
                        pixelVals = b.GetGrayval((int)row, (int)column);
                        pixelString = pixelString + "," + Convert.ToInt32(pixelVals.D);
                    }
                }

                lblColorValue.Text = pixelString;
            }
            catch
            { }
            }
        }

        /// <summary>
        /// Refreshes the regions in halcon window.
        /// </summary>
        /// <param name="window">The window.</param>
        private void RefreshRegionsInHalconWindow(HalconWindowControl window)
        {
            if (window != null)
            {
                window.HalconWindow.SetColor("green");
                window.HalconWindow.SetLineWidth(2);
                window.HalconWindow.SetDraw("margin");
                window.HalconWindow.DispRectangle1(0.0, this.cameraAcq.CurrentCameraProperties.NumberOfPixelsToBeClippedAtLeft, this.cameraAcq.CurrentImageHeight, this.cameraAcq.CurrentImageWidth - this.cameraAcq.CurrentCameraProperties.NumberOfPixelsToBeClippedAtRight);
                window.HalconWindow.SetColor("cyan");
                window.HalconWindow.SetLineWidth(2);
                window.HalconWindow.DispRectangle1(0.0, this.cameraAcq.CurrentCameraProperties.CameraHeightReferenceLowerLimit, this.cameraAcq.CurrentImageHeight, this.cameraAcq.CurrentCameraProperties.CameraHeightReferenceUpperLimit);
            }
        }

        private void OnCickSaveSettingsMenu(object sender, EventArgs e)
        {

        }

        private void OnClickSaveImageMenu(object sender, EventArgs e)
        {
            SaveFileDialog sd = new SaveFileDialog();
            sd.DefaultExt = "bmp";
            sd.FileName = "Image Grabbed";
            sd.Filter = "Bitmap (*.bmp)|*.bmp|JPEG (*.jpeg)|*.jpeg|PNG (*.png)|*.png";
            sd.InitialDirectory = "D:\\";
            if(sd.ShowDialog() == DialogResult.OK)
            {
                string imageType = "";
                switch (sd.FilterIndex)
                {
                    case 1:
                        imageType = "bmp";
                        break;
                    case 2:
                        imageType = "jpg";
                        break;
                    case 3:
                        imageType = "png";
                        break;
                    default:
                        imageType = "bmp";
                        break;
                }
                HImage rgbImage;
                lock (this.currentImage)
                {
                    HImage gImage, bImage;
                    rgbImage = this.currentImage.Decompose3(out gImage, out bImage);
                    rgbImage = rgbImage.Compose3(gImage, bImage);
                }
                rgbImage.WriteImage(imageType, 0, sd.FileName);
            }
        }

        private void OnClickExitMenu(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void OnClickOpenSerialCMDWindow(object sender, EventArgs e)
        {
            frmCommandWindow frm = new frmCommandWindow(this.cameraAcq.CurrentCameraProperties.SerialPortIndex);
            frm.StartPosition = FormStartPosition.CenterScreen;
            frm.ShowDialog();
        }
    }

    public class StepDescriptor
    {
        public StepDescriptor()
        {
            this.isTriggerMode = false;
            this.isLearningRequired = false;
            this.isCorrectingRequired = false;
            isCameraCommunicationRequired = false;
        }

        /// <summary>
        /// Gets or sets the title for the step.
        /// </summary>
        /// <value>
        /// The step title.
        /// </value>
        public string StepTitle
        {
            get;
            set;
        }
        /// <summary>
        /// Gets or sets the description for the step.
        /// </summary>
        /// <value>
        /// The step description.
        /// </value>
        public string StepDescription
        {
            get;
            set;
        }

        /// <summary>
        /// Get or sets the mode of image grabber.
        /// </summary>
        public bool isTriggerMode
        {
            get;
            set;
        }

        /// <summary>
        /// Get or sets if step involves learning process.
        /// </summary>
        public bool isLearningRequired
        {
            get;
            set;
        }

        /// <summary>
        /// Get or sets if step involves learning process.
        /// </summary>
        public bool isCorrectingRequired
        {
            get;
            set;
        }

        /// <summary>
        /// Get or sets if step involves learning process.
        /// </summary>
        public bool isCameraCommunicationRequired
        {
            get;
            set;
        }
    }
}
