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
            return "Dominik, Job, Janita, Wendy & Erik";
        }

        /***
         * 
         * THIS METHOD 'UPDATE' SHOULD BE MODIFIED TO YOUR WANTED BEHAVIOR
         * 
         * PURPOSE: FIND THE BEST MOVE FOR THE PACMAN
         * 
         ***/

        protected Point NewPosition(Point newDirection, Point currentPosition)
        {
            Point newPosition = new Point();
            newPosition.X = currentPosition.X + Speed * newDirection.X;
            newPosition.Y = currentPosition.Y + Speed * newDirection.Y;
            return newPosition;
        }

        protected Point NewGridPosition(Point newDirection)
        {
            Point newPosition = new Point();
            newPosition.X = GridPosition.X + newDirection.X;
            newPosition.Y = GridPosition.Y + newDirection.Y;
            return newPosition;
        }

        protected Point GridToPixel(Point gridPosition)
        {
            return new Point(gridPosition.X * World.BLOCKSIZE, gridPosition.Y * World.BLOCKSIZE);
        }

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
                    Point newPosition = new Point(gridPosition.X -1, gridPosition.Y);
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(-1, 0))))
                    {
                        bool CanAdd = true;
                        if (World.Instance.CanUp(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, -1), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanLeft(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(-1, 0), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanDown(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, 1), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (CanAdd)
                        {
                            d2.Add(new Point(-1, 0));       //  left direction possible and there is no ghost
                            if (Direction.X != 1)
                                d1.Add(new Point(-1, 0));   //  same, but it's our reversed direction: so second choice!
                        }
                        else
                        {

                        }
                    }
                }

                if (World.Instance.CanUp(gridPosition))
                {
                    Point newPosition = new Point(gridPosition.X, gridPosition.Y - 1);
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, -1))))
                    {
                        bool CanAdd = true;
                        if (World.Instance.CanRight(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(1, 0), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanUp(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, -1), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanLeft(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(-1, 0), GridToPixel(newPosition))))
                                CanAdd = false;
                        }

                        if (CanAdd)
                        {
                            d2.Add(new Point(0, -1));
                            if (Direction.Y != 1)
                                d1.Add(new Point(0, -1));
                        }
                        else
                        {

                        }
                    }
                }

                if (World.Instance.CanRight(gridPosition))
                {
                    Point newPosition = new Point(gridPosition.X + 1, gridPosition.Y);
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(1, 0))))
                    {
                        bool CanAdd = true;
                        if (World.Instance.CanRight(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(1, 0), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanUp(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, -1), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanDown(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, 1), GridToPixel(newPosition))))
                                CanAdd = false;
                        }

                        if (CanAdd)
                        {
                            d2.Add(new Point(1, 0));
                            if (Direction.X != -1)
                                d1.Add(new Point(1, 0));
                        }
                        else
                        {

                        }
                    }
                }

                if (World.Instance.CanDown(gridPosition))
                {
                    Point newPosition = new Point(gridPosition.X, gridPosition.Y + 1);
                    if (!World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, 1))))
                    {
                        bool CanAdd = true;
                        if (World.Instance.CanRight(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(1, 0), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanLeft(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(-1, 0), GridToPixel(newPosition))))
                                CanAdd = false;
                        }
                        if (World.Instance.CanDown(newPosition))
                        {
                            if (World.Instance.IsThereAGhostAtPixel(NewPosition(new Point(0, 1), GridToPixel(newPosition))))
                                CanAdd = false;
                        }

                        if (CanAdd)
                        {
                            d2.Add(new Point(0, 1));
                            if (Direction.Y != -1)
                                d1.Add(new Point(0, 1));
                        }
                        else
                        {

                        }
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
                        List<Point> choise1 = new List<Point>();
                        List<Point> choise2 = new List<Point>();

                        foreach (Point p in d2)
                        {
                            if (World.Instance.IsSpot(NewGridPosition(p), World.DOT) || World.Instance.IsSpot(NewGridPosition(p), World.POWER))
                                choise1.Add(p);
                            else
                                choise2.Add(p);
                        }

                        if (choise1.Count > 0)
                        {
                            //  make a random choise from first best
                            int random = World.GetRandomInt(choise1.Count);
                            Direction = new Point(choise1[random].X, choise1[random].Y);
                        }
                        else
                        {
                            //  make a random choise from first best
                            int random = World.GetRandomInt(choise2.Count);
                            Direction = new Point(choise2[random].X, choise2[random].Y);
                        }
                    }
                }
                else
                {
                    List<Point> choise1 = new List<Point>();
                    List<Point> choise2 = new List<Point>();

                    foreach (Point p in d1)
                    {
                        if (World.Instance.IsSpot(NewGridPosition(p), World.DOT) || World.Instance.IsSpot(NewGridPosition(p), World.POWER))
                            choise1.Add(p);
                        else
                            choise2.Add(p);
                    }    
                
                    foreach(Point p in d2)
                    {
                        if (World.Instance.IsSpot(NewGridPosition(p), World.DOT) || World.Instance.IsSpot(NewGridPosition(p), World.POWER))
                            choise1.Add(p);                        
                        else
                            choise2.Add(p);
                    }

                    if (choise1.Count > 0)
                    {
                        Point bestChoise = new Point(0, 0);
                        int shortestDistance = Int32.MaxValue;
                        foreach (Point possibleChoise in choise1)
                        {
                            int tempDistance = getDistanceToPointsSpot(new Point(GridPosition.X + possibleChoise.X, GridPosition.Y + possibleChoise.Y));
                            if (tempDistance < shortestDistance)
                            {
                                bestChoise = possibleChoise;
                                shortestDistance = tempDistance;
                            }
                        }
                        Direction = bestChoise;
                    }
                    else
                    {
                        
                        Point bestChoise = new Point(0,0);
                        int shortestDistance = Int32.MaxValue;
                        foreach (Point possibleChoise in choise2)
                        {
                            int tempDistance = getDistanceToPointsSpot(new Point(GridPosition.X+possibleChoise.X, GridPosition.Y+possibleChoise.Y));
                            if (tempDistance < shortestDistance)
                            {
                                bestChoise = possibleChoise;
                                shortestDistance = tempDistance;
                            }
                        }
                        Direction = bestChoise;
                    }
                }
            }

            //  compute new position depending on the found direction

            pixelPosition = NewPosition(Direction);
        }

        private int getDistanceToPointsSpot(Point point)
        {
            return getDistanceToPointsSpot(point, 0);
        }

        private int getDistanceToPointsSpot(Point point, int distance)
        {
            if (distance > 10)
                return distance;
            if (World.Instance.IsSpot(point, World.DOT) || World.Instance.IsSpot(point, World.POWER))
            {
                return distance;
            }
            else
            {
                distance++;
                int tempdistance;
                int lowestdistance = Int32.MaxValue;

                if (World.Instance.CanLeft(point))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(GridToPixel(point)))
                    {
                        tempdistance = getDistanceToPointsSpot(new Point(point.X - 1, point.Y), distance);
                        if (tempdistance < lowestdistance)
                            lowestdistance = tempdistance;
                    }
                }
                if (World.Instance.CanRight(point))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(GridToPixel(point)))
                    {
                        tempdistance = getDistanceToPointsSpot(new Point(point.X + 1, point.Y), distance);
                        if (tempdistance < lowestdistance)
                            lowestdistance = tempdistance;
                    }
                }
                if (World.Instance.CanDown(point))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(GridToPixel(point)))
                    {
                        tempdistance = getDistanceToPointsSpot(new Point(point.X, point.Y + 1), distance);
                        if (tempdistance < lowestdistance)
                            lowestdistance = tempdistance;
                    }
                }
                if (World.Instance.CanUp(point))
                {
                    if (!World.Instance.IsThereAGhostAtPixel(GridToPixel(point)))
                    {
                        tempdistance = getDistanceToPointsSpot(new Point(point.X, point.Y - 1), distance);
                        if (tempdistance < lowestdistance)
                            lowestdistance = tempdistance;
                    }
                }
                return lowestdistance;
            }
        }

    }
}
