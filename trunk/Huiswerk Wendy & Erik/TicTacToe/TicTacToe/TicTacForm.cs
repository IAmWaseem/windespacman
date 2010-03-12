using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace TicTacToe
{
    public partial class TicTacForm : Form
    {
        public TicTacForm()
        {
            InitializeComponent();

            InitGame();
            StartGame();
        }

        Player One;
        Player Two;
        Player None;

        List<TicTacField> GameGrid;

        private void InitGame()
        {
            GameGrid = new List<TicTacField>();

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                    TicTacField temp = new TicTacField();
                    temp.Player = 0;
                    temp.X = i;
                    temp.Y = j;
                    GameGrid.Add(temp);
                }

            One = new Player();
            One.PlayerNumber = 1;
            if (player1Human.Checked)
                One.Controller = Controller.Human;
            else
                One.Controller = Controller.AI;

            Two = new Player();
            Two.PlayerNumber = 2;
            if (player1Human.Checked)
                Two.Controller = Controller.Human;
            else
                Two.Controller = Controller.AI;

            None = new Player();
            None.PlayerNumber = 0;
            None.Controller = Controller.None;
        }


        Thread thread;
        int CurrentPlayer;
        private void StartGame()
        {
            // first player to move
            Random rand = new Random();
            CurrentPlayer = rand.Next(1, 3);
            if (CurrentPlayer < 1 || CurrentPlayer > 2)
                CurrentPlayer = 1;

            Game.GameRuns = true;

            ThreadStart start = new ThreadStart(Gameloop);
            thread = new Thread(start);
            thread.Start();
        }

        private bool firstMove = false;
        private bool winner = false;
        private bool validMove = true;
        private bool DoTheLoop = false;
        private int tempSelected;
        private void Gameloop()
        {
            while (Game.GameRuns)
            {
                if (DoTheLoop)
                {
                    validMove = true;
                    if (!winner)
                    {
                        List<TicTacField> ttList = GameGrid.Where(n => n.X == xCol && n.Y == yCol).ToList();

                        TicTacField temp = ttList[0];
                        int index = GameGrid.IndexOf(temp);

                        if (temp.Player == 0)
                        {
                            temp.Player = CurrentPlayer;

                            if ((CountTicTacFields(CurrentPlayer) < 3 && GameWithATwist.Checked) || GameClassic.Checked)
                            {
                                GameGrid[index] = temp;
                                if (CurrentPlayer == 1)
                                    CurrentPlayer = 2;
                                else
                                    CurrentPlayer = 1;
                            }
                            else
                            {
                                if (CountTicTacFields(CurrentPlayer) == 3 && GameWithATwist.Checked)
                                {
                                    if (tempSelected > -1)
                                    {
                                        TicTacField otherTemp = GameGrid[tempSelected];
                                        int indexOther = GameGrid.IndexOf(otherTemp);

                                        temp.Player = CurrentPlayer;
                                        otherTemp.Player = 0;

                                        GameGrid[index] = otherTemp;
                                        GameGrid[indexOther] = temp;

                                        if (CurrentPlayer == 1)
                                            CurrentPlayer = 2;
                                        else
                                            CurrentPlayer = 1;
                                    }
                                    else
                                    {
                                        validMove = false;
                                    }
                                }
                            }
                            tempSelected = -1;
                        }
                        else
                        {
                            // already selected
                            if (CountTicTacFields(CurrentPlayer) == 3 && GameWithATwist.Checked)
                            {
                                if (temp.Player == CurrentPlayer)
                                    tempSelected = GameGrid.IndexOf(temp);
                                else
                                {
                                    tempSelected = -1;
                                    validMove = false;
                                }
                            }
                            if (GameClassic.Checked && CountTicTacFields(0) <= 0)
                            {
                                tempSelected = -1;
                                validMove = false;
                            }
                        }
                        winner = CalculateWinner();                        
                    }
                    DoTheLoop = false;
                }
            }
        }

        private List<Point> WinningPoints = new List<Point>();
        private int WinningPlayer = 0;
        private bool CalculateWinner()
        {
            // create temp grid with playernumbers
            List<List<int>> grid = new List<List<int>>();
            List<int> grid0 = new List<int>();
            grid0.Add(0); grid0.Add(0); grid0.Add(0);
            List<int> grid1 = new List<int>();
            grid1.Add(0); grid1.Add(0); grid1.Add(0);
            List<int> grid2 = new List<int>();
            grid2.Add(0); grid2.Add(0); grid2.Add(0);
            grid.Add(grid0);
            grid.Add(grid1);
            grid.Add(grid2);
            
            for (int i = 0; i < GameGrid.Count; i++)
            {
                TicTacField ttf = GameGrid[i];
                grid[ttf.X][ttf.Y] = ttf.Player;
            }

            // horizontal column
            for (int i = 0; i <= 2; i++)
            {

                if ((grid[0][i] > 0 && grid[1][i] > 0 && grid[2][i] > 0) && (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]))
                {
                    WinningPoints.Clear();
                    WinningPoints.Add(new Point(0, i));
                    WinningPoints.Add(new Point(1, i));
                    WinningPoints.Add(new Point(2, i));
                    WinningPlayer = grid[0][i];
                    return true;
                }
            }

            // vertical column
            for (int i = 0; i <= 2; i++)
            {

                if ((grid[i][0] > 0 && grid[i][1] > 0 && grid[i][2] > 0) && (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]))
                {                    
                    WinningPoints.Clear();
                    WinningPoints.Add(new Point(i, 0));
                    WinningPoints.Add(new Point(i, 1));
                    WinningPoints.Add(new Point(i, 2));
                    WinningPlayer = grid[i][0];
                    return true;
                }
            }

            // diagonal left-top to right-bottom
            if ((grid[0][0] > 0 && grid[1][1] > 0 && grid[2][2] > 0) && (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]))
            {
                WinningPoints.Clear();
                WinningPoints.Add(new Point(0, 0));
                WinningPoints.Add(new Point(1, 1));
                WinningPoints.Add(new Point(2, 2));
                WinningPlayer = grid[0][0];
                return true;
            }

            // diagonal left-bottom to right-top
            if ((grid[0][2] > 0 && grid[1][1] > 0 && grid[2][0] > 0) && (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]))
            {
                WinningPoints.Clear();
                WinningPoints.Add(new Point(0, 2));
                WinningPoints.Add(new Point(1, 1));
                WinningPoints.Add(new Point(2, 0));
                WinningPlayer = grid[0][2];
                return true;
            }            
            return false;
        }

        private int CountTicTacFields(int playernumber)
        {
            int count = 0;
            for (int i = 0; i < GameGrid.Count; i++)
            {
                if (GameGrid[i].Player == playernumber)
                    count++;
            }
            return count;
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            if (ClickedPosition != new Point())
            {
                int CircleWidth = 10;
                g.DrawEllipse(Pens.Green, ClickedPosition.X - (CircleWidth / 2), ClickedPosition.Y - (CircleWidth / 2), CircleWidth, CircleWidth);
            }
            if (firstMove)
            {
                GameClassic.Enabled = false;
                GameWithATwist.Enabled = false;
            }

            Brush rectBrush = Brushes.LightGray;
            if (!DoTheLoop)
            {
                for (int i = 0; i < GameGrid.Count; i++)
                {
                    TicTacField ttf = GameGrid[i];
                    
                        if (ttf.Player == One.PlayerNumber)
                            rectBrush = Brushes.Orange;
                        else if (ttf.Player == Two.PlayerNumber)
                            rectBrush = Brushes.LightBlue;
                        else if (ttf.Player == None.PlayerNumber)
                            rectBrush = Brushes.LightGray;
                    
                    if (tempSelected > -1)
                    {
                        if(GameGrid.IndexOf(ttf) == tempSelected)
                            if (ttf.Player == One.PlayerNumber)
                                rectBrush = Brushes.Red;
                            else if (ttf.Player == Two.PlayerNumber)
                                rectBrush = Brushes.Blue;
                            else
                                rectBrush = Brushes.LightGray;
                    }
                    g.FillRectangle(rectBrush, (400 / 3) * ttf.X, (400 / 3) * ttf.Y, (400 / 3), (400 / 3));
                }
            }
            else
                panel1.Invalidate();            

            CurrentPlayerLabel.Text = "Turn of player " + CurrentPlayer;
            if (validMove)
                label1.Text = "Valid move";
            else
                label1.Text = "Non-valid move";

            Pen BorderPen = new Pen(Brushes.Gray, 3);
            g.DrawLine(BorderPen, (400 / 3) * 1, 0, (400 / 3) * 1, 400);
            g.DrawLine(BorderPen, (400 / 3) * 2, 0, (400 / 3) * 2, 400);

            g.DrawLine(BorderPen, 0, (400 / 3) * 1, 400, (400 / 3) * 1);
            g.DrawLine(BorderPen, 0, (400 / 3) * 2, 400, (400 / 3) * 2);
            if (winner)
            {
                winner = false;
                firstMove = false;
                GameClassic.Enabled = true;
                GameWithATwist.Enabled = true;
                string playerColor = "";
                if (WinningPlayer == 1)
                    playerColor = "orange";
                else if (WinningPlayer == 2)
                    playerColor = "light blue";
                else
                    playerColor = "light gray";
                MessageBox.Show("Player " + WinningPlayer + " (" + playerColor + ") has won! Click OK for a new game");
                thread.Abort();
                WinningPlayer = 0;
                InitGame();
                StartGame();
                panel1.Invalidate();
            }
        }

        int xCol = -1;
        int yCol = -1;
        Point ClickedPosition;
        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                ClickedPosition = new Point(e.X, e.Y);

                if (ClickedPosition != new Point())
                {
                    if (ClickedPosition.X < (400 / 3) * 1)
                        xCol = 0;
                    else if (ClickedPosition.X < (400 / 3) * 2)
                        xCol = 1;
                    else
                        xCol = 2;

                    if (ClickedPosition.Y < (400 / 3) * 1)
                        yCol = 0;
                    else if (ClickedPosition.Y < (400 / 3) * 2)
                        yCol = 1;
                    else
                        yCol = 2;
                }

                DoTheLoop = true;
                firstMove = true;
            }
            panel1.Invalidate();
        }

        struct Player
        {
            public Controller Controller;
            public int PlayerNumber;
        }

        struct TicTacField
        {
            public int X;
            public int Y;
            public int Player;
        }

        enum Controller
        {
            Human = 1,
            AI = 2,
            None = 3
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            Game.GameRuns = false;
            if (thread.ThreadState == ThreadState.Running)
            {
                thread.Abort();
            }
        }
    }
}
