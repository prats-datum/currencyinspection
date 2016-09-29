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

namespace CameraSetupTool.UserControls
{
    public partial class LightIntensityCheck : UserControl, iCameraSettingSteps
    {
        public LightIntensityCheck()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
            this.ImageToBeSaved = new HImage();
        }

        public HImage ImageToBeSaved { get; set; }

        LightStickAlignmentData currentLSAData;

        CameraAcquisition cameraAcquisition;

        int AcceptableRangeMin = 0;
        int AcceptableRangeMax = 0;
        int ReferenceGrayValue = 0;
        
        public CameraAcquisition CameraAcquisition 
        {
            get { return this.cameraAcquisition;}
            set 
            {
                this.cameraAcquisition = value;
                AcceptableRangeMin = this.cameraAcquisition.CurrentCameraProperties.MinimumGrayLevel;
                AcceptableRangeMax = this.cameraAcquisition.CurrentCameraProperties.MaximumGrayLevel;
                ReferenceGrayValue = this.cameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel;

                this.lblAcceptableRangeMin.Text = AcceptableRangeMin.ToString();
                this.lblAcceptableRangeMax.Text =AcceptableRangeMax.ToString();
                this.txtReferenceValue.Text = ReferenceGrayValue.ToString();
            }
        }

        public event Action<string> UpdateStepStatusMessage;
        public event RefreshImageWindowEventHandler RefreshImageWindow;

        public StepDescriptor GetStepDescriptor()
        {
            StepDescriptor desc = new StepDescriptor();
            desc.StepDescription = "Please insert the \"ISU Plain Calibration Document\" to verify light uniformity.";

            return desc;
        }

        public void ProcessStep(HImage imageGrabbed)
        {
            HTuple startTime = null;
            HTuple endTime = null;
            HOperatorSet.CountSeconds(out startTime);
            HOperatorSet.CountSeconds(out endTime);
            currentLSAData = new LightStickAlignmentData();
            HImage imageCropped = new HImage();
            try
            {
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

                int presentImageNoOfChannels = imageGrabbed.CountChannels();

                lock (this.ImageToBeSaved)
                {
                    this.ImageToBeSaved = imageGrabbed.CopyImage();
                }
                // Feed the image to the script
                imageGrabbed = imageGrabbed.CropDomain();
                currentLSAData.Image = imageGrabbed;

                if (imageChannels == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
                {
                    HImage ho_R;
                    HImage ho_G;
                    HImage ho_B;

                    ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);

                    HTuple RAOIGrayValues = Globals.GetGrayValuesOfLine(ho_R);
                    HTuple GAOIGrayValues = Globals.GetGrayValuesOfLine(ho_G);
                    HTuple BAOIGrayValues = Globals.GetGrayValuesOfLine(ho_B);
                    HTuple IRAOIGrayVals = Globals.GetGrayValuesOfLine(irImg);

                    currentLSAData.GrayValues.RPlaneVals = RAOIGrayValues.ToDArr();
                    currentLSAData.GrayValues.GPlaneVals = GAOIGrayValues.ToDArr();
                    currentLSAData.GrayValues.BPlaneVals = BAOIGrayValues.ToDArr();
                    currentLSAData.GrayValues.MPlaneVals = IRAOIGrayVals.ToDArr();

                    imageCropped = imageGrabbed.CropPart((this.CameraAcquisition.CurrentImageHeight / 2) - Properties.Settings.Default.LICROIRectangleHeight,
                        (this.CameraAcquisition.CurrentImageWidth / 2) - Properties.Settings.Default.LICROIRectangleWidth,
                        Properties.Settings.Default.LICROIRectangleWidth * 2,
                        (this.CameraAcquisition.CurrentImageHeight / 2));

                    ho_R = imageCropped.Decompose3(out ho_G, out ho_B);

                    RAOIGrayValues = Globals.GetGrayValuesOfLine(ho_R);

                    // Clipping the pixels at Left & Right of the line 
                    RAOIGrayValues = RAOIGrayValues.TupleSelectRange(
                       this.cameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtLeft,
                       (Properties.Settings.Default.LICROIRectangleWidth * 2) - this.cameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtRight);

                    // Update the labels showing the results of light uniformity check                
                    int RminGrayValue;
                    int RmaxGrayValue;

                    // Checking whether the gray values is within the defined range in RED plane
                    bool RPlaneOptimum = this.cameraAcquisition.IsLightIntensityLevelOptimum(RAOIGrayValues.ToDArr(), out RminGrayValue, out RmaxGrayValue);

                    currentLSAData.MinGrayValue = RminGrayValue;
                    currentLSAData.MaxGrayValue = RmaxGrayValue;
                    currentLSAData.Status = RPlaneOptimum;

                }
                else if (this.cameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
                {
                    HTuple AOIGrayValues = Globals.GetGrayValuesOfLine(imageGrabbed);
                    currentLSAData.GrayValues.MPlaneVals = AOIGrayValues.ToDArr();

                    // Clipping the pixels at Left & Right of the line 
                    AOIGrayValues = AOIGrayValues.TupleSelectRange(
                        this.cameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtLeft,
                        this.cameraAcquisition.CurrentImageWidth - this.cameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtRight);

                    // Update the labels showing the results of light uniformity check                
                    int minGrayValue;
                    int maxGrayValue;

                    // Checking whether the gray values is within the defined range in MONO plane
                    bool MonoPlaneOptimum = this.cameraAcquisition.IsLightIntensityLevelOptimum(AOIGrayValues.ToDArr(), out minGrayValue, out maxGrayValue);

                    currentLSAData.MinGrayValue = minGrayValue;
                    currentLSAData.MaxGrayValue = maxGrayValue;
                    currentLSAData.Status = MonoPlaneOptimum;
                }
                HOperatorSet.CountSeconds(out endTime);
                currentLSAData.TimeTaken = (endTime - startTime).D * 1000;

                this.BeginInvoke(new Action(UpdateStepUI));
            }
            catch (Exception ex)
            {
                string errorMessage = "Exception occurred during light intensity check. ";
                errorMessage = errorMessage + " Error Message: " + ex.Message;
                //MessageBox.Show(errorMessage, "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);

                this.BeginInvoke(new Action(UpdateStepUI));

                //lblStatus.Text = errorMessage;
                //lblStatus.BackColor = Color.Red;
            }
        }

        void UpdateStepUI()
        {
            HTuple startTimeDisplay = null;
            HTuple endTimeDisplay = null;
            HTuple endTimeLineProfile = null;
            HOperatorSet.CountSeconds(out startTimeDisplay);
            HOperatorSet.CountSeconds(out endTimeDisplay);
            HOperatorSet.CountSeconds(out endTimeLineProfile);
            string message;
            this.lblCurrentRangeMin.Text = currentLSAData.MinGrayValue.ToString();
            this.lblCurrentRangeMax.Text = currentLSAData.MaxGrayValue.ToString();
            if (currentLSAData.Status)
            {
                lblStatus.Text = "OK";
                lblStatus.BackColor = Color.LimeGreen;
            }
            else
            {
                lblStatus.Text = "NOT OK";
                lblStatus.BackColor = Color.Red;
            }
            if (Properties.Settings.Default.ShowTimeTakenInStatusLabel)
            {
                message = string.Format("Time taken for - processing: {0}ms  Displaying image : {1}ms  Updating line profile : {2}ms ",
                    currentLSAData.TimeTaken.ToString("02"), (endTimeDisplay - startTimeDisplay).D.ToString("02"),
                    (endTimeLineProfile - endTimeDisplay).D.ToString("02"));
                UpdateStepStatusMessage(message);
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
                redData = currentLSAData.GrayValues.RPlaneVals;
                greenData = currentLSAData.GrayValues.GPlaneVals;
                blueData = currentLSAData.GrayValues.BPlaneVals;
                data = currentLSAData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
                c.addSplineLayer(data, 0x000000);
            }
            else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
            {
                data = currentLSAData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(data);
            }
            else
            {
                redData = currentLSAData.GrayValues.RPlaneVals;
                greenData = currentLSAData.GrayValues.GPlaneVals;
                blueData = currentLSAData.GrayValues.BPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
            }

            double XAxisDataCount = this.cameraAcquisition.CurrentImageWidth;

            c.yAxis().setLinearScale(0, 255, 255);
            double majorTicks = Math.Round(XAxisDataCount / 8, 0);
            double minorTicks = Math.Round(XAxisDataCount);
            c.xAxis().setLinearScale(0, Math.Round(XAxisDataCount, 0), majorTicks);

            c.yAxis().addMark(AcceptableRangeMin, 0x82E0AE, AcceptableRangeMin.ToString()).setLineWidth(2);
            c.yAxis().addMark(AcceptableRangeMax, 0x82E0AE, AcceptableRangeMax.ToString()).setLineWidth(2);
            c.yAxis().addMark(ReferenceGrayValue, 0xA31F1F, ReferenceGrayValue.ToString()).setLineWidth(1);

            // Output the chart
            viewer.Chart = c;

            //include tool tip for the chart
            viewer.ImageMap = c.getHTMLImageMap("clickable", "",
                "title='Hour {xLabel}: Traffic {value} GBytes'");

            return viewer;
        }

        private void OnUpdateReferenceGrayValue(object sender, EventArgs e)
        {
            int prevRefGrayVal = this.cameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel;
            this.cameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel = Convert.ToInt32(this.txtReferenceValue.Text);
            int differenceInRefGrayVal = this.cameraAcquisition.CurrentCameraProperties.BrightRegionReferenceGrayLevel - prevRefGrayVal;
            this.cameraAcquisition.CurrentCameraProperties.MinimumGrayLevel += differenceInRefGrayVal;
            this.cameraAcquisition.CurrentCameraProperties.MaximumGrayLevel += differenceInRefGrayVal;

            if (this.cameraAcquisition.CurrentCameraProperties.MinimumGrayLevel < 0)
            {
                this.cameraAcquisition.CurrentCameraProperties.MinimumGrayLevel = 0;
            }
            if (this.cameraAcquisition.CurrentCameraProperties.MaximumGrayLevel > 255)
            {
                this.cameraAcquisition.CurrentCameraProperties.MaximumGrayLevel = 255;
            }

            this.lblAcceptableRangeMin.Text = this.cameraAcquisition.CurrentCameraProperties.MinimumGrayLevel.ToString();
            this.lblAcceptableRangeMax.Text = this.cameraAcquisition.CurrentCameraProperties.MaximumGrayLevel.ToString();
        }

        private void OnClickUpdateLightIntensity(object sender, EventArgs e)
        {
            if (!DIOManager.Current.IsInitialized)
            {
                if (!DIOManager.Current.Initialize())
                {
                    MessageBox.Show("Unable to Initialize DIO, Please check and try again", "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }
            }
            Button b = sender as Button;
            int value = 0;
            bool updatedLightIntensity = true;

            switch (b.Name)
            {
                case "btnUpdateWL1":
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(true);
                    value = (nsWhiteLight1.Value * 255) / 100;
                    updatedLightIntensity &= DIOManager.Current.WriteValueToLight(Lights.WhiteLight1, value);
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(false);
                    break;
                case "btnUpdateIRL1":
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(true);
                    value = nsIRLight1.Value * (255 / 100);
                    updatedLightIntensity &= DIOManager.Current.WriteValueToLight(Lights.IRLight1, value);
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(false);
                    break;
                case "btnUpdateWL2":
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(true);
                    value = nsWhiteLight2.Value * (255 / 100);
                    updatedLightIntensity &= DIOManager.Current.WriteValueToLight(Lights.WhiteLight2, value);
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(false);
                    break;
                case "btnUpdateIRL2":
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(true);
                    value = nsIRLight2.Value * (255 / 100);
                    updatedLightIntensity &= DIOManager.Current.WriteValueToLight(Lights.IRLight2, value);
                    updatedLightIntensity &= DIOManager.Current.WriteToDataWriteBit(false);
                    break;
            }

            if (!updatedLightIntensity)
            {
                MessageBox.Show("Unable to refresh light intensity, Please check and try again", "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }

        private void LightIntensityCheck_Resize(object sender, EventArgs e)
        {
            this.nsWhiteLight1.Dock = DockStyle.None;
            this.nsWhiteLight1.Dock = DockStyle.Fill;
            this.nsWhiteLight2.Dock = DockStyle.None;
            this.nsWhiteLight2.Dock = DockStyle.Fill;
            this.nsIRLight1.Dock = DockStyle.None;
            this.nsIRLight1.Dock = DockStyle.Fill;
            this.nsIRLight2.Dock = DockStyle.None;
            this.nsIRLight2.Dock = DockStyle.Fill;
        }
    }
}
