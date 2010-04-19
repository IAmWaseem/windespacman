using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PacManGame
{
    class PacManDraw: IDrawObject
    {
        const int pacanimdelay = 2;
        const int pacmananimcount = 4;

        int pacmananimpos = 0;
        int pacanimcount = pacanimdelay;
        int pacanimdir = 1;

        static Image pacman1, pacman2up, pacman2left, pacman2right, pacman2down;
        static Image pacman3up, pacman3down, pacman3left, pacman3right;
        static Image pacman4up, pacman4down, pacman4left, pacman4right;

        public PacManDraw()
        {
            if (pacman4right == null)
                GetImages();
        }

        private static void GetImages()
        {
            pacman1 = Image.FromFile("../../Images/PacMan1.gif");
            pacman2up = Image.FromFile("../../Images/PacMan2up.gif");
            pacman3up = Image.FromFile("../../Images/PacMan3up.gif");
            pacman4up = Image.FromFile("../../Images/PacMan4up.gif");

            pacman2down = Image.FromFile("../../Images/PacMan2down.gif");
            pacman3down = Image.FromFile("../../Images/PacMan3down.gif");
            pacman4down = Image.FromFile("../../Images/PacMan4down.gif");

            pacman2left = Image.FromFile("../../Images/PacMan2left.gif");
            pacman3left = Image.FromFile("../../Images/PacMan3left.gif");
            pacman4left = Image.FromFile("../../Images/PacMan4left.gif");

            pacman2right = Image.FromFile("../../Images/PacMan2right.gif");
            pacman3right = Image.FromFile("../../Images/PacMan3right.gif");
            pacman4right = Image.FromFile("../../Images/PacMan4right.gif");
        }

        public void DoAnim()
        {
            pacanimcount--;
            if (pacanimcount <= 0)
            {
                pacanimcount = pacanimdelay;
                pacmananimpos = pacmananimpos + pacanimdir;
                if (pacmananimpos == (pacmananimcount - 1) || pacmananimpos == 0)
                    pacanimdir = -pacanimdir;
            }
        }

        public void Draw(Graphics g, Point pixelPosition, Point direction)
        {
            if (direction.X == -1)
                DrawPacManLeft(g, pixelPosition);
            else if (direction.X == 1)
                DrawPacManRight(g, pixelPosition);
            else if (direction.Y == -1)
                DrawPacManUp(g, pixelPosition);
            else
                DrawPacManDown(g, pixelPosition);
        }

        private void DrawPacManUp(Graphics g, Point pixelPosition)
        {
            Image image = null;
            switch (pacmananimpos)
            {
                case 1:
                    image = pacman2up;
                    break;
                case 2:
                    image = pacman3up;
                    break;
                case 3:
                    image = pacman4up;
                    break;
                default:
                    image = pacman1;
                    break;
            }
            g.DrawImage(image, pixelPosition.X + 1, pixelPosition.Y + 1);
        }

        private void DrawPacManDown(Graphics g, Point pixelPosition)
        {
            Image image = null;
            switch (pacmananimpos)
            {
                case 1:
                    image = pacman2down;
                    break;
                case 2:
                    image = pacman3down;
                    break;
                case 3:
                    image = pacman4down;
                    break;
                default:
                    image = pacman1;
                    break;
            }
            g.DrawImage(image, pixelPosition.X + 1, pixelPosition.Y + 1);
        }

        private void DrawPacManLeft(Graphics g, Point pixelPosition)
        {
            Image image = null;
            switch (pacmananimpos)
            {
                case 1:
                    image = pacman2left;
                    break;
                case 2:
                    image = pacman3left;
                    break;
                case 3:
                    image = pacman4left;
                    break;
                default:
                    image = pacman1;
                    break;
            }
            g.DrawImage(image, pixelPosition.X + 1, pixelPosition.Y + 1);
        }

        private void DrawPacManRight(Graphics g, Point pixelPosition)
        {
            Image image = null;
            switch (pacmananimpos)
            {
                case 1:
                    image = pacman2right;
                    break;
                case 2:
                    image = pacman3right;
                    break;
                case 3:
                    image = pacman4right;
                    break;
                default:
                    image = pacman1;
                    break;
            }
            g.DrawImage(image, pixelPosition.X + 1, pixelPosition.Y + 1);
        }

        public void Death(Graphics g, int count, Point position)
        {
            int k = (count & 15) / 4;
            Image image;
            switch (k)
            {
                case 0:
                    image = pacman4up;
                    break;
                case 1:
                    image = pacman4right;
                    break;
                case 2:
                    image = pacman4down;
                    break;
                default:
                    image = pacman4left;
                    break;
            }
            g.DrawImage(image, position.X + 1, position.Y + 1);
        }
    }
}
