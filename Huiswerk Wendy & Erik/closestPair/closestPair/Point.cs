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

        public Point(int xc, int yc)
        { 
            x = xc; 
            y = yc; 
        }
        public Point(Point p) 
        { 
            x = p.x; 
            y = p.y; 
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
