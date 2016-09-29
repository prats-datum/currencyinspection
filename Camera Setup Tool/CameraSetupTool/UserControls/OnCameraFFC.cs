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
    public partial class OnCameraFFC : UserControl, iCameraSettingSteps
    {
        public OnCameraFFC()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
            ImageToBeSaved = new HImage();
        }

        OnCameraFFCData currentOnCameraFFCData;

        public HImage ImageToBeSaved { get; set; }

        /// <summary>
        /// Indicates whether On Camera FPN has been done
        /// </summary>
        private bool fpnDone;
        /// <summary>
        /// Indicates whether On Camera PRNU has been done
        /// </summary>
        private bool prnuDone;

        public CameraAcquisition CameraAcquisition { get; set; }

        public event Action<string> UpdateStepStatusMessage;
        public event RefreshImageWindowEventHandler RefreshImageWindow;

        public StepDescriptor GetStepDescriptor()
        {
            StepDescriptor desc = new StepDescriptor();
            desc.StepDescription = "Please insert the \"ISU Plain Calibration Document\" to perform FFC";

            return desc;
        }

        public void ProcessStep(HImage imageGrabbed)
        {
            HTuple startTime = null;
            HTuple endTime = null;
            HOperatorSet.CountSeconds(out startTime);
            HOperatorSet.CountSeconds(out endTime);
            currentOnCameraFFCData = new OnCameraFFCData();
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

                lock (this.ImageToBeSaved)
                {
                    this.ImageToBeSaved = imageGrabbed.CopyImage();
                }
                // Feed the image to the script
                imageGrabbed = imageGrabbed.CropDomain();
                currentOnCameraFFCData.Image = imageGrabbed;

                if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
                {
                    HImage ho_R;
                    HImage ho_G;
                    HImage ho_B;

                    ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);

                    HTuple RAOIGrayValues = Globals.GetGrayValuesOfLine(ho_R);
                    HTuple GAOIGrayValues = Globals.GetGrayValuesOfLine(ho_G);
                    HTuple BAOIGrayValues = Globals.GetGrayValuesOfLine(ho_B);
                    HTuple IRAOIGrayValues = Globals.GetGrayValuesOfLine(irImg);

                    currentOnCameraFFCData.GrayValues.RPlaneVals = RAOIGrayValues.ToDArr();
                    currentOnCameraFFCData.GrayValues.GPlaneVals = GAOIGrayValues.ToDArr();
                    currentOnCameraFFCData.GrayValues.BPlaneVals = BAOIGrayValues.ToDArr();
                    currentOnCameraFFCData.GrayValues.MPlaneVals = IRAOIGrayValues.ToDArr();

                }
                else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
                {
                    HTuple AOIGrayValues = Globals.GetGrayValuesOfLine(imageGrabbed);
                    currentOnCameraFFCData.GrayValues.MPlaneVals = AOIGrayValues.ToDArr();

                }
                HOperatorSet.CountSeconds(out endTime);
                currentOnCameraFFCData.TimeTaken = (endTime - startTime).D * 1000;

            }
            catch (Exception ex)
            {
                string errorMessage = "Exception occurred during On-Camera FFC step. ";
                errorMessage = errorMessage + " Error Message: " + ex.Message;
                MessageBox.Show(errorMessage, "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Performs the FPN.
        /// </summary>
        /// <remarks></remarks>
        private void PerformFPN()
        {
            this.btnFFC_FPN.Enabled = false;
            this.btnFFC_PRNU.Enabled = false;
            this.lblStatus.Text = "Performing FPN...";
            this.lblStatus.BackColor = Color.Yellow;
            this.fpnDone = false;
            Application.DoEvents();
            string buffer;
            string command;
            bool dfcStatus = true;
            currentOnCameraFFCData = new OnCameraFFCData();

            HImage imageGrabbed = new HImage();
            HImage ho_RGB = new HImage();
            HImage ho_R = new HImage();
            HImage ho_G = new HImage();
            HImage ho_B = new HImage();
            HImage ho_M = new HImage();

            try
            {
                lock (this.ImageToBeSaved)
                {
                    imageGrabbed = this.ImageToBeSaved.CopyImage();
                }

                ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);
                ho_RGB = ho_R.Compose3(ho_G, ho_B);

                int presentChannel = ho_RGB.CountChannels();

                if (presentChannel == Properties.Settings.Default.NumberOfChannelsInColorImage)
                {
                    //ho_R = ho_RGB.Decompose3(out ho_G, out ho_B);

                    HTuple RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
                    HTuple GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
                    HTuple BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);


                    currentOnCameraFFCData.Image = ho_RGB;
                    currentOnCameraFFCData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
                    currentOnCameraFFCData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
                    currentOnCameraFFCData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();

                    HTuple maxGrayValueInCenterLineR = RAOIGrayVals.TupleMax();
                    HTuple maxGrayValueInCenterLineG = GAOIGrayVals.TupleMax();
                    HTuple maxGrayValueInCenterLineB = BAOIGrayVals.TupleMax();
                    if ((maxGrayValueInCenterLineR.I > Properties.Settings.Default.DarkFieldCorrectionMaximumGrayLevel) ||
                        (maxGrayValueInCenterLineG.I > Properties.Settings.Default.DarkFieldCorrectionMaximumGrayLevel) ||
                        (maxGrayValueInCenterLineB.I > Properties.Settings.Default.DarkFieldCorrectionMaximumGrayLevel))
                    {
                        this.RefreshImageWindow(ho_RGB);

                        this.lblStatus.Text = Properties.Settings.Default.FPNLightIntensityNotOptimumMessage;
                        this.lblStatus.BackColor = Color.Red;
                        this.btnFFC_FPN.Enabled = true;
                        this.btnFFC_PRNU.Enabled = true;
                        //Application.DoEvents();
                        return;
                    }
                }
                else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
                {
                    lock (this.ImageToBeSaved)
                    {
                        ho_M = this.ImageToBeSaved.CopyImage();
                    }

                    HTuple MAOIGrayVals = Globals.GetGrayValuesOfLine(ho_M);

                    currentOnCameraFFCData.Image = ho_M;
                    currentOnCameraFFCData.GrayValues.MPlaneVals = MAOIGrayVals.ToDArr();

                    HTuple maxGrayValueInCenterLineM = MAOIGrayVals.TupleMax();
                    if (maxGrayValueInCenterLineM.I > Properties.Settings.Default.DarkFieldCorrectionMaximumGrayLevel)
                    {
                        this.RefreshImageWindow(ho_M);
                        this.lblStatus.Text = Properties.Settings.Default.FPNLightIntensityNotOptimumMessage;
                        this.lblStatus.BackColor = Color.Red;
                        this.btnFFC_FPN.Enabled = true;
                        this.btnFFC_PRNU.Enabled = true;
                        //Application.DoEvents();
                        return;
                    }
                }
                
                command = Globals.e2vUC4CommandToDoOnCameraDFC + System.Environment.NewLine;
                dfcStatus = Globals.ExecuteSerialCommand((uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                    command,
                    out buffer,
                    2000,
                    1000);

                command = Globals.e2vUC4CommandToSaveFFCToUserBank1 + System.Environment.NewLine;
                dfcStatus &= Globals.ExecuteSerialCommand((uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                    command,
                    out buffer,
                    1000,
                    2000);

                command = Globals.e2vUC4CommandToSaveALLSettingsToUserBank1 + System.Environment.NewLine;
                dfcStatus &= Globals.ExecuteSerialCommand((uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                    command,
                    out buffer,
                    1000,
                    2000);

                if (dfcStatus)
                {
                    lblStatus.Text = "On Camera Dark Field Correction Done";
                    lblStatus.BackColor = Color.LimeGreen;
                }
                else
                {
                    lblStatus.Text = "On Camera Dark Field Correction not done properly";
                    lblStatus.BackColor = Color.Red;
                }
                this.fpnDone = dfcStatus;
                this.btnFFC_FPN.Enabled = true;
                this.btnFFC_PRNU.Enabled = true;
            }
            catch (System.Exception ex)
            {
                lblStatus.Text = "On Camera Dark Field Correction not done properly";
                lblStatus.BackColor = Color.Red;
                this.btnFFC_FPN.Enabled = true;
                this.btnFFC_PRNU.Enabled = true;
                this.fpnDone = false;
                MessageBox.Show("Exception occurred while performing FPN.\r\n Error: " + ex.Message,
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Performs the PRNU.
        /// </summary>
        /// <remarks></remarks>
        private void PerformPRNU()
        {
            try
            {
                this.btnFFC_FPN.Enabled = false;
                this.btnFFC_PRNU.Enabled = false;
                this.lblStatus.Text = "Performing PRNU...";
                this.lblStatus.BackColor = Color.Yellow;
                this.prnuDone = false;
                Application.DoEvents();
                string buffer;
                string command;
                bool bfcStatus = true;

                HImage imageCropped;

                currentOnCameraFFCData = new OnCameraFFCData();

                HImage imageGrabbed = new HImage();
                HImage ho_RGB = new HImage();
                HImage ho_R = new HImage();
                HImage ho_G = new HImage();
                HImage ho_B = new HImage();
                HImage ho_M = new HImage();

                lock (this.ImageToBeSaved)
                {
                    imageGrabbed = this.ImageToBeSaved.CopyImage();
                }

                ho_R = imageGrabbed.Decompose3(out ho_G, out ho_B);
                ho_RGB = ho_R.Compose3(ho_G, ho_B);

                int presentChannel = ho_RGB.CountChannels();


                if (presentChannel == Properties.Settings.Default.NumberOfChannelsInColorImage)
                {
                    lock (this.ImageToBeSaved)
                    {
                        ho_RGB = this.ImageToBeSaved.CopyImage();
                    }

                    ho_R = ho_RGB.Decompose3(out ho_G, out ho_B);

                    HTuple RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
                    HTuple GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
                    HTuple BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);


                    currentOnCameraFFCData.Image = ho_RGB;
                    currentOnCameraFFCData.GrayValues.RPlaneVals = RAOIGrayVals.ToDArr();
                    currentOnCameraFFCData.GrayValues.GPlaneVals = GAOIGrayVals.ToDArr();
                    currentOnCameraFFCData.GrayValues.BPlaneVals = BAOIGrayVals.ToDArr();

                    bool lightIntensityOptimum = true;

                    imageCropped = ho_RGB.CropPart((this.CameraAcquisition.CurrentImageHeight / 2) - Properties.Settings.Default.FFCROIRectangleHeight,
                        (this.CameraAcquisition.CurrentImageWidth / 2) - Properties.Settings.Default.FFCROIRectangleWidth,
                        Properties.Settings.Default.FFCROIRectangleWidth * 2,
                        (this.CameraAcquisition.CurrentImageHeight / 2));

                    ho_R = imageCropped.Decompose3(out ho_G, out ho_B);

                    RAOIGrayVals = Globals.GetGrayValuesOfLine(ho_R);
                    GAOIGrayVals = Globals.GetGrayValuesOfLine(ho_G);
                    BAOIGrayVals = Globals.GetGrayValuesOfLine(ho_B);

                    if (Properties.Settings.Default.CheckForImproperCalibrationTarget)
                    {
                        int minGrayValue;
                        int maxGrayValue;
                        double[] tempLineProfileR = RAOIGrayVals.ToDArr();

                        double[] tempLineProfileG = GAOIGrayVals.ToDArr();

                        double[] tempLineProfileB = BAOIGrayVals.ToDArr();

                        lightIntensityOptimum &=
                            this.CameraAcquisition.IsLightIntensityLevelOptimum(tempLineProfileR, out minGrayValue, out maxGrayValue, Properties.Settings.Default.PRNUMinimumGrayLevelOffset) &&
                            this.CameraAcquisition.IsLightIntensityLevelOptimum(tempLineProfileG, out minGrayValue, out maxGrayValue, Properties.Settings.Default.PRNUMinimumGrayLevelOffset) &&
                            this.CameraAcquisition.IsLightIntensityLevelOptimum(tempLineProfileB, out minGrayValue, out maxGrayValue, Properties.Settings.Default.PRNUMinimumGrayLevelOffset);
                    }

                    if (!lightIntensityOptimum)
                    {
                        this.RefreshImageWindow(ho_RGB);

                        this.lblStatus.Text = Properties.Settings.Default.PRNULightIntensityNotOptimumMessage;
                        this.lblStatus.BackColor = Color.Red;
                        this.btnFFC_FPN.Enabled = true;
                        this.btnFFC_PRNU.Enabled = true;
                        Application.DoEvents();
                        return;
                    }
                }
                else if (presentChannel == Properties.Settings.Default.NumberOfChannelsInMonoImage)
                {
                    lock (this.ImageToBeSaved)
                    {
                        ho_M = this.ImageToBeSaved.CopyImage();
                    }

                    HTuple MAOIGrayVals = Globals.GetGrayValuesOfLine(ho_M);


                    currentOnCameraFFCData.Image = ho_M;
                    currentOnCameraFFCData.GrayValues.MPlaneVals = MAOIGrayVals.ToDArr();

                    bool lightIntensityOptimum = true;

                    if (Properties.Settings.Default.CheckForImproperCalibrationTarget)
                    {
                        int minGrayValue;
                        int maxGrayValue;
                        double[] tempLineProfileM = MAOIGrayVals.ToDArr();

                        lightIntensityOptimum &=
                            this.CameraAcquisition.IsLightIntensityLevelOptimum(tempLineProfileM, out minGrayValue, out maxGrayValue, Properties.Settings.Default.PRNUMinimumGrayLevelOffset);
                    }

                    if (!lightIntensityOptimum)
                    {
                        this.RefreshImageWindow(ho_M);

                        this.lblStatus.Text = Properties.Settings.Default.PRNULightIntensityNotOptimumMessage;
                        this.lblStatus.BackColor = Color.Red;
                        this.btnFFC_FPN.Enabled = true;
                        this.btnFFC_PRNU.Enabled = true;
                        Application.DoEvents();
                        return;
                    }
                }

                command = Globals.e2vUC4CommandToDoOnCameraBFC + System.Environment.NewLine;
                bfcStatus = Globals.ExecuteSerialCommand(
                    (uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                    command,
                    out buffer,
                    5000,
                    1000);

                command = Globals.e2vUC4CommandToSaveFFCToUserBank1 + System.Environment.NewLine;
                bfcStatus &= Globals.ExecuteSerialCommand(
                    (uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                    command,
                    out buffer,
                    1000,
                    2000);

                command = Globals.e2vUC4CommandToSaveALLSettingsToUserBank1 + System.Environment.NewLine;
                bfcStatus &= Globals.ExecuteSerialCommand((uint)this.CameraAcquisition.CurrentCameraProperties.SerialPortIndex,
                    command,
                    out buffer,
                    1000,
                    2000);

                if (bfcStatus)
                {
                    lblStatus.Text = "On Camera Bright Field Correction Done";
                    lblStatus.BackColor = Color.LimeGreen;
                }
                else
                {
                    lblStatus.Text = "On Camera Bright Field Correction not done properly";
                    lblStatus.BackColor = Color.Red;
                }
                this.prnuDone = bfcStatus;
                this.btnFFC_FPN.Enabled = true;
                this.btnFFC_PRNU.Enabled = true;

                if (this.fpnDone && this.prnuDone)
                {
                    this.CameraAcquisition.CurrentCameraSetupProperties.LastOnCameraFFCSavingDate = "";
                    this.CameraAcquisition.CurrentCameraSetupProperties.LastOnCameraFFCSavingDate = DateTime.Now.Day.ToString() + "-" +
                            DateTime.Now.Month.ToString() + "-" + DateTime.Now.Year.ToString() + " " +
                            DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + ":" +
                            DateTime.Now.Second.ToString();
                }
            }
            catch (System.Exception ex)
            {
                lblStatus.Text = "On Camera Bright Field Correction not done properly";
                lblStatus.BackColor = Color.Red;
                this.btnFFC_FPN.Enabled = true;
                this.btnFFC_PRNU.Enabled = true;
                this.prnuDone = false;
                MessageBox.Show("Exception occurred while performing PRNU.\r\n Error: " + ex.Message,
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
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
                redData = currentOnCameraFFCData.GrayValues.RPlaneVals;
                greenData = currentOnCameraFFCData.GrayValues.GPlaneVals;
                blueData = currentOnCameraFFCData.GrayValues.BPlaneVals;
                data = currentOnCameraFFCData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(redData, 0xFF0000);
                c.addSplineLayer(greenData, 0x00FF00);
                c.addSplineLayer(blueData, 0x0000FF);
                c.addSplineLayer(data, 0x000000);
            }
            else if (this.CameraAcquisition.CurrentNumberOfChannels == Properties.Settings.Default.NumberOfChannelsInMonoImage)
            {
                data = currentOnCameraFFCData.GrayValues.MPlaneVals;

                // Add a line chart layer using the given data
                c.addSplineLayer(data);
            }
            else
            {
                redData = currentOnCameraFFCData.GrayValues.RPlaneVals;
                greenData = currentOnCameraFFCData.GrayValues.GPlaneVals;
                blueData = currentOnCameraFFCData.GrayValues.BPlaneVals;

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

        private void OnClickPerformFPN(object sender, EventArgs e)
        {
            string instruction = string.Format("Close the lens.\n\nClick 'OK' once you are done.");

            frmInstruction darkFieldCorrectionInstructionForm = new frmInstruction(instruction);
            if (darkFieldCorrectionInstructionForm.ShowDialog() == DialogResult.OK)
            {
                this.PerformFPN();
            }
        }

        private void OnClickPerformPRNU(object sender, EventArgs e)
        {
            string instruction = string.Format("Remove the lens cap.\n\nInsert the white calibration target and ensure that the complete FOV is covered.\n\nDefocus the lens by rotating the focus ring by 20 degrees.\n\nClick 'OK' once you are done.");

            frmInstruction brightFieldCorrectionInstructionForm = new frmInstruction(instruction);
            if (brightFieldCorrectionInstructionForm.ShowDialog() == DialogResult.OK)
            {
                this.PerformPRNU();
            }
        }
    }
}
