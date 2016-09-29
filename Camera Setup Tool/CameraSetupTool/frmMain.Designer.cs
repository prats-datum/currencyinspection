namespace CameraSetupTool
{
    partial class frmMain
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
            this.currentCameraStep.CameraAcquisition.ImageGrabbed -= new ImageGrabbedHandler(UpdateUIAfterProcessingStep);
            while (!this.currentCameraStep.CameraAcquisition.StopGrabbing())
            {
                return;
            }
            this.currentImage = null;
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.tlpMainContainer = new System.Windows.Forms.TableLayoutPanel();
            this.statusBar = new System.Windows.Forms.Panel();
            this.lblColorValue = new System.Windows.Forms.Label();
            this.panel4 = new System.Windows.Forms.Panel();
            this.lblRowColData = new System.Windows.Forms.Label();
            this.panel5 = new System.Windows.Forms.Panel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.tlpOptions = new System.Windows.Forms.TableLayoutPanel();
            this.btnImageViewer = new System.Windows.Forms.RadioButton();
            this.btnFFC = new System.Windows.Forms.RadioButton();
            this.btnWhiteBalancing = new System.Windows.Forms.RadioButton();
            this.btnLightIntensityCheck = new System.Windows.Forms.RadioButton();
            this.btnFocusSetting = new System.Windows.Forms.RadioButton();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.tlpImageLayout = new System.Windows.Forms.TableLayoutPanel();
            this.winChart = new ChartDirector.WinChartViewer();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.hwcRGBImage = new CameraSetupTool.HalconWindowControl();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.hwcIRImage = new CameraSetupTool.HalconWindowControl();
            this.tableLayoutPanel7 = new System.Windows.Forms.TableLayoutPanel();
            this.lblInstruction = new System.Windows.Forms.Label();
            this.pnlControls = new System.Windows.Forms.Panel();
            this.tlpMain = new System.Windows.Forms.TableLayoutPanel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveImageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveSettingsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openSerialCommandWindowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tlpMainContainer.SuspendLayout();
            this.statusBar.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.tlpOptions.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.tlpImageLayout.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.winChart)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tableLayoutPanel7.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tlpMainContainer
            // 
            this.tlpMainContainer.ColumnCount = 1;
            this.tlpMainContainer.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tlpMainContainer.Controls.Add(this.statusBar, 0, 1);
            this.tlpMainContainer.Controls.Add(this.tableLayoutPanel3, 0, 0);
            this.tlpMainContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpMainContainer.Location = new System.Drawing.Point(0, 24);
            this.tlpMainContainer.Name = "tlpMainContainer";
            this.tlpMainContainer.RowCount = 2;
            this.tlpMainContainer.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tlpMainContainer.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 40F));
            this.tlpMainContainer.Size = new System.Drawing.Size(1259, 674);
            this.tlpMainContainer.TabIndex = 0;
            // 
            // statusBar
            // 
            this.statusBar.BackColor = System.Drawing.SystemColors.Desktop;
            this.statusBar.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.statusBar.Controls.Add(this.lblColorValue);
            this.statusBar.Controls.Add(this.panel4);
            this.statusBar.Controls.Add(this.lblRowColData);
            this.statusBar.Controls.Add(this.panel5);
            this.statusBar.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.statusBar.Location = new System.Drawing.Point(3, 640);
            this.statusBar.Name = "statusBar";
            this.statusBar.Size = new System.Drawing.Size(1253, 31);
            this.statusBar.TabIndex = 6;
            // 
            // lblColorValue
            // 
            this.lblColorValue.AutoEllipsis = true;
            this.lblColorValue.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblColorValue.Dock = System.Windows.Forms.DockStyle.Left;
            this.lblColorValue.Font = new System.Drawing.Font("Calibri", 12.75F, System.Drawing.FontStyle.Bold);
            this.lblColorValue.ForeColor = System.Drawing.Color.White;
            this.lblColorValue.Location = new System.Drawing.Point(158, 0);
            this.lblColorValue.Name = "lblColorValue";
            this.lblColorValue.Size = new System.Drawing.Size(142, 29);
            this.lblColorValue.TabIndex = 3;
            this.lblColorValue.Text = "0,0,0";
            this.lblColorValue.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.White;
            this.panel4.BackgroundImage = global::CameraSetupTool.Properties.Resources.RGB;
            this.panel4.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.panel4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel4.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel4.Location = new System.Drawing.Point(127, 0);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(31, 29);
            this.panel4.TabIndex = 5;
            // 
            // lblRowColData
            // 
            this.lblRowColData.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblRowColData.Dock = System.Windows.Forms.DockStyle.Left;
            this.lblRowColData.Font = new System.Drawing.Font("Calibri", 12.75F, System.Drawing.FontStyle.Bold);
            this.lblRowColData.ForeColor = System.Drawing.Color.White;
            this.lblRowColData.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.lblRowColData.Location = new System.Drawing.Point(31, 0);
            this.lblRowColData.Name = "lblRowColData";
            this.lblRowColData.Size = new System.Drawing.Size(96, 29);
            this.lblRowColData.TabIndex = 2;
            this.lblRowColData.Text = "0,0";
            this.lblRowColData.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // panel5
            // 
            this.panel5.BackColor = System.Drawing.Color.White;
            this.panel5.BackgroundImage = global::CameraSetupTool.Properties.Resources.ArrowXY;
            this.panel5.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.panel5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel5.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel5.Location = new System.Drawing.Point(0, 0);
            this.panel5.Name = "panel5";
            this.panel5.Size = new System.Drawing.Size(31, 29);
            this.panel5.TabIndex = 4;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.tlpOptions, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.tableLayoutPanel5, 0, 1);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 2;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 8.255659F));
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 91.74434F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(1253, 628);
            this.tableLayoutPanel3.TabIndex = 1;
            // 
            // tlpOptions
            // 
            this.tlpOptions.ColumnCount = 5;
            this.tlpOptions.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tlpOptions.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tlpOptions.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tlpOptions.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tlpOptions.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tlpOptions.Controls.Add(this.btnImageViewer, 4, 0);
            this.tlpOptions.Controls.Add(this.btnFFC, 3, 0);
            this.tlpOptions.Controls.Add(this.btnWhiteBalancing, 2, 0);
            this.tlpOptions.Controls.Add(this.btnLightIntensityCheck, 1, 0);
            this.tlpOptions.Controls.Add(this.btnFocusSetting, 0, 0);
            this.tlpOptions.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpOptions.Location = new System.Drawing.Point(4, 4);
            this.tlpOptions.Name = "tlpOptions";
            this.tlpOptions.RowCount = 1;
            this.tlpOptions.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tlpOptions.Size = new System.Drawing.Size(1245, 45);
            this.tlpOptions.TabIndex = 3;
            // 
            // btnImageViewer
            // 
            this.btnImageViewer.Appearance = System.Windows.Forms.Appearance.Button;
            this.btnImageViewer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnImageViewer.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnImageViewer.Location = new System.Drawing.Point(999, 3);
            this.btnImageViewer.Name = "btnImageViewer";
            this.btnImageViewer.Size = new System.Drawing.Size(243, 39);
            this.btnImageViewer.TabIndex = 4;
            this.btnImageViewer.Tag = "ImageViewer";
            this.btnImageViewer.Text = "IMAGE VIEWER";
            this.btnImageViewer.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnImageViewer.UseVisualStyleBackColor = true;
            this.btnImageViewer.CheckedChanged += new System.EventHandler(this.OnCameraSetupStepChanged);
            // 
            // btnFFC
            // 
            this.btnFFC.Appearance = System.Windows.Forms.Appearance.Button;
            this.btnFFC.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnFFC.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnFFC.Location = new System.Drawing.Point(750, 3);
            this.btnFFC.Name = "btnFFC";
            this.btnFFC.Size = new System.Drawing.Size(243, 39);
            this.btnFFC.TabIndex = 3;
            this.btnFFC.Text = "FFC";
            this.btnFFC.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnFFC.UseVisualStyleBackColor = true;
            this.btnFFC.CheckedChanged += new System.EventHandler(this.OnCameraSetupStepChanged);
            // 
            // btnWhiteBalancing
            // 
            this.btnWhiteBalancing.Appearance = System.Windows.Forms.Appearance.Button;
            this.btnWhiteBalancing.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnWhiteBalancing.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnWhiteBalancing.Location = new System.Drawing.Point(501, 3);
            this.btnWhiteBalancing.Name = "btnWhiteBalancing";
            this.btnWhiteBalancing.Size = new System.Drawing.Size(243, 39);
            this.btnWhiteBalancing.TabIndex = 2;
            this.btnWhiteBalancing.Text = "WHITE BALANCING";
            this.btnWhiteBalancing.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnWhiteBalancing.UseVisualStyleBackColor = true;
            this.btnWhiteBalancing.CheckedChanged += new System.EventHandler(this.OnCameraSetupStepChanged);
            // 
            // btnLightIntensityCheck
            // 
            this.btnLightIntensityCheck.Appearance = System.Windows.Forms.Appearance.Button;
            this.btnLightIntensityCheck.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnLightIntensityCheck.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnLightIntensityCheck.Location = new System.Drawing.Point(252, 3);
            this.btnLightIntensityCheck.Name = "btnLightIntensityCheck";
            this.btnLightIntensityCheck.Size = new System.Drawing.Size(243, 39);
            this.btnLightIntensityCheck.TabIndex = 1;
            this.btnLightIntensityCheck.Text = "LIGHT INTENSITY CHECK";
            this.btnLightIntensityCheck.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnLightIntensityCheck.UseVisualStyleBackColor = true;
            this.btnLightIntensityCheck.CheckedChanged += new System.EventHandler(this.OnCameraSetupStepChanged);
            // 
            // btnFocusSetting
            // 
            this.btnFocusSetting.Appearance = System.Windows.Forms.Appearance.Button;
            this.btnFocusSetting.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnFocusSetting.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnFocusSetting.Location = new System.Drawing.Point(3, 3);
            this.btnFocusSetting.Name = "btnFocusSetting";
            this.btnFocusSetting.Size = new System.Drawing.Size(243, 39);
            this.btnFocusSetting.TabIndex = 0;
            this.btnFocusSetting.Tag = "FocusSetting";
            this.btnFocusSetting.Text = "FOCUS SETTING";
            this.btnFocusSetting.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.btnFocusSetting.UseVisualStyleBackColor = true;
            this.btnFocusSetting.CheckedChanged += new System.EventHandler(this.OnCameraSetupStepChanged);
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.ColumnCount = 2;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 48.94046F));
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 51.05954F));
            this.tableLayoutPanel5.Controls.Add(this.tlpImageLayout, 0, 0);
            this.tableLayoutPanel5.Controls.Add(this.tableLayoutPanel7, 1, 0);
            this.tableLayoutPanel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel5.Location = new System.Drawing.Point(4, 56);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 1;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(1245, 568);
            this.tableLayoutPanel5.TabIndex = 1;
            // 
            // tlpImageLayout
            // 
            this.tlpImageLayout.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tlpImageLayout.ColumnCount = 1;
            this.tlpImageLayout.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tlpImageLayout.Controls.Add(this.winChart, 0, 2);
            this.tlpImageLayout.Controls.Add(this.groupBox1, 0, 0);
            this.tlpImageLayout.Controls.Add(this.groupBox2, 0, 1);
            this.tlpImageLayout.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpImageLayout.Location = new System.Drawing.Point(3, 3);
            this.tlpImageLayout.Name = "tlpImageLayout";
            this.tlpImageLayout.RowCount = 3;
            this.tlpImageLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tlpImageLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tlpImageLayout.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 40F));
            this.tlpImageLayout.Size = new System.Drawing.Size(603, 562);
            this.tlpImageLayout.TabIndex = 2;
            // 
            // winChart
            // 
            this.winChart.Dock = System.Windows.Forms.DockStyle.Fill;
            this.winChart.Location = new System.Drawing.Point(4, 340);
            this.winChart.Name = "winChart";
            this.winChart.Size = new System.Drawing.Size(595, 218);
            this.winChart.TabIndex = 2;
            this.winChart.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.hwcRGBImage);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(4, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(595, 161);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "RGB-IMAGE";
            // 
            // hwcRGBImage
            // 
            this.hwcRGBImage.BackColor = System.Drawing.Color.Black;
            this.hwcRGBImage.BorderColor = System.Drawing.Color.Black;
            this.hwcRGBImage.DisplayBorder = true;
            this.hwcRGBImage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hwcRGBImage.ImageFit = CameraSetupTool.HalconWindowControl.ImageFitType.XAxis;
            this.hwcRGBImage.ImagePart = new System.Drawing.Rectangle(0, 0, 640, 480);
            this.hwcRGBImage.Location = new System.Drawing.Point(3, 19);
            this.hwcRGBImage.Name = "hwcRGBImage";
            this.hwcRGBImage.PanZoomType = CameraSetupTool.HalconWindowControl.ZoomPanType.ZoomAndPan;
            this.hwcRGBImage.Size = new System.Drawing.Size(589, 139);
            this.hwcRGBImage.TabIndex = 4;
            this.hwcRGBImage.WindowSize = new System.Drawing.Size(589, 139);
            this.hwcRGBImage.WindowRepainted += new CameraSetupTool.HalconWindowControl.RepaintEventHandler(this.OnImageWindowRepainted);
            this.hwcRGBImage.ImageChanged += new CameraSetupTool.HalconWindowControl.ImageChangedEventHandler(this.OnImageWindowImageChanged);
            this.hwcRGBImage.HMouseMove += new HalconDotNet.HMouseEventHandler(this.OnImageWindowMouseMove);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.hwcIRImage);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(4, 172);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(595, 161);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "IR-IMAGE";
            // 
            // hwcIRImage
            // 
            this.hwcIRImage.BackColor = System.Drawing.Color.Black;
            this.hwcIRImage.BorderColor = System.Drawing.Color.Black;
            this.hwcIRImage.DisplayBorder = true;
            this.hwcIRImage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hwcIRImage.ImageFit = CameraSetupTool.HalconWindowControl.ImageFitType.XAxis;
            this.hwcIRImage.ImagePart = new System.Drawing.Rectangle(0, 0, 640, 480);
            this.hwcIRImage.Location = new System.Drawing.Point(3, 19);
            this.hwcIRImage.Name = "hwcIRImage";
            this.hwcIRImage.PanZoomType = CameraSetupTool.HalconWindowControl.ZoomPanType.ZoomAndPan;
            this.hwcIRImage.Size = new System.Drawing.Size(589, 139);
            this.hwcIRImage.TabIndex = 5;
            this.hwcIRImage.WindowSize = new System.Drawing.Size(589, 139);
            this.hwcIRImage.WindowRepainted += new CameraSetupTool.HalconWindowControl.RepaintEventHandler(this.OnImageWindowRepainted);
            this.hwcIRImage.ImageChanged += new CameraSetupTool.HalconWindowControl.ImageChangedEventHandler(this.OnImageWindowImageChanged);
            this.hwcIRImage.HMouseMove += new HalconDotNet.HMouseEventHandler(this.OnImageWindowMouseMove);
            // 
            // tableLayoutPanel7
            // 
            this.tableLayoutPanel7.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tableLayoutPanel7.ColumnCount = 1;
            this.tableLayoutPanel7.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel7.Controls.Add(this.lblInstruction, 0, 1);
            this.tableLayoutPanel7.Controls.Add(this.pnlControls, 0, 0);
            this.tableLayoutPanel7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel7.Location = new System.Drawing.Point(612, 3);
            this.tableLayoutPanel7.Name = "tableLayoutPanel7";
            this.tableLayoutPanel7.RowCount = 2;
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel7.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 55F));
            this.tableLayoutPanel7.Size = new System.Drawing.Size(630, 562);
            this.tableLayoutPanel7.TabIndex = 3;
            // 
            // lblInstruction
            // 
            this.lblInstruction.AutoSize = true;
            this.lblInstruction.BackColor = System.Drawing.Color.LemonChiffon;
            this.lblInstruction.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblInstruction.Font = new System.Drawing.Font("Calibri", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblInstruction.ForeColor = System.Drawing.Color.DarkBlue;
            this.lblInstruction.Location = new System.Drawing.Point(4, 506);
            this.lblInstruction.Name = "lblInstruction";
            this.lblInstruction.Size = new System.Drawing.Size(622, 55);
            this.lblInstruction.TabIndex = 0;
            this.lblInstruction.Text = "Steps to Perform";
            this.lblInstruction.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pnlControls
            // 
            this.pnlControls.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlControls.Location = new System.Drawing.Point(4, 4);
            this.pnlControls.Name = "pnlControls";
            this.pnlControls.Size = new System.Drawing.Size(622, 498);
            this.pnlControls.TabIndex = 1;
            // 
            // tlpMain
            // 
            this.tlpMain.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tlpMain.ColumnCount = 1;
            this.tlpMain.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tlpMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpMain.Location = new System.Drawing.Point(0, 0);
            this.tlpMain.Name = "tlpMain";
            this.tlpMain.RowCount = 2;
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tlpMain.Size = new System.Drawing.Size(200, 100);
            this.tlpMain.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.toolToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1259, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveImageToolStripMenuItem,
            this.saveSettingsToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // saveImageToolStripMenuItem
            // 
            this.saveImageToolStripMenuItem.Name = "saveImageToolStripMenuItem";
            this.saveImageToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.I)));
            this.saveImageToolStripMenuItem.Size = new System.Drawing.Size(238, 22);
            this.saveImageToolStripMenuItem.Text = "Save Image";
            this.saveImageToolStripMenuItem.Click += new System.EventHandler(this.OnClickSaveImageMenu);
            // 
            // saveSettingsToolStripMenuItem
            // 
            this.saveSettingsToolStripMenuItem.Name = "saveSettingsToolStripMenuItem";
            this.saveSettingsToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Alt) 
            | System.Windows.Forms.Keys.Shift) 
            | System.Windows.Forms.Keys.S)));
            this.saveSettingsToolStripMenuItem.Size = new System.Drawing.Size(238, 22);
            this.saveSettingsToolStripMenuItem.Text = "Save Settings";
            this.saveSettingsToolStripMenuItem.Click += new System.EventHandler(this.OnCickSaveSettingsMenu);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.X)));
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(238, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.OnClickExitMenu);
            // 
            // toolToolStripMenuItem
            // 
            this.toolToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openSerialCommandWindowToolStripMenuItem});
            this.toolToolStripMenuItem.Name = "toolToolStripMenuItem";
            this.toolToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
            this.toolToolStripMenuItem.Text = "Tool";
            // 
            // openSerialCommandWindowToolStripMenuItem
            // 
            this.openSerialCommandWindowToolStripMenuItem.Name = "openSerialCommandWindowToolStripMenuItem";
            this.openSerialCommandWindowToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openSerialCommandWindowToolStripMenuItem.Size = new System.Drawing.Size(284, 22);
            this.openSerialCommandWindowToolStripMenuItem.Text = "Open Serial Command Window";
            this.openSerialCommandWindowToolStripMenuItem.Click += new System.EventHandler(this.OnClickOpenSerialCMDWindow);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1259, 698);
            this.Controls.Add(this.tlpMainContainer);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "frmMain";
            this.Text = "Camera Setup Tool";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmMain_FormClosed);
            this.tlpMainContainer.ResumeLayout(false);
            this.statusBar.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tlpOptions.ResumeLayout(false);
            this.tableLayoutPanel5.ResumeLayout(false);
            this.tlpImageLayout.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.winChart)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.tableLayoutPanel7.ResumeLayout(false);
            this.tableLayoutPanel7.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tlpMainContainer;
        private System.Windows.Forms.TableLayoutPanel tlpMain;
        private System.Windows.Forms.Panel statusBar;
        private System.Windows.Forms.Label lblColorValue;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label lblRowColData;
        private System.Windows.Forms.Panel panel5;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.TableLayoutPanel tlpOptions;
        private System.Windows.Forms.RadioButton btnFFC;
        private System.Windows.Forms.RadioButton btnWhiteBalancing;
        private System.Windows.Forms.RadioButton btnLightIntensityCheck;
        private System.Windows.Forms.RadioButton btnFocusSetting;
        private System.Windows.Forms.RadioButton btnImageViewer;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel7;
        private System.Windows.Forms.Label lblInstruction;
        private System.Windows.Forms.Panel pnlControls;
        private System.Windows.Forms.TableLayoutPanel tlpImageLayout;
        private ChartDirector.WinChartViewer winChart;
        private System.Windows.Forms.GroupBox groupBox1;
        private HalconWindowControl hwcIRImage;
        private System.Windows.Forms.GroupBox groupBox2;
        private HalconWindowControl hwcRGBImage;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveSettingsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openSerialCommandWindowToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveImageToolStripMenuItem;
    }
}