namespace CameraSetupTool
{
    partial class frmCameraList
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            this.cameraAcquistion.ImageGrabbed -= new ImageGrabbedHandler(OnImageGrabbedFromSelectedCamera);
            while (!this.cameraAcquistion.StopGrabbing())
            {
                return;
            }
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmCameraList));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.btnCancel = new System.Windows.Forms.Button();
            this.btnOk = new System.Windows.Forms.Button();
            this.btnSendCommand = new System.Windows.Forms.Button();
            this.btnFactoryReset = new System.Windows.Forms.Button();
            this.pnlDataGrid = new System.Windows.Forms.Panel();
            this.dgvCameraList = new System.Windows.Forms.DataGridView();
            this.colFGIndex = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colFGSerialNumber = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colPort = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colSerialPortNo = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCameraManufacturer = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCameraModel = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCameraSerialNumber = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colCameraLabel = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuRefreshList = new System.Windows.Forms.ToolStripMenuItem();
            this.saveSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.cameraSelectorImageWindow = new HalconDotNet.HWindowControl();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.pnlDataGrid.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dgvCameraList)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel5, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.pnlDataGrid, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.menuStrip1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.groupBox1, 0, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 4;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 17.59657F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 82.40343F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 220F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 67F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(745, 515);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.ColumnCount = 5;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 122F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 122F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 122F));
            this.tableLayoutPanel5.Controls.Add(this.btnCancel, 4, 0);
            this.tableLayoutPanel5.Controls.Add(this.btnOk, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.btnSendCommand, 3, 0);
            this.tableLayoutPanel5.Controls.Add(this.btnFactoryReset, 2, 0);
            this.tableLayoutPanel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel5.Location = new System.Drawing.Point(2, 449);
            this.tableLayoutPanel5.Margin = new System.Windows.Forms.Padding(2);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 1;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(741, 64);
            this.tableLayoutPanel5.TabIndex = 3;
            // 
            // btnCancel
            // 
            this.btnCancel.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnCancel.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnCancel.Location = new System.Drawing.Point(631, 8);
            this.btnCancel.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(98, 47);
            this.btnCancel.TabIndex = 0;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            this.btnCancel.Click += new System.EventHandler(this.OnClickCancelButton);
            // 
            // btnOk
            // 
            this.btnOk.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnOk.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnOk.Location = new System.Drawing.Point(113, 8);
            this.btnOk.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnOk.Name = "btnOk";
            this.btnOk.Size = new System.Drawing.Size(98, 47);
            this.btnOk.TabIndex = 0;
            this.btnOk.Text = "OK";
            this.btnOk.UseVisualStyleBackColor = true;
            this.btnOk.Visible = false;
            this.btnOk.Click += new System.EventHandler(this.OnClickOK);
            // 
            // btnSendCommand
            // 
            this.btnSendCommand.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnSendCommand.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSendCommand.Location = new System.Drawing.Point(509, 8);
            this.btnSendCommand.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnSendCommand.Name = "btnSendCommand";
            this.btnSendCommand.Size = new System.Drawing.Size(98, 47);
            this.btnSendCommand.TabIndex = 1;
            this.btnSendCommand.Text = "Send Command";
            this.btnSendCommand.UseVisualStyleBackColor = true;
            this.btnSendCommand.Click += new System.EventHandler(this.btnSendCommand_Click);
            // 
            // btnFactoryReset
            // 
            this.btnFactoryReset.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.btnFactoryReset.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnFactoryReset.Location = new System.Drawing.Point(387, 8);
            this.btnFactoryReset.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.btnFactoryReset.Name = "btnFactoryReset";
            this.btnFactoryReset.Size = new System.Drawing.Size(98, 47);
            this.btnFactoryReset.TabIndex = 1;
            this.btnFactoryReset.Text = "Factory Reset";
            this.btnFactoryReset.UseVisualStyleBackColor = true;
            this.btnFactoryReset.Click += new System.EventHandler(this.OnFactoryResetClicked);
            // 
            // pnlDataGrid
            // 
            this.pnlDataGrid.Controls.Add(this.dgvCameraList);
            this.pnlDataGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlDataGrid.Location = new System.Drawing.Point(3, 42);
            this.pnlDataGrid.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.pnlDataGrid.Name = "pnlDataGrid";
            this.pnlDataGrid.Size = new System.Drawing.Size(739, 183);
            this.pnlDataGrid.TabIndex = 1;
            // 
            // dgvCameraList
            // 
            this.dgvCameraList.AllowUserToAddRows = false;
            this.dgvCameraList.AllowUserToDeleteRows = false;
            this.dgvCameraList.AllowUserToResizeColumns = false;
            this.dgvCameraList.AllowUserToResizeRows = false;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dgvCameraList.AlternatingRowsDefaultCellStyle = dataGridViewCellStyle1;
            this.dgvCameraList.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dgvCameraList.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dgvCameraList.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
            this.dgvCameraList.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvCameraList.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colFGIndex,
            this.colFGSerialNumber,
            this.colPort,
            this.colSerialPortNo,
            this.colCameraManufacturer,
            this.colCameraModel,
            this.colCameraSerialNumber,
            this.colCameraLabel});
            this.dgvCameraList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvCameraList.Location = new System.Drawing.Point(0, 0);
            this.dgvCameraList.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.dgvCameraList.MultiSelect = false;
            this.dgvCameraList.Name = "dgvCameraList";
            dataGridViewCellStyle3.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dgvCameraList.RowsDefaultCellStyle = dataGridViewCellStyle3;
            this.dgvCameraList.RowTemplate.DefaultCellStyle.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.dgvCameraList.RowTemplate.Height = 28;
            this.dgvCameraList.Size = new System.Drawing.Size(739, 183);
            this.dgvCameraList.TabIndex = 2;
            this.dgvCameraList.CellMouseDoubleClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.OnCameraSelected);
            this.dgvCameraList.CurrentCellDirtyStateChanged += new System.EventHandler(this.OnCameraLabelBeingChanged);
            this.dgvCameraList.EditingControlShowing += new System.Windows.Forms.DataGridViewEditingControlShowingEventHandler(this.OnEditControlShown);
            this.dgvCameraList.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.OnCameraSelected);
            // 
            // colFGIndex
            // 
            this.colFGIndex.HeaderText = "Framegrabber Index";
            this.colFGIndex.Name = "colFGIndex";
            this.colFGIndex.ReadOnly = true;
            this.colFGIndex.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // colFGSerialNumber
            // 
            this.colFGSerialNumber.HeaderText = "Framegrabber Serial Number";
            this.colFGSerialNumber.Name = "colFGSerialNumber";
            this.colFGSerialNumber.ReadOnly = true;
            this.colFGSerialNumber.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // colPort
            // 
            this.colPort.HeaderText = "Port";
            this.colPort.Name = "colPort";
            this.colPort.ReadOnly = true;
            this.colPort.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // colSerialPortNo
            // 
            this.colSerialPortNo.HeaderText = "Serial Port No";
            this.colSerialPortNo.Name = "colSerialPortNo";
            this.colSerialPortNo.Visible = false;
            // 
            // colCameraManufacturer
            // 
            this.colCameraManufacturer.HeaderText = "Camera Manufacturer";
            this.colCameraManufacturer.Name = "colCameraManufacturer";
            this.colCameraManufacturer.ReadOnly = true;
            this.colCameraManufacturer.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // colCameraModel
            // 
            this.colCameraModel.HeaderText = "Camera Model";
            this.colCameraModel.Name = "colCameraModel";
            this.colCameraModel.ReadOnly = true;
            this.colCameraModel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // colCameraSerialNumber
            // 
            this.colCameraSerialNumber.HeaderText = "Camera Serial Number";
            this.colCameraSerialNumber.Name = "colCameraSerialNumber";
            this.colCameraSerialNumber.ReadOnly = true;
            this.colCameraSerialNumber.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.NotSortable;
            // 
            // colCameraLabel
            // 
            this.colCameraLabel.HeaderText = "Camera Label";
            this.colCameraLabel.Name = "colCameraLabel";
            this.colCameraLabel.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.colCameraLabel.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.menuStrip1.Font = new System.Drawing.Font("Calibri", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuRefreshList,
            this.saveSettingsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(5, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(745, 40);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuRefreshList
            // 
            this.menuRefreshList.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuRefreshList.Name = "menuRefreshList";
            this.menuRefreshList.Size = new System.Drawing.Size(76, 36);
            this.menuRefreshList.Text = "Refresh List";
            this.menuRefreshList.Click += new System.EventHandler(this.OnClickRefreshCameraList);
            // 
            // saveSettingsToolStripMenuItem
            // 
            this.saveSettingsToolStripMenuItem.Font = new System.Drawing.Font("Tahoma", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.saveSettingsToolStripMenuItem.Name = "saveSettingsToolStripMenuItem";
            this.saveSettingsToolStripMenuItem.Size = new System.Drawing.Size(110, 36);
            this.saveSettingsToolStripMenuItem.Text = "Save and Continue";
            this.saveSettingsToolStripMenuItem.Click += new System.EventHandler(this.OnSaveSettingsClicked);
            this.saveSettingsToolStripMenuItem.EnabledChanged += new System.EventHandler(this.saveSettingsToolStripMenuItem_EnabledChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.cameraSelectorImageWindow);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(3, 229);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.groupBox1.Size = new System.Drawing.Size(739, 216);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Image Window";
            // 
            // cameraSelectorImageWindow
            // 
            this.cameraSelectorImageWindow.BackColor = System.Drawing.Color.Black;
            this.cameraSelectorImageWindow.BorderColor = System.Drawing.Color.Black;
            this.cameraSelectorImageWindow.Dock = System.Windows.Forms.DockStyle.Fill;
            this.cameraSelectorImageWindow.ImagePart = new System.Drawing.Rectangle(0, 0, 640, 480);
            this.cameraSelectorImageWindow.Location = new System.Drawing.Point(3, 16);
            this.cameraSelectorImageWindow.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.cameraSelectorImageWindow.Name = "cameraSelectorImageWindow";
            this.cameraSelectorImageWindow.Size = new System.Drawing.Size(733, 198);
            this.cameraSelectorImageWindow.TabIndex = 1;
            this.cameraSelectorImageWindow.WindowSize = new System.Drawing.Size(733, 198);
            // 
            // frmCameraList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(745, 515);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Font = new System.Drawing.Font("Verdana", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.Name = "frmCameraList";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Available Cameras";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmCameraList_FormClosing);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel5.ResumeLayout(false);
            this.pnlDataGrid.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dgvCameraList)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel pnlDataGrid;
        private System.Windows.Forms.DataGridView dgvCameraList;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuRefreshList;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.Button btnOk;
        private System.Windows.Forms.Button btnFactoryReset;
        private System.Windows.Forms.Button btnSendCommand;
        private System.Windows.Forms.GroupBox groupBox1;
        private HalconDotNet.HWindowControl cameraSelectorImageWindow;
        private System.Windows.Forms.ToolStripMenuItem saveSettingsToolStripMenuItem;
        private System.Windows.Forms.DataGridViewTextBoxColumn colFGIndex;
        private System.Windows.Forms.DataGridViewTextBoxColumn colFGSerialNumber;
        private System.Windows.Forms.DataGridViewTextBoxColumn colPort;
        private System.Windows.Forms.DataGridViewTextBoxColumn colSerialPortNo;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCameraManufacturer;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCameraModel;
        private System.Windows.Forms.DataGridViewTextBoxColumn colCameraSerialNumber;
        private System.Windows.Forms.DataGridViewComboBoxColumn colCameraLabel;


    }
}