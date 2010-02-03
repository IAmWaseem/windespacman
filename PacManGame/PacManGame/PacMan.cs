using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace PacManGame
{
    class PacMan:MovingObject
    {
        /***
         * Constructor: please don't modify !!
         ***/

        public PacMan(): base(new PacManDraw(), new Point(7,11), new Point(0,1), 6)
        {
        }

        /***
         * GIVE IT YOUR NAME
         * */

        public string AuthorName()
        {
            return "JanV: \"mostly random moves\"";
        }

        /***
         * 
         * THIS METHOD 'UPDATE' SHOULD BE MODIFIED TO YOUR WANTED BEHAVIOR
         * 
         * PURPOSE: FIND THE BEST MOVE FOR THE PACMAN
         * 
         ***/

        public override void Update()
        {
            if (InGrid())
            {
                //  current grid position:
                Point gridPosition = this.GridPosition;

                //  arrays for the possible directions
                List<Point> d1 = new List<Point>();
                List<Point> d2 = new List<Point>();

                //  find possibilities per direction, and see if there is no ghost, and if we are not reversing ...

                if (World.Instance.CanLeft(gridPosition))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(-1, 0))))
                    {
                        d2.Add(new Point(-1, 0));       //  left direction possible and there is no ghost
                        if (Direction.X != 1)
                            d1.Add(new Point(-1, 0));   //  same, but it's our reversed direction: so second choice!
                    }
                }

                if (World.Instance.CanUp(gridPosition))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, -1))))
                    {
                        d2.Add(new Point(0, -1));
                        if (Direction.Y != 1)
                            d1.Add(new Point(0, -1));
                    }
                }

                if (World.Instance.CanRight(gridPosition))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(1, 0))))
                    {
                        d2.Add(new Point(1, 0));
                        if (Direction.X != -1)
                            d1.Add(new Point(1, 0));
                    }
                }

                if (World.Instance.CanDown(gridPosition))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, 1))))
                    {
                        d2.Add(new Point(0, 1));
                        if (Direction.Y != -1)
                            d1.Add(new Point(0, 1));
                    }
                }

                if (d1.Count == 0)     //  no possiblities first choice
                {
                    if (d2.Count == 0)  //  no possibilities second choice
                    {
                        if (World.Instance.CanNoWay(gridPosition))
                        {
                            Direction = new Point(0, 0);
                        }
                        else
                        {
                            Direction = new Point(-Direction.X, -Direction.Y);  //  reverse direction

                        }
                    }
                    else
                    {
                        //  make a random choise from second best
                        int random = World.GetRandomInt(d2.Count);
                        Direction = new Point(d2[random].X, d2[random].Y);
                    }
                }
                else
                {
                    //  make a random choise from first best
                    int random = World.GetRandomInt(d1.Count);
                    Direction = new Point(d1[random].X, d1[random].Y);
                }
            }

            //  compute new position depending on the found direction

            pixelPosition = NewPosition(Direction);
        }

    }
}
