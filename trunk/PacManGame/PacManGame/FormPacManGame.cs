using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PacManGame
{
    public partial class FormPacManGame : Form
    {
        public FormPacManGame()
        {
            InitializeComponent();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            World.Instance.Render(e.Graphics);
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            timer1.Enabled = true;
        }


        long elapsedTime = 0;

        private void timer1_Tick(object sender, EventArgs e)
        {
            elapsedTime += timer1.Interval;

            World.Instance.Update(elapsedTime);         //  compute new situation
            pictureBox1.Invalidate();                   //  causes world to render
        }
    }
}
