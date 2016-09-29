using HalconDotNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Xml.Serialization;

namespace CameraSetupTool
{
    public class CameraAcquisition : iCameraAcquisition
    {
        public CameraAcquisition()
        {
            this.currentFGHandler = new HFramegrabber();
            this.currentFGProperties.DeviceID = -1;
            this.currentFGProperties.PortIndex = -1;

            this.currentCameraProperties = new CameraConfig();
            this.currentCameraSetupProperties = new CameraSetupConfig();

            acquisitionThread = new Thread(new ThreadStart(GrabImages));

            acquisitionThread.Start();
        }

        ManualResetEvent acquistionThreadActiveEvent = new ManualResetEvent(true);

        public AutoResetEvent acquistionThreadTerminateEvent = new AutoResetEvent(false);

        /// <summary>
        /// Gets or Sets the Mode of Grabbbing Image.
        /// </summary>
        public ImageGrabMode grabmode { get; set; }

        /// <summary>
        /// Thread that handles the image grabbing from the selected camera
        /// </summary>
        private Thread acquisitionThread;

        /// <summary>
        /// Represents the properties of the frame grabber that connects the selected camera
        /// </summary>        
        private static Logger logger = Logger.GetLogger();

        /// <summary>
        /// Width of image that is grabbed from the selected camera
        /// </summary>
        public int CurrentImageWidth
        {
            get { return this.currentImageWidth; }
            set { this.currentImageWidth = value; }
        }
        /// <summary>
        /// Height of image that is grabbed from the selected camera
        /// </summary>
        public int CurrentImageHeight
        {
            get { return this.currentImageHeight; }
            set { this.currentImageHeight = value; }
        }

        /// <summary>
        /// Number of channels in the image that is grabbed from the selected camera
        /// </summary>
        public int CurrentNumberOfChannels
        {
            get { return this.currentNumberOfChannels; }
            set { this.currentNumberOfChannels = value; }
        }

        /// <summary>
        /// Number of channels in the image that is grabbed from the selected camera
        /// </summary>
        private int currentNumberOfChannels;

        /// <summary>
        /// Width of image that is grabbed from the selected camera
        /// </summary>
        private int currentImageWidth;
        /// <summary>
        /// Height of image that is grabbed from the selected camera
        /// </summary>
        private int currentImageHeight;

        public bool StopGrabbing()
        {
            //this.acquisitionThreadActive = value;
            this.acquistionThreadActiveEvent.Reset();
            if (!this.acquistionThreadTerminateEvent.WaitOne(1000))
            {
                //throw new Exception("");
                return false;
            }

            return true;
        }

        /// <summary>
        /// Removes the handlers for ImageGrabbed event.
        /// </summary>
        public void RemoveImageGrabbedHandlers()
        {
            if (ImageGrabbed != null)
            {
                foreach (ImageGrabbedHandler handler in ImageGrabbed.GetInvocationList())
                {
                    ImageGrabbed -= handler;
                }
            }
        }

        private FrameGrabberProperties currentFGProperties;
        /// <summary>
        /// Gets or sets the current Frame grabber properties.
        /// </summary>
        /// <value>The current Frame grabber properties.</value>
        public FrameGrabberProperties CurrentFGProperties
        {
            get { return currentFGProperties; }
            set
            {
                // If no camera is selected when Camera Selector is opened first time, 
                // dispose the FG Handle (this was initialized to check the camera status of 
                // each frame grabber from the Camera Selector form)
                lock (this.currentFGHandler)
                {
                    if (value.DeviceID == -1 || value.PortIndex == -1)
                    {
                        if (this.currentFGHandler != null)
                        {
                            if (this.currentFGHandler.IsInitialized())
                            {
                                this.currentFGHandler.Dispose();
                            }
                        }
                        this.currentFGProperties.DeviceID = value.DeviceID;
                        this.currentFGProperties.PortIndex = value.PortIndex;
                        return;
                    }

                    if (this.currentFGProperties.DeviceID == value.DeviceID &&
                        this.currentFGProperties.PortIndex == value.PortIndex)
                    {
                        if (this.currentFGProperties.AppletMCFFile == value.AppletMCFFile)
                        {
                            return;
                        }
                        else
                        {
                            this.currentFGHandler.Dispose();
                        }
                    }

                    this.currentFGProperties.DeviceID = value.DeviceID;
                    this.currentFGProperties.PortIndex = value.PortIndex;
                    this.currentFGProperties.AppletMCFFile = value.AppletMCFFile;

                    HFramegrabber tempFGHandle = null;
                    try
                    {
                        HOperatorSet.SetSystem("do_low_error", "false");
                        logger.AppendLog(Severity.Debug,
                            string.Format("Before opening framegrabber. Device ID : {0} Port Index : {1} Applet Config File : {2}",
                            this.currentFGProperties.DeviceID, this.currentFGProperties.PortIndex,
                            this.currentFGProperties.AppletMCFFile));
                        tempFGHandle = new HFramegrabber(Properties.Settings.Default.ImageAcquisitionInterface,
                            1, 1, 0, 0, 0, 0, "default", -1, "default", "num_dma_channels=2", "false",
                            Globals.CameraSelectorDefaultAppletMCFFile, currentFGProperties.DeviceID.ToString(),
                            currentFGProperties.PortIndex, -1);
                        logger.AppendLog(Severity.Debug,
                           string.Format("After opening framegrabber. Device ID : {0} Port Index : {1} Applet Config File : {2}",
                           this.currentFGProperties.DeviceID, this.currentFGProperties.PortIndex,
                           this.currentFGProperties.AppletMCFFile));
                        tempFGHandle.SetFramegrabberParam("continuous_grabbing", "enable");  /// NOTE: Enable "continuous_grabbing" before setting "grab_timeout" value
                        HTuple parameterName = "grab_timeout";
                        HTuple timeoutValue = Properties.Settings.Default.ImageAcquisitionTimeoutValue;
                        tempFGHandle.SetFramegrabberParam(parameterName, timeoutValue);
                        logger.AppendLog(Severity.Debug,
                           string.Format("After setting framegrabber properties. Device ID : {0} Port Index : {1} Applet Config File : {2}",
                           this.currentFGProperties.DeviceID, this.currentFGProperties.PortIndex,
                           this.currentFGProperties.AppletMCFFile));
                    }
                    catch (System.Exception ex)
                    {
                        this.currentFGProperties.DeviceID = -1;
                        this.currentFGProperties.PortIndex = -1;
                        if (tempFGHandle != null)
                        {
                            tempFGHandle.Dispose();
                            tempFGHandle = null;
                        }

                        throw new Exception(string.Format("Exception occurred while opening/switching camera. Please close any other application that is using the framegrabbers. \r\n Error Message: {0}", ex.Message));
                    }
                    finally
                    {
                        if (tempFGHandle != null)
                        {
                            lock (this.currentFGHandler)
                            {
                                if (currentFGHandler != null && currentFGHandler.IsInitialized())
                                {
                                    currentFGHandler.Dispose();
                                }
                                currentFGHandler = tempFGHandle;
                            }
                        }
                    }
                }
            }
        }

        private CameraConfig currentCameraProperties;
        /// <summary>
        /// Gets or sets the current camera properties.
        /// </summary>
        /// <value>The current camera properties.</value>
        public CameraConfig CurrentCameraProperties
        {
            get { return currentCameraProperties; }
            set
            {
                this.currentCameraProperties.CameraLabel = value.CameraLabel;
                this.currentCameraProperties.CameraID = value.CameraID;
                this.currentCameraProperties.FGIndex = value.FGIndex;
                this.currentCameraProperties.PortIndex = value.PortIndex;
                this.currentCameraProperties.SerialPortIndex = value.SerialPortIndex;
                this.currentCameraProperties.CameraType = value.CameraType;
                this.currentCameraProperties.CameraManufacturer = value.CameraManufacturer;
                this.currentCameraProperties.CameraModel = value.CameraModel;
                this.currentCameraProperties.CameraSerialNumber = value.CameraSerialNumber;
                this.currentCameraProperties.FrameGrabberSerialNumber = value.FrameGrabberSerialNumber;
                this.currentCameraProperties.MinimumGrayLevel = value.MinimumGrayLevel;
                this.currentCameraProperties.MaximumGrayLevel = value.MaximumGrayLevel;
                this.currentCameraProperties.BrightRegionReferenceGrayLevel = value.BrightRegionReferenceGrayLevel;
                this.currentCameraProperties.DarkRegionReferenceGrayLevel = value.DarkRegionReferenceGrayLevel;
                this.currentCameraProperties.BrightRegionMinimumThresholdLevel = value.BrightRegionMinimumThresholdLevel;
                this.currentCameraProperties.BrightRegionMaximumThresholdLevel = value.BrightRegionMaximumThresholdLevel;
                this.currentCameraProperties.DarkRegionMinimumThresholdLevel = value.DarkRegionMinimumThresholdLevel;
                this.currentCameraProperties.DarkRegionMaximumThresholdLevel = value.DarkRegionMaximumThresholdLevel;
                this.currentCameraProperties.NumberOfPixelsToBeClippedAtLeft = value.NumberOfPixelsToBeClippedAtLeft;
                this.currentCameraProperties.NumberOfPixelsToBeClippedAtRight = value.NumberOfPixelsToBeClippedAtRight;
                this.currentCameraProperties.FFCWidthOfRegionToDetectDarkDefects = value.FFCWidthOfRegionToDetectDarkDefects;
                this.currentCameraProperties.FFCMaximumDeviationAllowed = value.FFCMaximumDeviationAllowed;
                this.currentCameraProperties.IPAAppletParametersDefaultConfigFile = value.IPAAppletParametersDefaultConfigFile;
                this.currentCameraProperties.CameraHeightReferenceLowerLimit = value.CameraHeightReferenceLowerLimit;
                this.currentCameraProperties.CameraHeightReferenceUpperLimit = value.CameraHeightReferenceUpperLimit;

                lock (this.currentFGHandler)
                {
                    if (this.currentFGHandler != null && this.currentFGHandler.IsInitialized())
                    {
                        if (!Properties.Settings.Default.UseDualLineTriggeredApplet)
                        {
                            // TODO Uncomment
                            // Set the encoder input parameter
                            //this.currentFGHandler.SetFramegrabberParam(
                            //    AppletSpecificConstantDefinitions.EncoderInputPinParameterName,
                            //    this.currentCameraProperties.EncoderInputPin);
                        }
                    }
                    // Set the image acquisition mode to free run
                    //SetImageAcquisitionMode(false);

                    // Get image width, height and number of channels
                    this.currentImageWidth = this.currentFGHandler.GetFramegrabberParam("image_width").I;
                    this.currentImageHeight = this.currentFGHandler.GetFramegrabberParam("image_height").I;

                    this.currentNumberOfChannels =
                        (this.currentFGHandler.GetFramegrabberParam("color_space").S == "rgb") ?
                        Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage :
                        Properties.Settings.Default.NumberOfChannelsInMonoImage;
                }
            }
        }

        /// <summary>
        /// Sets the image acquisition mode as free run or external triggered.
        /// </summary>
        /// <param name="triggeredMode">if set to <c>true</c> [triggered mode].</param>
        public void SetImageAcquisitionMode(bool triggeredMode)
        {
            try
            {
                if (!Properties.Settings.Default.UseDualLineTriggeredApplet)
                {
                    lock (this.currentFGHandler)
                    {
                        if (this.currentFGHandler != null && this.currentFGHandler.IsInitialized())
                        {
                            if (triggeredMode)
                            {
                                this.currentFGHandler.SetFramegrabberParam(AppletSpecificConstantDefinitions.TriggerGateParameterName,
                                                        AppletSpecificConstantDefinitions.TriggerGateResetParameterValue);
                                this.currentFGHandler.SetFramegrabberParam(AppletSpecificConstantDefinitions.TriggerModeParameterName,
                                    AppletSpecificConstantDefinitions.TriggerModeParameterValue);
                                this.currentFGHandler.SetFramegrabberParam(AppletSpecificConstantDefinitions.EncoderModeParameterName,
                                    AppletSpecificConstantDefinitions.TriggerModeParameterValue);
                            }
                            else
                            {
                                this.currentFGHandler.SetFramegrabberParam(AppletSpecificConstantDefinitions.EncoderModeParameterName,
                                    AppletSpecificConstantDefinitions.FreeRunModeParameterValue);
                                this.currentFGHandler.SetFramegrabberParam(AppletSpecificConstantDefinitions.TriggerModeParameterName,
                                    AppletSpecificConstantDefinitions.FreeRunModeParameterValue);
                            }
                            currentFGHandler.GrabImageStart(-1);
                            HTuple parameterName = "grab_timeout";
                            HTuple timeoutValue = Properties.Settings.Default.ImageAcquisitionTimeoutValue;
                            if (triggeredMode)
                            {
                                bool imagesRemainingInBuffer = true;
                                do
                                {
                                    try
                                    {
                                        currentFGHandler.GrabImageAsync(-1);
                                    }
                                    catch
                                    {
                                        imagesRemainingInBuffer = false;
                                    }
                                } while (imagesRemainingInBuffer);
                            }
                            this.currentFGHandler.SetFramegrabberParam(AppletSpecificConstantDefinitions.TriggerGateParameterName,
                                    AppletSpecificConstantDefinitions.TriggerGateSetParameterValue);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                throw new Exception(string.Format("Exception occurred while changing the image acquisition mode. \r\nError Message : \r\n{0}", ex.Message));
            }
        }

        /// <summary>
        /// Handle for the framegrabber that is currently selected (selected camera)
        /// </summary>
        private HFramegrabber currentFGHandler;

        /// <summary>
        /// Gets or sets the current Frame grabber handle.
        /// </summary>
        /// <value>The current Frame grabber handle.</value>
        public HFramegrabber CurrentFGHandler
        {
            get { return currentFGHandler; }
            set
            {
                lock (currentFGHandler)
                {
                    currentFGHandler = value;
                }
            }
        }

        private CameraSetupConfig currentCameraSetupProperties;

        /// <summary>
        /// Occurs when [image grabbed].
        /// </summary>
        /// <remarks></remarks>
        public event ImageGrabbedHandler ImageGrabbed;

        /// <summary>
        /// Denotes whether the setup configuration for the selected camera already exists or not
        /// </summary>
        public bool CurrentCameraSetupConfigExists;

        /// <summary>
        /// Gets or sets the current camera setup properties.
        /// </summary>
        /// <value>The current camera setup properties.</value>
        public CameraSetupConfig CurrentCameraSetupProperties
        {
            get { return currentCameraSetupProperties; }
            set
            {
                this.currentCameraSetupProperties.CameraLabel = value.CameraLabel;
                this.currentCameraSetupProperties.CameraID = value.CameraID;
                this.currentCameraSetupProperties.FocusMaxAutoCorrelationValue = value.FocusMaxAutoCorrelationValue;
                this.currentCameraSetupProperties.MagnificationPercentage = value.MagnificationPercentage;
                this.currentCameraSetupProperties.PixelResolution = value.PixelResolution;
                this.currentCameraSetupProperties.MinimumGrayValue = value.MinimumGrayValue;
                this.currentCameraSetupProperties.MaximumGrayValue = value.MaximumGrayValue;
                this.currentCameraSetupProperties.DistanceFromMipdInMM = value.DistanceFromMipdInMM;
                this.currentCameraSetupProperties.CalibrationPatternTotalWidth = value.CalibrationPatternTotalWidth;
                this.currentCameraSetupProperties.FFCEnabled = value.FFCEnabled;
                this.currentCameraSetupProperties.LastFFCSavingDate = value.LastFFCSavingDate;
                this.currentCameraSetupProperties.LastOnCameraFFCSavingDate = value.LastOnCameraFFCSavingDate;
            }
        }

        public void GrabImages()
        {
            while (acquistionThreadActiveEvent.WaitOne(0))
            {
                lock (this.currentFGHandler)
                {
                    if (this.currentFGHandler != null && this.currentFGHandler.IsInitialized())
                    {
                        try
                        {
                            HImage imageCaptured = currentFGHandler.GrabImage();
                            //this.numberOfImagesGrabbedInTriggeredMode++;
                            if (imageCaptured != null)
                            {
                                if (this.ImageGrabbed != null)
                                {
                                    ImageGrabbed.Invoke(imageCaptured);
                                }
                            }
                        }
                        catch (HOperatorException hex)
                        {
                            switch (hex.GetErrorCode())
                            {
                                case 5322:
                                    break;
                                //case 5311:
                                //    // The fg handle is invalidated. Reset it.
                                //    FrameGrabberProperties currentSettings = this.currentFGProperties;
                                //    this.currentFGProperties.DeviceID = 0;
                                //    this.currentFGProperties.PortIndex = (currentSettings.PortIndex + 1) % 2;
                                //    this.CurrentFGProperties = this.currentFGProperties;
                                //    this.CurrentFGProperties = currentSettings;
                                //    break;

                                default:
                                    throw hex;

                            }
                        }
                        catch (Exception ex)
                        {
                            throw new Exception(string.Format("Exception occurred while grabbing images. \r\n Message : {0} \r\n Stack Trace : {1}",
                                ex.Message, ex.StackTrace));
                        }
                    }
                    else
                    {
                        // Thread.Sleep(1000);
                    }
                }
                //Thread.Sleep(100);
            //    Application.DoEvents();
            //    if (!this.IsDisposed)
            //    {
            //        Action formRefresher = new Action(this.Invalidate);
            //        this.BeginInvoke(formRefresher);
            //    }
            }
            this.acquistionThreadTerminateEvent.Set();
        }

        /// <summary>
        /// Determines whether one or more camera is connected to the frame grabber and 
        /// whether active signals are available from the camera(s).
        /// </summary>
        /// <returns>
        /// 	<c>true</c> if [is camera connected]; otherwise, <c>false</c>.
        /// </returns>
        public bool IsCameraConnected()
        {
            HTuple cameraStatus;
            lock (this.currentFGHandler)
            {
                if (this.currentFGHandler != null && this.currentFGHandler.IsInitialized())
                {
                    cameraStatus = currentFGHandler.GetFramegrabberParam("camera_status");
                    if (cameraStatus == 0)
                    {
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                return false;
            }
        }


        /// <summary>
        /// Gets the frame grabber serial number.
        /// </summary>
        /// <returns>frame grabber serial number</returns>
        public string GetFrameGrabberSerialNumber()
        {
            string serialNumber = "";
            lock (this.currentFGHandler)
            {
                if (this.currentFGHandler != null && this.currentFGHandler.IsInitialized())
                {
                    serialNumber = currentFGHandler.GetFramegrabberParam("serial_number");
                }
            }
            return serialNumber;
        }

        /// <summary>
        /// Determines whether the light intensity level is optimum by comparing the minimum and maximum 
        /// gray values against the acceptable range
        /// </summary>
        /// <param name="GrayValues">The gray values.</param>
        /// <param name="minValue">The minimum gray value.</param>
        /// <param name="maxValue">The maximum gray value.</param>
        /// <returns>
        /// 	<c>true</c> if light intensity is optimum; otherwise, <c>false</c>.
        /// </returns>
        public bool IsLightIntensityLevelOptimum(double[] GrayValues, out int minValue, out int maxValue)
        {
            minValue = (int)GrayValues.Min();
            maxValue = (int)GrayValues.Max();

            if ((minValue >= this.currentCameraProperties.MinimumGrayLevel) &&
                (maxValue <= this.currentCameraProperties.MaximumGrayLevel))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Determines whether the light intensity level is optimum by comparing the minimum and maximum 
        /// gray values against the acceptable range. Here another offset value is subtracted from the 
        /// minimum level before comparing.
        /// </summary>
        /// <param name="GrayValues">The gray values.</param>
        /// <param name="minValue">The minimum gray value.</param>
        /// <param name="maxValue">The maximum gray value.</param>
        /// <returns>
        /// 	<c>true</c> if light intensity is optimum; otherwise, <c>false</c>.
        /// </returns>
        public bool IsLightIntensityLevelOptimum(double[] GrayValues, out int minValue, out int maxValue, int offsettoBeAppliedOnMinimum)
        {
            minValue = (int)GrayValues.Min();
            maxValue = (int)GrayValues.Max();

            if ((minValue >= this.currentCameraProperties.MinimumGrayLevel - offsettoBeAppliedOnMinimum) &&
                (maxValue <= this.currentCameraProperties.MaximumGrayLevel))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    public enum ImageGrabMode
    {
        FreeRun,
        TriggerOREncode
    }
}
