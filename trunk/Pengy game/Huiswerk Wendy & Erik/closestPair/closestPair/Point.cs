using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace closestPair
{
    public class Point
    {
        public int x;
        public int y;
        public int color;

        public Point(int xc, int yc, int colorc)
        { 
            x = xc; 
            y = yc;
            color = colorc;
        }
        public Point(Point p) 
        { 
            x = p.x; 
            y = p.y;
            color = p.color;
        }

        public Boolean equals(Point p)
        {
            return ((x == p.x) && (y == p.y));
        }

        public String toString()
        {
            String str = "( ";
            str += x;
            str += " , ";
            str += y;
            str += " ) ";
            return str;
        }
    }
}
