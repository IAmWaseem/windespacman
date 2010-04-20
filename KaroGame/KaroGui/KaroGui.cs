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

            // Other stuff
            Logger.AddLine("Hoi");
            Logger.AddLine("Ik");
            Logger.AddLine("Ben");
            Logger.AddLine("Logger");
            Logger.ShowLog();
            
        }
    }
}
