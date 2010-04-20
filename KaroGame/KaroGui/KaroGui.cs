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
        public KaroGui()
        {
            InitializeComponent();     
            PlayerSettings playerA = new PlayerSettings();
            PlayerSettings playerB = new PlayerSettings();

            UIConnector.Instance.StartGame(playerA, playerB);
                        
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

        private void KaroGui_Paint(object sender, PaintEventArgs e)
        {
            Board currentBoard = UIConnector.Instance.GetBoard();
            if (currentBoard != null)
            {
                BoardPosition[,] board = currentBoard.GetBoardState();

                foreach (BoardPosition b in board)
                {

                }
            }
        }
    }
}
