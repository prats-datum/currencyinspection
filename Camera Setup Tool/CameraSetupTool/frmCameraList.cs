using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using HalconDotNet;
using System.Runtime.InteropServices;

namespace CameraSetupTool
{
    public delegate void CameraInitializer(int port, int selectedCameraIndex, out FrameGrabberProperties fgProps, out CameraConfig camProps);
    public interface iProgressWindow
    {
        event Action<string> UpdateStatusMsgEvent;
    }
    public partial class frmCameraList : Form, iProgressWindow
    {
        public event Action<string> UpdateStatusMsgEvent;

        private static Logger logger = Logger.GetLogger();

        CameraAcquisition cameraAcquistion;

        bool localSettingsExists;

        bool noCameraConnected;

        System.Threading.AutoResetEvent CameraConnectedEvent = new System.Threading.AutoResetEvent(false);

        /// <summary>
        /// Denotes whether refreshing camera list is needed or not
        /// </summary>
        private bool refreshingCameraListNeeded;

        /// <summary>
        /// Handles the "Image Grabbed" event of selected camera.
        /// </summary>
        /// <param name="imageGrabbed">The image grabbed.</param>
        public void OnImageGrabbedFromSelectedCamera(HImage imageGrabbed)
        {
            if (this.InvokeRequired)
            {
                Action<HImage> delDisplayImage = new Action<HImage>(OnImageGrabbedFromSelectedCamera);
                this.BeginInvoke(delDisplayImage, imageGrabbed);
            }
            else
            {
                HImage currentImage = imageGrabbed.CopyImage();
                imageGrabbed.Dispose();
                // Display image
                cameraSelectorImageWindow.SetFullImagePart(currentImage);
                if (cameraSelectorImageWindow != null)
                {
                    if (currentImage.CountChannels().I == Properties.Settings.Default.NumberOfChannelsInIRAndRGBImage)
                    {
                        HImage rImage, gImage, bImage, rgbImage;
                        rImage = currentImage.Decompose3(out gImage, out bImage);
                        rgbImage = rImage.Compose3(gImage, bImage);
                        cameraSelectorImageWindow.HalconWindow.DispColor(rgbImage);
                    }
                    else if (currentImage.CountChannels().I == Properties.Settings.Default.NumberOfChannelsInColorImage)
                    {
                        cameraSelectorImageWindow.HalconWindow.DispColor(currentImage);
                    }
                    else
                    {
                        cameraSelectorImageWindow.HalconWindow.DispImage(currentImage);
                    }
                }
            }
        }

        /// <summary>
        /// Represents the details of all cameras queried by sending serial commands 
        /// </summary>
        private List<CameraConfig> cameraConfigurationsQueriedFromSystem;

        private uint noOfCamerasToBeConnected = 0;

        public frmCameraList()
        {
            InitializeComponent();
            cameraAcquistion = new CameraAcquisition();
            cameraConfigurationsQueriedFromSystem = new List<CameraConfig>();
        }

        /// <summary>
        /// Gets the list of cameras available from the local configuration file.
        /// </summary>
        void InitializeCamerasFromConfigFile()
        {
            if (dgvCameraList.Rows.Count > 0)
            {
                dgvCameraList.Rows.Clear();
            }

            if (this.cameraConfigurationsQueriedFromSystem.Count > 0)
            {
                this.cameraConfigurationsQueriedFromSystem.Clear();
            }

            List<string> camerasToBeConnected = HardwareConfig.Current.GetCameraLabelsFromLocalSettings();

            noOfCamerasToBeConnected = (uint)camerasToBeConnected.Count;

            Action del = new Action(PopulateDataGridView);
            IAsyncResult asyncresult = del.BeginInvoke(null, null);

            ProgressWindow pw = new ProgressWindow(this);
            pw.ShowDialog(asyncresult);

            //PopulateDataGridView();
        }

        /// <summary>
        /// Get the number of serial port available in the system and updates the gridview as per the number
        /// of connected cameras.
        /// </summary>
        void InitializeCamerasFromSerialPort()
        {
            if (dgvCameraList.Rows.Count > 0)
            {
                dgvCameraList.Rows.Clear();
            }

            if (this.cameraConfigurationsQueriedFromSystem.Count > 0)
            {
                this.cameraConfigurationsQueriedFromSystem.Clear();
            }

            int retVal = ClserWrapper.clGetNumSerialPorts(out noOfCamerasToBeConnected);

            Action del = new Action(PopulateDataGridView);
            IAsyncResult asyncresult = del.BeginInvoke(null, null);

            ProgressWindow pw = new ProgressWindow(this);
            pw.ShowDialog(asyncresult);
        }

        protected override void OnShown(EventArgs e)
        {
            base.OnShown(e);
            this.Text = string.Format("Please wait while detecting the connected cameras...");
            this.Refresh();
            this.Enabled = false;

            LoadDefaultCameraCommands();

            //Commented to retrieve camera from port by default
            localSettingsExists = HardwareConfig.Current.CameraConfigurationLocalSettingsExists();
            //localSettingsExists = false;
            try {
                InitializeCameras();
            } catch (Exception ex)
            {

            }

            this.Text = string.Format("Camera Selector");
            this.Enabled = true;
            this.Refresh(); this.Focus();
            cameraAcquistion.ImageGrabbed += new ImageGrabbedHandler(OnImageGrabbedFromSelectedCamera);

            if (this.refreshingCameraListNeeded)
            {
                MessageBox.Show("Camera are loaded from config, to connect double click on camera row.",
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                //this.dgvCameraList.Enabled = false;
                this.dgvCameraList.Columns["colCameraLabel"].ReadOnly = true;
                this.saveSettingsToolStripMenuItem.Enabled = false;
                this.btnOk.Enabled = false;
                this.btnFactoryReset.Enabled = false;
                this.btnSendCommand.Enabled = false;
            }
            else
            {
                if (this.dgvCameraList.RowCount != 0)
                {
                    this.dgvCameraList.Enabled = true;
                    this.dgvCameraList.Columns["colCameraLabel"].ReadOnly = false;
                    this.btnOk.Enabled = true;
                    this.btnFactoryReset.Enabled = true;
                    this.btnSendCommand.Enabled = true;
                    bool enableSave = true;
                    foreach (DataGridViewRow r in dgvCameraList.Rows)
                    {
                        DataGridViewComboBoxCell c = (DataGridViewComboBoxCell)this.dgvCameraList.Rows[r.Index].Cells[dgvCameraList.ColumnCount - 1];
                        if (String.IsNullOrEmpty(c.Value.ToString()))
                        {
                            enableSave = false;
                        }
                    }
                    this.saveSettingsToolStripMenuItem.Enabled = enableSave;
                }
                else
                {
                    MessageBox.Show("Please check whether all camera are connected / powered and click \"Refresh Camera List\".",
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    this.dgvCameraList.Enabled = false;
                    this.btnOk.Enabled = false;
                    this.btnFactoryReset.Enabled = false;
                    this.btnSendCommand.Enabled = false;
                    this.saveSettingsToolStripMenuItem.Enabled = false;
                }
            }

            if (!localSettingsExists || noCameraConnected)
            {
                this.btnOk.Enabled = false;
            }
        }

        private Dictionary<string, string> CameraDefaultSettingsCommand;

        private void LoadDefaultCameraCommands()
        {
            if (System.IO.File.Exists(Globals.CameraDefaultSettingsFilePath))
            {
                string[] defaultCommands = System.IO.File.ReadAllLines(Globals.CameraDefaultSettingsFilePath);
                if(CameraDefaultSettingsCommand !=null)
                    CameraDefaultSettingsCommand.Clear();
                CameraDefaultSettingsCommand = defaultCommands.Select(a => a.Split('=')).ToDictionary(b => b[0], b => b[1]);
            }
        }

        /// <summary>
        /// Retrieves cameras either from local settings or from serial port.S
        /// </summary>
        void InitializeCameras()
        {
            List<string> cameraLabelsFromMasterSetting = HardwareConfig.Current.GetCameraLabelsFromMasterSettings();
            dgvCameraList.Rows.Clear();
            DataGridViewComboBoxColumn cameraLabelCmb = (DataGridViewComboBoxColumn)this.dgvCameraList.Columns[this.dgvCameraList.ColumnCount - 1];
            if (cameraLabelCmb.Items.Count > 0)
            {
                cameraLabelCmb.Items.Clear();
            }
            cameraLabelCmb.Items.AddRange(cameraLabelsFromMasterSetting.ToArray());

            if (localSettingsExists)
            {
                InitializeCamerasFromConfigFile();
            }
            else
            {
                InitializeCamerasFromSerialPort();
            }
        }

        /// <summary>
        /// Populates the data grid view with details of cameras connected such as Port number, Manufacturer, 
        /// Camera model, Camera serial number.
        /// </summary>
        void PopulateDataGridView()
        {
            try
            {
                string cameraModel;
                string cameraSerialNumber;
                int serialPortNumber;
                string camLabel = "";
                string configFilePath = Globals.CameraSelectorDefaultAppletMCFFile;
                if (noOfCamerasToBeConnected > 0)
                {
                    int rowIndex = 0;
                    if (localSettingsExists)
                    {
                        List<string> camerasToBeConnected = HardwareConfig.Current.GetCameraLabelsFromLocalSettings();
                        for (int i = 0; i < noOfCamerasToBeConnected; i++)
                        {
                            camLabel = camerasToBeConnected[i];

                            CameraConfig camConfigFromFile = HardwareConfig.Current.GetLocalSettingForCamera(camLabel);

                            //int deviceIndex = camConfigFromFile.FGIndex;
                            //int portIndex = camConfigFromFile.PortIndex;

                            //string fgSerNumber = camConfigFromFile.FrameGrabberSerialNumber;

                            //camLabel = "";

                            CameraConfig camConfig = new CameraConfig();
                            camConfig.CameraLabel = camConfigFromFile.CameraLabel;
                            camConfig.FGIndex = camConfigFromFile.FGIndex;
                            camConfig.PortIndex = camConfigFromFile.PortIndex;
                            camConfig.SerialPortIndex = camConfigFromFile.SerialPortIndex;
                            camConfig.CameraManufacturer = camConfigFromFile.CameraManufacturer;
                            camConfig.CameraModel = camConfigFromFile.CameraModel;
                            camConfig.CameraSerialNumber = camConfigFromFile.CameraSerialNumber;
                            camConfig.FrameGrabberSerialNumber = camConfigFromFile.FrameGrabberSerialNumber;
                            cameraConfigurationsQueriedFromSystem.Add(camConfigFromFile);

                            if (this.UpdateStatusMsgEvent != null)
                            {
                                this.UpdateStatusMsgEvent(string.Format("Added {0} camera(s) to the list", i + 1));
                            }

                            AddCameraDetailsToDataGridView(new List<string>(
                                (
                                new string[] {
                         camConfigFromFile.FGIndex.ToString(),
                         camConfigFromFile.FrameGrabberSerialNumber.ToString(),
                         camConfigFromFile.PortIndex.ToString(),
                         camConfigFromFile.SerialPortIndex.ToString(),
                         camConfigFromFile.CameraManufacturer,
                         camConfigFromFile.CameraModel,
                         camConfigFromFile.CameraSerialNumber,
                         ""})), camConfigFromFile.CameraLabel, false, rowIndex);

                            rowIndex++;

                        }
                    }
                    else
                    {
                        rowIndex = 0;
                        for (int i = 0; i < noOfCamerasToBeConnected; i++)
                        {
                            CameraMake camMake = GetCameraInfo(i, out cameraModel, out cameraSerialNumber);
                            if (camMake != CameraMake.None)
                            {
                                int deviceIndex = i / 2;
                                int portIndex = i % 2;

                                FrameGrabberProperties selectedFGProperties = new FrameGrabberProperties();
                                selectedFGProperties.DeviceID = deviceIndex;
                                selectedFGProperties.PortIndex = portIndex;
                                selectedFGProperties.AppletMCFFile = configFilePath;
                                cameraAcquistion.CurrentFGProperties = selectedFGProperties;

                                string fgSerNumber = cameraAcquistion.GetFrameGrabberSerialNumber();

                                camLabel = HardwareConfig.Current.GetCameraLabelAsPerSerialNumber(cameraSerialNumber, fgSerNumber);

                                CameraConfig camConf = new CameraConfig();
                                camConf.CameraLabel = camLabel;
                                camConf.FGIndex = deviceIndex;
                                camConf.PortIndex = portIndex;
                                camConf.SerialPortIndex = i;
                                camConf.CameraManufacturer = camMake.ToString();
                                camConf.CameraModel = cameraModel;
                                camConf.CameraSerialNumber = cameraSerialNumber;
                                camConf.FrameGrabberSerialNumber = fgSerNumber;
                                cameraConfigurationsQueriedFromSystem.Add(camConf);

                                AddCameraDetailsToDataGridView(new List<string>(
                                        (
                                        new string[] {
                             deviceIndex.ToString(),
                             fgSerNumber,
                             portIndex.ToString(),
                             i.ToString(),
                             camMake.ToString(),
                             cameraModel,
                             cameraSerialNumber,
                             ""})), camLabel, cameraAcquistion.IsCameraConnected(), rowIndex);

                                rowIndex++;
                            }
                        }
                    }
                }
                else
                {
                    noCameraConnected = true;
                }
            }
            catch (Exception ex)
            {
                noCameraConnected = true;

                throw new Exception(ex.Message);
            }
        }

        /// <summary>
        /// Adds the camera details to data grid view.
        /// </summary>
        /// <param name="camDetails">The cam details.</param>
        /// <param name="cameraConnected">if set to <c>true</c> [camera connected].</param>
        /// <param name="rowIndex">Index of the row.</param>
        /// <remarks></remarks>
        void AddCameraDetailsToDataGridView(List<string> camDetails, string camLabel, bool cameraConnected, int rowIndex)
        {
            if (this.InvokeRequired)
            {
                Action<List<string>, string, bool, int> actionAddCameraDetails = new Action<List<string>, string, bool, int>(AddCameraDetailsToDataGridView);
                this.Invoke(actionAddCameraDetails, camDetails, camLabel, cameraConnected, rowIndex);
                return;
            }
            this.dgvCameraList.Rows.Add(camDetails.ToArray());
            DataGridViewComboBoxColumn cameraLabelCmb = (DataGridViewComboBoxColumn)this.dgvCameraList.Columns[this.dgvCameraList.ColumnCount - 1];
            if (cameraLabelCmb.Items.Count > 0)
            {
                if (!string.IsNullOrEmpty(camLabel))
                    this.dgvCameraList.Rows[rowIndex].Cells[this.dgvCameraList.ColumnCount - 1].Value = camLabel.ToString();
            }
            if (cameraConnected)
            {
                dgvCameraList.Rows[rowIndex].Cells[0].Style.BackColor = Color.LimeGreen;
            }
            else
            {
                dgvCameraList.Rows[rowIndex].Cells[0].Style.BackColor = Color.Red;
                this.refreshingCameraListNeeded = true;
            }
        }

        /// <summary>
        /// Gets the camera model name and serial number.
        /// </summary>
        /// <param name="portNumber">The port number.</param>
        /// <param name="cameraModel">The camera model.</param>
        /// <param name="cameraSerialNumber">The camera serial number.</param>
        /// <returns></returns>
        private CameraMake GetCameraInfo(int portNumber,
           out string cameraModel,
           out string cameraSerialNumber)
        {
            //this.Text = string.Format("Please wait while detecting the connected cameras...");
            // this.Refresh();
            int retVal;
            IntPtr serialCommRef = new IntPtr();

            retVal = ClserWrapper.clSerialInit((uint)portNumber, ref serialCommRef);

            if (retVal != ClserWrapper.CL_ERR_NO_ERR)
            {
                logger.AppendLog(Severity.Error, string.Format("Cannot initialize serial port : {0}", portNumber));
                cameraModel = "";
                cameraSerialNumber = "";
                ClserWrapper.clSerialClose(serialCommRef);
                return CameraMake.None;
            }

            retVal = ClserWrapper.clSetBaudRate(serialCommRef, ClserWrapper.CL_BAUDRATE_9600);
            if (retVal != ClserWrapper.CL_ERR_NO_ERR)
            {
                logger.AppendLog(Severity.Debug, string.Format("Cannot set baud rate 9600 for serial port {0}", portNumber));
            }

            string bufferDataFromCamera;
            string err;

            // Check whether camera is a "e2v" camera
            string command = Globals.e2vCommandToGetUC4CameraModel + System.Environment.NewLine;

            if (Globals.GetResponseFromSerialPort(serialCommRef,
                                                      (uint)portNumber,
                                                      command,
                                                      out bufferDataFromCamera,
                                                      10, out err))
            {

                char[] splitCharacters = new char[] { '-' };
                string[] cameraInfo = bufferDataFromCamera.Split(splitCharacters, StringSplitOptions.RemoveEmptyEntries);
                if (cameraInfo.Length > 3)
                {
                    cameraSerialNumber = cameraInfo[3];
                    cameraModel = cameraInfo[0];
                    ClserWrapper.clSerialClose(serialCommRef);
                    return CameraMake.e2v;
                }
                else
                {
                    cameraModel = "";
                    cameraSerialNumber = "";
                    ClserWrapper.clSerialClose(serialCommRef);
                    return CameraMake.None;
                }
            }
            cameraModel = "";
            cameraSerialNumber = "";

            ClserWrapper.clSerialClose(serialCommRef);

            return CameraMake.None;
        }


        ///// <summary>
        ///// Gets the response from serial port for JAI camera.This function send the serial commands to the camera and read 
        ///// the response from the camera.
        ///// </summary>
        ///// <param name="serialComRef">The serial communication port reference.</param>
        ///// <param name="portNumber">The serial port number.</param>
        ///// <param name="command">The command.</param>
        ///// <param name="bufferData">The buffer to receive the response from camera.</param>
        ///// <returns></returns>
        //public static bool GetResponseFromSerialPortForJAICamera(IntPtr serialComRef,
        //   uint portNumber,
        //   string command,
        //   int timeout,
        //   out string bufferData,
        //   int delayBeforeReadingResponse)
        //{
        //    char cont = 'y';
        //    bool commandProcessingSuccess = true;
        //    uint numberOfTrials = 0;
        //    do
        //    {
        //        int retVal = ClserWrapper.clFlushPort(serialComRef);
        //        if (retVal != ClserWrapper.CL_ERR_NO_ERR)
        //        {
        //            logger.AppendLog(Severity.Error,
        //               string.Format("Error in flushing serial port {0}. Error code : {1}", portNumber, retVal));
        //            cont = 'y';
        //            bufferData = "";
        //        }

        //        byte[] writeBuffer = System.Text.ASCIIEncoding.ASCII.GetBytes(command);
        //        uint writeBufferSize = (uint)writeBuffer.Length;

        //        retVal = ClserWrapper.clSerialWrite(serialComRef, writeBuffer, ref writeBufferSize,
        //                                            GlobalVariables.SerialCommunicationTimeout);

        //        System.Threading.Thread.Sleep(500);


        //        if (retVal != ClserWrapper.CL_ERR_NO_ERR)
        //        {

        //            logger.AppendLog(Severity.Error,
        //                string.Format("Error in writing command to serial port {0}. Error Code : {1}. Commad written : {2}", portNumber, retVal, command));
        //            commandProcessingSuccess = false;
        //            bufferData = "";
        //        }
        //        else
        //        {
        //            System.Threading.Thread.Sleep(delayBeforeReadingResponse);
        //            uint numBytes = GlobalVariables.DefaultReadWriteBufferSize;
        //            byte[] readBuffer = new byte[GlobalVariables.DefaultReadWriteBufferSize];
        //            IntPtr ipReadBuffer = Marshal.AllocHGlobal(readBuffer.Length);
        //            retVal = ClserWrapper.clSerialRead(serialComRef, ipReadBuffer, ref numBytes,
        //                                               GlobalVariables.SerialCommunicationTimeout);
        //            if (retVal == ClserWrapper.CL_ERR_NO_ERR)
        //            {
        //                Marshal.Copy(ipReadBuffer, readBuffer, 0, (int)numBytes);
        //                readBuffer = readBuffer.Take((int)numBytes).ToArray();
        //                string readBufferContents = System.Text.ASCIIEncoding.ASCII.GetString(readBuffer);
        //                if (readBufferContents.IndexOf("Unknown Command") >= 0)
        //                {
        //                    cont = 'y';
        //                    bufferData = "";
        //                    commandProcessingSuccess = false;
        //                }
        //                else
        //                {
        //                    bufferData = readBufferContents;
        //                    commandProcessingSuccess = true;
        //                    cont = 'n';
        //                }
        //            }
        //            else
        //            {
        //                logger.AppendLog(Severity.Error,
        //                   string.Format("Error in getting response from JAI camera. Reading from serial port {0}. Error code : {1}. Trial Number : {2}. Command sent to camera : {3}",
        //                   portNumber, retVal, numberOfTrials, command));
        //                commandProcessingSuccess = false;
        //                bufferData = "";
        //            }
        //        }
        //    } while ((cont == 'y') && ((numberOfTrials++) < GlobalVariables.SerCommMaximumNumberOfTrialsForGettingResponse));
        //    return commandProcessingSuccess;
        //}

        ///// <summary>
        ///// Gets the response from e2v camera. This function send the serial commands to the camera and read 
        ///// the response from the camera. A maximum of three attempts are made to read the response from camera 
        ///// in case of failures (such as internal error). 
        ///// </summary>
        ///// <param name="serialComRef">The serial communication port reference.</param>
        ///// <param name="portNumber">The serial port number.</param>
        ///// <param name="command">The command.</param>
        ///// <param name="bufferData">The buffer to receive the response from camera.</param>
        ///// <returns></returns>
        //public static bool GetResponseFromSerialPortForE2VCamera(IntPtr serialComRef,
        //    uint portNumber,
        //    string command,
        //    out string bufferData,
        //    int delayBeforeReadingResponse)
        //{
        //    char cont = 'y';
        //    bool commandProcessingSuccess = true;
        //    uint numberOfTrials = 0;
        //    do
        //    {
        //        int retVal = ClserWrapper.clFlushPort(serialComRef);
        //        if (retVal != ClserWrapper.CL_ERR_NO_ERR)
        //        {
        //            logger.AppendLog(Severity.Error,
        //                string.Format("Error in flushing serial port {0}. Error code : {1}", portNumber, retVal));
        //            cont = 'y';
        //            bufferData = "";
        //        }

        //        byte[] writeBuffer = System.Text.ASCIIEncoding.ASCII.GetBytes(command);
        //        uint writeBufferSize = (uint)writeBuffer.Length;

        //        retVal = ClserWrapper.clSerialWrite(serialComRef, writeBuffer, ref writeBufferSize,
        //                                                Globals.SerialCommunicationTimeout);

        //        if (retVal != ClserWrapper.CL_ERR_NO_ERR)
        //        {
        //            logger.AppendLog(Severity.Error,
        //                string.Format("Error in writing command to serial port {0}. Error Code : {1}. Commad written : {2}", portNumber, retVal, command));
        //            cont = 'y';
        //            commandProcessingSuccess = false;
        //            bufferData = "";
        //        }
        //        else
        //        {
        //            System.Threading.Thread.Sleep(delayBeforeReadingResponse);
        //            uint numBytes = Globals.DefaultReadWriteBufferSize;
        //            byte[] readBuffer = new byte[Globals.DefaultReadWriteBufferSize];
        //            IntPtr ipReadBuffer = Marshal.AllocHGlobal(readBuffer.Length);
        //            retVal = ClserWrapper.clSerialRead(serialComRef, ipReadBuffer, ref numBytes,
        //                                               Globals.SerialCommunicationTimeout);
        //            if (retVal == ClserWrapper.CL_ERR_NO_ERR)
        //            {
        //                Marshal.Copy(ipReadBuffer, readBuffer, 0, (int)numBytes);
        //                readBuffer = readBuffer.Take((int)numBytes).ToArray();
        //                string readBufferContents = System.Text.ASCIIEncoding.ASCII.GetString(readBuffer);
        //                if (readBufferContents.IndexOf(">2\r") >= 0 || readBufferContents.IndexOf(">4\r") >= 0 ||
        //                    readBufferContents.IndexOf(">6\r") >= 0 || readBufferContents.IndexOf(">7\r") >= 0)
        //                {
        //                    cont = 'y';
        //                    bufferData = "";
        //                    commandProcessingSuccess = false;
        //                }
        //                else
        //                {
        //                    bufferData = readBufferContents;
        //                    commandProcessingSuccess = true;
        //                    cont = 'n';
        //                }
        //            }
        //            else
        //            {
        //                commandProcessingSuccess = false;
        //                bufferData = "";

        //                logger.AppendLog(Severity.Error,
        //                   string.Format("Error in getting response from E2V camera. Reading from serial port {0}. Error code : {1}. Trial Number : {2}. Command sent to camera : {3}",
        //                   portNumber, retVal, numberOfTrials, command));

        //            }
        //        }
        //    } while ((cont == 'y') && ((numberOfTrials++) < Globals.SerCommMaximumNumberOfTrialsForGettingResponse));
        //    return commandProcessingSuccess;
        //}

        private void OnCameraSelected(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.ColumnIndex == this.dgvCameraList.ColumnCount - 1 || e.RowIndex == -1)
            {
                return;
            }
            int selectedCameraIndex = e.RowIndex;
            int serialPortNo = Convert.ToInt32(dgvCameraList.Rows[selectedCameraIndex].Cells["colSerialPortNo"].Value);

            if (dgvCameraList.Rows[selectedCameraIndex].Cells[0].Style.BackColor == Color.LimeGreen)
            {
                //if (!btnOk.Enabled)
                //{
                //    OnSaveSettingsClicked(sender, new EventArgs());
                //}

                //OnClickOK(sender, new EventArgs());// MessageBox.Show("Camera already connecetd", "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            FrameGrabberProperties fgProps;
            CameraConfig camProps;

            CameraInitializer c = new CameraInitializer(UpdateUIAfterConnectingCamera);
            IAsyncResult r = c.BeginInvoke(serialPortNo, selectedCameraIndex, out fgProps, out camProps, null, null);

            string title = string.Format("Connecting camera at serial Port : {0}", serialPortNo);

            ProgressWindow p = new ProgressWindow(this, title);
            p.ShowDialog(r);
            CameraConnectedEvent.WaitOne();

            if (dgvCameraList.Rows[selectedCameraIndex].Cells[0].Style.BackColor != Color.LimeGreen)
            {
                MessageBox.Show("Please check whether all camera are connected / powered and try to connect again",
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            else
            {
                this.saveSettingsToolStripMenuItem.Enabled = true;
                this.btnFactoryReset.Enabled = true;
                this.btnSendCommand.Enabled = true;
            }
        }

        void UpdateUIAfterConnectingCamera(int serialPortNo, int selectedCameraIndex, out FrameGrabberProperties fgProps, out CameraConfig camConfig)
        {
            fgProps = new FrameGrabberProperties();
            camConfig = new CameraConfig();

            try
            {
                string cameraModel;
                string cameraSerialNumber;
                string camLabel = "";
                string configFilePath = Globals.CameraSelectorDefaultAppletMCFFile;
                CameraMake camMake = GetCameraInfo(serialPortNo, out cameraModel, out cameraSerialNumber);
                if (camMake != CameraMake.None)
                {
                    int deviceIndex = serialPortNo / 2;
                    int portIndex = serialPortNo % 2;

                    FrameGrabberProperties selectedFGProperties = new FrameGrabberProperties();
                    selectedFGProperties.DeviceID = deviceIndex;
                    selectedFGProperties.PortIndex = portIndex;
                    selectedFGProperties.AppletMCFFile = configFilePath;
                    cameraAcquistion.CurrentFGProperties = selectedFGProperties;

                    string fgSerNumber = cameraAcquistion.GetFrameGrabberSerialNumber();


                    camLabel = "";

                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraLabel = camLabel;
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].FGIndex = deviceIndex;
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].PortIndex = portIndex;
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].SerialPortIndex = serialPortNo;
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraManufacturer = camMake.ToString();
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraModel = cameraModel;
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraSerialNumber = cameraSerialNumber;
                    cameraConfigurationsQueriedFromSystem[selectedCameraIndex].FrameGrabberSerialNumber = fgSerNumber;

                    camConfig = this.cameraConfigurationsQueriedFromSystem[selectedCameraIndex];

                    dgvCameraList.Rows[selectedCameraIndex].Cells["colFGIndex"].Value = camConfig.FGIndex.ToString();
                    dgvCameraList.Rows[selectedCameraIndex].Cells["colFGSerialNumber"].Value = camConfig.FrameGrabberSerialNumber.ToString();
                    dgvCameraList.Rows[selectedCameraIndex].Cells["colPort"].Value = camConfig.PortIndex.ToString();
                    dgvCameraList.Rows[selectedCameraIndex].Cells["colSerialPortNo"].Value = camConfig.SerialPortIndex.ToString();
                    dgvCameraList.Rows[selectedCameraIndex].Cells["colCameraManufacturer"].Value = camConfig.CameraManufacturer.ToString();
                    dgvCameraList.Rows[selectedCameraIndex].Cells["colCameraModel"].Value = camConfig.CameraModel;
                    dgvCameraList.Rows[selectedCameraIndex].Cells["colCameraSerialNumber"].Value = camConfig.CameraSerialNumber;

                    dgvCameraList.Rows[selectedCameraIndex].Cells["colCameraLabel"].ReadOnly = false;

                    dgvCameraList.Rows[selectedCameraIndex].Cells[0].Style.BackColor = Color.LimeGreen;

                    camLabel = HardwareConfig.Current.GetCameraLabelAsPerSerialNumber(camConfig.CameraSerialNumber, camConfig.FrameGrabberSerialNumber);
                    if (!string.IsNullOrEmpty(camLabel))
                        this.dgvCameraList.Rows[selectedCameraIndex].Cells[this.dgvCameraList.ColumnCount - 1].Value = camLabel.ToString();
                }
                else
                {
                    camConfig = null;
                }
            }
            catch(Exception ex)
            {
                camConfig = null;
            }
            CameraConnectedEvent.Set();
        }
        void ConnectCameraAtPort(int i, out FrameGrabberProperties fgProps, out CameraConfig camConfig)
        {
            fgProps = new FrameGrabberProperties();
            camConfig = new CameraConfig();
            string cameraModel;
            string cameraSerialNumber;
            string camLabel = "";
            string configFilePath = Globals.CameraSelectorDefaultAppletMCFFile;
            CameraMake cammake = GetCameraInfo(i, out cameraModel, out cameraSerialNumber);
            if (cammake != CameraMake.None)
            {
                int deviceIndex = i / 2;
                int portIndex = i % 2;

                FrameGrabberProperties selectedFGProperties = new FrameGrabberProperties();
                selectedFGProperties.DeviceID = deviceIndex;
                selectedFGProperties.PortIndex = portIndex;
                selectedFGProperties.AppletMCFFile = configFilePath;

                camLabel = "";

                CameraConfig camConf = new CameraConfig();
                camConf.CameraLabel = camLabel;
                camConf.FGIndex = deviceIndex;
                camConf.PortIndex = portIndex;
                camConf.SerialPortIndex = i;
                camConf.CameraManufacturer = cammake.ToString();
                camConf.CameraModel = cameraModel;
                camConf.CameraSerialNumber = cameraSerialNumber;


                fgProps = selectedFGProperties;
                camConfig = camConf;
            }
            else
            {
                camConfig = null;
            }
        }

        private void OnCameraLabelBeingChanged(object sender, EventArgs e)
        {
            this.dgvCameraList.CommitEdit(DataGridViewDataErrorContexts.Commit);
        }

        private void OnEditControlShown(object sender, DataGridViewEditingControlShowingEventArgs e)
        {
            ComboBox cameraLabelComboBox = e.Control as ComboBox;
            if (cameraLabelComboBox == null)
            {
                return;
            }
            {
                cameraLabelComboBox.SelectedValueChanged += new EventHandler(OnCameraLabelSelectedValueChanged);
            }
        }

        /// <summary>
        /// Called when [camera label selected value changed].
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        void OnCameraLabelSelectedValueChanged(object sender, EventArgs e)
        {
            ComboBox cameraLabelComboBox = sender as ComboBox;

            if (cameraLabelComboBox == null)
            {
                return;
            }

            if (cameraLabelComboBox.SelectedItem == null)
            {
                return;
            }

            if (cameraConfigurationsQueriedFromSystem[dgvCameraList.CurrentRow.Index].CameraLabel != cameraLabelComboBox.SelectedItem.ToString())
            {
                this.saveSettingsToolStripMenuItem.Enabled = true;
            }
            cameraConfigurationsQueriedFromSystem[dgvCameraList.CurrentRow.Index].CameraLabel =
                    cameraLabelComboBox.SelectedItem.ToString();
        }

        /// <summary>
        /// Loads the factory settings to camera.
        /// </summary>
        /// <param name="selectedCamIndex">Index of the selected cam.</param>
        /// <remarks></remarks>
        private void LoadFactorySettingsToCamera(int selectedCamIndex)
        {
            string command;
            string bufferDataFromCamera;
            string err;
            int retVal;
            IntPtr serialCommRef = new IntPtr();
            uint selectedPort = (uint)cameraConfigurationsQueriedFromSystem[selectedCamIndex].SerialPortIndex;
            retVal = ClserWrapper.clSerialInit(selectedPort, ref serialCommRef);

            if (retVal != ClserWrapper.CL_ERR_NO_ERR)
            {
                logger.AppendLog(Severity.Error,
                    string.Format("Cannot initialize serial port {0} to load factory settings.", selectedPort));
                MessageBox.Show(string.Format("Cannot initialize serial port {0} to load factory settings.", selectedPort),
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            if (this.UpdateStatusMsgEvent != null)
            {
                this.UpdateStatusMsgEvent(string.Format("Initialized serial port for communication"));
            }


            bool initialSettingsLoadedToCamera = true;

            if(CameraDefaultSettingsCommand.Keys.Count > 0)
            {
                foreach(string val in CameraDefaultSettingsCommand.Values)
                {
                    // Send commands that are specific to e2v UC4 camera
                    command = val + System.Environment.NewLine;
                    initialSettingsLoadedToCamera &= Globals.GetResponseFromSerialPort(serialCommRef,
                    selectedPort, command, out bufferDataFromCamera, Properties.Settings.Default.DelayBetweenCommandsInLoadingInitialSettings, out err);
                    if (!initialSettingsLoadedToCamera)
                    {
                        if (this.UpdateStatusMsgEvent != null)
                        {
                            this.UpdateStatusMsgEvent(string.Format("Failed to send command {0} to camera", command));
                        }

                    }
                    else
                    {
                        if (this.UpdateStatusMsgEvent != null)
                        {
                            this.UpdateStatusMsgEvent(string.Format("Succeded in sending command {0} to camera", command));
                        }

                    }
                }
            }

            if (this.UpdateStatusMsgEvent != null)
            {
                if (initialSettingsLoadedToCamera)
                {
                    this.UpdateStatusMsgEvent(string.Format("Camera default settings has been loaded!!"));
                }
                else
                {
                    this.UpdateStatusMsgEvent(string.Format("Error in loading settings to camera"));
                }
            }
            System.Threading.Thread.Sleep(1000);
            ClserWrapper.clSerialClose(serialCommRef);
            if (this.UpdateStatusMsgEvent != null)
            {
                this.UpdateStatusMsgEvent(string.Format("Serial communication port is closed"));
            }

            System.Threading.Thread.Sleep(1000);
        }

        private void OnClickRefreshCameraList(object sender, EventArgs e)
        {
            this.Text = string.Format("Please wait while detecting the connected cameras...");
            this.Refresh();
            this.Enabled = false;
            refreshingCameraListNeeded = false;

            localSettingsExists = false;

            InitializeCameras();

            this.Text = string.Format("Camera Selector");
            this.Enabled = true;
            this.Refresh(); this.Focus();

            if (this.refreshingCameraListNeeded)
            {
                MessageBox.Show("Camera are loaded from config, double click to connect.",
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                //this.dgvCameraList.Enabled = false;
                this.dgvCameraList.Columns["colCameraLabel"].ReadOnly = true;
                this.dgvCameraList.Enabled = localSettingsExists;
                this.btnOk.Enabled = false;
                this.btnFactoryReset.Enabled = false;
                this.btnSendCommand.Enabled = false;
            }
            else
            {
                if (this.dgvCameraList.RowCount != 0)
                {
                    this.dgvCameraList.Enabled = true;
                    this.dgvCameraList.Columns["colCameraLabel"].ReadOnly = false;
                    this.btnOk.Enabled = true;
                    this.btnFactoryReset.Enabled = true;
                    this.btnSendCommand.Enabled = true;
                    bool enableSave = true;
                    foreach(DataGridViewRow r in dgvCameraList.Rows)
                    {
                        DataGridViewComboBoxCell c = (DataGridViewComboBoxCell)this.dgvCameraList.Rows[r.Index].Cells[dgvCameraList.ColumnCount - 1];
                        if (String.IsNullOrEmpty(c.Value.ToString()))
                        {
                            enableSave = false;
                        }
                    }
                    this.saveSettingsToolStripMenuItem.Enabled = enableSave;
                }
                else
                {
                    MessageBox.Show("Please check whether all camera are connected / powered and click \"Refresh Camera List\".",
                    "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    this.dgvCameraList.Enabled = false;
                    this.btnOk.Enabled = false;
                    this.btnFactoryReset.Enabled = false;
                    this.btnSendCommand.Enabled = false;
                }
            }

            if (!localSettingsExists || noCameraConnected)
            {
                this.btnOk.Enabled = false;
            }
        }

        private void OnClickCancelButton(object sender, EventArgs e)
        {
            this.Close();
        }

        private void saveSettingsToolStripMenuItem_EnabledChanged(object sender, EventArgs e)
        {
            btnOk.Enabled = !saveSettingsToolStripMenuItem.Enabled;
        }

        private void OnSaveSettingsClicked(object sender, EventArgs e)
        {
            // Check whether all cameras are labeled
            for (int i = 0; i <= this.dgvCameraList.RowCount - 1; i++)
            {
                DataGridViewComboBoxCell camLabelCmb = this.dgvCameraList.Rows[i].Cells[this.dgvCameraList.ColumnCount - 1] as DataGridViewComboBoxCell;
                if (camLabelCmb != null)
                {
                    if (string.IsNullOrEmpty(camLabelCmb.Value.ToString()))
                    {
                        //MessageBox.Show("Please select labels for all cameras.", "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
            }

            // Check whether the same camera label has been selected for more than one camera
            int cameraLabelIndex = this.dgvCameraList.ColumnCount - 1;
            for (int i = 0; i <= this.dgvCameraList.RowCount - 1; i++)
            {
                string firstCameraLabel = this.dgvCameraList[cameraLabelIndex, i].Value.ToString();
                for (int j = i + 1; j < this.dgvCameraList.RowCount; j++)
                {
                    string secondCameraLabel = this.dgvCameraList[cameraLabelIndex, j].Value.ToString();
                    if (firstCameraLabel.CompareTo(secondCameraLabel) == 0)
                    {
                        MessageBox.Show("Cannot select the same label for two cameras",
                        "Camera Setup Tool",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Warning);
                        return;
                    }
                }
            }

            // Check whether local settings already exists or not
            if (localSettingsExists)
            {
                foreach (CameraConfig cameraItem in this.cameraConfigurationsQueriedFromSystem)
                {
                    string camSerialNumber = cameraItem.CameraSerialNumber;
                    string fgSerialNumber = cameraItem.FrameGrabberSerialNumber;

                    bool serialNumberMatching = false;
                    CameraConfig selectedCamera = null;
                    foreach (CameraConfig cameraItemSaved in HardwareConfig.Current.LocalSetting)
                    {
                        if (cameraItem.CameraLabel.Equals(cameraItemSaved.CameraLabel))
                        {
                            if ((cameraItem.CameraSerialNumber.Equals(cameraItemSaved.CameraSerialNumber)) &&
                                (cameraItem.FrameGrabberSerialNumber.Equals(cameraItemSaved.FrameGrabberSerialNumber)))
                            {
                                serialNumberMatching = true;
                                selectedCamera = cameraItemSaved;
                                break;
                            }
                        }
                    }
                    if (serialNumberMatching)
                    {
                        cameraItem.CameraID = selectedCamera.CameraID;
                        cameraItem.CameraType = selectedCamera.CameraType;
                        cameraItem.MinimumGrayLevel = selectedCamera.MinimumGrayLevel;
                        cameraItem.MaximumGrayLevel = selectedCamera.MaximumGrayLevel;
                        cameraItem.BrightRegionReferenceGrayLevel = selectedCamera.BrightRegionReferenceGrayLevel;
                        cameraItem.DarkRegionReferenceGrayLevel = selectedCamera.DarkRegionReferenceGrayLevel;
                        cameraItem.BrightRegionMinimumThresholdLevel = selectedCamera.BrightRegionMinimumThresholdLevel;
                        cameraItem.BrightRegionMaximumThresholdLevel = selectedCamera.BrightRegionMaximumThresholdLevel;
                        cameraItem.DarkRegionMinimumThresholdLevel = selectedCamera.DarkRegionMinimumThresholdLevel;
                        cameraItem.DarkRegionMaximumThresholdLevel = selectedCamera.DarkRegionMaximumThresholdLevel;
                        cameraItem.NumberOfPixelsToBeClippedAtLeft = selectedCamera.NumberOfPixelsToBeClippedAtLeft;
                        cameraItem.NumberOfPixelsToBeClippedAtRight = selectedCamera.NumberOfPixelsToBeClippedAtRight;
                        cameraItem.FFCWidthOfRegionToDetectDarkDefects = selectedCamera.FFCWidthOfRegionToDetectDarkDefects;
                        cameraItem.FFCMaximumDeviationAllowed = selectedCamera.FFCMaximumDeviationAllowed;
                        cameraItem.IPAAppletParametersDefaultConfigFile = selectedCamera.IPAAppletParametersDefaultConfigFile;
                        cameraItem.CameraHeightReferenceLowerLimit = selectedCamera.CameraHeightReferenceLowerLimit;
                        cameraItem.CameraHeightReferenceUpperLimit = selectedCamera.CameraHeightReferenceUpperLimit;
                    }
                    else
                    {
                        CameraConfig masterSettingOfSelectedCamera = HardwareConfig.Current.GetMasterSettingForCamera(cameraItem.CameraLabel);
                        cameraItem.CameraID = masterSettingOfSelectedCamera.CameraID;
                        cameraItem.CameraType = masterSettingOfSelectedCamera.CameraType;
                        cameraItem.MinimumGrayLevel = masterSettingOfSelectedCamera.MinimumGrayLevel;
                        cameraItem.MaximumGrayLevel = masterSettingOfSelectedCamera.MaximumGrayLevel;
                        cameraItem.BrightRegionReferenceGrayLevel = masterSettingOfSelectedCamera.BrightRegionReferenceGrayLevel;
                        cameraItem.DarkRegionReferenceGrayLevel = masterSettingOfSelectedCamera.DarkRegionReferenceGrayLevel;
                        cameraItem.BrightRegionMinimumThresholdLevel = masterSettingOfSelectedCamera.BrightRegionMinimumThresholdLevel;
                        cameraItem.BrightRegionMaximumThresholdLevel = masterSettingOfSelectedCamera.BrightRegionMaximumThresholdLevel;
                        cameraItem.DarkRegionMinimumThresholdLevel = masterSettingOfSelectedCamera.DarkRegionMinimumThresholdLevel;
                        cameraItem.DarkRegionMaximumThresholdLevel = masterSettingOfSelectedCamera.DarkRegionMaximumThresholdLevel;
                        cameraItem.NumberOfPixelsToBeClippedAtLeft = masterSettingOfSelectedCamera.NumberOfPixelsToBeClippedAtLeft;
                        cameraItem.NumberOfPixelsToBeClippedAtRight = masterSettingOfSelectedCamera.NumberOfPixelsToBeClippedAtRight;
                        cameraItem.FFCWidthOfRegionToDetectDarkDefects = masterSettingOfSelectedCamera.FFCWidthOfRegionToDetectDarkDefects;
                        cameraItem.FFCMaximumDeviationAllowed = masterSettingOfSelectedCamera.FFCMaximumDeviationAllowed;
                        cameraItem.IPAAppletParametersDefaultConfigFile = masterSettingOfSelectedCamera.IPAAppletParametersDefaultConfigFile;
                        cameraItem.CameraHeightReferenceLowerLimit = masterSettingOfSelectedCamera.CameraHeightReferenceLowerLimit;
                        cameraItem.CameraHeightReferenceUpperLimit = masterSettingOfSelectedCamera.CameraHeightReferenceUpperLimit;
                    }
                }
            }
            else
            {
                foreach (CameraConfig cameraItem in this.cameraConfigurationsQueriedFromSystem)
                {
                    CameraConfig masterSettingOfSelectedCamera = HardwareConfig.Current.GetMasterSettingForCamera(cameraItem.CameraLabel);
                    cameraItem.CameraID = masterSettingOfSelectedCamera.CameraID;
                    cameraItem.CameraType = masterSettingOfSelectedCamera.CameraType;
                    cameraItem.MinimumGrayLevel = masterSettingOfSelectedCamera.MinimumGrayLevel;
                    cameraItem.MaximumGrayLevel = masterSettingOfSelectedCamera.MaximumGrayLevel;
                    cameraItem.BrightRegionReferenceGrayLevel = masterSettingOfSelectedCamera.BrightRegionReferenceGrayLevel;
                    cameraItem.DarkRegionReferenceGrayLevel = masterSettingOfSelectedCamera.DarkRegionReferenceGrayLevel;
                    cameraItem.BrightRegionMinimumThresholdLevel = masterSettingOfSelectedCamera.BrightRegionMinimumThresholdLevel;
                    cameraItem.BrightRegionMaximumThresholdLevel = masterSettingOfSelectedCamera.BrightRegionMaximumThresholdLevel;
                    cameraItem.DarkRegionMinimumThresholdLevel = masterSettingOfSelectedCamera.DarkRegionMinimumThresholdLevel;
                    cameraItem.DarkRegionMaximumThresholdLevel = masterSettingOfSelectedCamera.DarkRegionMaximumThresholdLevel;
                    cameraItem.NumberOfPixelsToBeClippedAtLeft = masterSettingOfSelectedCamera.NumberOfPixelsToBeClippedAtLeft;
                    cameraItem.NumberOfPixelsToBeClippedAtRight = masterSettingOfSelectedCamera.NumberOfPixelsToBeClippedAtRight;
                    cameraItem.FFCWidthOfRegionToDetectDarkDefects = masterSettingOfSelectedCamera.FFCWidthOfRegionToDetectDarkDefects;
                    cameraItem.FFCMaximumDeviationAllowed = masterSettingOfSelectedCamera.FFCMaximumDeviationAllowed;
                    cameraItem.IPAAppletParametersDefaultConfigFile = masterSettingOfSelectedCamera.IPAAppletParametersDefaultConfigFile;
                    cameraItem.CameraHeightReferenceLowerLimit = masterSettingOfSelectedCamera.CameraHeightReferenceLowerLimit;
                    cameraItem.CameraHeightReferenceUpperLimit = masterSettingOfSelectedCamera.CameraHeightReferenceUpperLimit;
                }
            }

            // Update local settings 
            try
            {
                HardwareConfig.Current.LocalSetting.Clear();
                HardwareConfig.Current.LocalSetting.AddRange(this.cameraConfigurationsQueriedFromSystem);
                HardwareConfig.Current.SaveCameraConfiguration();

                //MessageBox.Show("Camera configuration has been saved.",
                //    "Camera Setup Tool",
                //    MessageBoxButtons.OK,
                //    MessageBoxIcon.Information);

                this.saveSettingsToolStripMenuItem.Enabled = false;

                OnClickOK(sender, new EventArgs());
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(string.Format("Exception occurred while saving camera configuration. Error Message : {0}", ex.Message),
                     "Camera Setup Tool",
                      MessageBoxButtons.OK,
                      MessageBoxIcon.Error);

                this.saveSettingsToolStripMenuItem.Enabled = true;
            }
        }

        /// <summary>
        /// Called when [click OK].
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="System.EventArgs"/> instance containing the event data.</param>
        private void OnClickOK(object sender, EventArgs e)
        {
            // Check whether all cameras are labeled
            for (int i = 0; i <= this.dgvCameraList.RowCount - 1; i++)
            {
                DataGridViewComboBoxCell camLabelCmb = this.dgvCameraList.Rows[i].Cells[this.dgvCameraList.ColumnCount - 1] as DataGridViewComboBoxCell;
                if (camLabelCmb != null)
                {
                    if (string.IsNullOrEmpty(camLabelCmb.Value.ToString()))
                    {
                        MessageBox.Show("Please select labels for all cameras.", "Camera Setup Tool", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                }
            }

            // Check whether the same camera label has been selected for more than one camera
            int cameraLabelIndex = this.dgvCameraList.ColumnCount - 1;
            for (int i = 0; i <= this.dgvCameraList.RowCount - 1; i++)
            {
                string firstCameraLabel = this.dgvCameraList[cameraLabelIndex, i].Value.ToString();
                for (int j = i + 1; j < this.dgvCameraList.RowCount; j++)
                {
                    string secondCameraLabel = this.dgvCameraList[cameraLabelIndex, j].Value.ToString();
                    if (firstCameraLabel.CompareTo(secondCameraLabel) == 0)
                    {
                        MessageBox.Show("Cannot select the same label for two cameras",
                        "Camera Setup Tool",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Warning);
                        return;
                    }
                }
            }

            // Check whether local settings already exists or not
            if (localSettingsExists)
            {
                foreach (CameraConfig cameraItem in this.cameraConfigurationsQueriedFromSystem)
                {
                    foreach (CameraConfig cameraItemSaved in HardwareConfig.Current.LocalSetting)
                    {
                        if (cameraItem.CameraLabel == cameraItemSaved.CameraLabel)
                        {
                            cameraItem.CameraID = cameraItemSaved.CameraID;
                            cameraItem.CameraType = cameraItemSaved.CameraType;
                            cameraItem.MinimumGrayLevel = cameraItemSaved.MinimumGrayLevel;
                            cameraItem.MaximumGrayLevel = cameraItemSaved.MaximumGrayLevel;
                            cameraItem.BrightRegionReferenceGrayLevel = cameraItemSaved.BrightRegionReferenceGrayLevel;
                            cameraItem.DarkRegionReferenceGrayLevel = cameraItemSaved.DarkRegionReferenceGrayLevel;
                            cameraItem.BrightRegionMinimumThresholdLevel = cameraItemSaved.BrightRegionMinimumThresholdLevel;
                            cameraItem.BrightRegionMaximumThresholdLevel = cameraItemSaved.BrightRegionMaximumThresholdLevel;
                            cameraItem.DarkRegionMinimumThresholdLevel = cameraItemSaved.DarkRegionMinimumThresholdLevel;
                            cameraItem.DarkRegionMaximumThresholdLevel = cameraItemSaved.DarkRegionMaximumThresholdLevel;
                            cameraItem.NumberOfPixelsToBeClippedAtLeft = cameraItemSaved.NumberOfPixelsToBeClippedAtLeft;
                            cameraItem.NumberOfPixelsToBeClippedAtRight = cameraItemSaved.NumberOfPixelsToBeClippedAtRight;
                            cameraItem.FFCWidthOfRegionToDetectDarkDefects = cameraItemSaved.FFCWidthOfRegionToDetectDarkDefects;
                            cameraItem.FFCMaximumDeviationAllowed = cameraItemSaved.FFCMaximumDeviationAllowed;
                            cameraItem.IPAAppletParametersDefaultConfigFile = cameraItemSaved.IPAAppletParametersDefaultConfigFile;
                            cameraItem.CameraHeightReferenceLowerLimit = cameraItemSaved.CameraHeightReferenceLowerLimit;
                            cameraItem.CameraHeightReferenceUpperLimit = cameraItemSaved.CameraHeightReferenceUpperLimit;
                            break;
                        }
                    }
                }
            }
            else
            {
                foreach (CameraConfig cameraItem in this.cameraConfigurationsQueriedFromSystem)
                {
                    CameraConfig masterSettingOfSelectedCamera = HardwareConfig.Current.GetMasterSettingForCamera(cameraItem.CameraLabel);
                    cameraItem.CameraID = masterSettingOfSelectedCamera.CameraID;
                    cameraItem.CameraType = masterSettingOfSelectedCamera.CameraType;
                    cameraItem.MinimumGrayLevel = masterSettingOfSelectedCamera.MinimumGrayLevel;
                    cameraItem.MaximumGrayLevel = masterSettingOfSelectedCamera.MaximumGrayLevel;
                    cameraItem.BrightRegionReferenceGrayLevel = masterSettingOfSelectedCamera.BrightRegionReferenceGrayLevel;
                    cameraItem.DarkRegionReferenceGrayLevel = masterSettingOfSelectedCamera.DarkRegionReferenceGrayLevel;
                    cameraItem.BrightRegionMinimumThresholdLevel = masterSettingOfSelectedCamera.BrightRegionMinimumThresholdLevel;
                    cameraItem.BrightRegionMaximumThresholdLevel = masterSettingOfSelectedCamera.BrightRegionMaximumThresholdLevel;
                    cameraItem.DarkRegionMinimumThresholdLevel = masterSettingOfSelectedCamera.DarkRegionMinimumThresholdLevel;
                    cameraItem.DarkRegionMaximumThresholdLevel = masterSettingOfSelectedCamera.DarkRegionMaximumThresholdLevel;
                    cameraItem.NumberOfPixelsToBeClippedAtLeft = masterSettingOfSelectedCamera.NumberOfPixelsToBeClippedAtLeft;
                    cameraItem.NumberOfPixelsToBeClippedAtRight = masterSettingOfSelectedCamera.NumberOfPixelsToBeClippedAtRight;
                    cameraItem.FFCWidthOfRegionToDetectDarkDefects = masterSettingOfSelectedCamera.FFCWidthOfRegionToDetectDarkDefects;
                    cameraItem.FFCMaximumDeviationAllowed = masterSettingOfSelectedCamera.FFCMaximumDeviationAllowed;
                    cameraItem.IPAAppletParametersDefaultConfigFile = masterSettingOfSelectedCamera.IPAAppletParametersDefaultConfigFile;
                    cameraItem.CameraHeightReferenceLowerLimit = masterSettingOfSelectedCamera.CameraHeightReferenceLowerLimit;
                    cameraItem.CameraHeightReferenceUpperLimit = masterSettingOfSelectedCamera.CameraHeightReferenceUpperLimit;
                }
            }

            if (dgvCameraList.SelectedCells.Count == 0)
            {
                if (dgvCameraList.Rows.Count == 0)
                {
                    MessageBox.Show("No cameras detected. Please connect the cameras and click \"Refresh Camera List\".",
                        "Camera Setup Tool",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Warning);
                }
                else
                {
                    MessageBox.Show("Please select a camera and try again.",
                        "Camera Setup Tool",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Warning);
                }
                return;
            }
            int selectedCameraIndex = this.dgvCameraList.SelectedCells[0].RowIndex;
            bool selectedCameraSetupConfigExists = false;
            CameraSetupConfig selectedCameraSetupProperties = new CameraSetupConfig();
            if (ImagingSetupConfig.ImagingSetupConfigurationExists())
            {
                ImagingSetupConfig.Current.ReadImagingSetupConfiguration();
                foreach (CameraSetupConfig cameraSetupItem in ImagingSetupConfig.Current.LocalImagingSetupConfig)
                {
                    if (cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraLabel.Equals(cameraSetupItem.CameraLabel))
                    {
                        selectedCameraSetupProperties.CameraLabel = cameraSetupItem.CameraLabel;
                        selectedCameraSetupProperties.CameraID = cameraSetupItem.CameraID;
                        selectedCameraSetupProperties.FocusMaxAutoCorrelationValue = cameraSetupItem.FocusMaxAutoCorrelationValue;
                        selectedCameraSetupProperties.MagnificationPercentage = cameraSetupItem.MagnificationPercentage;
                        selectedCameraSetupProperties.PixelResolution = cameraSetupItem.PixelResolution;
                        selectedCameraSetupProperties.MinimumGrayValue = cameraSetupItem.MinimumGrayValue;
                        selectedCameraSetupProperties.MaximumGrayValue = cameraSetupItem.MaximumGrayValue;
                        selectedCameraSetupProperties.DistanceFromMipdInMM = cameraSetupItem.DistanceFromMipdInMM;
                        selectedCameraSetupProperties.CalibrationPatternTotalWidth = cameraSetupItem.CalibrationPatternTotalWidth;
                        selectedCameraSetupProperties.FFCEnabled = cameraSetupItem.FFCEnabled;
                        selectedCameraSetupProperties.LastFFCSavingDate = cameraSetupItem.LastFFCSavingDate;
                        selectedCameraSetupProperties.LastOnCameraFFCSavingDate = cameraSetupItem.LastOnCameraFFCSavingDate;
                        selectedCameraSetupConfigExists = true;
                        break;
                    }
                }
            }
            if (!selectedCameraSetupConfigExists)
            {
                selectedCameraSetupProperties.CameraLabel = cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraLabel;
                selectedCameraSetupProperties.CameraID = cameraConfigurationsQueriedFromSystem[selectedCameraIndex].CameraID;
                selectedCameraSetupProperties.LastFFCSavingDate = "FFC not yet done";
                selectedCameraSetupProperties.LastOnCameraFFCSavingDate = "On Camera FFC not yet done";
            }

            FrameGrabberProperties selectedFGProperties = new FrameGrabberProperties();
            selectedFGProperties.DeviceID = (int)cameraConfigurationsQueriedFromSystem[selectedCameraIndex].FGIndex;
            selectedFGProperties.PortIndex = (int)cameraConfigurationsQueriedFromSystem[selectedCameraIndex].PortIndex;
            selectedFGProperties.AppletMCFFile = Globals.CameraSelectorDefaultAppletMCFFile;

            cameraAcquistion.CurrentFGProperties = selectedFGProperties;
            CameraConfig selectedCameraProperties = cameraConfigurationsQueriedFromSystem[selectedCameraIndex];
            cameraAcquistion.CurrentCameraProperties = selectedCameraProperties;
            cameraAcquistion.CurrentCameraSetupConfigExists = selectedCameraSetupConfigExists;
            cameraAcquistion.CurrentCameraSetupProperties = selectedCameraSetupProperties;
            this.DialogResult = DialogResult.OK;
            frmMain frm = new frmMain();
            frm.cameraAcq = this.cameraAcquistion;
            frm.WindowState = FormWindowState.Maximized;
            frm.Show();
            this.Hide();
        }

        private void frmCameraList_FormClosing(object sender, FormClosingEventArgs e)
        {
            //cameraAcquistion.StopGrabbing = false;
            //System.Threading.Thread.Sleep(1000);
        }

        private void btnSendCommand_Click(object sender, EventArgs e)
        {
            if(dgvCameraList.Rows.Count != 0)
            {
                //DataGridViewRow r = dgvCameraList.SelectedCells[0].OwningRow;
                //int cameraPortNo = Convert.ToInt32(r.Cells[2].Value);
                frmCommandWindow frm = new frmCommandWindow(this.cameraAcquistion.CurrentCameraProperties.SerialPortIndex);
                frm.StartPosition = FormStartPosition.CenterScreen;
                frm.ShowDialog();
            }
        }

        private void OnFactoryResetClicked(object sender, EventArgs e)
        {
            if (dgvCameraList.SelectedCells.Count == 0)
            {
                if (dgvCameraList.Rows.Count == 0)
                {
                    MessageBox.Show("No cameras detected. Please connect the cameras and click \"Refresh Camera List\".",
                        "Imaging Setup Utility",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Warning);
                }
                else
                {
                    MessageBox.Show("Please select a camera and try again.",
                        "Imaging Setup Utility",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Warning);
                }
                return;
            }
            int selectedCameraIndex = this.dgvCameraList.CurrentCell.RowIndex;

            Action<int> del = new Action<int>(LoadFactorySettingsToCamera);
            IAsyncResult asyncResult = del.BeginInvoke(selectedCameraIndex, null, null);

            ProgressWindow progressBarForm = new ProgressWindow(this, "Loading Factory Settings to camera... Please wait...");
            progressBarForm.ShowDialog(asyncResult);
        }
    }
}