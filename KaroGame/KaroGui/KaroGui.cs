using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using Karo;

namespace Karo.Gui
{
    public partial class KaroGui : Form
    {
        /// <summary>
        /// The engine for the game
        /// </summary>
        public UIConnector KaroEngine { get; set; }

        public KaroGui()
        {
            InitializeComponent();

            // Load the Karo Engine
            this.KaroEngine = new UIConnector();

            
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void clearToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.ClearLog();
        }

        private void showToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.ShowLog();
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Logger.CloseLog();
        }
    }
}
