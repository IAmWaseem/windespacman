using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Karo
{
    public partial class Logger : Form
    {
        public Logger()
        {
            InitializeComponent();
        }

        private static Logger mLogger;
        private static Logger Instance
        {
            get
            {
                if (mLogger == null)
                {
                    mLogger = new Logger();
                }
                return mLogger;
            }
            set 
            { 
                mLogger = value; 
            }
        }

        public static void ShowLog()
        {
            Instance.Show();
        }

        public static void AddLine(string s)
        {
            Instance.textBox1.Text += s + Environment.NewLine;
        }

        public static void ClearLog()
        {
            Instance.textBox1.Text = "";
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ClearLog();
        }

        private void Logger_FormClosing(object sender, FormClosingEventArgs e)
        {
            mLogger = null;
        }
    }
}
