using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace PacManGame
{
    class GhostDraw: IDrawObject
    {
        int ghostanimpos = 0;
        int animcount = animdelay;
        const int ghostanimcount = 2;
        const int animdelay = 8;
        static Image[] images = new Image[4];

        public GhostDraw()
        {
            GetImages();
        }

        public static void GetImages()
        {
            images[0] = Image.FromFile("../../Images/Ghost1.gif");
            images[1] = Image.FromFile("../../Images/Ghost2.gif");
            images[2] = Image.FromFile("../../Images/GhostScared1.gif");
            images[3] = Image.FromFile("../../Images/GhostScared2.gif");
        }

        public void DoAnim()
        {
            animcount--;
            if (animcount <= 0)
            {
                animcount = animdelay;
                ghostanimpos++;
                if (ghostanimpos >= ghostanimcount)
                    ghostanimpos = 0;
            }
        }

        public void Draw(Graphics g, Point pixelPosition, Point direction)
        {
            int image = 0;

            if (ghostanimpos == 0)  // && !maze.mazeState.Scared)
            {
                image = 0;
            }
            else if (ghostanimpos == 1) // && !maze.mazeState.Scared)
            {
                image = 1;
            }

                /*
            else if (ghostanimpos == 0 && maze.mazeState.Scared)
            {
                image = 2;
            }
            else if (ghostanimpos == 1 && maze.mazeState.Scared)
            {
                image = 3;
            }
                 * */

            g.DrawImage(images[image], pixelPosition.X + 1, pixelPosition.Y + 1);
        }
    }

}
