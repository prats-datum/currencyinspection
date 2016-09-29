using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using HalconDotNet;

namespace CameraSetupTool
{
    /// <summary>
    /// Represents the data to update the UI of Light Stick Alignment step
    /// </summary>
    public struct LightStickAlignmentData
    {
        public HImage Image;
        public int MinGrayValue;
        public int MaxGrayValue;
        public LineProfileGrayValues GrayValues;
        public bool Status;
        public double TimeTaken;
    }

    /// <summary>
    /// Represents the data to update the UI of Focus & Magnification check step
    /// </summary>
    public struct FocusMagnificationCheckData
    {
        public HImage Image;
        public LineProfileGrayValues GrayValues;
        public string FocusPercentage;
        public string MagnificationPercentage;
        public string PixelResolution;
        public double TimeTaken;

    }

    /// <summary>
    /// Represents the data to update the UI of Whitebalancing step
    /// </summary>
    public struct WhiteBalancingData
    {
        public HImage Image;
        public LineProfileGrayValues GrayValues;
        public string WhiteBalancingStatus;
        public double TimeTaken;
        public double RedMax;
        public double GreenMax;
        public double BlueMax;
        public double ErrorLevel;

    }

    /// <summary>
    /// Represents the data to update the UI of On Camera FFC step
    /// </summary>
    /// <remarks></remarks>
    public struct OnCameraFFCData
    {
        public HImage Image;
        public LineProfileGrayValues GrayValues;
        public double TimeTaken;
    }

    /// <summary>
    /// Represents the data to update the UI of ImageViewer step
    /// </summary>
    public struct ImageViewerData
    {
        public HImage Image;
        public LineProfileGrayValues GrayValues;
    }

    /// <summary>
    /// Represents the data to update the UI of FFC step
    /// </summary>
    public struct FFCData
    {
        public HImage Image;
        public LineProfileGrayValues GrayValues;
        public double TimeTaken;
    }

    /// <summary>
    /// Represents the data to update the UI of Applet configuration step
    /// </summary>
    public struct AppletConfigurationData
    {
        public HImage Image;
        public int ImageCount;
        public double TimeTaken;

        public LineProfileGrayValues GrayValues;
    }

    /// <summary>
    /// Represents the gray values of one line in the image for all color planes
    /// </summary>
    public struct LineProfileGrayValues
    {
        public double[] RPlaneVals;
        public double[] GPlaneVals;
        public double[] BPlaneVals;
        public double[] MPlaneVals;
    }
}
