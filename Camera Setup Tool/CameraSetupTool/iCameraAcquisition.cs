using HalconDotNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CameraSetupTool
{
    /// <summary>
    /// Represents the method that processes the image captured according to the step selected 
    /// </summary>
    /// <param name="imageGrabbed">The image grabbed.</param>
    /// <remarks></remarks>
    public delegate void ImageGrabbedHandler(HImage imageGrabbed);

    public interface iCameraAcquisition
    {
        /// <summary>
        /// Gets or Sets the Mode of Grabbbing Image.
        /// </summary>
        ImageGrabMode grabmode { get; set; }

        /// <summary>
        /// Gets or Sets Camera Properties.
        /// </summary>
        CameraConfig CurrentCameraProperties { get; set; }

        /// <summary>
        /// Gets or Sets Frame Grabber Properties.
        /// </summary>
        FrameGrabberProperties CurrentFGProperties { get; set; }

        /// <summary>
        /// Gets or sets the Handler for frame grabber.
        /// </summary>
        HFramegrabber CurrentFGHandler { get; set; }

        /// <summary>
        /// Occurs when ever a image is grabbed from the frame grabber.
        /// </summary>
        event ImageGrabbedHandler ImageGrabbed;

        /// <summary>
        /// Grabs the Images from the Framgrabber and Camera Properties Associated with
        /// </summary>
        /// <returns>HImage</returns>
        void GrabImages();

    }
}
