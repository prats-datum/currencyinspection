using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ChartDirector;
using HalconDotNet;

namespace CameraSetupTool.UserControls
{
    public partial class ImageViewer : UserControl, iCameraSettingSteps
    {
        public ImageViewer()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
            currentIVData = new ImageViewerData();
            ImageToBeSaved = new HImage();
        }

        public HImage ImageToBeSaved { get; set; }

        public CameraAcquisition CameraAcquisition { get; set; }

        public event RefreshImageWindowEventHandler RefreshImageWindow;
        public event Action<string> UpdateStepStatusMessage;

        public StepDescriptor GetStepDescriptor()
        {
            StepDescriptor desc = new StepDescriptor();
            desc.StepDescription = "Displays Line profile and histogram of the image";

            return desc;
        }

        ImageViewerData currentIVData;

        public void ProcessStep(HImage imageGrabbed)
        {
            currentIVData.Image = imageGrabbed;

            int imageChannels = imageGrabbed.CountChannels();

            HImage rImg = null, gImg = null, bImg = null, rgbImg = null, irImg = null;

            if (imageChannels == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
            {
                rImg = imageGrabbed.Decompose4(out gImg, out bImg, out irImg);
                rgbImg = rImg.Compose3(gImg, bImg);
            }

            HImage grayImage = new HImage();
            if (rgbImg == null) return;

            imageGrabbed = rgbImg.CopyImage();

            lock (this.ImageToBeSaved)
            {
                this.ImageToBeSaved = imageGrabbed.CopyImage();
            }

            HImage ho_R;
            HImage ho_G;
            HImage ho_B;

            ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);

            HTuple RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
            HTuple GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
            HTuple BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);
            HTuple IRAOIGrayVals = Globals.GetGrayValuesOfLine(irImg);

            currentIVData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
            currentIVData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
            currentIVData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();
            currentIVData.GrayValues.MPlaneVals = IRAOIGrayVals.ToDArr();

            UpdateHistogramForImage();
        }

        private void UpdateHistogramForImage()
        {
            if (this.InvokeRequired)
            {
                Action a = new Action(UpdateHistogramForImage);
                this.BeginInvoke(a);
            }
            else
            {
                HImage currentImage = this.ImageToBeSaved.CopyImage();

                HImage rImg, gImg, bImg;

                rImg = currentImage.Decompose3(out gImg, out bImg);
                
                HTuple RGrayValues = Globals.GetGrayValuesOfPixel(rImg);
                HTuple GGrayValues = Globals.GetGrayValuesOfPixel(gImg);
                HTuple BGrayValues = Globals.GetGrayValuesOfPixel(bImg);

                double[] redData;
                double[] greenData;
                double[] blueData;

                XYChart c = new XYChart(chartViewer.Width - 10, chartViewer.Height - 10, 0xffdddd, 0x000000, 1);

                c.setPlotArea(50, 10, chartViewer.Width - 100, chartViewer.Height - 60, 0xffffff, -1, -1);

                redData = RGrayValues;
                greenData = GGrayValues;
                blueData = BGrayValues;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);

                c.xAxis().setLinearScale(0, 255, 255);

                chartViewer.Chart = c;
            }
        }

        public WinChartViewer UpdateChartUI(WinChartViewer viewer)
        {
            double[] data = { };
            double[] redData;
            double[] greenData;
            double[] blueData;

            // Create a XYChart object of size 250 x 250 pixels
            XYChart c = new XYChart(viewer.Width - 10, viewer.Height - 10, 0xffdddd, 0x000000, 1);

            // Set the plotarea at (30, 20) and of size 200 x 200 pixels
            c.setPlotArea(50, 10, viewer.Width - 100, viewer.Height - 60, 0xffffff, -1, -1);

            if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
            {
                redData = currentIVData.GrayValues.RPlaneVals;
                greenData = currentIVData.GrayValues.GPlaneVals;
                blueData = currentIVData.GrayValues.BPlaneVals;
                data = currentIVData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
                c.addSplineLayer(data, 0x000000);
            }
            else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
            {
                data = currentIVData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(data);
            }
            else
            {
                redData = currentIVData.GrayValues.RPlaneVals;
                greenData = currentIVData.GrayValues.GPlaneVals;
                blueData = currentIVData.GrayValues.BPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
            }

            double XAxisDataCount = this.CameraAcquisition.CurrentImageWidth;

            c.yAxis().setLinearScale(0, 255, 255);
            double majorTicks = Math.Round(XAxisDataCount / 8, 0);
            double minorTicks = Math.Round(XAxisDataCount);
            c.xAxis().setLinearScale(0, Math.Round(XAxisDataCount, 0), majorTicks);

            c.yAxis().addMark(200, 0xA31F1F, "Max").setLineWidth(2);

            // Output the chart
            viewer.Chart = c;

            //include tool tip for the chart
            viewer.ImageMap = c.getHTMLImageMap("clickable", "",
                "title='Hour {xLabel}: Traffic {value} GBytes'");

            return viewer;
        }
    }
}
