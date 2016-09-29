using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CameraSetupTool.UserControls
{
    public partial class NumberSelector : UserControl
    {
        public NumberSelector()
        {
            InitializeComponent();
            AdjustControlWidthHeight();
            this.lblValue.Font = valueFont;
            incrementTimer.Tick += new EventHandler(incrementTimer_Tick);
            decrementTimer.Tick += new EventHandler(decrementTimer_Tick);
        }

        void decrementTimer_Tick(object sender, EventArgs e)
        {
            PerformDecrement();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            AdjustControlWidthHeight();
        }

        private void AdjustControlWidthHeight()
        {
            int width = this.ClientRectangle.Width;
            int height = this.ClientRectangle.Height;

            double a = (double)width / 100;
            this.pnlbtnMinus.Width =Convert.ToInt32((double)width / 100 * 27);
            this.pnlbtnPlus.Width = Convert.ToInt32((double)width / 100 * 27);
            this.pnlLabel.Width = Convert.ToInt32((double)width / 100 * 46);

            this.pnlbtnMinus.Height = height;
            this.pnlbtnPlus.Height = height;
            this.pnlLabel.Height = height;

            this.Invalidate();
        }

        void incrementTimer_Tick(object sender, EventArgs e)
        {
            PerformIncrement();
        }

        int initialValue = 0;
        int minimumValue = 0;
        int maximumValue = 100;
        int presentValue = 0;
        int counter = 1;
        int decrementValue = 1;
        int incrementValue = 1;
        Font valueFont = new Font("Verdana", 14.25f, FontStyle.Bold);

        Timer incrementTimer = new Timer();
        Timer decrementTimer = new Timer();

        [DefaultValue(0)]
        [Description("Indicate the value of the control")]
        public int Value
        {
            get { return this.presentValue; }
            set
            {
                this.initialValue = value;
                this.presentValue = initialValue;
                this.lblValue.Text = this.presentValue.ToString();
            }
        }

        [DefaultValue(0)]
        [Description("Indicate the minimum value of the control")]
        public int MinimumValue
        {
            get { return this.minimumValue; }
            set
            {
                this.minimumValue = value;
            }
        }

        [DefaultValue(100)]
        [Description("Indicate the maximum value of the control")]
        public int MaximumValue
        {
            get { return this.maximumValue; }
            set
            {
                this.maximumValue = value;
            }
        }

        //[DefaultValue(false)]
        //[Description("Indicates whether negative numbers are accepted or not")]
        //public bool AcceptNegativeValues
        //{
        //    get;
        //    set;
        //}

        [DefaultValue(1)]
        [Description("Indicate the amount of value to incremented by on button click")]
        public int IncrementValue
        {
            get
            {
                return this.incrementValue;
            }
            set
            {
                this.incrementValue = value;
            }
        }

        [DefaultValue(1)]
        [Description("Indicate the amount of value to decremented by on button click")]
        public int DecrementValue
        {
            get
            {
                return this.decrementValue;
            }
            set
            {
                this.decrementValue = value;
            }
        }

        [DefaultValue(typeof(Font), "Verdana, 14.25pt, style=Bold")]
        public Font FontForValue
        {
            get { return this.valueFont; }
            set
            {
                this.valueFont = value;
                this.lblValue.Font = valueFont;
            }
        }

        private void OnClickIncrement(object sender, EventArgs e)
        {
            PerformIncrement();
        }

        void PerformIncrement()
        {
            this.presentValue += this.incrementValue;
            if (this.presentValue >= this.maximumValue)
            {
                this.presentValue = this.maximumValue;
            }
            this.lblValue.Text = this.presentValue.ToString();
        }

        void PerformDecrement()
        {
            this.presentValue -= this.decrementValue;

            if (this.presentValue <= this.minimumValue)
            {
                this.presentValue = this.minimumValue;
            }

            this.lblValue.Text = this.presentValue.ToString();
        }

        private void OnClickDecrement(object sender, EventArgs e)
        {
            PerformDecrement();
        }

        private void OnMouseHoldIncrement(object sender, MouseEventArgs e)
        {
            incrementTimer.Start();
        }

        private void OnMouseReleaseIncrement(object sender, MouseEventArgs e)
        {
            incrementTimer.Stop();
        }

        private void OnMouseHoldDecrement(object sender, MouseEventArgs e)
        {
            decrementTimer.Start();
        }

        private void OnMouseReleaseDecrement(object sender, MouseEventArgs e)
        {
            decrementTimer.Stop();
        }

        private void NumberSelector_Resize(object sender, EventArgs e)
        {
            AdjustControlWidthHeight();
        }
    }
}
