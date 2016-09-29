using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;

namespace CameraSetupTool
{
    /// <summary>
    /// Statically provides the hardware configuration of the system.
    /// </summary>
    public class HardwareConfig
    {
        /// <summary>
        /// Represents the instance that holds the hardware configuration
        /// </summary>
        private static HardwareConfig instance;

        /// <summary>
        /// Represents the path of the config file
        /// </summary>
        private const string HardwareConfigFilePath = "\\Config\\HardwareConfiguration.xml";

        /// <summary>
        /// Gets or sets the master setting.
        /// </summary>
        /// <value>The master setting.</value>
        /// <remarks></remarks>
        [XmlArrayItem]
        public List<CameraConfig> MasterSetting { get; set; }

        /// <summary>
        /// Gets or sets the local setting.
        /// </summary>
        /// <value>The local setting.</value>
        /// <remarks></remarks>
        [XmlArrayItem]
        public List<CameraConfig> LocalSetting { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="HardwareConfig"/> class.
        /// </summary>
        private HardwareConfig()
        {
            this.MasterSetting = new List<CameraConfig>();
            this.LocalSetting = new List<CameraConfig>();
        }

        /// <summary>
        /// Gets the hardware configuration.
        /// </summary>
        /// <value>The hardware configuration.</value>
        /// <returns>
        /// Hardware configuration of the system. This includes the master settings for the application
        /// and the local settings of the current machine/server/IPA.
        /// </returns>
        public static HardwareConfig Current
        {
            get
            {
                if (instance == null)
                {
                    instance = new HardwareConfig();
                    try
                    {
                        string configFileName = System.Windows.Forms.Application.StartupPath + HardwareConfig.HardwareConfigFilePath;
                        StreamReader reader = new StreamReader(configFileName);
                        XmlSerializer serializer = new XmlSerializer(instance.GetType());
                        instance = serializer.Deserialize(reader) as HardwareConfig;
                        reader.Close();

                    }
                    catch (System.Exception ex)
                    {
                        System.Windows.Forms.MessageBox.Show("Exception in reading hardware configuration of system\r\n" + ex.Message);
                    }
                }
                return instance;
            }
        }

        /// <summary>
        /// Gets the camera labels from master settings.
        /// </summary>
        /// <returns>
        /// List of labels of all cameras connected to system. 
        /// </returns>
        public List<string> GetCameraLabelsFromMasterSettings()
        {
            List<string> cameraLabels = new List<string>();

            foreach (CameraConfig cameraConfig in instance.MasterSetting)
            {
                cameraLabels.Add(cameraConfig.CameraLabel);
            }

            return cameraLabels;
        }

        /// <summary>
        /// Gets the camera labels from local settings.
        /// </summary>
        /// <returns>
        /// List of labels of all cameras connected to system. 
        /// </returns>
        public List<string> GetCameraLabelsFromLocalSettings()
        {
            List<string> cameraLabels = new List<string>();

            foreach (CameraConfig cameraConfig in instance.LocalSetting)
            {
                cameraLabels.Add(cameraConfig.CameraLabel);
            }

            return cameraLabels;
        }

        /// <summary>
        /// Checks whether camera configuration local settings exists or not.
        /// </summary>
        /// <returns>
        /// true if the configuration exists; otherwise false. 
        /// </returns>
        public bool CameraConfigurationLocalSettingsExists()
        {

            if (instance.LocalSetting.Count != 0)
            {
                return true;
            }

            return false;
        }

        /// <summary>
        /// Gets the label of camera as per the specified serial number.
        /// </summary>
        /// <param name="cameraSerialNumber">The camera serial number.</param>
        /// <param name="fgSerialNumber">The frame grabber serial number.</param>
        /// <returns></returns>
        public string GetCameraLabelAsPerSerialNumber(string cameraSerialNumber, string fgSerialNumber)
        {
            string cameraLabel = "";

            if (instance.MasterSetting.Count != 0)
            {
                foreach (CameraConfig cameraItem in instance.MasterSetting)
                {
                    if (cameraItem.CameraSerialNumber == cameraSerialNumber)
                    {
                        if (cameraItem.FrameGrabberSerialNumber == fgSerialNumber)
                        {
                            cameraLabel = cameraItem.CameraLabel;
                        }
                        break;
                    }
                }
            }

            return cameraLabel;
        }

        /// <summary>
        /// Gets the master setting for camera with the specified label.
        /// </summary>
        /// <param name="cameraLabel">The camera label.</param>
        /// <returns></returns>
        public CameraConfig GetMasterSettingForCamera(string cameraLabel)
        {
            CameraConfig selectedCameraMasterSetting = null;

            foreach (CameraConfig cameraItem in instance.MasterSetting)
            {
                if (cameraItem.CameraLabel == cameraLabel)
                {
                    selectedCameraMasterSetting = cameraItem;
                }
            }

            return selectedCameraMasterSetting;
        }

        /// <summary>
        /// Gets the local setting for camera with the specified label.
        /// </summary>
        /// <param name="cameraLabel">The camera label.</param>
        /// <returns></returns>
        public CameraConfig GetLocalSettingForCamera(string cameraLabel)
        {
            CameraConfig selectedCameraLocalSetting = null;

            foreach (CameraConfig cameraItem in instance.LocalSetting)
            {
                if (cameraItem.CameraLabel == cameraLabel)
                {
                    selectedCameraLocalSetting = cameraItem;
                }
            }

            return selectedCameraLocalSetting;
        }

        /// <summary>
        /// Saves the camera configuration.
        /// </summary>
        public void SaveCameraConfiguration()
        {
            string configFileName = System.Windows.Forms.Application.StartupPath + HardwareConfig.HardwareConfigFilePath;
            StreamWriter writer = new StreamWriter(configFileName);
            XmlSerializer serializer = new XmlSerializer(instance.GetType());
            serializer.Serialize(writer, instance);
            writer.Close();
        }
    }

    public class ImagingSetupConfig
    {
        /// <summary>
        /// Represents the instance that holds the imaging setup configuration
        /// </summary>
        private static ImagingSetupConfig instance;
        /// <summary>
        /// Represents the path of the config file
        /// </summary>
        public const string ImagingSetupConfigFilePath = "\\Config\\ImagingSetupConfiguration.xml";
        /// <summary>
        /// Gets or sets the local imaging setup config.
        /// </summary>
        /// <value>The local imaging setup config.</value>
        /// <remarks></remarks>
        [XmlArrayItem]
        public List<CameraSetupConfig> LocalImagingSetupConfig { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="ImagingSetupConfig"/> class.
        /// </summary>
        private ImagingSetupConfig()
        {
            LocalImagingSetupConfig = new List<CameraSetupConfig>();
        }

        /// <summary>
        /// Gets the imaging setup configuration.
        /// </summary>
        /// <value>The imaging setup configuration.</value>
        public static ImagingSetupConfig Current
        {
            get
            {
                if (instance == null)
                {
                    instance = new ImagingSetupConfig();

                    try
                    {
                        if (ImagingSetupConfigurationExists())
                        {
                            string configFileName = System.Windows.Forms.Application.StartupPath + ImagingSetupConfig.ImagingSetupConfigFilePath;
                            StreamReader reader = new StreamReader(configFileName);
                            XmlSerializer serializer = new XmlSerializer(instance.GetType());
                            instance = serializer.Deserialize(reader) as ImagingSetupConfig;
                            reader.Close();
                        }

                    }
                    catch (System.Exception ex)
                    {
                        System.Windows.Forms.MessageBox.Show("Exception in reading imaging setup configuration of system\r\n" + ex.Message);
                    }
                }
                return instance;
            }
        }

        /// <summary>
        /// Checks whether the Imaging setup configuration file exists or not.
        /// </summary>
        /// <returns>
        /// true if the configuration exists; otherwise false. 
        /// </returns>
        public static bool ImagingSetupConfigurationExists()
        {
            string ImagingSetupConfigFileName = System.Windows.Forms.Application.StartupPath + ImagingSetupConfig.ImagingSetupConfigFilePath;
            if (System.IO.File.Exists(ImagingSetupConfigFileName))
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// Sets the imaging setup config of camera.
        /// </summary>
        /// <param name="selectedSetupConfig">The selected setup config.</param>
        public void SetImagingSetupConfigOfCamera(CameraSetupConfig selectedSetupConfig)
        {
            bool localSettingsModified = false;
            if (instance.LocalImagingSetupConfig.Count != 0)
            {
                foreach (CameraSetupConfig configItem in instance.LocalImagingSetupConfig)
                {
                    if (configItem.CameraLabel.Equals(selectedSetupConfig.CameraLabel))
                    {
                        configItem.CameraID = selectedSetupConfig.CameraID;
                        configItem.FocusMaxAutoCorrelationValue = selectedSetupConfig.FocusMaxAutoCorrelationValue;
                        configItem.MagnificationPercentage = selectedSetupConfig.MagnificationPercentage;
                        configItem.PixelResolution = selectedSetupConfig.PixelResolution;
                        configItem.MinimumGrayValue = selectedSetupConfig.MinimumGrayValue;
                        configItem.MaximumGrayValue = selectedSetupConfig.MaximumGrayValue;
                        configItem.DistanceFromMipdInMM = selectedSetupConfig.DistanceFromMipdInMM;
                        configItem.CalibrationPatternTotalWidth = selectedSetupConfig.CalibrationPatternTotalWidth;
                        configItem.FFCEnabled = selectedSetupConfig.FFCEnabled;
                        configItem.LastFFCSavingDate = selectedSetupConfig.LastFFCSavingDate;
                        configItem.LastOnCameraFFCSavingDate = selectedSetupConfig.LastOnCameraFFCSavingDate;
                        localSettingsModified = true;
                        break;
                    }
                }
            }

            if (!localSettingsModified)
            {
                instance.LocalImagingSetupConfig.Add(selectedSetupConfig);
            }
        }
        /// <summary>
        /// Saves the imaging setup configuration.
        /// </summary>
        public void SaveImagingSetupConfiguration()
        {
            if (instance != null)
            {
                string configFileName = System.Windows.Forms.Application.StartupPath + ImagingSetupConfig.ImagingSetupConfigFilePath;
                StreamWriter writer = new StreamWriter(configFileName);
                XmlSerializer serializer = new XmlSerializer(instance.GetType());
                serializer.Serialize(writer, instance);
                writer.Close();
            }
        }

        /// <summary>
        /// Reads the imaging setup configuration.
        /// </summary>
        public void ReadImagingSetupConfiguration()
        {
            try
            {
                if (instance == null)
                {
                    instance = new ImagingSetupConfig();
                }
                string configFileName = System.Windows.Forms.Application.StartupPath + ImagingSetupConfig.ImagingSetupConfigFilePath;
                StreamReader reader = new StreamReader(configFileName);
                XmlSerializer serializer = new XmlSerializer(instance.GetType());
                instance = serializer.Deserialize(reader) as ImagingSetupConfig;
                reader.Close();

            }
            catch (System.Exception ex)
            {
                System.Windows.Forms.MessageBox.Show("Exception in reading imaging setup configuration of system\r\n" + ex.Message);
            }
        }
    }

    /// <summary>
    /// Represents an object that provides the configuration corresponding to setup of camera connected to the system 
    /// </summary>
    public class CameraSetupConfig
    {
        /// <summary>
        /// Gets or sets the camera label.
        /// </summary>
        /// <value>The camera label.</value>
        [XmlAttribute("CameraLabel")]
        public string CameraLabel { get; set; }
        /// <summary>
        /// Gets or sets the camera ID.
        /// </summary>
        /// <value>The camera ID.</value>
        [XmlAttribute("CameraID")]
        public int CameraID { get; set; }
        /// <summary>
        /// Gets or sets the maximum auto correlation value learnt in Focus step.
        /// </summary>
        /// <value>The maximum auto correlation value.</value>
        [XmlAttribute("FocusMaxAutoCorrelationValue")]
        public double FocusMaxAutoCorrelationValue { get; set; }
        /// <summary>
        /// Gets or sets the magnification percentage.
        /// </summary>
        /// <value>The magnification percentage.</value>
        [XmlAttribute("MagnificationPercentage")]
        public double MagnificationPercentage { get; set; }
        /// <summary>
        /// Gets or sets the pixel resolution.
        /// </summary>
        /// <value>The pixel resolution.</value>
        [XmlAttribute("PixelResolution")]
        public double PixelResolution { get; set; }
        /// <summary>
        /// Gets or sets the minimum gray value in the image. For color image, green plane is considered.
        /// </summary>
        /// <value>The minimum gray value.</value>
        [XmlAttribute("MinimumGrayValue")]
        public int MinimumGrayValue { get; set; }
        /// <summary>
        /// Gets or sets the maximum gray value in the image. For color image, green plane is considered.
        /// </summary>
        /// <value>The maximum gray value.</value>
        [XmlAttribute("MaximumGrayValue")]
        public int MaximumGrayValue { get; set; }
        /// <summary>
        /// Gets or sets the distance from MIPD in MM.
        /// </summary>
        /// <value>The distance from MIPD in MM.</value>
        [XmlAttribute("DistanceFromMipdInMM")]
        public int DistanceFromMipdInMM { get; set; }
        /// <summary>
        /// Gets or sets the width of the stripes in calibration pattern.
        /// </summary>
        /// <value>The width of the stripe in calibration pattern.</value>
        [XmlAttribute("CalibrationPatternTotalWidth")]
        public double CalibrationPatternTotalWidth { get; set; }
        /// <summary>
        /// Gets or sets a value indicating whether FFC is enabled.
        /// </summary>
        /// <value><c>true</c> if [FFC enabled]; otherwise, <c>false</c>.</value>
        [XmlAttribute("FFCEnabled")]
        public bool FFCEnabled { get; set; }
        /// <summary>
        /// Gets or sets the last FFC date.
        /// </summary>
        /// <value>The last FFC date.</value>
        [XmlAttribute("LastFFCSavingDate")]
        public string LastFFCSavingDate { get; set; }
        /// <summary>
        /// Gets or sets the last On Camera FFC date.
        /// </summary>
        /// <value>The last On Camera FFC date.</value>
        [XmlAttribute("LastOnCameraFFCSavingDate")]
        public string LastOnCameraFFCSavingDate { get; set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="CameraSetupConfig"/> class.
        /// </summary>
        public CameraSetupConfig()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="CameraSetupConfig"/> class.
        /// </summary>
        /// <param name="cameraLabel">The camera label.</param>
        /// <param name="cameraID">The camera ID.</param>
        /// <param name="magnificationPercentage">The magnification percentage.</param>
        /// <param name="pixelResolution">The pixel resolution.</param>
        /// <param name="minimumGrayValue">The minimum gray value.</param>
        /// <param name="maximumGrayValue">The maximum gray value.</param>
        /// <param name="distanceFromMipdInMM">The distance from mipd in MM.</param>
        /// <param name="calibrationPatternBlackStripeWidth">Width of the calibration pattern black stripe.</param>
        /// <param name="calibrationPatternWhiteStripeWidth">Width of the calibration pattern white stripe.</param>
        /// <param name="updationDate">The updation date.</param>
        public CameraSetupConfig(
            string cameraLabel,
            int cameraID,
            double magnificationPercentage,
            double pixelResolution,
            int minimumGrayValue,
            int maximumGrayValue,
            int distanceFromMipdInMM,
            double calibrationPatternTotalWidth,
            bool ffcEnabled,
            string lastFFCDate,
            string lastOCFFCDate
        )
        {
            this.CameraLabel = cameraLabel;
            this.CameraID = cameraID;
            this.MagnificationPercentage = magnificationPercentage;
            this.PixelResolution = pixelResolution;
            this.MinimumGrayValue = minimumGrayValue;
            this.MaximumGrayValue = maximumGrayValue;
            this.DistanceFromMipdInMM = distanceFromMipdInMM;
            this.CalibrationPatternTotalWidth = calibrationPatternTotalWidth;
            this.FFCEnabled = ffcEnabled;
            this.LastFFCSavingDate = lastFFCDate;
            this.LastOnCameraFFCSavingDate = lastOCFFCDate;
        }
    }

    /// <summary>
    /// Frame grabber properties
    /// </summary>
    public struct FrameGrabberProperties
    {
        /// <summary>
        /// Gets or sets the device ID.
        /// </summary>
        /// <value>The device ID.</value>
        public int DeviceID
        {
            get;
            set;
        }
        /// <summary>
        /// Gets or sets the index of the port (Port A ==> 0, Port B ==> 1).
        /// </summary>
        /// <value>The index of the port.</value>
        public int PortIndex
        {
            get;
            set;
        }
        /// <summary>
        /// Gets or sets the applet configuration file (.MCF file).
        /// </summary>
        /// <value>The applet MCF file.</value>
        public string AppletMCFFile
        {
            get;
            set;
        }
    }

    /// <summary>
    /// Represents an object that provides the configuration corresponding to camera connected to the system 
    /// </summary>
    public class CameraConfig
    {
        /// <summary>
        /// Gets or sets the camera label.
        /// </summary>
        /// <value>The camera label.</value>
        [XmlAttribute("Label")]
        public string CameraLabel { get; set; }
        /// <summary>
        /// Gets or sets the camera ID.
        /// </summary>
        /// <value>The camera ID.</value>
        [XmlAttribute("ID")]
        public int CameraID { get; set; }
        /// <summary>
        /// Gets or sets the index of the Framegrabber to which camera is connected.
        /// </summary>
        /// <value>The index of the Framegrabber.</value>
        [XmlAttribute("FrameGrabberIndex")]
        public int FGIndex { get; set; }
        /// <summary>
        /// Gets or sets the index of the port in the framegrabber to which camera is connected..
        /// </summary>
        /// <value>The index of the port.</value>
        [XmlAttribute("PortIndex")]
        public int PortIndex { get; set; }
        /// <summary>
        /// Gets or sets the index of the serial port (cameralink port) used for sending serial commands to camera.
        /// </summary>
        /// <value>The index of the serial port.</value>
        [XmlAttribute("SerialPortIndex")]
        public int SerialPortIndex { get; set; }
        /// <summary>
        /// Gets or sets the type of the camera.
        /// </summary>
        /// <value>The type of the camera.</value>
        [XmlAttribute("CameraType")]
        public string CameraType { get; set; }
        /// <summary>
        /// Gets or sets the camera manufacturer.
        /// </summary>
        /// <value>The camera manufacturer.</value>
        [XmlAttribute("CameraManufacturer")]
        public string CameraManufacturer { get; set; }
        /// <summary>
        /// Gets or sets the camera model.
        /// </summary>
        /// <value>The camera model.</value>
        [XmlAttribute("CameraModel")]
        public string CameraModel { get; set; }
        /// <summary>
        /// Gets or sets the camera serial number.
        /// </summary>
        /// <value>The camera serial number.</value>
        [XmlAttribute("CameraSerialNumber")]
        public string CameraSerialNumber { get; set; }
        /// <summary>
        /// Gets or sets the frame grabber serial number.
        /// </summary>
        /// <value>The frame grabber serial number.</value>
        [XmlAttribute("FrameGrabberSerialNumber")]
        public string FrameGrabberSerialNumber { get; set; }
        /// <summary>
        /// Gets or sets the minimum gray level for white target.
        /// </summary>
        /// <value>The minimum gray level.</value>
        [XmlAttribute("MinimumGrayLevel")]
        public int MinimumGrayLevel { get; set; }
        /// <summary>
        /// Gets or sets the maximum gray level for white target.
        /// </summary>
        /// <value>The maximum gray level.</value>
        [XmlAttribute("MaximumGrayLevel")]
        public int MaximumGrayLevel { get; set; }
        /// <summary>
        /// Gets or sets the reference gray level for white region in the 
        /// calibration document used for FFC / Color correction.
        /// </summary>
        /// <value>The reference gray level for bright region.</value>
        [XmlAttribute("BrightRegionReferenceGrayLevel")]
        public int BrightRegionReferenceGrayLevel { get; set; }
        /// <summary>
        /// Gets or sets the reference gray level for dark region in the 
        /// calibration document used for FFC / Color correction.
        /// </summary>
        /// <value>The reference gray level for dark region.</value>
        [XmlAttribute("DarkRegionReferenceGrayLevel")]
        public int DarkRegionReferenceGrayLevel { get; set; }
        /// <summary>
        /// Gets or sets the minimum level for thresholding bright region in the 
        /// calibration document for color correction
        /// </summary>
        /// <value>The minimum threshold level for bright region.</value>
        [XmlAttribute("BrightRegionMinimumThresholdLevel")]
        public int BrightRegionMinimumThresholdLevel { get; set; }
        /// <summary>
        /// Gets or sets the maximum level for thresholding bright region in the 
        /// calibration document for color correction
        /// </summary>
        /// <value>The maximum threshold level for bright region.</value>
        [XmlAttribute("BrightRegionMaximumThresholdLevel")]
        public int BrightRegionMaximumThresholdLevel { get; set; }
        /// <summary>
        /// Gets or sets the minimum level for thresholding dark region in the 
        /// calibration document for color correction
        /// </summary>
        /// <value>The minimum threshold level for dark region.</value>
        [XmlAttribute("DarkRegionMinimumThresholdLevel")]
        public int DarkRegionMinimumThresholdLevel { get; set; }
        /// <summary>
        /// Gets or sets the maximum level for thresholding dark region in the 
        /// calibration document for color correction
        /// </summary>
        /// <value>The maximum threshold level for dark region.</value>
        [XmlAttribute("DarkRegionMaximumThresholdLevel")]
        public int DarkRegionMaximumThresholdLevel { get; set; }
        /// <summary>
        /// Gets or sets the number of pixels to be clipped at left.
        /// </summary>
        /// <value>The number of pixels to be clipped at left.</value>
        [XmlAttribute("NumberOfPixelsToBeClippedAtLeft")]
        public int NumberOfPixelsToBeClippedAtLeft { get; set; }
        /// <summary>
        /// Gets or sets the number of pixels to be clipped at right.
        /// </summary>
        /// <value>The number of pixels to be clipped at right.</value>
        [XmlAttribute("NumberOfPixelsToBeClippedAtRight")]
        public int NumberOfPixelsToBeClippedAtRight { get; set; }
        /// <summary>
        /// Gets or sets the width of region to detect dark defects in the white target 
        /// during FFC step.
        /// </summary>
        /// <value>The width of region to detect dark defects.</value>
        [XmlAttribute("FFCWidthOfRegionToDetectDarkDefects")]
        public int FFCWidthOfRegionToDetectDarkDefects { get; set; }
        /// <summary>
        /// Gets or sets the maximum deviation allowed in FFC step.
        /// </summary>
        /// <value>The maximum deviation allowed.</value>
        [XmlAttribute("FFCMaximumDeviationAllowed")]
        public double FFCMaximumDeviationAllowed { get; set; }
        /// <summary>
        /// Gets or sets the default config file for setting IPA applet parameters.
        /// </summary>
        /// <value>The IPA applet parameter default config file.</value>
        [XmlAttribute("IPAAppletParametersDefaultConfigFile")]
        public string IPAAppletParametersDefaultConfigFile { get; set; }
        /// <summary>
        /// Gets or sets the camera height reference lower limit.
        /// </summary>
        /// <value>The camera height reference lower limit.</value>
        [XmlAttribute("CameraHeightReferenceLowerLimit")]
        public int CameraHeightReferenceLowerLimit { get; set; }
        /// <summary>
        /// Gets or sets the camera height reference upper limit.
        /// </summary>
        /// <value>The camera height reference upper limit.</value>
        [XmlAttribute("CameraHeightReferenceUpperLimit")]
        public int CameraHeightReferenceUpperLimit { get; set; }


        /// <summary>
        /// Initializes a new instance of the <see cref="CameraConfig"/> class.
        /// </summary>
        public CameraConfig()
        {
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="CameraConfig"/> class.
        /// </summary>
        /// <param name="cameraLabel">The camera label.</param>
        /// <param name="cameraID">The camera ID.</param>
        /// <param name="fgIndex">Index of the framegrabber to which camera is connected.</param>
        /// <param name="portIndex">Index of the port in the framegrabber to which camera is connected.</param>
        /// <param name="serialPortIndex">Index of the serial port (cameralink port) used for sending serial commands to camera.</param>
        /// <param name="cameraType">Type of the camera.</param>
        /// <param name="cameraManufacturer">The camera manufacturer.</param>
        /// <param name="cameraModel">The camera model.</param>
        /// <param name="cameraSerialNumber">The camera serial number.</param>
        /// <param name="frameGrabberSerialNumber">The frame grabber serial number.</param>
        /// <param name="minimumDistanceFromMipdInMM">The minimum distance from mipd in MM.</param>
        /// <param name="distanceFromMipdInMM">The distance from mipd in MM.</param>
        /// <param name="maximumDistanceFromMipdInMM">The maximum distance from mipd in MM.</param>
        /// <param name="workingDistanceInMM">The working distance in MM.</param>
        /// <param name="minimumPixelResolution">The minimum pixel resolution.</param>
        /// <param name="maximumPixelResolution">The maximum pixel resolution.</param>
        /// <param name="minimumLightIntensityLevel">The minimum light intensity level.</param>
        /// <param name="maximumLightIntensityLevel">The maximum light intensity level.</param>
        /// <param name="brightRegionReferenceGrayLevel">The reference gray level for bright region.</param>
        /// <param name="numberOfPixelsToBeClippedAtLeft">The number of pixels to be clipped at left.</param>
        /// <param name="numberOfPixelsToBeClippedAtRight">The number of pixels to be clipped at right.</param>
        /// <param name="ffcWidthOfRegionToDetectDarkDefects">The FFC width of region to detect dark defects.</param>
        /// <param name="ffcMaximumDeviationAllowed">The FFC maximum deviation allowed.</param>
        /// <param name="ipaAppletParametersDefaultConfigFile">The ipa applet parameters default config file.</param>
        /// <param name="guiAppletParametersDefaultConfigFile">The GUI applet parameters default config file.</param>
        /// <param name="ipaAppletParametersConfigFile">The IPA applet parameters config file.</param>
        /// <param name="guiAppletParametersConfigFile">The GUI applet parameters config file.</param>
        /// <param name="encoderInputPin">The encoder input pin.</param>
        /// <param name="calibrationPatternTotalWidth">Total width of stripes in calibration document</param>
        /// <param name="cameraHeightReferenceLowerLimit">The camera height reference lower limit.</param>
        /// <param name="cameraHeightReferenceUpperLimit">The camera height reference upper limit.</param>
        public CameraConfig(
            string cameraLabel,
            int cameraID,
            int fgIndex,
            int portIndex,
            int serialPortIndex,
            string cameraType,
            string cameraManufacturer,
            string cameraModel,
            string cameraSerialNumber,
            string frameGrabberSerialNumber,
            int minimumLightIntensityLevel,
            int maximumLightIntensityLevel,
            int brightRegionReferenceGrayLevel,
            int darkRegionReferenceGrayLevel,
            int brightRegionMinimumThresholdLevel,
            int brightRegionMaximumThresholdLevel,
            int darkRegionMinimumThresholdLevel,
            int darkRegionMaximumThresholdLevel,
            int numberOfPixelsToBeClippedAtLeft,
            int numberOfPixelsToBeClippedAtRight,
            int ffcWidthOfRegionToDetectDarkDefects,
            double ffcMaximumDeviationAllowed,
            string ipaAppletParametersDefaultConfigFile,
            int cameraHeightReferenceLowerLimit,
            int cameraHeightReferenceUpperLimit
            )
        {
            this.CameraLabel = cameraLabel;
            this.CameraID = cameraID;
            this.FGIndex = fgIndex;
            this.PortIndex = portIndex;
            this.SerialPortIndex = serialPortIndex;
            this.CameraType = cameraType;
            this.CameraManufacturer = cameraManufacturer;
            this.CameraModel = cameraModel;
            this.CameraSerialNumber = cameraSerialNumber;
            this.FrameGrabberSerialNumber = frameGrabberSerialNumber;
            this.MaximumGrayLevel = maximumLightIntensityLevel;
            this.BrightRegionReferenceGrayLevel = brightRegionReferenceGrayLevel;
            this.DarkRegionReferenceGrayLevel = darkRegionReferenceGrayLevel;
            this.BrightRegionMinimumThresholdLevel = brightRegionMinimumThresholdLevel;
            this.BrightRegionMaximumThresholdLevel = brightRegionMaximumThresholdLevel;
            this.DarkRegionMinimumThresholdLevel = darkRegionMinimumThresholdLevel;
            this.DarkRegionMaximumThresholdLevel = darkRegionMaximumThresholdLevel;
            this.NumberOfPixelsToBeClippedAtLeft = numberOfPixelsToBeClippedAtLeft;
            this.NumberOfPixelsToBeClippedAtRight = numberOfPixelsToBeClippedAtRight;
            this.FFCWidthOfRegionToDetectDarkDefects = ffcWidthOfRegionToDetectDarkDefects;
            this.FFCMaximumDeviationAllowed = ffcMaximumDeviationAllowed;
            this.IPAAppletParametersDefaultConfigFile = ipaAppletParametersDefaultConfigFile;
            this.CameraHeightReferenceLowerLimit = cameraHeightReferenceLowerLimit;
            this.CameraHeightReferenceUpperLimit = cameraHeightReferenceUpperLimit;
        }
    }
}
