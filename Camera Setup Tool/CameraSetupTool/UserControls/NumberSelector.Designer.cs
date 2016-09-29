namespace CameraSetupTool.UserControls
{
    partial class NumberSelector
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
            this.pnlbtnMinus = new System.Windows.Forms.Panel();
            this.btnDecrement = new System.Windows.Forms.Button();
            this.pnlLabel = new System.Windows.Forms.Panel();
            this.lblValue = new System.Windows.Forms.Label();
            this.pnlbtnPlus = new System.Windows.Forms.Panel();
            this.btnIncrement = new System.Windows.Forms.Button();
            this.pnlbtnMinus.SuspendLayout();
            this.pnlLabel.SuspendLayout();
            this.pnlbtnPlus.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlbtnMinus
            // 
            this.pnlbtnMinus.Controls.Add(this.btnDecrement);
            this.pnlbtnMinus.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlbtnMinus.Location = new System.Drawing.Point(0, 0);
            this.pnlbtnMinus.Name = "pnlbtnMinus";
            this.pnlbtnMinus.Size = new System.Drawing.Size(75, 51);
            this.pnlbtnMinus.TabIndex = 0;
            // 
            // btnDecrement
            // 
            this.btnDecrement.BackgroundImage = global::CameraSetupTool.Properties.Resources.icon_minus_round_128;
            this.btnDecrement.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnDecrement.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnDecrement.Location = new System.Drawing.Point(0, 0);
            this.btnDecrement.Name = "btnDecrement";
            this.btnDecrement.Size = new System.Drawing.Size(75, 51);
            this.btnDecrement.TabIndex = 0;
            this.btnDecrement.UseVisualStyleBackColor = true;
            this.btnDecrement.Click += new System.EventHandler(this.OnClickDecrement);
            this.btnDecrement.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OnMouseHoldDecrement);
            this.btnDecrement.MouseUp += new System.Windows.Forms.MouseEventHandler(this.OnMouseReleaseDecrement);
            // 
            // pnlLabel
            // 
            this.pnlLabel.Controls.Add(this.lblValue);
            this.pnlLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlLabel.Location = new System.Drawing.Point(75, 0);
            this.pnlLabel.Name = "pnlLabel";
            this.pnlLabel.Size = new System.Drawing.Size(60, 51);
            this.pnlLabel.TabIndex = 1;
            // 
            // lblValue
            // 
            this.lblValue.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblValue.Font = new System.Drawing.Font("Verdana", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblValue.Location = new System.Drawing.Point(0, 0);
            this.lblValue.Name = "lblValue";
            this.lblValue.Size = new System.Drawing.Size(60, 51);
            this.lblValue.TabIndex = 0;
            this.lblValue.Text = "0";
            this.lblValue.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pnlbtnPlus
            // 
            this.pnlbtnPlus.Controls.Add(this.btnIncrement);
            this.pnlbtnPlus.Dock = System.Windows.Forms.DockStyle.Right;
            this.pnlbtnPlus.Location = new System.Drawing.Point(135, 0);
            this.pnlbtnPlus.Name = "pnlbtnPlus";
            this.pnlbtnPlus.Size = new System.Drawing.Size(65, 51);
            this.pnlbtnPlus.TabIndex = 2;
            // 
            // btnIncrement
            // 
            this.btnIncrement.BackgroundImage = global::CameraSetupTool.Properties.Resources.add_128;
            this.btnIncrement.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.btnIncrement.Dock = System.Windows.Forms.DockStyle.Fill;
            this.btnIncrement.Location = new System.Drawing.Point(0, 0);
            this.btnIncrement.Name = "btnIncrement";
            this.btnIncrement.Size = new System.Drawing.Size(65, 51);
            this.btnIncrement.TabIndex = 0;
            this.btnIncrement.UseVisualStyleBackColor = true;
            this.btnIncrement.Click += new System.EventHandler(this.OnClickIncrement);
            this.btnIncrement.MouseDown += new System.Windows.Forms.MouseEventHandler(this.OnMouseHoldIncrement);
            this.btnIncrement.MouseUp += new System.Windows.Forms.MouseEventHandler(this.OnMouseReleaseIncrement);
            // 
            // NumberSelector
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.pnlLabel);
            this.Controls.Add(this.pnlbtnMinus);
            this.Controls.Add(this.pnlbtnPlus);
            this.DoubleBuffered = true;
            this.Name = "NumberSelector";
            this.Size = new System.Drawing.Size(200, 51);
            this.Resize += new System.EventHandler(this.NumberSelector_Resize);
            this.pnlbtnMinus.ResumeLayout(false);
            this.pnlLabel.ResumeLayout(false);
            this.pnlbtnPlus.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlbtnMinus;
        private System.Windows.Forms.Panel pnlLabel;
        private System.Windows.Forms.Panel pnlbtnPlus;
        private System.Windows.Forms.Button btnIncrement;
        private System.Windows.Forms.Button btnDecrement;
        private System.Windows.Forms.Label lblValue;
    }
}
