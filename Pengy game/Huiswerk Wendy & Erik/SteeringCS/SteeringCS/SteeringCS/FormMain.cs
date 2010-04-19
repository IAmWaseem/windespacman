using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SteeringCS
{
    public partial class FormSteeringCS : Form
    {
        string steeringName = "None";

        public FormSteeringCS()
        {
            InitializeComponent();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            World.Instance.Init(steeringName);
             World.Instance.mirrored = checkBox1.Checked;
           this.pictureBox1.Size = World.Instance.ClientSize;
            timer1.Enabled = true;
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            World.Instance.Render(e.Graphics);   
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            World.Instance.Update(100);
            this.pictureBox1.Invalidate();
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (World.Instance.target != null)
                World.Instance.target.CurrentPosition = new Vector2D(e.X, e.Y);
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            this.steeringName = ((RadioButton)sender).Text;
            timer1.Enabled = false;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            World.Instance.mirrored = checkBox1.Checked;
        }


    }
}
