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
    public partial class ProgressWindow : Form
    {
        /// <summary>
        /// Event that notifies that progress bar form is force closed
        /// </summary>
        System.Threading.AutoResetEvent forceClose = new System.Threading.AutoResetEvent(false);

        /// <summary>
        /// Event that notifies that progress bar form is closed
        /// </summary>
        System.Threading.AutoResetEvent formClosed = new System.Threading.AutoResetEvent(false);

        public ProgressWindow(iProgressWindow parentForm)
        {
            InitializeComponent();

            parentForm.UpdateStatusMsgEvent += new Action<string>(UpdateStatusMessage);
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ProgressBarForm"/> class.
        /// </summary>
        /// <param name="progressHeading">The progress bar heading.</param>
        /// <remarks></remarks>
        public ProgressWindow(string progressHeading)
        {
            InitializeComponent();
            lblStatusMessage.Text = progressHeading;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="ProgressBarForm"/> class.
        /// </summary>
        /// <param name="parentForm">The parent form.</param>
        /// <param name="progressHeading">The progress bar heading.</param>
        /// <remarks></remarks>
        public ProgressWindow(iProgressWindow parentForm, string progressHeading)
        {
            InitializeComponent();
            this.lblStatusMessage.Text = progressHeading;
            parentForm.UpdateStatusMsgEvent += new Action<string>(UpdateStatusMessage);
        }

        /// <summary>
        /// Gets or sets the heading.
        /// </summary>
        /// <value>The heading.</value>
        /// <remarks></remarks>
        public string Heading
        {
            get { return lblStatusMessage.Text; }
            set { lblStatusMessage.Text = value; }
        }

        /// <summary>
        /// Gets a value indicating whether the window will be activated when it is shown.
        /// </summary>
        /// <returns>True if the window will not be activated when it is shown; otherwise, false. The default is false.</returns>
        /// <remarks></remarks>
        protected override bool ShowWithoutActivation
        {
            get
            {
                return true;
            }
        }

        /// <summary>
        /// Shows the dialog.
        /// </summary>
        /// <param name="asyncResult">The async result.</param>
        /// <returns></returns>
        /// <remarks></remarks>
        public DialogResult ShowDialog(IAsyncResult asyncResult)
        {
            new Action<IAsyncResult>(CloseWhenRequired).BeginInvoke(asyncResult, null, null);
            return base.ShowDialog();
        }

        public new DialogResult ShowDialog()
        {
            return base.ShowDialog();
        }

        /// <summary>
        /// Updates the status message in the progress bar form.
        /// </summary>
        /// <param name="statusMsg">The status MSG.</param>
        /// <remarks></remarks>
        void UpdateStatusMessage(string statusMsg)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new Action<string>(UpdateStatusMessage), statusMsg);
                return;
            }
            this.lblStatusMessage.Text = statusMsg;
        }

        /// <summary>
        /// Closes the form when required.
        /// </summary>
        /// <param name="asyncResult">The async result.</param>
        /// <remarks></remarks>
        private void CloseWhenRequired(IAsyncResult asyncResult)
        {
            System.Threading.WaitHandle[] closeSignals = new System.Threading.WaitHandle[] { asyncResult.AsyncWaitHandle, this.forceClose };
            System.Threading.WaitHandle.WaitAny(closeSignals);
            if(!this.IsDisposed)
                this.Invoke(new Action(this.Close));
            this.formClosed.Set();
        }

        /// <summary>
        /// Force close the form.
        /// </summary>
        /// <remarks></remarks>
        public void ForceClose()
        {
            this.forceClose.Set();
            this.formClosed.WaitOne(-1);
        }
    }
}
