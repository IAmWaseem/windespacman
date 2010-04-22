using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace Karo
{
    /// <summary>
    /// WinForms window with a textbox on it to show log information
    /// </summary>
    public partial class LogForm : Form
    {
        /// <summary>
        /// Constructor for the logger
        /// </summary>
        public LogForm()
        {
            InitializeComponent();
            mLogTextBox.WordWrap = true;
        }

        /// <summary>
        /// Adds a line to the textbox and scrolls to the bottom
        /// </summary>
        /// <param name="s"></param>
        public void AddLine(string s)
        {
            mLogTextBox.Text += s + Environment.NewLine;
            mLogTextBox.SelectionStart = mLogTextBox.Text.Length;
            mLogTextBox.ScrollToCaret();
        }

        /// <summary>
        /// Clears the textbox
        /// </summary>
        public void ClearLog()
        {
            mLogTextBox.Text = "";
        }

        /// <summary>
        /// Saves the log
        /// </summary>
        /// <param name="s"></param>
        public void SaveLog(string s)
        {
            StreamWriter sw;
            sw = File.CreateText(s);

            sw.WriteLine("Log created at " + DateTime.Now.ToLocalTime());
            sw.WriteLine("============================================");
            sw.WriteLine();

            sw.Write(mLogTextBox.Text);

            sw.Close();

            MessageBox.Show("Log saved in: '" + s + "'");
        }

        #region "Event Handling"

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void clearToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            ClearLog();
        }

        private void saveToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            SaveLog("log.txt");
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();

            sfd.InitialDirectory = Directory.GetCurrentDirectory();
            sfd.Filter = "Text file|*.txt";
            sfd.Title = "Save the log";

            sfd.ShowDialog();

            if (sfd.FileName != "")
            {
                SaveLog(sfd.FileName);
            }
        }

        #endregion     
    }
}
