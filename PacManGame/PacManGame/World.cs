using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace PacManGame
{
    class World
    {
        //  private attributes  //

        List<Ghost> ghost;
        int food = 0;
        long elapsedTime = 0;
        bool gameOver = false;
        long finalScore = 0;
        int score = 0;

        //  public attributes //
        public PacMan pacMan;

        //  singleton pattern   //
        private static World instance;
        private World()
        {
            pacMan = new PacMan();
            ghost = new List<Ghost>();
            for (int i = 0; i < 4; i++)
                ghost.Add(new Ghost());

            int j = 0;
            while (j < NROFBLOCKS * NROFBLOCKS)
            {
                if ((screendata[j] & (POWER | DOT)) != 0)
                    food++;
                j++;
            }
        }

        //  public methos   //
        public static World Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new World();
                }
                return instance;
            }
        }

        public void Update(long elapsedTime)
        {
            this.elapsedTime = elapsedTime;

            foreach (Ghost aghost in ghost)
                aghost.Update();

            pacMan.Update();

            if (pacMan.InGrid())
            {
                if (IsSpot(pacMan.GridPosition, DOT))
                {
                    ResetSpot(pacMan.GridPosition);
                    ChangeScore(1);
                    food--;
                }

                if (IsSpot(pacMan.GridPosition, POWER))
                {
                    //maze.mazeState.Scared = true;
                    //maze.scaredCount = maze.scaredTime;
                    ResetSpot(pacMan.GridPosition);
                    ChangeScore(25);
                    food--;
                }
            }

            if (food <= 0 && !gameOver)
            {
                gameOver = true;
                finalScore = score * 100 / (elapsedTime / 1000);
            }


        }

        public void Render(Graphics g)
        {
            g.Clear(Color.Black);
            DrawMaze(g);
            foreach (Ghost aghost in ghost)
                aghost.Render(g);
            pacMan.Render(g);

            if (gameOver)
            {
                Font font = new Font("Verdana", 24, FontStyle.Bold);
                Brush brush = new SolidBrush(Color.Red);
                g.DrawString("    GAME OVER  ", font, brush, 0, 100);
                g.DrawString("Final Score: " + finalScore, font, brush, 0, 200);
            }
        }

        int previousValue = 0;

        public void ChangeScore(int value)
        {
            if (value < 0 && previousValue < 0)
                return; //   count negative value not more than once

            previousValue = value;
            score += value;
        }


        //  public methods telling you facts about this world's current situation //

        public bool CanLeft(Point p)
        {
            return (screendata[p.X + p.Y * NROFBLOCKS] & LEFT) == 0;
        }

        public bool CanUp(Point p)
        {
            return (screendata[p.X + p.Y * NROFBLOCKS] & UP) == 0;
        }

        public bool CanRight(Point p)
        {
            return (screendata[p.X + p.Y * NROFBLOCKS] & RIGHT) == 0;
        }

        public bool CanDown(Point p)
        {
            return (screendata[p.X + p.Y * NROFBLOCKS] & DOWN) == 0;
        }

        public bool CanNoWay(Point p)
        {
            return (screendata[p.X + p.Y * NROFBLOCKS] & BLOCKED) == BLOCKED;      //  all ways blocked
        }

        public bool IsSpot(Point p, short value)
        {
            return (screendata[p.X + p.Y * NROFBLOCKS] & value) != 0;
        }

        public void ResetSpot(Point p)
        {
            screendata[p.X + p.Y * NROFBLOCKS] &= BLOCKED;
        }

        public bool IsThereAGhostAtPixel(Point pixelPostion)
        {
            foreach (Ghost aghost in ghost)
                if (aghost.IsClose(pixelPostion, BLOCKSIZE))
                    return true;

            return false;
        }


        //  public static methods   //
        public static int GetRandomInt(int max)
        {
            return randInt.Next(max);
        }

        //  private attributes  //
        static Random randInt = new Random();


        //  THE REMAINING CODE IS COPIED CODE   //

        short[] screendata = { 
	19,26,26,22, 9,12,19,26,22, 9,12,19,26,26,22,
	37,11,14,17,26,26,20,15,17,26,26,20,11,14,37,
	17,26,26,20,11, 6,17,26,20, 3,14,17,26,26,20,
	21, 3, 6,25,22, 5,21, 7,21, 5,19,28, 3, 6,21,
	21, 9, 8,14,21,13,21, 5,21,13,21,11, 8,12,21,
	25,18,26,18,24,18,28, 5,25,18,24,18,26,18,28,
	 6,21, 7,21, 7,21,11, 8,14,21, 7,21, 7,21,03,
	 4,21, 5,21, 5,17,26,26,26,20, 5,21, 5,21, 1,
	12,21,13,21,13,21,11,10,14,21,13,21,13,21, 9,
	19,24,26,24,26,16,26,18,26,16,26,24,26,24,22,
	21, 3, 2, 2, 6,21,15,21,15,21, 3, 2, 2,06,21,
	21, 9, 8, 8, 4,17,26, 8,26,20, 1, 8, 8,12,21,
	17,26,26,22,13,21,11, 2,14,21,13,19,26,26,20,
	37,11,14,17,26,24,22,13,19,24,26,20,11,14,37,
	25,26,26,28, 3, 6,25,26,28, 3, 6,25,26,26,28  };

        public static short LEFT = 1;
        public static short UP = 2;
        public static short RIGHT = 4;
        public static short DOWN = 8;
        public static short BLOCKED = 15;
        public static short DOT = 16;
        public static short POWER = 32;
        public const int BLOCKSIZE = 24;
        public const int NROFBLOCKS = 15;

        const int scrsize = NROFBLOCKS * BLOCKSIZE;
        const int maxScaredTime = 120;
        const int minScaredTime = 20;

        Color dotcolor = Color.FromArgb(192, 192, 0);
        Color mazecolor = Color.Aqua;
        int bigdotcolor = 192;
        int dbigdotcolor = -2;

        public void DrawMaze(Graphics g)
        {
            short i = 0;
            int x, y;

            bigdotcolor = bigdotcolor + dbigdotcolor;
            if (bigdotcolor <= 64 || bigdotcolor >= 192)
                dbigdotcolor = -dbigdotcolor;

            Pen pen = new Pen(mazecolor, 2);
            Brush brush1 = new SolidBrush(dotcolor);
            Brush brush2 = new SolidBrush(Color.FromArgb(224, 224 - bigdotcolor, bigdotcolor));

            for (y = 0; y < scrsize; y += BLOCKSIZE)
            {
                for (x = 0; x < scrsize; x += BLOCKSIZE)
                {
                    if ((screendata[i] & LEFT) != 0)
                    {
                        g.DrawLine(pen, x, y, x, y + BLOCKSIZE);
                    }
                    if ((screendata[i] & UP) != 0)
                    {
                        g.DrawLine(pen, x, y, x + BLOCKSIZE, y);
                    }
                    if ((screendata[i] & RIGHT) != 0)
                    {
                        g.DrawLine(pen, x + BLOCKSIZE, y, x + BLOCKSIZE, y + BLOCKSIZE);
                    }
                    if ((screendata[i] & DOWN) != 0)
                    {
                        g.DrawLine(pen, x, y + BLOCKSIZE, x + BLOCKSIZE, y + BLOCKSIZE);
                    }
                    if ((screendata[i] & DOT) != 0)
                    {
                        g.FillRectangle(brush1, x + 11, y + 11, 2, 2);
                    }
                    if ((screendata[i] & POWER) != 0)
                    {
                        g.FillRectangle(brush2, x + 8, y + 8, 8, 8);
                    }
                    i++;
                }
            }

            Font font = new Font("Arial", 12);
            Brush brush = new SolidBrush(Color.Red);
            g.DrawString("Scored points: " + score.ToString("0"), font, brush, 0, scrsize + 18);
            g.DrawString("Food left: " + food, font, brush, 140, scrsize + 18);
            g.DrawString("Time: " + this.elapsedTime / 1000, font, brush, 300, scrsize + 18);
            brush = new SolidBrush(Color.Aqua);
            g.DrawString("Author: " + pacMan.AuthorName(), font, brush, 0, scrsize + 36);
        }

    }
}
