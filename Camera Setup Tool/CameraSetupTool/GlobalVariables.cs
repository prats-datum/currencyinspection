using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using HalconDotNet;
using System.Runtime.InteropServices;

namespace CameraSetupTool
{
    /// <summary>
    /// Manufacturers of cameras used in BQIS
    /// </summary>
    public enum CameraMake
    {
        /// <summary>
        /// none
        /// </summary>
        None = 0,
        /// <summary>
        /// JAI camera
        /// </summary>
        JAI = 1,
        /// <summary>
        /// e2v camera
        /// </summary>
        e2v = 2
    }

    public enum CameraChannels
    {
        Red,
        Green,
        Blue
    }

    public class Globals
    {
        public static string LogFilePath = Application.StartupPath + "\\ISU Log.log";
        public static string CameraSelectorDefaultAppletMCFFile = Application.StartupPath + "\\Config\\UC4_Just_Grab.mcf";

        public static string CameraDefaultSettingsFilePath = Application.StartupPath + "\\Config\\CameraDefaultsCommands.ini";

        #region e2v Camera Commands

        #region UC4 Camera Inital Settings Commands
        public const string e2vCommandToGetUC4CameraModel = "r idnb";

        public const string ModelNameReferenceStringForUC4Camera = "UC4";

        #endregion

        public const string e2vUC4CommandToPerformAutoWhiteBalancing = "w sawb 1";

        public const string e2vUC4CommandToGetRedPlaneGain = "r wbar";
        public const string e2vUC4CommandToGetBluePlaneGain = "r wbab";
        public const string e2vUC4CommandToGetGreenPlaneGain = "r wbag";
        public const string e2vUC4CommandToGetNIRPlaneGain = "r wbai";

        public const string e2vUC4CommandToSetRedPlaneGain = "w wbar ";
        public const string e2vUC4CommandToSetBluePlaneGain = "w wbab ";
        public const string e2vUC4CommandToSetGreenPlaneGain = "w wbag ";
        public const string e2vUC4CommandToSetNIRPlaneGain = "w wbai ";

        public const string e2vUC4CommandToResetRedPlaneGain = "w wbar 0";
        public const string e2vUC4CommandToResetBluePlaneGain = "w wbab 0";
        public const string e2vUC4CommandToResetGreenPlaneGain = "w wbag 0";
        public const string e2vUC4CommandToResetNIRPlaneGain = "w wbai 0";

        public const string e2vUC4CommandToEnableWhiteBalancing = "w wben 1";

        public const string e2vUC4CommandToSaveWhiteBalancingToUserBank1 = "w scol 1";
        public const string e2vUC4CommandToSaveWhiteBalancingToUserBank2 = "w scol 2";
        public const string e2vUC4CommandToSaveWhiteBalancingToUserBank3 = "w scol 3";
        public const string e2vUC4CommandToSaveWhiteBalancingToUserBank4 = "w scol 4";

        public const string e2vUC4CommandToDoOnCameraDFC = "w calo 1";
        public const string e2vUC4CommandToDoOnCameraBFC = "w calg 1";
        public const string e2vUC4CommandToReadStatusOfOnCameraDFC = "r calo";
        public const string e2vUC4CommandToReadStatusOfOnCameraBFC = "r calg";

        public const string e2vUC4CommandToSaveFFCToUserBank1 = "w sffc 3";
        public const string e2vUC4CommandToSaveFFCToUserBank2 = "w sffc 2";
        public const string e2vUC4CommandToSaveFFCToUserBank3 = "w sffc 3";
        public const string e2vUC4CommandToSaveFFCToUserBank4 = "w sffc 4";

        public const string e2vUC4CommandToSaveALLSettingsToUserBank1 = "w scfg 1";
        public const string e2vUC4CommandToSaveALLSettingsToUserBank2 = "w scfg 2";
        public const string e2vUC4CommandToSaveALLSettingsToUserBank3 = "w scfg 3";
        public const string e2vUC4CommandToSaveALLSettingsToUserBank4 = "w scfg 4";

        #endregion

        //#region Constants used in DIO Communication with PCIE-1751

        //public const string DeviceDescription = "PCIE-1751,BID#0";

        //#endregion

        //#region Constants used in Image Acquistion and in serial communication with cameras

        ///// <summary>
        ///// Image Acquisition Interface
        ///// </summary>
        //public const string ImageAcquisitionInterface = "SiliconSoftware";
        //public const int SerialCommunicationTimeout = 100;


        //public const UInt32 SerCommMaximumNumberOfTrialsForGettingResponse = 3;
        ////public const String CameraSelectorDefaultAppletMCFFile = "Config\\CameraSelectorDefaultApplet_512_256.mcf";
        //public const int ImageAcquisitionTimeoutValue = 2000;

        //public const int NumberOfChannelsInIRAndRGBImage = 6;
        //public const int NumberOfChannelsInColorImage = 3;
        //public const int NumberOfChannelsInMonoImage = 1;

        //public const int DelayBetweenCommandsInLoadingInitialSettings = 100;

        //public const bool UseDualLineTriggeredApplet = false;
        //#endregion

        //#region Constants used in ISU

        //public const bool ShowTimeTakenInStatusLabel = false;
        //public const bool CheckForImproperCalibrationTarget = true;
        //#endregion

        //#region Constants used in Camera Alignment, Focus & Magnification step

        //public const int UIROIRectangleWidth = 500;
        //public const int UIROIRectangleHeight = 10;

        //public const int FocusROIRectangleWidth = 500;
        //public const int FocusROIRectangleHeight = 10;

        //public const int WBROIRectangleWidth = 250;
        //public const int WbROIRectangleHeight = 10;

        //public const int FFCROIRectangleWidth = 250;
        //public const int FFCROIRectangleHeight = 10;

        //public const int LICROIRectangleWidth = 250;
        //public const int LICROIRectangleHeight = 10;

        //public const int NoOfSamplesUsedInFocusStep = 32;

        //public const double MinimumFocusLearningRangeRequired = 30.0;

        //public const int FocusPatternCheckReferenceGrayValue = 80;

        //#endregion

        //#region Constants used in FFC step

        //public const int DarkFieldCorrectionMaximumGrayLevel = 20;

        //public const string CoefficientsResetMessage = "Coefficient Values Reset";
        //public const string CoefficientComputationSuccessMessage = "Coefficients computed successfully";
        //public const string DFCCoefficientComputationFailedMessage = "Lens is not closed properly. Cannot compute coefficients.";

        //public const string FFCCorrectionDoneMessage = "Correction Done";
        //public const string FFCCoefficientsLoadedMessage = "FFC Coefficients loaded from file.";

        //// To select the dark regions in the calibration document for color correction
        //public const double FFCThresholdMinimum = 200.0;
        //public const double FFCThresholdMaximum = 255.0;

        //#endregion

        //#region Constants used in White Balancing Step
        //public const double MinThresholdInDeterminingGain = 90.0;
        //public const double MaxThresholdInDeterminingGain = 255.0;
        //public const double GainStepInitialValue = 1000;
        //public const double GainMaximumRange = 7999;
        //public const int MaxIterationsInSettingAutomaticGain = 20;
        //public const string WhiteBalancingLightIntensityNotOptimumMessage = "Light intensity is not optimum in one or more channels. Cannot perform white balancing.";
        //public const int WhiteBalancingOffsetFromRefGrayLevel = 1;
        //#endregion

        //#region Constants used in On Camera FFC Step
        //public const string FPNLightIntensityNotOptimumMessage = "Lens is not closed properly. Cannot perform FPN.";
        //public const string PRNULightIntensityNotOptimumMessage = "Light intensity is not optimum in one or more channels. Cannot perform PRNU.";
        //public const int PRNUMinimumGrayLevelOffset = 30;
        //#endregion

        //#region Literals used in reading / writing Settings from / to XML files

        //public const string FFCXMLFileRoot = "FFCMap";
        //public const string FFCXMLFileAttributeCameraID = "CameraID";
        //public const string FFCXMLFileAttributeNumberOfChannels = "NoOfChannels";
        //public const string FFCXMLFileAttributeFFCDate = "FFCDate";
        //public const string FFCXMLFileAttributeReferenceGrayLevel = "ReferenceGrayLevel";
        //public const string FFCXMLFileElementChannel = "Channel";
        //public const string FFCXMLFileAttributeChannelIndex = "ChannelIndex";
        //public const string FFCXMLFileElementPixelCorrection = "PixelCorrection";
        //public const string FFCXMLFileAttributePixelIndex = "PixelIndex";
        //public const string CCXMLFileAttributeGain = "CCGain";
        //public const string CCXMLFileAttributeOffset = "CCOffset";
        //public const string DFCXMLFileAttributeOffset = "DFCOffset";

        //#endregion

        //#region Constants used in Applet Configuration Step
        //public const double CalibDocumentThresholdMinimumLimit = 30.0;
        //public const double CalibDocumentThresholdMaximumLimit = 255.0;
        //public const int CalibDocumentWhiteRegionMinimumArea = 100000;

        //#endregion 

        #region Get Gray Values of an Image and Check Pattern of focus calibration

        /// <summary>
        /// Gets the gray values of center line of the image.
        /// </summary>
        /// <param name="image">The image.</param>        
        /// <returns>
        /// Tuple containing the gray values of the center line of image
        /// </returns>
        public static HTuple GetGrayValuesOfLine(HImage image)
        {
            // Feed the image to the script
            int imageWidth;
            int imageHeight;
            IntPtr imagePointer;
            System.String imageType;

            imagePointer = image.GetImagePointer1(out imageType, out imageWidth, out imageHeight);

            // Get  gray values of center line in the image
            int AOIBeginRow = imageHeight / 2 - 1;
            int AOIEndRow = AOIBeginRow;
            int AOIBeginCol = 0;
            int AOIEndCol = imageWidth - 1;

            HRegion AOIRegion = new HRegion();
            AOIRegion.GenRegionLine(AOIBeginRow, AOIBeginCol, AOIEndRow, AOIEndCol);
            HTuple AOIRowPoints = new HTuple();
            HTuple AOIColPoints = new HTuple();
            AOIRegion.GetRegionPoints(out AOIRowPoints, out AOIColPoints);
            HTuple AOIGrayVals = image.GetGrayval(AOIRowPoints, AOIColPoints);

            return AOIGrayVals;

        }

        /// <summary>
        /// Gets the gray values of specified row of the image.
        /// </summary>
        /// <param name="image">The image.</param>
        /// <param name="row">The row.</param>
        /// <returns>
        /// Tuple containing the gray values of the specified row of image
        /// </returns>
        public static HTuple GetGrayValuesOfLine(HImage image, int row)
        {
            // Feed the image to the script
            int imageWidth;
            int imageHeight;
            IntPtr imagePointer;
            System.String imageType;

            imagePointer = image.GetImagePointer1(out imageType, out imageWidth, out imageHeight);

            // Get  gray values of center line in the image
            int AOIBeginRow = row;
            int AOIEndRow = AOIBeginRow;
            int AOIBeginCol = 0;
            int AOIEndCol = imageWidth - 1;

            HRegion AOIRegion = new HRegion();
            AOIRegion.GenRegionLine(AOIBeginRow, AOIBeginCol, AOIEndRow, AOIEndCol);
            HTuple AOIRowPoints = new HTuple();
            HTuple AOIColPoints = new HTuple();
            AOIRegion.GetRegionPoints(out AOIRowPoints, out AOIColPoints);
            HTuple AOIGrayVals = image.GetGrayval(AOIRowPoints, AOIColPoints);

            return AOIGrayVals;
        }

        public static HTuple GetGrayValuesOfPixel(HImage image)
        {
            HRegion imageRegion = image.GetDomain();
            HTuple absoluteTuples = new HTuple();
            image.GrayHisto(imageRegion, out absoluteTuples);

            return absoluteTuples;
        }

        /// <summary>
        /// Finds the white & black pattern area in the calibration document.
        /// </summary>
        /// <param name="image1">The image1.</param>
        /// <returns></returns>
        /// <remarks></remarks>
        public static HImage FindPatternArea(HImage image1)
        {
            HImage reducedImage = new HImage();
            try
            {
                double row;
                double column;
                double phi;
                double length1;
                double length2;

                HRegion regions = image1.Threshold(Properties.Settings.Default.CalibDocumentThresholdMinimumLimit,
                    Properties.Settings.Default.CalibDocumentThresholdMaximumLimit);

                int areaOfWhiteRegion = regions.AreaCenter(out row, out column);
                // If the segmented white region does not have the specified area, return from the function
                if (areaOfWhiteRegion < Properties.Settings.Default.CalibDocumentWhiteRegionMinimumArea)
                {
                    return null;
                }
                regions.SmallestRectangle2(out row, out column, out phi, out length1, out length2);

                HRegion rectangleRegion = new HRegion();
                rectangleRegion.GenRectangle2(row, column, phi, length1, length2);
                reducedImage = image1.ReduceDomain(rectangleRegion);

            }
            catch (Exception ex)
            {
                string errorMessage = "Exception occurred in FindPatternArea. ";

                errorMessage = errorMessage + " Error Message: " + ex.Message;

                MessageBox.Show(errorMessage, "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);

            }
            return reducedImage;
        }

        #endregion

        #region SerialCommunication Functions

        public static bool ExecuteSerialCommand(uint portNumber, string Command, out string bufferData)
        {
            IntPtr i = new IntPtr();
            return ExecuteSerialCommand(i, portNumber, Command, out bufferData, Properties.Settings.Default.SerialCommunicationTimeout, Properties.Settings.Default.SerialCommunicationTimeout);
        }

        public static bool ExecuteSerialCommand(uint portNumber, string Command, out string bufferData, int timeOut, int delayBeforeReadingResponse)
        {
            IntPtr i = new IntPtr();
            return ExecuteSerialCommand(i, portNumber, Command, out bufferData, timeOut, delayBeforeReadingResponse);
        }

        public static bool ExecuteSerialCommand(IntPtr serialCommRef, uint portNumber, string Command, out string bufferData, int delayBeforeReadingResponse)
        {
            return ExecuteSerialCommand(serialCommRef, portNumber, Command, out bufferData, Properties.Settings.Default.SerialCommunicationTimeout, delayBeforeReadingResponse);
        }

        public static bool ExecuteSerialCommand(IntPtr serialCommRef, uint portNumber, string Command, out string bufferData, int timeOut, int delayBeforeReadingResponse)
        {
            bool portConnected = false;
            string error = "";
            int retVal;
            string bufferDataFromCamera = "";

            try
            {
                //this.Text = string.Format("Please wait while detecting the connected cameras...");
                // this.Refresh();

                retVal = ClserWrapper.clSerialInit((uint)portNumber, ref serialCommRef);

                if (retVal != ClserWrapper.CL_ERR_NO_ERR)
                {
                    error = string.Format("Cannot initialize serial port : {0}", portNumber);
                    portConnected = false;
                }

                retVal = ClserWrapper.clSetBaudRate(serialCommRef, ClserWrapper.CL_BAUDRATE_9600);
                if (retVal != ClserWrapper.CL_ERR_NO_ERR)
                {
                    error = string.Format("Cannot set baud rate 9600 for serial port {0}", portNumber);
                    portConnected = false;
                }

                // Check whether camera is a "e2v" camera

                string command = Command.Contains(System.Environment.NewLine) ? Command : Command + System.Environment.NewLine;

                if (GetResponseFromSerialPort(serialCommRef,
                                                          (uint)portNumber,
                                                          command,
                                                          timeOut,
                                                          out bufferDataFromCamera,
                                                          delayBeforeReadingResponse, out error))
                {
                    portConnected = true;
                }
                else
                {
                    portConnected = false;
                    throw new Exception(error);
                }

            }
            catch (Exception ex)
            {
                portConnected = false;
                bufferDataFromCamera = "";
                throw new Exception(error);
            }


            ClserWrapper.clSerialClose(serialCommRef);
            bufferData = bufferDataFromCamera;
            return portConnected;
        }

        /// <summary>
        /// Gets the response from e2v camera. This function send the serial commands to the camera and read 
        /// the response from the camera. A maximum of three attempts are made to read the response from camera 
        /// in case of failures (such as internal error). 
        /// </summary>
        /// <param name="serialComRef">The serial communication port reference.</param>
        /// <param name="portNumber">The serial port number.</param>
        /// <param name="command">The command.</param>
        /// <param name="bufferData">The buffer to receive the response from camera.</param>
        /// <returns></returns>
        public static bool GetResponseFromSerialPort(IntPtr serialComRef,
            uint portNumber,
            string command,
            out string bufferData,
            int delayBeforeReadingResponse, out string err)
        {
            return GetResponseFromSerialPort(serialComRef, portNumber, command, Properties.Settings.Default.SerialCommunicationTimeout,out bufferData, delayBeforeReadingResponse,out err);
        }

        /// <summary>
        /// Gets the response from e2v camera. This function send the serial commands to the camera and read 
        /// the response from the camera. A maximum of three attempts are made to read the response from camera 
        /// in case of failures (such as internal error). 
        /// </summary>
        /// <param name="serialComRef">The serial communication port reference.</param>
        /// <param name="portNumber">The serial port number.</param>
        /// <param name="command">The command.</param>
        /// <param name="bufferData">The buffer to receive the response from camera.</param>
        /// <returns></returns>
        public static bool GetResponseFromSerialPort(IntPtr serialComRef,
            uint portNumber,
            string command,
            int timeOut,
            out string bufferData,
            int delayBeforeReadingResponse, out string err)
        {
            char cont = 'y';
            bool commandProcessingSuccess = true;
            uint numberOfTrials = 0;
            string error = "";
            do
            {
                int retVal = ClserWrapper.clFlushPort(serialComRef);
                if (retVal != ClserWrapper.CL_ERR_NO_ERR)
                {
                    error = string.Format("Error in flushing serial port {0}. Error code : {1}", portNumber, retVal);
                    cont = 'y';
                    bufferData = "";
                }

                byte[] writeBuffer = System.Text.ASCIIEncoding.ASCII.GetBytes(command);
                uint writeBufferSize = (uint)writeBuffer.Length;

                retVal = ClserWrapper.clSerialWrite(serialComRef, writeBuffer, ref writeBufferSize,
                    (uint)timeOut);

                if (retVal != ClserWrapper.CL_ERR_NO_ERR)
                {
                    error = string.Format("Error in writing command to serial port {0}. Error Code : {1}. Commad written : {2}", portNumber, retVal, command);
                    cont = 'y';
                    commandProcessingSuccess = false;
                    bufferData = "";
                }
                else
                {
                    System.Threading.Thread.Sleep(delayBeforeReadingResponse);
                    uint numBytes = 1024;
                    byte[] readBuffer = new byte[1024];
                    IntPtr ipReadBuffer = Marshal.AllocHGlobal(readBuffer.Length);
                    retVal = ClserWrapper.clSerialRead(serialComRef, ipReadBuffer, ref numBytes,
                                                      (uint)timeOut);
                    if (retVal == ClserWrapper.CL_ERR_NO_ERR)
                    {
                        Marshal.Copy(ipReadBuffer, readBuffer, 0, (int)numBytes);
                        readBuffer = readBuffer.Take((int)numBytes).ToArray();
                        string readBufferContents = System.Text.ASCIIEncoding.ASCII.GetString(readBuffer);
                        if (readBufferContents.IndexOf(">Ok\r") >= 0)
                        {
                            bufferData = readBufferContents;
                            commandProcessingSuccess = true;
                            cont = 'n';
                        }
                        else if (readBufferContents.IndexOf(">3\r") >= 0 || readBufferContents.IndexOf(">16\r") >= 0 ||
                            readBufferContents.IndexOf(">21\r") >= 0 || readBufferContents.IndexOf(">33\r") >= 0 ||
                            readBufferContents.IndexOf(">34\r") >= 0 || readBufferContents.IndexOf(">7\r") >= 0)
                        {
                            cont = 'y';
                            bufferData = "";
                            commandProcessingSuccess = false;
                            error = string.Format("Error in getting response from E2V camera. Reading from serial port {0}. Error code : {1}. Trial Number : {2}. Command sent to camera : {3}. Buffer response : {4} ",
                                portNumber, retVal, numberOfTrials, command, readBufferContents);
                        }
                        else
                        {
                            bufferData = readBufferContents;
                            commandProcessingSuccess = true;
                            cont = 'n';
                        }
                    }
                    else
                    {
                        commandProcessingSuccess = false;
                        bufferData = "";

                        error = string.Format("Error in getting response from E2V camera. Reading from serial port {0}. Error code : {1}. Trial Number : {2}. Command sent to camera : {3}",
                           portNumber, retVal, numberOfTrials, command);

                    }
                }
            } while ((cont == 'y') && ((numberOfTrials++) < 3));
            err = error;
            return commandProcessingSuccess;
        }

        #endregion
    }

    /// <summary>
    /// Represents the class the defines the constants used for the parameter names 
    /// in the applets loaded for ISU
    /// </summary>
    /// <remarks></remarks>
    public static class AppletSpecificConstantDefinitions
    {
        #region applet specific parameter names used in default image capturing applet loaded in ISU
        public const string EncoderInputPinParameterName =
            "Device1_Process0_Trigger_Manipulator_Trigger_Source_Trigger_Source_Line_Trigger_Input_Select";
        public const string EncoderModeParameterName =
            "Device1_Process0_Trigger_Manipulator_Trigger_Source_Encoder_Mode_Select";
        public const string TriggerModeParameterName =
            "Device1_Process0_Trigger_Manipulator_Trigger_Source_Trigger_Mode_Select";

        public const string DelayInMultiplesOfThousandParameterName =
            "Device1_Process0_Trigger_Manipulator_Image_Trigger_Manipulator_Delay_Select_Delay_Modules_Select";
        public const string ProgrammableDelayParameterName =
            "Device1_Process0_Trigger_Manipulator_Image_Trigger_Manipulator_Delay_Programmable_Delay_Port1_Delay";
        public const string TriggerGateParameterName =
            "Device1_Process0_Trigger_Manipulator_Trigger_Source_Trigger_Gate_Select";


        #endregion

        #region applet specific parameter values for free run mode
        public const int FreeRunModeParameterValue = 1;
        #endregion 

        #region applet specific parameter values for triggered mode
        public const int TriggerModeParameterValue = 0;
        public const int TriggerGateResetParameterValue = 0;
        public const int TriggerGateSetParameterValue = 1;

        #endregion

        #region Applet specific parameter names used in FFC module 

        public const string RedPlaneDFCLutContentParameterName = "Device1_Process0_FFC_R_Plane_Dark_Field_Offset_LUTcontent";
        public const string GreenPlaneDFCLutContentParameterName = "Device1_Process0_FFC_G_Plane_Dark_Field_Offset_LUTcontent";
        public const string BluePlaneDFCLutContentParameterName = "Device1_Process0_FFC_B_Plane_Dark_Field_Offset_LUTcontent";


        public const string RedPlaneBFCLutContentParameterName = "Device1_Process0_FFC_R_Plane_Bright_Field_Gain_LUTcontent";
        public const string GreenPlaneBFCLutContentParameterName = "Device1_Process0_FFC_G_Plane_Bright_Field_Gain_LUTcontent";
        public const string BluePlaneBFCLutContentParameterName = "Device1_Process0_FFC_B_Plane_Bright_Field_Gain_LUTcontent";

        public const string RedPlaneDFCEnableParameterName = "Device1_Process0_FFC_R_Plane_Dark_Field_Dark_Field_Correction_Enable_Value";
        public const string GreenPlaneDFCEnableParameterName = "Device1_Process0_FFC_G_Plane_Dark_Field_Dark_Field_Correction_Enable_Value";
        public const string BluePlaneDFCEnableParameterName = "Device1_Process0_FFC_B_Plane_Dark_Field_Dark_Field_Correction_Enable_Value";


        public const string RedPlaneBFCEnableParameterName = "Device1_Process0_FFC_R_Plane_Bright_Field_Bright_Field_Correction_Enable_Value";
        public const string GreenPlaneBFCEnableParameterName = "Device1_Process0_FFC_G_Plane_Bright_Field_Bright_Field_Correction_Enable_Value";
        public const string BluePlaneBFCEnableParameterName = "Device1_Process0_FFC_B_Plane_Bright_Field_Bright_Field_Correction_Enable_Value";

        public const string MonoPlaneDFCLutContentParameterName = "Device1_Process0_FFC_Mono_Plane_Dark_Field_Offset_LUTcontent";
        public const string MonoPlaneBFCLutContentParameterName = "Device1_Process0_FFC_Mono_Plane_Bright_Field_Gain_LUTcontent";
        public const string MonoPlaneDFCEnableParameterName = "Device1_Process0_FFC_Mono_Plane_Dark_Field_Dark_Field_Correction_Enable_Value";
        public const string MonoPlaneBFCEnableParameterName = "Device1_Process0_FFC_Mono_Plane_Bright_Field_Bright_Field_Correction_Enable_Value";

        #endregion 

        #region Applet specific parameter values used in FFC module
        public const int EnableAppletFFCParameterValue = 1;
        public const int DisableAppeltFFCParameterValue = 0;
        #endregion

    }

    /// <summary>
    /// Denotes the constants that represents how the exposure value should be adjusted in 
    /// the WhiteBalancing step. 
    /// </summary>
    /// <remarks></remarks>
    public enum WhiteBalancingStepIncrementSetting
    {
        NONE = 0,
        LESSER = 1,
        GREATER = 2
    }
}
