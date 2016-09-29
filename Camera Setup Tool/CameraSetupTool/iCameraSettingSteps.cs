using HalconDotNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace CameraSetupTool
{
    /// <summary>
    /// Defines the prototype of method that is used to refresh image window
    /// </summary>
    /// <param name="image"></param>
    public delegate void RefreshImageWindowEventHandler(HImage image);

    public interface iCameraSettingSteps
    {
        /// <summary>
        /// Gets or sets the instance CameraAcquisition Class
        /// </summary>
        CameraAcquisition CameraAcquisition { get; set; }

        /// <summary>
        /// Occurs when the parameters are changed by the user.
        /// </summary>
        event RefreshImageWindowEventHandler RefreshImageWindow;

        /// <summary>
        /// Updates the UI associated with the step.
        /// </summary>
        void ProcessStep(HImage inputImage);

        HImage ImageToBeSaved { get; set; }

        /// <summary>
        /// Occurs when a status update is required.
        /// </summary>
        event Action<string> UpdateStepStatusMessage;

        /// <summary>
        /// Gets the step descriptor for this step.
        /// </summary>
        /// <returns>The descriptor for this step.</returns>
        StepDescriptor GetStepDescriptor();

        /// <summary>
        /// Generate a demo chart and display it in the given WinChartViewer. The chartIndex 
        /// argument indicate which demo chart to generate. It must be a number from 0 to (n - 1).
        /// </summary>
        ChartDirector.WinChartViewer UpdateChartUI(ChartDirector.WinChartViewer viewer);
    }
}
