using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Karo
{
    /// <summary>
    /// Wrapper class for the logger
    /// </summary>
    public class Logger
    {
        private LogForm mLogForm;
        private static Logger mLogger;

        /// <summary>
        /// Provides the instance to the logger
        /// </summary>
        public static Logger Instance
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
        /// Constructor for logger
        /// </summary>
        private Logger()
        {
            mLogForm = new LogForm();
        }

        /// <summary>
        /// Brings to front
        /// </summary>
        public static void BringToFront()
        {
            Instance.mLogForm.BringToFront();
        }

        /// <summary>
        /// Will show the log window
        /// </summary>
        public static void ShowLog()
        {
            Instance.mLogForm.Show();
            Instance.mLogForm.Visible = true;
            Instance.mLogForm.BringToFront();
        }

        /// <summary>
        /// Hides the log window
        /// </summary>
        public static void HideLog()
        {
            Instance.mLogForm.Visible = false;
        }

        /// <summary>
        /// Will close the log window
        /// </summary>
        public static void CloseLog()
        {
            Instance.mLogForm.Close();
        }

        /// <summary>
        /// Adds a line to the log textbox
        /// </summary>
        /// <param name="s">Text to add</param>
        public static void AddLine(string s)
        {
            Instance.mLogForm.AddLine(s);
        }

        /// <summary>
        /// Clears the log
        /// </summary>
        public static void ClearLog()
        {
            Instance.mLogForm.ClearLog();
        }
    }
}
