using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using HalconDotNet;
using ChartDirector;
using System.Threading;

namespace CameraSetupTool.UserControls
{
    public partial class WhiteBalancing : UserControl, iCameraSettingSteps
    {
        public WhiteBalancing()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
            ImageToBeSaved = new HImage();
        }

        public HImage ImageToBeSaved { get; set; }

        WhiteBalancingData currentWBData;

        /// <summary>
        /// Denotes whether the White Balancing process has started
        /// </summary>
        private bool whitebalancingStarted;

        public CameraAcquisition CameraAcquisition { get; set; }

        public event Action<string> UpdateStepStatusMessage;
        public event RefreshImageWindowEventHandler RefreshImageWindow;

        AutoResetEvent imageGrabbedEvent = new AutoResetEvent(false);
        ManualResetEvent wbIterationCompletedEvent = new ManualResetEvent(true);

        public StepDescriptor GetStepDescriptor()
        {
            StepDescriptor desc = new StepDescriptor();
            desc.StepDescription = "Please insert the \"ISU Plain Calibration Document\" to perform white balancing.";

            return desc;
        }

        public void ProcessStep(HImage imageGrabbed)
        {
            try
            {
                HTuple startTime = null;
                HTuple endTime = null;
                HOperatorSet.CountSeconds(out startTime);
                int imageChannels = imageGrabbed.CountChannels();

                HImage rImg = null, gImg = null, bImg = null, rgbImg = null, irImg = null;

                if (imageChannels == 6)
                {
                    rImg = imageGrabbed.Decompose4(out gImg, out bImg, out irImg);
                    rgbImg = rImg.Compose3(gImg, bImg);
                }

                HImage grayImage = new HImage();
                if (rgbImg == null) return;

                imageGrabbed = rgbImg.CopyImage();

                int presentImageNoOfChannels = imageGrabbed.CountChannels();

                if (presentImageNoOfChannels == Properties.Settings.Default.NumberOfChannelsInColorImage)
                {
                    lock (this.ImageToBeSaved)
                    {
                        this.ImageToBeSaved = imageGrabbed.CopyImage();
                    }
                    if (whitebalancingStarted)
                    {
                        wbIterationCompletedEvent.Reset();
                    }
                    imageGrabbedEvent.Set();

                    HImage ho_R;
                    HImage ho_G;
                    HImage ho_B;

                    ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);

                    HTuple RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
                    HTuple GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
                    HTuple BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);
                    HTuple IRAOIGrayVals = Globals.GetGrayValuesOfLine(irImg);

                    currentWBData.Image = imageGrabbed;
                    currentWBData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
                    currentWBData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
                    currentWBData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();
                    currentWBData.GrayValues.MPlaneVals = IRAOIGrayVals.ToDArr();

                    HImage ho_GrayImage;
                    ho_GrayImage = imageGrabbed.Rgb1ToGray();

                    HRegion whiteRegion = ho_GrayImage.Threshold(
                        Properties.Settings.Default.MinThresholdInDeterminingGain,
                        Properties.Settings.Default.MaxThresholdInDeterminingGain);
                    whiteRegion = whiteRegion.FillUp();
                    whiteRegion = whiteRegion.ErosionRectangle1(20, 20);

                    double rClipValue = 15.0;
                    double gClipValue = 15.0;
                    double bClipValue = 15.0;
                    //CalculateOptimumClipValue(whiteRegion, ho_R, out rClipValue);
                    //CalculateOptimumClipValue(whiteRegion, ho_G, out gClipValue);
                    //CalculateOptimumClipValue(whiteRegion, ho_B, out bClipValue);

                    double rMin, rMax, rRange;
                    double gMin, gMax, gRange;
                    double bMin, bMax, bRange;

                    ho_R.MinMaxGray(whiteRegion, rClipValue, out rMin, out rMax,
                        out rRange);
                    ho_G.MinMaxGray(whiteRegion, gClipValue, out gMin, out gMax,
                        out gRange);
                    ho_B.MinMaxGray(whiteRegion, bClipValue, out bMin, out bMax,
                        out bRange);

                    double RGDiff = rMax - gMax;
                    double GBDiff = gMax - bMax;
                    double BRDiff = bMax - rMax;

                    currentWBData.ErrorLevel = (Math.Max(RGDiff, Math.Max(GBDiff, BRDiff)) / this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel) * 100;
                    currentWBData.RedMax = rMax;
                    currentWBData.GreenMax = gMax;
                    currentWBData.BlueMax = bMax;


                    HOperatorSet.CountSeconds(out endTime);
                    currentWBData.TimeTaken = (endTime - startTime).D;

                    UpdateControlUI();

                    wbIterationCompletedEvent.WaitOne();
                }
            }
            catch (Exception ex)
            {
                string errorMessage = "Exception occurred during white balancing step. ";
                errorMessage = errorMessage + " Error Message: " + ex.Message;
                MessageBox.Show(errorMessage, "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                redData = currentWBData.GrayValues.RPlaneVals;
                greenData = currentWBData.GrayValues.GPlaneVals;
                blueData = currentWBData.GrayValues.BPlaneVals;
                data = currentWBData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
                c.addSplineLayer(data, 0x000000);
            }
            else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
            {
                data = currentWBData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(data);
            }
            else
            {
                redData = currentWBData.GrayValues.RPlaneVals;
                greenData = currentWBData.GrayValues.GPlaneVals;
                blueData = currentWBData.GrayValues.BPlaneVals;

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

        private void OnClickWhiteBalancing(object sender, EventArgs e)
        {
            this.whitebalancingStarted = true;
            this.btnWhiteBalancing.Enabled = false;
            this.btnReset.Enabled = false;
            this.lblStatus.Text = "Whitebalancing...";
            this.lblStatus.BackColor = Color.Yellow;
            Application.DoEvents();

            #region ManualWhiteBalancing

            //try
            //{
            //    HTuple startTime = null;
            //    HTuple endTime = null;
            //    HOperatorSet.CountSeconds(out startTime);

            //    double PERStep = Properties.Settings.Default.GainStepInitialValue;
            //    double PEGStep = Properties.Settings.Default.GainStepInitialValue;
            //    double PEBStep = Properties.Settings.Default.GainStepInitialValue;

            //    bool retVal;

            //    if (this.CameraAcquisition.CurrentNumberOfChannels >= Properties.Settings.Default.NumberOfChannelsInColorImage)
            //    {
            //        HImage ho_R;
            //        HImage ho_G;
            //        HImage ho_B;
            //        HImage ho_RGB;
            //        lock (this.ImageToBeSaved)
            //        {
            //            ho_RGB = this.ImageToBeSaved.CopyImage();
            //        }

            //        ho_R = ho_RGB.Decompose3(out ho_G, out ho_B);

            //        HTuple RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
            //        HTuple GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
            //        HTuple BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);


            //        currentWBData.Image = ho_RGB;
            //        currentWBData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
            //        currentWBData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
            //        currentWBData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();

            //        ho_RGB = ho_RGB.CropPart((this.CameraAcquisition.CurrentImageHeight / 2) - Properties.Settings.Default.WBROIRectangleHeight,
            //            (this.CameraAcquisition.CurrentImageWidth / 2) - Properties.Settings.Default.WBROIRectangleWidth,
            //            Properties.Settings.Default.WBROIRectangleWidth * 2,
            //            (this.CameraAcquisition.CurrentImageHeight / 2));

            //        ho_R = ho_RGB.Decompose3(out ho_G, out ho_B);

            //        RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
            //        GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
            //        BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);

            //        bool lightIntensityOptimum = true;

            //        if (Properties.Settings.Default.CheckForImproperCalibrationTarget)
            //        {
            //            int minGrayValue;
            //            int maxGrayValue;
            //            double[] tempLineProfileR = RAOIGrayVals.TupleSelectRange(
            //                        this.CameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtLeft,
            //                        (Properties.Settings.Default.WBROIRectangleWidth * 2) - this.CameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtRight).ToDArr();

            //            lightIntensityOptimum &= CameraAcquisition.IsLightIntensityLevelOptimum(tempLineProfileR, out minGrayValue, out maxGrayValue);
            //        }

            //        if (!lightIntensityOptimum)
            //        {
            //            this.lblStatus.Text = Properties.Settings.Default.WhiteBalancingLightIntensityNotOptimumMessage;
            //            this.lblStatus.BackColor = Color.Red;
            //            this.btnWhiteBalancing.Enabled = true;
            //            this.btnReset.Enabled = true;
            //            this.whitebalancingStarted = false;
            //            Application.DoEvents();
            //            return;
            //        }

            //        HImage ho_GrayImage;
            //        ho_GrayImage = ho_RGB.Rgb1ToGray();

            //        HRegion whiteRegion = ho_GrayImage.Threshold(
            //            Properties.Settings.Default.MinThresholdInDeterminingGain,
            //            Properties.Settings.Default.MaxThresholdInDeterminingGain);
            //        whiteRegion = whiteRegion.FillUp();
            //        whiteRegion = whiteRegion.ErosionRectangle1(20, 20);

            //        bool continueForRedChannel = true;
            //        bool continueForGreenChannel = true;
            //        bool continueForBlueChannel = true;

            //        int tempIndex = 1;
            //        int i;
            //        for (i = 0; ((i < Properties.Settings.Default.MaxIterationsInSettingAutomaticGain) &&
            //            (continueForRedChannel || continueForGreenChannel || continueForBlueChannel)); i++)
            //        {

            //            currentWBData = new WhiteBalancingData();


            //            imageGrabbedEvent.WaitOne();
            //            for (; tempIndex % 5 != 0; tempIndex++)
            //            {
            //                wbIterationCompletedEvent.Set();
            //                imageGrabbedEvent.WaitOne();
            //            }
            //            tempIndex++;

            //            lock (this.ImageToBeSaved)
            //            {
            //                ho_RGB = this.ImageToBeSaved.CopyImage();
            //            }

            //            ho_R = ho_RGB.Decompose3(out ho_G, out ho_B);

            //            RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
            //            GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
            //            BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);

            //            currentWBData.Image = ho_RGB;
            //            currentWBData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
            //            currentWBData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
            //            currentWBData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();

            //            ho_RGB = ho_RGB.CropPart((this.CameraAcquisition.CurrentImageHeight / 2) - Properties.Settings.Default.WBROIRectangleHeight,
            //            (this.CameraAcquisition.CurrentImageWidth / 2) - Properties.Settings.Default.WBROIRectangleWidth,
            //            Properties.Settings.Default.WBROIRectangleWidth * 2,
            //            (this.CameraAcquisition.CurrentImageHeight / 2));

            //            ho_R = ho_RGB.Decompose3(out ho_G, out ho_B);

            //            RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
            //            GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
            //            BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);

            //            ho_GrayImage = ho_RGB.Rgb1ToGray();
            //            whiteRegion = ho_GrayImage.Threshold(
            //             Properties.Settings.Default.MinThresholdInDeterminingGain,
            //             Properties.Settings.Default.MaxThresholdInDeterminingGain);
            //            whiteRegion = whiteRegion.FillUp();
            //            whiteRegion = whiteRegion.ErosionRectangle1(20, 20);
            //            this.lblStatus.Text = "Whitebalancing..." + System.Environment.NewLine +
            //                "Iteration: " + (i + 1).ToString();
            //            this.lblStatus.BackColor = Color.Yellow;
            //            Application.DoEvents();
            //            double rClipValue = 15.0;
            //            double gClipValue = 15.0;
            //            double bClipValue = 15.0;

            //            double rMin, rMax, rRange;
            //            double gMin, gMax, gRange;
            //            double bMin, bMax, bRange;

            //            ho_R.MinMaxGray(whiteRegion, rClipValue, out rMin, out rMax,
            //                out rRange);
            //            ho_G.MinMaxGray(whiteRegion, gClipValue, out gMin, out gMax,
            //                out gRange);
            //            ho_B.MinMaxGray(whiteRegion, bClipValue, out bMin, out bMax,
            //                out bRange);

            //            int currentPER = 0;
            //            int currentPEB = 0;
            //            int currentPEG = 0;

            //            if (continueForRedChannel)
            //            {
            //                //get intial PER Value
            //                currentPER = GetGainValueFromCamera(CameraChannels.Red);
            //                if (currentPER == -1)
            //                {
            //                    MessageBox.Show("Error occured while getting Red channel exposure value.",
            //                        "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);

            //                    UpdateControlUI();
            //                    this.RefreshImageWindow(currentWBData.Image);

            //                    this.lblStatus.Text = "White Balancing Not Done.";
            //                    this.lblStatus.BackColor = Color.Red;
            //                    this.btnWhiteBalancing.Enabled = true;
            //                    this.btnReset.Enabled = true;
            //                    this.whitebalancingStarted = false;
            //                    return;
            //                }
            //            }
            //            if (continueForGreenChannel)
            //            {
            //                //get intial PEG Value
            //                currentPEG = GetGainValueFromCamera(CameraChannels.Green);
            //                if (currentPER == -1)
            //                {
            //                    MessageBox.Show("Error occured while getting Green channel exposure value.",
            //                        "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //                    this.lblStatus.Text = "White Balancing Not Done.";
            //                    this.lblStatus.BackColor = Color.Red;
            //                    this.btnWhiteBalancing.Enabled = true;
            //                    this.btnReset.Enabled = true;
            //                    this.whitebalancingStarted = false;
            //                    return;
            //                }
            //            }
            //            if (continueForBlueChannel)
            //            {
            //                //get intial PEB Value
            //                currentPEB = GetGainValueFromCamera(CameraChannels.Blue);
            //                if (currentPER == -1)
            //                {
            //                    MessageBox.Show("Error occured while getting Blue channel exposure value.",
            //                        "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //                    this.lblStatus.Text = "White Balancing Not Done.";
            //                    this.lblStatus.BackColor = Color.Red;
            //                    this.btnWhiteBalancing.Enabled = true;
            //                    this.btnReset.Enabled = true;
            //                    this.whitebalancingStarted = false;
            //                    return;
            //                }
            //            }
            //            double expValue = 0;

            //            // Stop adjusting exposure values if the maximum gray level of 
            //            // red plane is within the range 
            //            // MaximumGrayLevel - Globals.WhiteBalancingOffsetFromRefGrayLevel to 
            //            // MaximumGrayLevel + Globals.WhiteBalancingOffsetFromRefGrayLevel       
            //            if ((rMax >= this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel - Properties.Settings.Default.WhiteBalancingOffsetFromRefGrayLevel) &&
            //               (rMax <= this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel + Properties.Settings.Default.WhiteBalancingOffsetFromRefGrayLevel))
            //            {
            //                continueForRedChannel = false;
            //            }
            //            if (continueForRedChannel)
            //            {
            //                PERStep = this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel / rMax;
            //                currentPER += 1024;
            //                double temp = (double)currentPER / 1024.0;
            //                currentPER = (int)Math.Round(temp * PERStep * 1024);
            //                currentPER -= 1024;
            //                if (currentPER < 0) currentPER *= -1;
            //                if (currentPER > 6500) currentPER = 6500;

            //                expValue = currentPER;

            //                retVal = WriteGainValueToCamera(CameraChannels.Red, expValue);
            //                if (!retVal)
            //                {
            //                    MessageBox.Show("Error occured while setting Red channel exposure value.",
            //                        "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //                    this.lblStatus.Text = "White Balancing Not Done.";
            //                    this.lblStatus.BackColor = Color.Red;
            //                    this.btnWhiteBalancing.Enabled = true;
            //                    this.btnReset.Enabled = true;
            //                    this.whitebalancingStarted = false;
            //                    return;
            //                }
            //            }

            //            // Stop adjusting exposure values if the maximum gray level of 
            //            // green plane is within the range 
            //            // MaximumGrayLevel - Globals.WhiteBalancingOffsetFromRefGrayLevel to 
            //            // MaximumGrayLevel + Globals.WhiteBalancingOffsetFromRefGrayLevel       
            //            if ((gMax >= this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel - Properties.Settings.Default.WhiteBalancingOffsetFromRefGrayLevel) &&
            //              (gMax <= this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel + Properties.Settings.Default.WhiteBalancingOffsetFromRefGrayLevel))
            //            {
            //                continueForGreenChannel = false;
            //            }
            //            if (continueForGreenChannel)
            //            {
            //                PEGStep = this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel / gMax;
            //                currentPEG += 1024;
            //                double temp = (double)currentPEG / 1024.0;
            //                currentPEG = (int)Math.Round(temp * PEGStep * 1024);
            //                currentPEG -= 1024;
            //                if (currentPEG < 0) currentPEG *= -1;
            //                if (currentPEG > 6500) currentPEG = 6500;

            //                expValue = currentPEG;
            //                retVal = WriteGainValueToCamera(CameraChannels.Green, expValue);
            //                if (!retVal)
            //                {
            //                    MessageBox.Show("Error occured while setting Green channel exposure value.",
            //                        "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //                    this.lblStatus.Text = "White Balancing Not Done.";
            //                    this.lblStatus.BackColor = Color.Red;
            //                    this.btnWhiteBalancing.Enabled = true;
            //                    this.btnReset.Enabled = true;
            //                    this.whitebalancingStarted = false;
            //                    return;
            //                }
            //            }

            //            // Stop adjusting exposure values if the maximum gray level of 
            //            // blue plane is within the range 
            //            // MaximumGrayLevel - Globals.WhiteBalancingOffsetFromRefGrayLevel to 
            //            // MaximumGrayLevel + Globals.WhiteBalancingOffsetFromRefGrayLevel       
            //            if ((bMax >= this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel - Properties.Settings.Default.WhiteBalancingOffsetFromRefGrayLevel) &&
            //              (bMax <= this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel + Properties.Settings.Default.WhiteBalancingOffsetFromRefGrayLevel))
            //            {
            //                continueForBlueChannel = false;
            //            }
            //            if (continueForBlueChannel)
            //            {
            //                PEBStep = this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel / bMax;
            //                currentPEB += 1024;
            //                double temp = (double)currentPEB / 1024.0;
            //                currentPEB = (int)Math.Round(temp * PEBStep * 1024);
            //                currentPEB -= 1024;

            //                if (currentPEB < 0) currentPEB *= -1;
            //                if (currentPEB > 6500) currentPEB = 6500;

            //                expValue = currentPEB;

            //                retVal = WriteGainValueToCamera(CameraChannels.Blue, expValue);
            //                if (!retVal)
            //                {
            //                    MessageBox.Show("Error occured while setting Blue channel exposure value.",
            //                        "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //                    this.lblStatus.Text = "White Balancing Not Done.";
            //                    this.lblStatus.BackColor = Color.Red;
            //                    this.btnWhiteBalancing.Enabled = true;
            //                    this.btnReset.Enabled = true;
            //                    this.whitebalancingStarted = false;
            //                    return;
            //                }
            //            }

            //            double RGDiff = rMax - gMax;
            //            double GBDiff = gMax - bMax;
            //            double BRDiff = bMax - rMax;

            //            currentWBData.ErrorLevel = (Math.Max(RGDiff, Math.Max(GBDiff, BRDiff)) / this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel) * 100;
            //            currentWBData.RedMax = rMax;
            //            currentWBData.GreenMax = gMax;
            //            currentWBData.BlueMax = bMax;

            //            HOperatorSet.CountSeconds(out endTime);
            //            currentWBData.TimeTaken = (endTime - startTime).D;
            //            wbIterationCompletedEvent.Set();

            //            UpdateControlUI();
            //            this.RefreshImageWindow(currentWBData.Image);
            //        }

            //        if ((i == Properties.Settings.Default.MaxIterationsInSettingAutomaticGain) &&
            //            (continueForRedChannel || continueForGreenChannel || continueForBlueChannel))
            //        {
            //            this.lblStatus.Text = "White Balancing Not Done Properly. Please reset and perform again.";
            //            this.lblStatus.BackColor = Color.Red;
            //            this.btnWhiteBalancing.Enabled = true;
            //            this.btnReset.Enabled = true;
            //            this.whitebalancingStarted = false;
            //            return;
            //        }
            //        else
            //        {
            //            string saveExposureCommand = Globals.e2vUC4CommandToSaveWhiteBalancingToUserBank1 + System.Environment.NewLine;
            //            retVal = Globals.ExecuteSerialCommand(
            //                (uint)CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
            //                saveExposureCommand,
            //                out buffer,
            //                Properties.Settings.Default.SerialCommunicationTimeout,
            //                10);

            //            string saveAllSettingsCommand = Globals.e2vUC4CommandToSaveALLSettingsToUserBank1 + System.Environment.NewLine;
            //            retVal &= Globals.ExecuteSerialCommand(
            //                (uint)CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
            //                saveAllSettingsCommand,
            //                out buffer,
            //                Properties.Settings.Default.SerialCommunicationTimeout,
            //                10);

            //            if (!retVal)
            //            {
            //                MessageBox.Show("Error occured while saving exposure values.",
            //                   "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //                this.lblStatus.Text = "White Balancing Not Done.";
            //                this.lblStatus.BackColor = Color.Red;
            //                this.btnWhiteBalancing.Enabled = true;
            //                this.btnReset.Enabled = true;
            //                this.whitebalancingStarted = false;
            //                return;
            //            }

            //            if (currentWBData.ErrorLevel <= 1.0)
            //            {
            //                this.lblStatus.Text = "Whitebalancing Done";
            //                this.lblStatus.BackColor = Color.LimeGreen;
            //            }
            //            else
            //            {
            //                this.lblStatus.Text = "Re-perform whitebalancing";
            //                this.lblStatus.BackColor = Color.Red;
            //            }
            //            this.btnWhiteBalancing.Enabled = true;
            //            this.btnReset.Enabled = true;
            //            this.whitebalancingStarted = false;
            //        }
            //    }
            //    else
            //    {
            //        this.lblStatus.Text = "White Balancing Not Done.";
            //        this.lblStatus.BackColor = Color.Red;
            //        string errorMessage = "Exception occurred during white balance step. ";
            //        errorMessage = errorMessage + " Error Message: Image is not a RGB Image";
            //        MessageBox.Show(errorMessage, "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //        this.btnWhiteBalancing.Enabled = true;
            //    }
            //}
            //catch (Exception ex)
            //{
            //    this.lblStatus.Text = "White Balancing Not Done.";
            //    this.lblStatus.BackColor = Color.Red;
            //    string errorMessage = "Exception occurred during white balance step. ";
            //    errorMessage = errorMessage + " Error Message: " + ex.Message;
            //    MessageBox.Show(errorMessage, "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //    this.btnWhiteBalancing.Enabled = true;
            //}

            #endregion

            #region Autowhite Balancing

            string buffer, command;
            bool retVal;
            command = Globals.e2vUC4CommandToPerformAutoWhiteBalancing + System.Environment.NewLine;

            retVal = Globals.ExecuteSerialCommand(
               (uint)CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
               command,
               out buffer,
               Properties.Settings.Default.SerialCommunicationTimeout,
               10);
            if (!retVal)
            {
                MessageBox.Show("Autowhite balancing failed, Please try again later!", "Camera Setup Utility", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            #endregion
        }

        private void UpdateControlUI()
        {
            if (this.InvokeRequired)
            {
                this.BeginInvoke(new Action(UpdateControlUI));
            }
            else
            {
                this.lblWBRefGrayLevel.Text = this.CameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel.ToString();
                this.lblWBRedMax.Text = currentWBData.RedMax.ToString();
                this.lblWBGreenMax.Text = currentWBData.GreenMax.ToString();
                this.lblWBBlueMax.Text = currentWBData.BlueMax.ToString();
                this.lblWBErrorLevel.Text = currentWBData.ErrorLevel.ToString("0.00");

                if (currentWBData.ErrorLevel > 1.0)
                {
                    this.lblWBErrorLevel.BackColor = Color.Red;
                    // COMMENTED because this message was overwriting the error status got after clicking "White Balance"
                    // e.g. if light intensity was not optimum and the function returned, this will over write that status 
                    // and just display "Re-perform whitebalancing"
                    //if (!this.whitebalancingStarted)
                    //{
                    //    this.lblWBStatus.Text = "Re-perform whitebalancing";
                    //    this.lblWBStatus.BackColor = Color.Red;
                    //}
                }
                else
                {
                    this.lblWBErrorLevel.BackColor = SystemColors.Control;
                }
            }
        }

        private int GetGainValueFromCamera(CameraChannels cameraChannels)
        {
            int currentGainValue = -1;
            string command = "";
            string buffer = "";
            bool retVal;
            switch (cameraChannels)
            {
                case CameraChannels.Red:
                    command = Globals.e2vUC4CommandToGetRedPlaneGain + System.Environment.NewLine;
                    break;
                case CameraChannels.Green:
                    command = Globals.e2vUC4CommandToGetGreenPlaneGain + System.Environment.NewLine;
                    break;
                case CameraChannels.Blue:
                    command = Globals.e2vUC4CommandToGetBluePlaneGain + System.Environment.NewLine;
                    break;
            }
            retVal = Globals.ExecuteSerialCommand(
                (uint)CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                command,
                out buffer,
                Properties.Settings.Default.SerialCommunicationTimeout,
                10);
            if (!retVal)
            {
                return -1;
            }

            string[] bufferArray = buffer.Split(new char[] { '>' }, StringSplitOptions.RemoveEmptyEntries);
            string bufferValue = Convert.ToString(bufferArray[0]);
            currentGainValue = Convert.ToInt32(bufferValue);

            return currentGainValue;
        }

        private bool WriteGainValueToCamera(CameraChannels cameraChannels, double gainValue)
        {
            bool retVal = false;
            string command = "";
            string buffer = "";
            switch (cameraChannels)
            {
                case CameraChannels.Red:
                    command = Globals.e2vUC4CommandToSetRedPlaneGain + gainValue.ToString() + System.Environment.NewLine;
                    break;
                case CameraChannels.Green:
                    command = Globals.e2vUC4CommandToSetGreenPlaneGain + gainValue.ToString() + System.Environment.NewLine;
                    break;
                case CameraChannels.Blue:
                    command = Globals.e2vUC4CommandToSetBluePlaneGain + gainValue.ToString() + System.Environment.NewLine;
                    break;
            }

            retVal = Globals.ExecuteSerialCommand(
                (uint)CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                command,
                out buffer,
                Properties.Settings.Default.SerialCommunicationTimeout,
                10);
            if (!retVal)
            {
                return retVal;
            }

            return retVal;
        }

        private void OnClickResetWhiteBalancing(object sender, EventArgs e)
        {
            this.btnReset.Enabled = false;
            this.lblStatus.Text = "Resetting...";
            this.lblStatus.BackColor = Color.Yellow;
            Application.DoEvents();
            string buffer;
            string command;
            string error;

            command = Globals.e2vUC4CommandToResetRedPlaneGain + System.Environment.NewLine;
            bool whiteBalancingReset = Globals.ExecuteSerialCommand(
                (uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                command, out buffer, Properties.Settings.Default.SerialCommunicationTimeout,
                10);

            command = Globals.e2vUC4CommandToResetBluePlaneGain + System.Environment.NewLine;
            whiteBalancingReset &= Globals.ExecuteSerialCommand(
                (uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                command, out buffer, Properties.Settings.Default.SerialCommunicationTimeout,
                10);

            command = Globals.e2vUC4CommandToResetGreenPlaneGain + System.Environment.NewLine;
            whiteBalancingReset &= Globals.ExecuteSerialCommand(
                (uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                command, out buffer, Properties.Settings.Default.SerialCommunicationTimeout,
                10);

            command = Globals.e2vUC4CommandToResetNIRPlaneGain + System.Environment.NewLine;
            whiteBalancingReset &= Globals.ExecuteSerialCommand(
                (uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                command, out buffer, Properties.Settings.Default.SerialCommunicationTimeout,
                10);
            if (whiteBalancingReset)
            {
                lblStatus.Text = "White balancing reset";
                lblStatus.BackColor = Color.Yellow;
            }
            else
            {
                lblStatus.Text = "White balancing not reset";
                lblStatus.BackColor = Color.Red;
            }
            this.btnReset.Enabled = true;
        }

        private void OnClickUpdateGainValue(object sender, EventArgs e)
        {
            Button b = sender as Button;
            bool retVal = false;
            string command = "";
            string buffer = "";
            switch (b.Tag.ToString().ToUpper())
            {
                case "RED":
                    command = Globals.e2vUC4CommandToSetRedPlaneGain + txtRedGainValue.Text.ToString() + System.Environment.NewLine;
                    break;
                case "GREEN":
                    command = Globals.e2vUC4CommandToSetRedPlaneGain + txtGreenGainValue.Text.ToString() + System.Environment.NewLine;
                    break;
                case "BLUE":
                    command = Globals.e2vUC4CommandToSetRedPlaneGain + txtBlueGainValue.Text.ToString() + System.Environment.NewLine;
                    break;
            }

            retVal = Globals.ExecuteSerialCommand(
               (uint)CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
               command,
               out buffer,
               Properties.Settings.Default.SerialCommunicationTimeout,
               10);
            if (!retVal)
            {
                MessageBox.Show("Updating gain value failed, Please check the gain value and try again!", "Camera Setup Utility", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void OnGainValueChanged(object sender, KeyPressEventArgs e)
        {
            if (!char.IsDigit(e.KeyChar) && e.KeyChar != '\b')
            {
                e.Handled = true;
                return;
            }
        }

        private void OnGainValueTextChanged(object sender, EventArgs e)
        {
            System.Windows.Forms.TextBox t = sender as System.Windows.Forms.TextBox;
            if (t.Text.Trim() != "")
            {
                int value = Convert.ToInt32(t.Text.Trim());
                if (value > 7999 || t.Text.Trim().Length > 4)
                {
                    t.Text = 7999.ToString();
                    return;
                }
            }
        }
    }
}
