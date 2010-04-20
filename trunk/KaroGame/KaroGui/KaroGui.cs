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
            Logger.ShowLog();

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

        private float tileWidth = 0;
        private float tileHeight = 0;
        private void mDrawPanel_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;

            Board currentBoard = UIConnector.Instance.GetBoard();
            tileWidth = mDrawPanel.Width / 21;
            tileHeight = mDrawPanel.Height / 20;

            if (currentBoard != null)
            {
                BoardPosition[,] board = currentBoard.GetBoardState();

                for (int x = 0; x < 21; x++)
                {
                    for (int y = 0; y < 20; y++)
                    {
                        BoardPosition bp = board[x, y];
                        Brush brush = Brushes.White;

                        if (bp != BoardPosition.Empty)
                            brush = Brushes.Black;

                        if (mClickedPosition != null)
                            if (mClickedPosition.X == x && mClickedPosition.Y == y && bp == BoardPosition.Tile)
                                brush = Brushes.DimGray;

                        g.FillRectangle(brush,
                            x * tileWidth, y * tileHeight, tileWidth, tileHeight);
                        g.DrawRectangle(Pens.Gray,
                            x * tileWidth, y * tileHeight, tileWidth, tileHeight);

                        if (bp != BoardPosition.Empty && bp != BoardPosition.Tile)
                        {
                            Brush pieceColor = Brushes.Red;
                            if (bp == BoardPosition.WhiteHead || bp == BoardPosition.WhiteTail)
                                pieceColor = Brushes.White;

                            if (mClickedPosition != null)
                            {
                                if (mClickedPosition.X == x && mClickedPosition.Y == y)
                                {
                                    if (bp == BoardPosition.RedHead || bp == BoardPosition.RedTail)
                                        pieceColor = Brushes.Gold;
                                    else if (bp == BoardPosition.WhiteHead || bp == BoardPosition.WhiteTail)
                                    {
                                        pieceColor = Brushes.DeepPink;
                                    }

                                }
                            }

                            float maxPieceWidth = Math.Min(tileHeight, tileWidth) * 0.90f;

                            float pieceX = (tileWidth - maxPieceWidth) / 2f;
                            float pieceY = (tileHeight - maxPieceWidth) / 2f;                            

                            g.FillEllipse(pieceColor,
                                x * tileWidth + pieceX, y * tileHeight + pieceY, maxPieceWidth, maxPieceWidth);
                            
                            if (bp == BoardPosition.RedHead || bp == BoardPosition.WhiteHead)
                            {
                                float maxHeadWidth = (Math.Min(tileHeight, tileWidth) * 0.50f);

                                float headX = (tileWidth - maxHeadWidth) / 2f;
                                float headY = (tileHeight - maxHeadWidth) / 2f;

                                g.DrawEllipse(Pens.Black,
                                    x * tileWidth + headX, y * tileHeight + headY, maxHeadWidth, maxHeadWidth);
                            }
                        }
                    }
                }
            }
        }

        private void mDrawPanel_Resize(object sender, EventArgs e)
        {
            mDrawPanel.Invalidate();
        }

        private Point mClickedPosition;
        private void mDrawPanel_MouseUp(object sender, MouseEventArgs e)
        {
            int x = (int) Math.Truncate(e.X / tileWidth);
            int y = (int) Math.Truncate(e.Y / tileHeight);
            mClickedPosition = new Point(x, y);
            mDrawPanel.Invalidate();
            Logger.AddLine("Mouse X:" + x + " Y:" + y);
        }
    }
}
