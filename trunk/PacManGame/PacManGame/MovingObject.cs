using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace PacManGame
{
    class MovingObject
    {
        //  public attributes //
        public Point pixelPosition;


        //  private attributes  //

        IDrawObject drawObject;

        protected Point Direction { get; set; }
        protected int Speed {get; set;}

        //  constructors //

        public MovingObject(IDrawObject drawObject, Point gridPosition)
        {
            this.drawObject = drawObject;
            this.pixelPosition = new Point(gridPosition.X * World.BLOCKSIZE, gridPosition.Y * World.BLOCKSIZE);
            this.Direction = new Point(0, 0);
            this.Speed = 0;
        }

        public MovingObject(IDrawObject drawObject, Point gridPosition, Point direction, int speed)
        {
            this.drawObject = drawObject;
            this.pixelPosition = new Point(gridPosition.X * World.BLOCKSIZE, gridPosition.Y * World.BLOCKSIZE);
            this.Direction = direction;
            this.Speed = speed;
        }

        // setters and getters //

        public Point PixelPosition
        {
            get { return pixelPosition; }
        }

        public Point GridPosition
        {
            get { return PixelToGrid(PixelPosition); }
        }


        protected Point NewPosition(Point newDirection)
        {
            Point newPosition = new Point();
            newPosition.X = pixelPosition.X + Speed * newDirection.X;
            newPosition.Y = pixelPosition.Y + Speed * newDirection.Y;
            return newPosition;
        }

        //  private methods //

        public bool InGrid()
        {
            return PixelPosition.X % World.BLOCKSIZE == 0 && PixelPosition.Y % World.BLOCKSIZE == 0;
        }

        protected Point PixelToGrid(Point pixelPosition)
        {
            return new Point(pixelPosition.X / World.BLOCKSIZE, pixelPosition.Y / World.BLOCKSIZE);
        }

        //  public methods  //

        public virtual void Update()
        {
            DoRandomMove();
        }

        public virtual void Render(Graphics g)
        {
            drawObject.DoAnim();
            drawObject.Draw(g, PixelPosition, Direction);
        }

        //

        public bool IsClose(Point pixelPosition, int distance)
        {
            Rectangle rect = new Rectangle
                (this.PixelPosition.X-distance, this.pixelPosition.Y - distance,
                World.BLOCKSIZE + 2 * distance + 1, World.BLOCKSIZE + 2 * distance + 1);

            return rect.Contains(pixelPosition);
        }




        //

        public void DoRandomMove()
        {
            if (InGrid())
            {
                Point gridPosition = GridPosition;

              
                List<Point> d = new List<Point>();

                if (World.Instance.CanLeft(gridPosition) && Direction.X != 1)
                {
                    d.Add(new Point(-1, 0));
                }

                if (World.Instance.CanUp(gridPosition) && Direction.Y != 1)
                {
                    d.Add(new Point(0, -1));
                }

                if (World.Instance.CanRight(gridPosition) && Direction.X != -1)
                {
                    d.Add(new Point(1, 0));
                }

                if (World.Instance.CanDown(gridPosition) && Direction.Y != -1)
                {
                    d.Add(new Point(0, 1));
                }

                if (d.Count == 0)     //  no possiblities
                {
                    if (World.Instance.CanNoWay(gridPosition))
                    {
                        Direction = new Point(0, 0);
                    }
                    else
                    {
                        Direction = new Point(-Direction.X, -Direction.Y);  //  reverse
                    }
                }
                else
                {
                    //  make a random choise
                    int random = World.GetRandomInt(d.Count);
                    Direction = new Point(d[random].X, d[random].Y);
                }
            }

            //  compute new position

            pixelPosition.X = pixelPosition.X + Speed * Direction.X;
            pixelPosition.Y = pixelPosition.Y + Speed * Direction.Y;

        }


    }
}
