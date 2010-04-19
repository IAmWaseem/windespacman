using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AStar2
{
    public class Vector2D
    {
        public int x { get; set; }
        public int y { get; set; }
        public Vector2D(int x, int y)
        {
            this.x = x;
            this.y = y;
        }
        public double Length()
        {
            return Math.Sqrt(x * x + y * y);
        }
    }
}
