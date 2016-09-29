using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CameraSetupTool
{
    public partial class frmInstruction : Form
    {
        public frmInstruction(string msg)
        {
            InitializeComponent();
            this.lblInstruction.Text = msg;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
