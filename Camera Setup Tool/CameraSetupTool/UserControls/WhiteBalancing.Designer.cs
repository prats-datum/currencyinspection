namespace CameraSetupTool.UserControls
{
    partial class WhiteBalancing
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
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WhiteBalancing));
            this.tlpMain = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.btnReset = new System.Windows.Forms.Button();
            this.btnWhiteBalancing = new System.Windows.Forms.Button();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.lblStatus = new System.Windows.Forms.Label();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.lblWBErrorLevel = new System.Windows.Forms.Label();
            this.lblWBBlueMax = new System.Windows.Forms.Label();
            this.lblWBGreenMax = new System.Windows.Forms.Label();
            this.lblWBRedMax = new System.Windows.Forms.Label();
            this.lblWBRefGrayLevel = new System.Windows.Forms.Label();
            this.label43 = new System.Windows.Forms.Label();
            this.label44 = new System.Windows.Forms.Label();
            this.label45 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label39 = new System.Windows.Forms.Label();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btnUpdateRedGain = new System.Windows.Forms.Button();
            this.btnUpdateGreenGain = new System.Windows.Forms.Button();
            this.btnUpdateBlueGain = new System.Windows.Forms.Button();
            this.txtRedGainValue = new System.Windows.Forms.TextBox();
            this.txtGreenGainValue = new System.Windows.Forms.TextBox();
            this.txtBlueGainValue = new System.Windows.Forms.TextBox();
            this.tlpMain.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.SuspendLayout();
            // 
            // tlpMain
            // 
            this.tlpMain.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tlpMain.ColumnCount = 1;
            this.tlpMain.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tlpMain.Controls.Add(this.tableLayoutPanel1, 0, 0);
            this.tlpMain.Controls.Add(this.tableLayoutPanel3, 0, 2);
            this.tlpMain.Controls.Add(this.tableLayoutPanel5, 0, 1);
            this.tlpMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpMain.Location = new System.Drawing.Point(0, 0);
            this.tlpMain.Name = "tlpMain";
            this.tlpMain.RowCount = 3;
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 58.28729F));
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 41.71271F));
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 195F));
            this.tlpMain.Size = new System.Drawing.Size(398, 564);
            this.tlpMain.TabIndex = 0;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 156F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel4, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(8, 8);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(5);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(382, 198);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.btnReset, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.btnWhiteBalancing, 0, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(150, 192);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // btnReset
            // 
            this.btnReset.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnReset.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnReset.Location = new System.Drawing.Point(6, 100);
            this.btnReset.Name = "btnReset";
            this.btnReset.Size = new System.Drawing.Size(138, 86);
            this.btnReset.TabIndex = 1;
            this.btnReset.Text = "Reset";
            this.btnReset.UseVisualStyleBackColor = true;
            this.btnReset.Click += new System.EventHandler(this.OnClickResetWhiteBalancing);
            // 
            // btnWhiteBalancing
            // 
            this.btnWhiteBalancing.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnWhiteBalancing.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnWhiteBalancing.Location = new System.Drawing.Point(6, 6);
            this.btnWhiteBalancing.Name = "btnWhiteBalancing";
            this.btnWhiteBalancing.Size = new System.Drawing.Size(138, 85);
            this.btnWhiteBalancing.TabIndex = 0;
            this.btnWhiteBalancing.Text = "White Balancing";
            this.btnWhiteBalancing.UseVisualStyleBackColor = true;
            this.btnWhiteBalancing.Click += new System.EventHandler(this.OnClickWhiteBalancing);
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tableLayoutPanel4.ColumnCount = 1;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Controls.Add(this.lblStatus, 0, 0);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(159, 3);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 1;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(220, 192);
            this.tableLayoutPanel4.TabIndex = 1;
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblStatus.Font = new System.Drawing.Font("Tahoma", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblStatus.Location = new System.Drawing.Point(6, 3);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(208, 186);
            this.lblStatus.TabIndex = 2;
            this.lblStatus.Text = "Status";
            this.lblStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.lblWBErrorLevel, 1, 4);
            this.tableLayoutPanel3.Controls.Add(this.lblWBBlueMax, 1, 3);
            this.tableLayoutPanel3.Controls.Add(this.lblWBGreenMax, 1, 2);
            this.tableLayoutPanel3.Controls.Add(this.lblWBRedMax, 1, 1);
            this.tableLayoutPanel3.Controls.Add(this.lblWBRefGrayLevel, 1, 0);
            this.tableLayoutPanel3.Controls.Add(this.label43, 0, 1);
            this.tableLayoutPanel3.Controls.Add(this.label44, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.label45, 0, 3);
            this.tableLayoutPanel3.Controls.Add(this.label16, 0, 4);
            this.tableLayoutPanel3.Controls.Add(this.label39, 0, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(8, 370);
            this.tableLayoutPanel3.Margin = new System.Windows.Forms.Padding(5);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 5;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(382, 186);
            this.tableLayoutPanel3.TabIndex = 1;
            // 
            // lblWBErrorLevel
            // 
            this.lblWBErrorLevel.AutoSize = true;
            this.lblWBErrorLevel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblWBErrorLevel.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Bold);
            this.lblWBErrorLevel.ForeColor = System.Drawing.SystemColors.ControlText;
            this.lblWBErrorLevel.Location = new System.Drawing.Point(195, 147);
            this.lblWBErrorLevel.Name = "lblWBErrorLevel";
            this.lblWBErrorLevel.Size = new System.Drawing.Size(181, 36);
            this.lblWBErrorLevel.TabIndex = 13;
            this.lblWBErrorLevel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblWBBlueMax
            // 
            this.lblWBBlueMax.AutoSize = true;
            this.lblWBBlueMax.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblWBBlueMax.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Bold);
            this.lblWBBlueMax.ForeColor = System.Drawing.Color.Blue;
            this.lblWBBlueMax.Location = new System.Drawing.Point(195, 111);
            this.lblWBBlueMax.Name = "lblWBBlueMax";
            this.lblWBBlueMax.Size = new System.Drawing.Size(181, 33);
            this.lblWBBlueMax.TabIndex = 12;
            this.lblWBBlueMax.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblWBGreenMax
            // 
            this.lblWBGreenMax.AutoSize = true;
            this.lblWBGreenMax.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblWBGreenMax.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Bold);
            this.lblWBGreenMax.ForeColor = System.Drawing.Color.Green;
            this.lblWBGreenMax.Location = new System.Drawing.Point(195, 75);
            this.lblWBGreenMax.Name = "lblWBGreenMax";
            this.lblWBGreenMax.Size = new System.Drawing.Size(181, 33);
            this.lblWBGreenMax.TabIndex = 11;
            this.lblWBGreenMax.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblWBRedMax
            // 
            this.lblWBRedMax.AutoSize = true;
            this.lblWBRedMax.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblWBRedMax.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Bold);
            this.lblWBRedMax.ForeColor = System.Drawing.Color.Red;
            this.lblWBRedMax.Location = new System.Drawing.Point(195, 39);
            this.lblWBRedMax.Name = "lblWBRedMax";
            this.lblWBRedMax.Size = new System.Drawing.Size(181, 33);
            this.lblWBRedMax.TabIndex = 10;
            this.lblWBRedMax.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblWBRefGrayLevel
            // 
            this.lblWBRefGrayLevel.AutoSize = true;
            this.lblWBRefGrayLevel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblWBRefGrayLevel.Font = new System.Drawing.Font("Tahoma", 24F, System.Drawing.FontStyle.Bold);
            this.lblWBRefGrayLevel.Location = new System.Drawing.Point(195, 3);
            this.lblWBRefGrayLevel.Name = "lblWBRefGrayLevel";
            this.lblWBRefGrayLevel.Size = new System.Drawing.Size(181, 33);
            this.lblWBRefGrayLevel.TabIndex = 9;
            this.lblWBRefGrayLevel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label43
            // 
            this.label43.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label43.AutoSize = true;
            this.label43.Font = new System.Drawing.Font("Calibri", 12.25F, System.Drawing.FontStyle.Bold);
            this.label43.Location = new System.Drawing.Point(3, 45);
            this.label43.Margin = new System.Windows.Forms.Padding(0);
            this.label43.Name = "label43";
            this.label43.Size = new System.Drawing.Size(147, 21);
            this.label43.TabIndex = 8;
            this.label43.Text = "Red Channel Max : ";
            // 
            // label44
            // 
            this.label44.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label44.AutoSize = true;
            this.label44.Font = new System.Drawing.Font("Calibri", 12.25F, System.Drawing.FontStyle.Bold);
            this.label44.Location = new System.Drawing.Point(3, 81);
            this.label44.Margin = new System.Windows.Forms.Padding(0);
            this.label44.Name = "label44";
            this.label44.Size = new System.Drawing.Size(163, 21);
            this.label44.TabIndex = 7;
            this.label44.Text = "Green Channel Max : ";
            // 
            // label45
            // 
            this.label45.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label45.AutoSize = true;
            this.label45.Font = new System.Drawing.Font("Calibri", 12.25F, System.Drawing.FontStyle.Bold);
            this.label45.Location = new System.Drawing.Point(3, 117);
            this.label45.Margin = new System.Windows.Forms.Padding(0);
            this.label45.Name = "label45";
            this.label45.Size = new System.Drawing.Size(151, 21);
            this.label45.TabIndex = 6;
            this.label45.Text = "Blue Channel Max : ";
            // 
            // label16
            // 
            this.label16.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Calibri", 12.25F, System.Drawing.FontStyle.Bold);
            this.label16.Location = new System.Drawing.Point(3, 154);
            this.label16.Margin = new System.Windows.Forms.Padding(0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(142, 21);
            this.label16.TabIndex = 5;
            this.label16.Text = "Error Level (in %) : ";
            // 
            // label39
            // 
            this.label39.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label39.AutoSize = true;
            this.label39.Font = new System.Drawing.Font("Calibri", 12.25F, System.Drawing.FontStyle.Bold);
            this.label39.Location = new System.Drawing.Point(3, 9);
            this.label39.Margin = new System.Windows.Forms.Padding(0);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(174, 21);
            this.label39.TabIndex = 4;
            this.label39.Text = "Reference Gray Level : ";
            this.label39.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetDouble;
            this.tableLayoutPanel5.ColumnCount = 3;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 55F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.tableLayoutPanel5.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.label2, 0, 1);
            this.tableLayoutPanel5.Controls.Add(this.label3, 0, 2);
            this.tableLayoutPanel5.Controls.Add(this.btnUpdateRedGain, 2, 0);
            this.tableLayoutPanel5.Controls.Add(this.btnUpdateGreenGain, 2, 1);
            this.tableLayoutPanel5.Controls.Add(this.btnUpdateBlueGain, 2, 2);
            this.tableLayoutPanel5.Controls.Add(this.txtRedGainValue, 1, 0);
            this.tableLayoutPanel5.Controls.Add(this.txtGreenGainValue, 1, 1);
            this.tableLayoutPanel5.Controls.Add(this.txtBlueGainValue, 1, 2);
            this.tableLayoutPanel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel5.Location = new System.Drawing.Point(6, 217);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 3;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 33.33333F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(386, 142);
            this.tableLayoutPanel5.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(78, 19);
            this.label1.TabIndex = 0;
            this.label1.Text = "Red Gain :";
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(6, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(93, 19);
            this.label2.TabIndex = 1;
            this.label2.Text = "Green Gain :";
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.Left;
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Calibri", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(6, 107);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 19);
            this.label3.TabIndex = 2;
            this.label3.Text = "Blue Gain :";
            // 
            // btnUpdateRedGain
            // 
            this.btnUpdateRedGain.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnUpdateRedGain.BackgroundImage")));
            this.btnUpdateRedGain.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateRedGain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateRedGain.Location = new System.Drawing.Point(329, 6);
            this.btnUpdateRedGain.Name = "btnUpdateRedGain";
            this.btnUpdateRedGain.Size = new System.Drawing.Size(51, 37);
            this.btnUpdateRedGain.TabIndex = 3;
            this.btnUpdateRedGain.Tag = "Red";
            this.btnUpdateRedGain.UseVisualStyleBackColor = true;
            this.btnUpdateRedGain.Click += new System.EventHandler(this.OnClickUpdateGainValue);
            // 
            // btnUpdateGreenGain
            // 
            this.btnUpdateGreenGain.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnUpdateGreenGain.BackgroundImage")));
            this.btnUpdateGreenGain.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateGreenGain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateGreenGain.Location = new System.Drawing.Point(329, 52);
            this.btnUpdateGreenGain.Name = "btnUpdateGreenGain";
            this.btnUpdateGreenGain.Size = new System.Drawing.Size(51, 37);
            this.btnUpdateGreenGain.TabIndex = 4;
            this.btnUpdateGreenGain.Tag = "Green";
            this.btnUpdateGreenGain.UseVisualStyleBackColor = true;
            this.btnUpdateGreenGain.Click += new System.EventHandler(this.OnClickUpdateGainValue);
            // 
            // btnUpdateBlueGain
            // 
            this.btnUpdateBlueGain.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("btnUpdateBlueGain.BackgroundImage")));
            this.btnUpdateBlueGain.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateBlueGain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateBlueGain.Location = new System.Drawing.Point(329, 98);
            this.btnUpdateBlueGain.Name = "btnUpdateBlueGain";
            this.btnUpdateBlueGain.Size = new System.Drawing.Size(51, 38);
            this.btnUpdateBlueGain.TabIndex = 5;
            this.btnUpdateBlueGain.Tag = "Blue";
            this.btnUpdateBlueGain.UseVisualStyleBackColor = true;
            this.btnUpdateBlueGain.Click += new System.EventHandler(this.OnClickUpdateGainValue);
            // 
            // txtRedGainValue
            // 
            this.txtRedGainValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.txtRedGainValue.Location = new System.Drawing.Point(121, 14);
            this.txtRedGainValue.Name = "txtRedGainValue";
            this.txtRedGainValue.Size = new System.Drawing.Size(199, 20);
            this.txtRedGainValue.TabIndex = 6;
            this.txtRedGainValue.TextChanged += new System.EventHandler(this.OnGainValueTextChanged);
            this.txtRedGainValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.OnGainValueChanged);
            // 
            // txtGreenGainValue
            // 
            this.txtGreenGainValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.txtGreenGainValue.Location = new System.Drawing.Point(121, 60);
            this.txtGreenGainValue.Name = "txtGreenGainValue";
            this.txtGreenGainValue.Size = new System.Drawing.Size(199, 20);
            this.txtGreenGainValue.TabIndex = 7;
            this.txtGreenGainValue.TextChanged += new System.EventHandler(this.OnGainValueTextChanged);
            this.txtGreenGainValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.OnGainValueChanged);
            // 
            // txtBlueGainValue
            // 
            this.txtBlueGainValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.txtBlueGainValue.Location = new System.Drawing.Point(121, 107);
            this.txtBlueGainValue.Name = "txtBlueGainValue";
            this.txtBlueGainValue.Size = new System.Drawing.Size(199, 20);
            this.txtBlueGainValue.TabIndex = 8;
            this.txtBlueGainValue.TextChanged += new System.EventHandler(this.OnGainValueTextChanged);
            this.txtBlueGainValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.OnGainValueChanged);
            // 
            // WhiteBalancing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tlpMain);
            this.Name = "WhiteBalancing";
            this.Size = new System.Drawing.Size(398, 564);
            this.tlpMain.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tableLayoutPanel5.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tlpMain;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button btnWhiteBalancing;
        private System.Windows.Forms.Button btnReset;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Label label39;
        private System.Windows.Forms.Label label44;
        private System.Windows.Forms.Label label45;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label43;
        private System.Windows.Forms.Label lblWBRefGrayLevel;
        private System.Windows.Forms.Label lblWBBlueMax;
        private System.Windows.Forms.Label lblWBGreenMax;
        private System.Windows.Forms.Label lblWBRedMax;
        private System.Windows.Forms.Label lblWBErrorLevel;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnUpdateRedGain;
        private System.Windows.Forms.Button btnUpdateGreenGain;
        private System.Windows.Forms.Button btnUpdateBlueGain;
        private System.Windows.Forms.TextBox txtRedGainValue;
        private System.Windows.Forms.TextBox txtGreenGainValue;
        private System.Windows.Forms.TextBox txtBlueGainValue;
    }
}
