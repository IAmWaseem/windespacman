using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace closestPair
{
    public class PointSet
    {
        double inf = 1.0 / 0.0;
        public double dmin;
        public List<Point> closestPair;
        public List<Point> points;

        public PointSet()
        {
            dmin = inf;
            closestPair = new List<Point>();
            points = new List<Point>();
        }

        public Point pointAt(int i)
        {
            return points[i];
        }

        public Point first()
        {
            return points[0];
        }

        public Point last()
        {
            return points[points.Count - 1];
        }

        public Boolean contains(Point p)
        {
            return points.Contains(p);
        }

        public void add(Point p)
        {
            if (points.Count == 0)
            {
                points.Add(p);
            }
            else
            {
                int i = 0;
                while (i < points.Count && pointAt(i).x < p.x)
                {
                    i++;
                }
                points.Insert(i, p);
            }
        }
        private static Random rand = new Random();
        public void add(int x, int y)
        {

            Point p = new Point(x, y, rand.Next(0,2));
            if (points.Count == 0)
            {
                points.Add(p);
            }
            else
            {
                int i = 0;
                while (i < points.Count && pointAt(i).x < p.x)
                {
                    i++;
                }
                points.Insert(i, p);
            }
        }
    }
}

