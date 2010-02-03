using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace PacManGame
{
    class Ghost: MovingObject
    {
        //  private attributes  //
        int[] validspeeds = { 1, 2, 3, 4, 6, 8 };
        
        //  constructor //
        
        public Ghost()
            : base(new GhostDraw(), new Point(7, 7))
        {
            Direction = (World.GetRandomInt(2) == 0) ? new Point(1, 0) : new Point(0, 1);
            Speed = validspeeds[World.GetRandomInt(4)];
        }

        public override void Update()
        {
            base.Update();

            if (Collision(World.Instance.pacMan.pixelPosition, this.pixelPosition))
            {
                World.Instance.ChangeScore(-20);
            }
        }

        //   do this Ghost and PacMan collide?
        bool Collision(Point pos1, Point pos2)
        {
            return (pos1.X > (pos2.X - 12)) && (pos1.X < (pos2.X + 12)) && (pos1.Y > (pos2.Y - 12)) && (pos1.Y < (pos2.Y + 12));
        }

    }
}
