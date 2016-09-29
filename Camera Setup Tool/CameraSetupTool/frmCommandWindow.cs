using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace CameraSetupTool
{
    public partial class frmCommandWindow : Form
    {
        public frmCommandWindow(int CameraPortID)
        {
            InitializeComponent();
            this.CameraPortID = CameraPortID;
            txtCommand.AutoCompleteMode = AutoCompleteMode.SuggestAppend;
            txtCommand.AutoCompleteSource = AutoCompleteSource.CustomSource;
            txtCommand.AutoCompleteCustomSource = CameraSerialCommand.CurrentInstance.CommandsSuggestions;
        }

        int CameraPortID;

        private void btnSendCommand_Click(object sender, EventArgs e)
        {
            try
            {
                if(txtCommand.Text.Trim() == "")
                {
                    WriteOutput("Incorrect command");
                    return;
                }
                string command = txtCommand.Text.Trim() + Environment.NewLine;
                string buffer;
                Globals.ExecuteSerialCommand((uint)CameraPortID, command, out buffer);
                WriteOutput(buffer);
                if (buffer.Contains("Ok"))
                {
                    CameraSerialCommand.CurrentInstance.AddCommandToCommandFile(command);
                    CameraSerialCommand.CurrentInstance.RefreshCommandsSuggestionList();
                }
            }
            catch(Exception ex)
            {
                WriteOutput(ex.Message);
            }
        }

        void WriteOutput(string msg)
        {
            int index = msg.IndexOf(">");
            if (index > 0)
                msg = msg.Substring(0, index);

            txtResponse.Text += msg;
        }

        private void txtResponse_TextChanged(object sender, EventArgs e)
        {
            txtResponse.SelectionStart = txtResponse.Text.Length;
            txtResponse.ScrollToCaret();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtResponse.Clear();
            txtCommand.Clear();
        }

        private void OnEscapeKeyPressed(object sender, KeyEventArgs e)
        {
            if(e.KeyCode == Keys.Escape)
            {
                this.Close();
            }
        }
    }

    public class CameraSerialCommand
    {
        private CameraSerialCommand()
        {
            cameracommands = GetCameraCommandSuggestions();
        }

        private static string CameraCommandSuggestionFilePath = Application.StartupPath + "\\Config\\CameraComands.ac";

        private AutoCompleteStringCollection GetCameraCommandSuggestions()
        {
            AutoCompleteStringCollection commands = new AutoCompleteStringCollection();
            try
            {
                commands.AddRange(System.IO.File.ReadAllLines(CameraCommandSuggestionFilePath));
            }
            catch(System.IO.FileNotFoundException ex)
            {
                if (!System.IO.File.Exists(CameraCommandSuggestionFilePath))
                {
                    FileStream a = File.Create(CameraCommandSuggestionFilePath);
                    a.Close();
                }
                commands.AddRange(System.IO.File.ReadAllLines(CameraCommandSuggestionFilePath));
            }
            catch(Exception ex)
            {
                commands = null;
            }
            return commands;
        }

        private static CameraSerialCommand instance;

        public static CameraSerialCommand CurrentInstance
        {
            get
            {
                if (instance == null)
                {
                    instance = new CameraSerialCommand();
                }
                return instance;
            }
        }

        private AutoCompleteStringCollection cameracommands;

        public AutoCompleteStringCollection CommandsSuggestions
        {
            get
            {
                if (cameracommands != null)
                    cameracommands = GetCameraCommandSuggestions();

                return cameracommands;
            }
        }

        public bool CheckForCommandExistence(string command)
        {
            bool exists = false;
            string[] cmd = command.Split(new char[] {' '});
            command = cmd[0] + " " + cmd[1];
            if (cameracommands.Contains(command))
            {
                exists = true;
            }
            return exists;
        }

        public bool AddCommandToCommandFile(string command)
        {
            bool success = true;
            try
            {
                if (!CheckForCommandExistence(command))
                {
                    System.IO.File.AppendAllText(CameraCommandSuggestionFilePath, command);
                }
            }
            catch
            {
                success = false;
            }
            return success;
        }

        public bool RefreshCommandsSuggestionList()
        {
            bool success = true;
            try
            {
                cameracommands.AddRange(System.IO.File.ReadAllLines(CameraCommandSuggestionFilePath));
            }
            catch
            {
                success = false;
            }
            return success;
        }
    }
}