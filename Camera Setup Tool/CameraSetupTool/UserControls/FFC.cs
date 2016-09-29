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
    public partial class FFC : UserControl, iCameraSettingSteps
    {
        public FFC()
        {
            InitializeComponent();
            this.Dock = DockStyle.Fill;
        }

        public CameraAcquisition CameraAcquisition { get; set; }

        public HImage ImageToBeSaved { get; set; }

        public event Action<string> UpdateStepStatusMessage;
        public event RefreshImageWindowEventHandler RefreshImageWindow;

        public StepDescriptor GetStepDescriptor()
        {
            StepDescriptor desc = new StepDescriptor();
            desc.StepDescription = "";

            return desc;
        }

        public void ProcessStep(HImage inputImage)
        {
            //throw new NotImplementedException();
        }

        public WinChartViewer UpdateChartUI(WinChartViewer viewer)
        {
            return viewer;
            //throw new NotImplementedException();
        }
    }
}
