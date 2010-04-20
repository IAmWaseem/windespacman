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
    /// <summary>
    /// WinForms window with a textbox on it to show log information
    /// </summary>
    public partial class Logger : Form
    {
        /// <summary>
        /// Constructor for the logger
        /// </summary>
        private Logger()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Contains the instance
        /// </summary>
        private static Logger mLogger;
        
        /// <summary>
        /// Instance of the logger
        /// </summary>
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

        /// <summary>
        /// Will show the log window
        /// </summary>
        public static void ShowLog()
        {
            Instance.Show();
        }

        /// <summary>
        /// Will close the log window
        /// </summary>
        public static void CloseLog()
        {
            Instance.Close();
        }

        /// <summary>
        /// Adds a line to the log textbox
        /// </summary>
        /// <param name="s">Text to add</param>
        public static void AddLine(string s)
        {
            Instance.mLogTextBox.Text += s + Environment.NewLine;
        }

        /// <summary>
        /// Clears the log
        /// </summary>
        public static void ClearLog()
        {
            Instance.mLogTextBox.Text = "";
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

        private void Logger_FormClosing(object sender, FormClosingEventArgs e)
        {
            mLogger = null;
        }

        #endregion        
    }
}
