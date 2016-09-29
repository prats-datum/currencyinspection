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
    public partial class FocusSetting : UserControl, iCameraSettingSteps
    {
        public FocusSetting()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
            focusLearningStarted = false;

            ImageToBeSaved = new HImage();
        }

        bool focusLearningStarted;
        bool focusLearningOver;

        FocusMagnificationCheckData currentFMCData;

        public HImage ImageToBeSaved { get; set; }


        /// <summary>
        /// Tuple that holds the auto-correlation value of each image processed during 
        /// Focus Learning
        /// </summary>
        private HTuple hv_AutoCorrelationTuple;

        /// <summary>
        /// Maximum Auto-Correlation value. This is the reference value against which
        /// the sharpness of image is compared during Focus Checking.
        /// </summary>
        private HTuple hv_MaxAutoCorrelation;

        /// <summary>
        /// Focus Percentage
        /// </summary>
        private HTuple hv_focus;

        public CameraAcquisition CameraAcquisition { get; set; }

        public event Action<string> UpdateStepStatusMessage;
        public event RefreshImageWindowEventHandler RefreshImageWindow;

        public StepDescriptor GetStepDescriptor()
        {
            StepDescriptor desc = new StepDescriptor();
            desc.StepDescription = "Please insert the \"ISU Calibration Document\" with stripes to check the focus";

            return desc;
        }

        public WinChartViewer UpdateChartUI(WinChartViewer viewer)
        {
            double[] data = {};
            double[] redData;
            double[] greenData;
            double[] blueData;

            // Create a XYChart object of size 250 x 250 pixels
            XYChart c = new XYChart(viewer.Width - 10, viewer.Height - 10, 0xffdddd, 0x000000, 1);

            // Set the plotarea at (30, 20) and of size 200 x 200 pixels
            c.setPlotArea(50, 10, viewer.Width - 100, viewer.Height - 60, 0xffffff, -1, -1);

            if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
            {
                redData = currentFMCData.GrayValues.RPlaneVals;
                greenData = currentFMCData.GrayValues.GPlaneVals;
                blueData = currentFMCData.GrayValues.BPlaneVals;
                data = currentFMCData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
                c.addSplineLayer(data, 0x000000);
            }
            else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
            {
                data = currentFMCData.GrayValues.MPlaneVals;
                
                // Add a line chart layer using the given data
                c.addSplineLayer(data);
            }
            else
            {
                redData = currentFMCData.GrayValues.RPlaneVals;
                greenData = currentFMCData.GrayValues.GPlaneVals;
                blueData = currentFMCData.GrayValues.BPlaneVals;

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

        public void ProcessStep(HImage imageGrabbed)
        {
            currentFMCData = new FocusMagnificationCheckData();
            lock (this.ImageToBeSaved)
            {
                this.ImageToBeSaved = imageGrabbed.CopyImage();
            }

            bool calibrationTargetContrastOK = true;

            // Feed the image to the script
            imageGrabbed = imageGrabbed.CropDomain();
            currentFMCData.Image = imageGrabbed;

            int imageChannels = imageGrabbed.CountChannels();

            HImage rImg = null, gImg = null, bImg = null, rgbImg = null, irImg = null;

            if(imageChannels == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
            {
                rImg = imageGrabbed.Decompose4(out gImg, out bImg, out irImg);
                rgbImg = rImg.Compose3(gImg, bImg);
            }

            HImage grayImage = new HImage();
            if (rgbImg == null) return;

            imageGrabbed = rgbImg.CopyImage();

            #region IntensityCheckForCheckingCalibrationTarget
            // Check the minimum and maximum light intensity to determine whether correct calibration target 
            // has been placed
            grayImage = imageGrabbed.Rgb1ToGray();

            HImage ho_R;
            HImage ho_G;
            HImage ho_B;

            ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);

            HTuple RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
            HTuple GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
            HTuple BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);
            HTuple IRAOIGrayVals = Globals.GetGrayValuesOfLine(irImg);

            currentFMCData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
            currentFMCData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
            currentFMCData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();
            currentFMCData.GrayValues.MPlaneVals = IRAOIGrayVals.ToDArr();

            int RPlaneMinValue;
            int RPlaneMaxValue;

            RAOIGrayVals = RAOIGrayVals.TupleSelectRange(this.CameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtLeft,
                this.CameraAcquisition.CurrentImageWidth - this.CameraAcquisition.CurrentCameraProperties.NumberOfPixelsToBeClippedAtRight);

            calibrationTargetContrastOK = this.CameraAcquisition.IsLightIntensityLevelOptimum(GAOIGrayVals.ToDArr(), out RPlaneMinValue, out RPlaneMaxValue);
            calibrationTargetContrastOK = (RPlaneMaxValue - RPlaneMinValue) > Properties.Settings.Default.FocusPatternCheckReferenceGrayValue;

            #endregion

            #region FindPatternArea
            //Finds the pattern area
            HImage reducedImage = Globals.FindPatternArea(grayImage);
            if (reducedImage == null)
            {
                SetFocusStatusMessage("Image is too dark or Incorrect Pattern", Color.Red);
                currentFMCData.FocusPercentage = "";
                currentFMCData.MagnificationPercentage = "";
                currentFMCData.PixelResolution = "";
                //this.BeginInvoke(new Action<FocusMagnificationCheckData>(UpdateFocusMagnificationStepUI), currentFMCData);
                return;
            }
            #endregion

            #region Focus Learning

            hv_focus = new HTuple();
            HTuple hv_currentSharpness = new HTuple();
            HImage imageCropped = new HImage();

            //Indicates that execution has entered the focus learning stage 
            //(For both successful and failed learning)       
            bool focusLearningDone = false;

            if (this.focusLearningStarted)
            {
                #region FocusLearningStage
                focusLearningDone = true;
                if (!this.focusLearningOver)
                {
                    HTuple hv_Scale;
                    HTuple hv_Subsampling = 1;
                    hv_Scale = 1.0 / hv_Subsampling;

                    int grabbedImageWidth, grabbedImageHeight;

                    imageGrabbed.GetImageSize(out grabbedImageWidth, out grabbedImageHeight);

                    // Crop the image before learning 
                    imageCropped = imageGrabbed.CropPart((this.CameraAcquisition.CurrentImageHeight / 2) - Properties.Settings.Default.FocusROIRectangleHeight,
                        (this.CameraAcquisition.CurrentImageWidth / 2) - Properties.Settings.Default.FocusROIRectangleWidth,
                        Properties.Settings.Default.FocusROIRectangleWidth * 2,
                        (this.CameraAcquisition.CurrentImageHeight / 2));

                    int croppedImageWidth, croppedImageHeight;

                    imageCropped.GetImageSize(out croppedImageWidth, out croppedImageHeight);

                    int noOfSamples = croppedImageHeight / Properties.Settings.Default.NoOfSamplesUsedInFocusStep;

                    for (int i = 0; i < Properties.Settings.Default.NoOfSamplesUsedInFocusStep; i++)
                    {
                        try
                        {
                            int row = i * noOfSamples;
                            HImage newCroppedImage = imageCropped.CopyImage().CropPart(row, 0, croppedImageWidth, noOfSamples);
                        //newCroppedImage.WriteImage("bmp", 0, "D:\\imageCropped" + i.ToString());

                        // Function Call for sharpness Measurement
                        hv_currentSharpness = MeasureSharpness(newCroppedImage, hv_Scale);
                        hv_AutoCorrelationTuple = hv_AutoCorrelationTuple.TupleConcat(hv_currentSharpness);
                        }
                        catch (Exception ex)
                        {

                        }
                    }

                    currentFMCData.FocusPercentage = "";
                    SetFocusStatusMessage("Learning...", Color.Yellow);
                    UpdateLabelMessage(currentFMCData.FocusPercentage);
                }
                else
                {
                    hv_MaxAutoCorrelation = new HTuple();
                    HTuple hv_Change = new HTuple();
                    if (hv_AutoCorrelationTuple.TupleLength() > 0)
                    {
                        hv_MaxAutoCorrelation = hv_AutoCorrelationTuple.TupleMax();
                        hv_Change = ((hv_AutoCorrelationTuple.TupleMax() - hv_AutoCorrelationTuple.TupleMin()) / hv_AutoCorrelationTuple.TupleMax()) * 100;

                        if (hv_MaxAutoCorrelation.D <= 0.0 || hv_Change.D < Properties.Settings.Default.MinimumFocusLearningRangeRequired)
                        {
                            currentFMCData.FocusPercentage = "";
                            SetFocusStatusMessage("Focus Learning not done properly. Range of focus learning is not enough.", Color.Orange);
                            this.focusLearningOver = false;
                            UpdateLabelMessage(currentFMCData.FocusPercentage);
                        }
                        else
                        {
                            this.CameraAcquisition.CurrentCameraSetupProperties.FocusMaxAutoCorrelationValue = hv_MaxAutoCorrelation.D;
                        }
                    }
                    else
                    {
                        currentFMCData.FocusPercentage = "";
                        SetFocusStatusMessage("Focus Learning not done properly. Sharpness measurement failed", Color.Orange);
                        this.focusLearningOver = false;
                        UpdateLabelMessage(currentFMCData.FocusPercentage);
                    }
                    this.focusLearningStarted = false;
                }
                #endregion
            }
            else if (this.focusLearningOver)
            {
                #region FocusTestingPhase
                if (!calibrationTargetContrastOK)
                {
                    currentFMCData.FocusPercentage = "";
                    currentFMCData.MagnificationPercentage = "";
                    currentFMCData.PixelResolution = "";
                    SetFocusStatusMessage("Incorrect Pattern. Not enough contrast", Color.Red);
                    UpdateLabelMessage(currentFMCData.FocusPercentage);
                    return;
                }

                HTuple hv_Scale;
                HTuple hv_Subsampling = 1;

                hv_Scale = 1.0 / hv_Subsampling;
                // Crop the image before learning 
                imageCropped = imageGrabbed.CropPart((this.CameraAcquisition.CurrentImageHeight / 2) - Properties.Settings.Default.FocusROIRectangleHeight,
                    (this.CameraAcquisition.CurrentImageWidth / 2) - Properties.Settings.Default.FocusROIRectangleWidth,
                    Properties.Settings.Default.FocusROIRectangleWidth * 2,
                    (this.CameraAcquisition.CurrentImageHeight / 2));

                // Function Call for sharpness Measurement
                hv_currentSharpness = MeasureSharpness(imageCropped, hv_Scale);
                if (hv_currentSharpness > hv_MaxAutoCorrelation + 2)
                {
                    SetFocusStatusMessage("Current sharpness is more than learnt sharpness. Insert valid calibration doc or Re-do focus learning !!", Color.Orange);
                    currentFMCData.PixelResolution = "";
                    currentFMCData.MagnificationPercentage = "";
                    currentFMCData.FocusPercentage = "";
                    UpdateLabelMessage(currentFMCData.FocusPercentage);
                    return;


                }
                else if (hv_currentSharpness > hv_MaxAutoCorrelation)
                {
                    hv_MaxAutoCorrelation = hv_currentSharpness;
                    hv_AutoCorrelationTuple = hv_AutoCorrelationTuple.TupleConcat(hv_currentSharpness);
                }
                hv_focus = 100 - (((hv_MaxAutoCorrelation - hv_currentSharpness) / hv_MaxAutoCorrelation) * 100);
                hv_focus = hv_focus.TupleRound();
                currentFMCData.FocusPercentage = hv_focus.ToString();
                if (hv_focus > 100)
                {
                    // Not Focused
                    currentFMCData.FocusPercentage = "";
                    SetFocusStatusMessage("Focus learning not done properly", Color.Red);
                    UpdateLabelMessage(currentFMCData.FocusPercentage);

                }
                if (hv_focus >= 95 && hv_focus <= 100)
                {
                    // Focused
                    SetFocusStatusMessage("Focused", Color.LimeGreen);
                }
                else if (hv_focus > 70 && hv_focus < 95)
                {
                    //// Fine Tuning is required
                    SetFocusStatusMessage("Fine Tuning is required", Color.Yellow);
                }
                else
                {
                    // Not Focused
                    SetFocusStatusMessage("Not focused", Color.Red);
                }
                #endregion

            }
            else if (!focusLearningOver && !focusLearningDone)
            {
                if (hv_MaxAutoCorrelation == null)
                {
                    SetFocusStatusMessage("Focus learning not done", Color.Yellow);
                }
            }

            UpdateLabelMessage(currentFMCData.FocusPercentage);
            #endregion

        }

        void UpdateLabelMessage(string msg)
        {
            if (this.currentFMCData.Image == null) return;
            if (this.InvokeRequired)
            {
                Action<string> a = new Action<string>(UpdateLabelMessage);
                this.BeginInvoke(a, msg);
            }
            else
            {
                lblCurrentFocusPercentage.Text = msg;
            }

        }

        /// <summary>
        /// Measures the sharpness.
        /// </summary>
        /// <param name="currentImage">The current image.</param>
        /// <param name="ScaleVal">The scale val.</param>
        /// <returns></returns>
        public HTuple MeasureSharpness(HImage currentImage, HTuple ScaleVal)
        {
            HTuple hv_Sharpness = new HTuple();
            try
            {
                if (currentImage.CountChannels() == 3)
                {
                    currentImage = currentImage.Rgb1ToGray();
                }
                string hv_Type = null;
                int hv_Width = 0;
                int hv_Height = 0;

                IntPtr imagePtr = currentImage.GetImagePointer1(out hv_Type, out hv_Width, out hv_Height);

                HImage ho_ImageZoomed = new HImage();
                HImage ho_ImageFFT = new HImage();
                HImage ho_ImageCorrelation = new HImage();
                HImage ho_ImageFFTInv = new HImage();


                HTuple hv_ZoomedWidth;
                HTuple hv_ZoomedHeight;

                HTuple IRow = new HTuple(4);

                HTuple ICol = new HTuple(4);
                HTuple hv_SumCorrelation;

                ho_ImageZoomed = currentImage.ZoomImageFactor(ScaleVal, ScaleVal, "constant");
                ho_ImageZoomed.GetImageSize(out hv_ZoomedWidth, out hv_ZoomedHeight);
                ho_ImageFFT = ho_ImageZoomed.RftGeneric("to_freq", "none", "complex", hv_ZoomedWidth);
                ho_ImageCorrelation = ho_ImageFFT.CorrelationFft(ho_ImageFFT);
                ho_ImageFFTInv = ho_ImageCorrelation.RftGeneric("from_freq", "n", "real", hv_ZoomedWidth);

                IRow[0] = 0;
                IRow[1] = 1;
                IRow[2] = hv_ZoomedHeight - 1;
                IRow[3] = hv_ZoomedHeight - 2;


                ICol[0] = 1;
                ICol[1] = 0;
                ICol[2] = hv_ZoomedWidth - 2;
                ICol[3] = hv_ZoomedWidth - 1;

                hv_SumCorrelation = ho_ImageFFTInv.GetGrayval(IRow, ICol);

                HTuple hv_Mean;
                HTuple hv_Deviation;

                hv_Mean = ho_ImageZoomed.Intensity(ho_ImageZoomed, out hv_Deviation);

                HTuple hv_Blurness;

                hv_Blurness = ((hv_SumCorrelation / (hv_ZoomedWidth * hv_ZoomedHeight)) - (hv_Mean * hv_Mean)) / (hv_Deviation * hv_Deviation);

                hv_Sharpness = 1000.0 - ((hv_Blurness.TupleMin()) * 1000.0);

                hv_Sharpness = hv_Sharpness * 100;
                hv_Sharpness = hv_Sharpness.TupleRound();
                hv_Sharpness = hv_Sharpness.TupleReal();
                hv_Sharpness = hv_Sharpness / 100;

            }
            catch (Exception ex)
            {
                SetFocusStatusMessage(ex.Message, Color.Pink);
                //this.lblFocusStatus.Text = ex.Message;
                //this.lblFocusStatus.BackColor = Color.Pink;
            }

            return hv_Sharpness;
        }

        /// <summary>
        /// Sets the focus checking status message.
        /// </summary>
        /// <param name="statusMsg">The status MSG.</param>
        /// <param name="statusColor">Color of the status.</param>
        private void SetFocusStatusMessage(string statusMsg, Color statusColor)
        {
            if (this.InvokeRequired)
            {
                Action<string, Color> setFocusStatusHandler = new Action<string, Color>(SetFocusStatusMessage);
                this.BeginInvoke(setFocusStatusHandler, statusMsg, statusColor);
            }
            else
            {
                this.lblFocusStatus.Text = statusMsg;
                this.lblFocusStatus.BackColor = statusColor;
            }
        }

        private void OnClickLearnFocus(object sender, EventArgs e)
        {
            this.focusLearningStarted = true;
            this.focusLearningOver = false;
            hv_AutoCorrelationTuple = new HTuple();
            string instruction = string.Format("Place the calibration target.\n\nLearn Image Sharpness / Focus - Turn the focus ring from one end to the other end.\n\nPress \"OK\" once learning is complete.");
            frmInstruction frm = new frmInstruction(instruction);
            frm.StartPosition = FormStartPosition.CenterScreen;
            if (frm.ShowDialog(this) == DialogResult.OK)
            {
                this.focusLearningOver = true;
            }
        }
    }
}
