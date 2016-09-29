namespace CameraSetupTool.UserControls
{
    partial class LightIntensityCheck
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.txtReferenceValue = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel7 = new System.Windows.Forms.TableLayoutPanel();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.lblAcceptableRangeMin = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.lblCurrentRangeMin = new System.Windows.Forms.Label();
            this.lblCurrentRangeMax = new System.Windows.Forms.Label();
            this.lblAcceptableRangeMax = new System.Windows.Forms.Label();
            this.tableLayoutPanel6 = new System.Windows.Forms.TableLayoutPanel();
            this.label10 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.tableLayoutPanel9 = new System.Windows.Forms.TableLayoutPanel();
            this.btnUpdateIRL2 = new System.Windows.Forms.Button();
            this.btnUpdateWL2 = new System.Windows.Forms.Button();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.tableLayoutPanel8 = new System.Windows.Forms.TableLayoutPanel();
            this.btnUpdateIRL1 = new System.Windows.Forms.Button();
            this.btnUpdateWL1 = new System.Windows.Forms.Button();
            this.label13 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.nsIRLight2 = new CameraSetupTool.UserControls.NumberSelector();
            this.nsWhiteLight2 = new CameraSetupTool.UserControls.NumberSelector();
            this.nsWhiteLight1 = new CameraSetupTool.UserControls.NumberSelector();
            this.nsIRLight1 = new CameraSetupTool.UserControls.NumberSelector();
            this.groupBox1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.panel1.SuspendLayout();
            this.tableLayoutPanel7.SuspendLayout();
            this.tableLayoutPanel6.SuspendLayout();
            this.tableLayoutPanel9.SuspendLayout();
            this.tableLayoutPanel8.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tableLayoutPanel1);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(656, 786);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Light Intensity Check";
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.OutsetPartial;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 409F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.lblStatus, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 23);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(650, 760);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.panel1, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.tableLayoutPanel6, 0, 2);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(6, 6);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 3;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 35F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(226, 748);
            this.tableLayoutPanel2.TabIndex = 0;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.InsetDouble;
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.txtReferenceValue, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(220, 106);
            this.tableLayoutPanel3.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label1.Font = new System.Drawing.Font("Tahoma", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 3);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(99, 100);
            this.label1.TabIndex = 0;
            this.label1.Text = "Reference Gray Value";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // txtReferenceValue
            // 
            this.txtReferenceValue.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.txtReferenceValue.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.txtReferenceValue.Location = new System.Drawing.Point(114, 39);
            this.txtReferenceValue.Name = "txtReferenceValue";
            this.txtReferenceValue.ReadOnly = true;
            this.txtReferenceValue.Size = new System.Drawing.Size(100, 27);
            this.txtReferenceValue.TabIndex = 1;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.tableLayoutPanel7);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 115);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(220, 255);
            this.panel1.TabIndex = 3;
            // 
            // tableLayoutPanel7
            // 
            this.tableLayoutPanel7.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.InsetDouble;
            this.tableLayoutPanel7.ColumnCount = 3;
            this.tableLayoutPanel7.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 34F));
            this.tableLayoutPanel7.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel7.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel7.Controls.Add(this.label6, 1, 0);
            this.tableLayoutPanel7.Controls.Add(this.label7, 2, 0);
            this.tableLayoutPanel7.Controls.Add(this.lblAcceptableRangeMin, 1, 1);
            this.tableLayoutPanel7.Controls.Add(this.label9, 0, 1);
            this.tableLayoutPanel7.Controls.Add(this.label12, 0, 2);
            this.tableLayoutPanel7.Controls.Add(this.lblCurrentRangeMin, 1, 2);
            this.tableLayoutPanel7.Controls.Add(this.lblCurrentRangeMax, 2, 2);
            this.tableLayoutPanel7.Controls.Add(this.lblAcceptableRangeMax, 2, 1);
            this.tableLayoutPanel7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel7.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel7.Name = "tableLayoutPanel7";
            this.tableLayoutPanel7.RowCount = 3;
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 34F));
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel7.Size = new System.Drawing.Size(220, 255);
            this.tableLayoutPanel7.TabIndex = 1;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label6.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(79, 3);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(62, 34);
            this.label6.TabIndex = 0;
            this.label6.Text = "Red Plane Min";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label7.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(150, 3);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(64, 34);
            this.label7.TabIndex = 1;
            this.label7.Text = "Red Plane Max";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblAcceptableRangeMin
            // 
            this.lblAcceptableRangeMin.AutoSize = true;
            this.lblAcceptableRangeMin.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblAcceptableRangeMin.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblAcceptableRangeMin.Location = new System.Drawing.Point(79, 40);
            this.lblAcceptableRangeMin.Name = "lblAcceptableRangeMin";
            this.lblAcceptableRangeMin.Size = new System.Drawing.Size(62, 104);
            this.lblAcceptableRangeMin.TabIndex = 2;
            this.lblAcceptableRangeMin.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label9.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(6, 40);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(64, 104);
            this.label9.TabIndex = 3;
            this.label9.Text = "Acceptable";
            this.label9.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label12.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(6, 147);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(64, 105);
            this.label12.TabIndex = 4;
            this.label12.Text = "Current";
            this.label12.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblCurrentRangeMin
            // 
            this.lblCurrentRangeMin.AutoSize = true;
            this.lblCurrentRangeMin.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblCurrentRangeMin.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCurrentRangeMin.Location = new System.Drawing.Point(79, 147);
            this.lblCurrentRangeMin.Name = "lblCurrentRangeMin";
            this.lblCurrentRangeMin.Size = new System.Drawing.Size(62, 105);
            this.lblCurrentRangeMin.TabIndex = 5;
            this.lblCurrentRangeMin.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblCurrentRangeMax
            // 
            this.lblCurrentRangeMax.AutoSize = true;
            this.lblCurrentRangeMax.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblCurrentRangeMax.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblCurrentRangeMax.Location = new System.Drawing.Point(150, 147);
            this.lblCurrentRangeMax.Name = "lblCurrentRangeMax";
            this.lblCurrentRangeMax.Size = new System.Drawing.Size(64, 105);
            this.lblCurrentRangeMax.TabIndex = 6;
            this.lblCurrentRangeMax.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblAcceptableRangeMax
            // 
            this.lblAcceptableRangeMax.AutoSize = true;
            this.lblAcceptableRangeMax.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblAcceptableRangeMax.Font = new System.Drawing.Font("Verdana", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblAcceptableRangeMax.Location = new System.Drawing.Point(150, 40);
            this.lblAcceptableRangeMax.Name = "lblAcceptableRangeMax";
            this.lblAcceptableRangeMax.Size = new System.Drawing.Size(64, 104);
            this.lblAcceptableRangeMax.TabIndex = 7;
            this.lblAcceptableRangeMax.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel6
            // 
            this.tableLayoutPanel6.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel6.ColumnCount = 2;
            this.tableLayoutPanel6.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.tableLayoutPanel6.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 85F));
            this.tableLayoutPanel6.Controls.Add(this.label10, 0, 0);
            this.tableLayoutPanel6.Controls.Add(this.label8, 0, 1);
            this.tableLayoutPanel6.Controls.Add(this.tableLayoutPanel9, 1, 1);
            this.tableLayoutPanel6.Controls.Add(this.tableLayoutPanel8, 1, 0);
            this.tableLayoutPanel6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel6.Location = new System.Drawing.Point(3, 376);
            this.tableLayoutPanel6.Name = "tableLayoutPanel6";
            this.tableLayoutPanel6.RowCount = 2;
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel6.Size = new System.Drawing.Size(220, 369);
            this.tableLayoutPanel6.TabIndex = 0;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label10.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(5, 2);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(26, 181);
            this.label10.TabIndex = 5;
            this.label10.Text = "Light 1";
            this.label10.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label8.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(5, 185);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(26, 182);
            this.label8.TabIndex = 4;
            this.label8.Text = "Light 2";
            this.label8.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel9
            // 
            this.tableLayoutPanel9.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel9.ColumnCount = 3;
            this.tableLayoutPanel9.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.tableLayoutPanel9.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 65F));
            this.tableLayoutPanel9.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel9.Controls.Add(this.btnUpdateIRL2, 2, 1);
            this.tableLayoutPanel9.Controls.Add(this.btnUpdateWL2, 2, 0);
            this.tableLayoutPanel9.Controls.Add(this.label15, 0, 1);
            this.tableLayoutPanel9.Controls.Add(this.label14, 0, 0);
            this.tableLayoutPanel9.Controls.Add(this.nsIRLight2, 1, 1);
            this.tableLayoutPanel9.Controls.Add(this.nsWhiteLight2, 1, 0);
            this.tableLayoutPanel9.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel9.Location = new System.Drawing.Point(39, 188);
            this.tableLayoutPanel9.Name = "tableLayoutPanel9";
            this.tableLayoutPanel9.RowCount = 2;
            this.tableLayoutPanel9.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel9.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel9.Size = new System.Drawing.Size(176, 176);
            this.tableLayoutPanel9.TabIndex = 2;
            // 
            // btnUpdateIRL2
            // 
            this.btnUpdateIRL2.BackgroundImage = global::CameraSetupTool.Properties.Resources.Refresh;
            this.btnUpdateIRL2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateIRL2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateIRL2.Location = new System.Drawing.Point(143, 92);
            this.btnUpdateIRL2.Name = "btnUpdateIRL2";
            this.btnUpdateIRL2.Size = new System.Drawing.Size(28, 79);
            this.btnUpdateIRL2.TabIndex = 11;
            this.btnUpdateIRL2.UseVisualStyleBackColor = true;
            // 
            // btnUpdateWL2
            // 
            this.btnUpdateWL2.BackgroundImage = global::CameraSetupTool.Properties.Resources.Refresh;
            this.btnUpdateWL2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateWL2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateWL2.Location = new System.Drawing.Point(143, 5);
            this.btnUpdateWL2.Name = "btnUpdateWL2";
            this.btnUpdateWL2.Size = new System.Drawing.Size(28, 79);
            this.btnUpdateWL2.TabIndex = 10;
            this.btnUpdateWL2.UseVisualStyleBackColor = true;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label15.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.Location = new System.Drawing.Point(5, 89);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(19, 85);
            this.label15.TabIndex = 7;
            this.label15.Text = "IRL 2";
            this.label15.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label14.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(5, 2);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(19, 85);
            this.label14.TabIndex = 6;
            this.label14.Text = "WL 2";
            this.label14.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel8
            // 
            this.tableLayoutPanel8.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Inset;
            this.tableLayoutPanel8.ColumnCount = 3;
            this.tableLayoutPanel8.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 15F));
            this.tableLayoutPanel8.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 65F));
            this.tableLayoutPanel8.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel8.Controls.Add(this.btnUpdateIRL1, 2, 1);
            this.tableLayoutPanel8.Controls.Add(this.btnUpdateWL1, 2, 0);
            this.tableLayoutPanel8.Controls.Add(this.label13, 0, 1);
            this.tableLayoutPanel8.Controls.Add(this.label11, 0, 0);
            this.tableLayoutPanel8.Controls.Add(this.nsWhiteLight1, 1, 0);
            this.tableLayoutPanel8.Controls.Add(this.nsIRLight1, 1, 1);
            this.tableLayoutPanel8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel8.Location = new System.Drawing.Point(39, 5);
            this.tableLayoutPanel8.Name = "tableLayoutPanel8";
            this.tableLayoutPanel8.RowCount = 2;
            this.tableLayoutPanel8.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel8.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel8.Size = new System.Drawing.Size(176, 175);
            this.tableLayoutPanel8.TabIndex = 1;
            // 
            // btnUpdateIRL1
            // 
            this.btnUpdateIRL1.BackgroundImage = global::CameraSetupTool.Properties.Resources.Refresh;
            this.btnUpdateIRL1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateIRL1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateIRL1.Location = new System.Drawing.Point(143, 91);
            this.btnUpdateIRL1.Name = "btnUpdateIRL1";
            this.btnUpdateIRL1.Size = new System.Drawing.Size(28, 79);
            this.btnUpdateIRL1.TabIndex = 11;
            this.btnUpdateIRL1.UseVisualStyleBackColor = true;
            // 
            // btnUpdateWL1
            // 
            this.btnUpdateWL1.BackgroundImage = global::CameraSetupTool.Properties.Resources.Refresh;
            this.btnUpdateWL1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnUpdateWL1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnUpdateWL1.Location = new System.Drawing.Point(143, 5);
            this.btnUpdateWL1.Name = "btnUpdateWL1";
            this.btnUpdateWL1.Size = new System.Drawing.Size(28, 78);
            this.btnUpdateWL1.TabIndex = 10;
            this.btnUpdateWL1.UseVisualStyleBackColor = true;
            this.btnUpdateWL1.Click += new System.EventHandler(this.OnClickUpdateLightIntensity);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label13.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(5, 88);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(19, 85);
            this.label13.TabIndex = 7;
            this.label13.Text = "IRL 1";
            this.label13.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label11.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(5, 2);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(19, 84);
            this.label11.TabIndex = 6;
            this.label11.Text = "WL 1";
            this.label11.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // lblStatus
            // 
            this.lblStatus.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblStatus.Font = new System.Drawing.Font("Tahoma", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblStatus.Location = new System.Drawing.Point(241, 3);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(403, 754);
            this.lblStatus.TabIndex = 1;
            this.lblStatus.Text = "Status";
            this.lblStatus.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.InsetDouble;
            this.tableLayoutPanel5.ColumnCount = 3;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 34F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel5.Controls.Add(this.label2, 1, 0);
            this.tableLayoutPanel5.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 1;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(200, 100);
            this.tableLayoutPanel5.TabIndex = 0;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label2.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(72, 3);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 94);
            this.label2.TabIndex = 0;
            this.label2.Text = "Red Plane Min";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label3.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(288, 3);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(132, 34);
            this.label3.TabIndex = 1;
            this.label3.Text = "Red Plane Max";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.InsetDouble;
            this.tableLayoutPanel4.ColumnCount = 3;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 34F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 33F));
            this.tableLayoutPanel4.Controls.Add(this.label4, 1, 0);
            this.tableLayoutPanel4.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 1;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(200, 100);
            this.tableLayoutPanel4.TabIndex = 0;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label4.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(72, 3);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 94);
            this.label4.TabIndex = 0;
            this.label4.Text = "Red Plane Min";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.label5.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(120, 3);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(49, 34);
            this.label5.TabIndex = 1;
            this.label5.Text = "Red Plane Max";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // nsIRLight2
            // 
            this.nsIRLight2.DecrementValue = 5;
            this.nsIRLight2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.nsIRLight2.IncrementValue = 5;
            this.nsIRLight2.Location = new System.Drawing.Point(32, 92);
            this.nsIRLight2.Name = "nsIRLight2";
            this.nsIRLight2.Size = new System.Drawing.Size(103, 79);
            this.nsIRLight2.TabIndex = 8;
            // 
            // nsWhiteLight2
            // 
            this.nsWhiteLight2.DecrementValue = 5;
            this.nsWhiteLight2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.nsWhiteLight2.IncrementValue = 5;
            this.nsWhiteLight2.Location = new System.Drawing.Point(32, 5);
            this.nsWhiteLight2.Name = "nsWhiteLight2";
            this.nsWhiteLight2.Size = new System.Drawing.Size(103, 79);
            this.nsWhiteLight2.TabIndex = 9;
            // 
            // nsWhiteLight1
            // 
            this.nsWhiteLight1.DecrementValue = 5;
            this.nsWhiteLight1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.nsWhiteLight1.IncrementValue = 5;
            this.nsWhiteLight1.Location = new System.Drawing.Point(32, 5);
            this.nsWhiteLight1.Name = "nsWhiteLight1";
            this.nsWhiteLight1.Size = new System.Drawing.Size(103, 78);
            this.nsWhiteLight1.TabIndex = 8;
            // 
            // nsIRLight1
            // 
            this.nsIRLight1.DecrementValue = 5;
            this.nsIRLight1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.nsIRLight1.IncrementValue = 5;
            this.nsIRLight1.Location = new System.Drawing.Point(32, 91);
            this.nsIRLight1.Name = "nsIRLight1";
            this.nsIRLight1.Size = new System.Drawing.Size(103, 79);
            this.nsIRLight1.TabIndex = 9;
            // 
            // LightIntensityCheck
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox1);
            this.DoubleBuffered = true;
            this.Name = "LightIntensityCheck";
            this.Size = new System.Drawing.Size(656, 786);
            this.Resize += new System.EventHandler(this.LightIntensityCheck_Resize);
            this.groupBox1.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.panel1.ResumeLayout(false);
            this.tableLayoutPanel7.ResumeLayout(false);
            this.tableLayoutPanel7.PerformLayout();
            this.tableLayoutPanel6.ResumeLayout(false);
            this.tableLayoutPanel6.PerformLayout();
            this.tableLayoutPanel9.ResumeLayout(false);
            this.tableLayoutPanel9.PerformLayout();
            this.tableLayoutPanel8.ResumeLayout(false);
            this.tableLayoutPanel8.PerformLayout();
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tableLayoutPanel5.PerformLayout();
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label lblAcceptableRangeMin;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label lblCurrentRangeMin;
        private System.Windows.Forms.Label lblCurrentRangeMax;
        private System.Windows.Forms.Label lblAcceptableRangeMax;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel6;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel9;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel8;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label11;
        private NumberSelector nsWhiteLight1;
        private NumberSelector nsIRLight1;
        private NumberSelector nsIRLight2;
        private NumberSelector nsWhiteLight2;
        private System.Windows.Forms.Button btnUpdateIRL2;
        private System.Windows.Forms.Button btnUpdateWL2;
        private System.Windows.Forms.Button btnUpdateIRL1;
        private System.Windows.Forms.Button btnUpdateWL1;
        private System.Windows.Forms.TextBox txtReferenceValue;
    }
}
