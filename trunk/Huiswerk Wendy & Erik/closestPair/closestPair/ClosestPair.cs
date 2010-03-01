using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;

namespace closestPair
{
    public partial class ClosestPair : Form
    {
        double inf = 1.0 / 0.0;
        int DELAY;
        int X_MAX, Y_MAX;
        int numComparisons = 0;
        PointSet T;

        /************************************************************
        *  CONSTRUCTORS/DESTRUCTORS AND FIELD MANIPULATORS          *
        ************************************************************/
        public ClosestPair()
        {
            InitializeComponent();
            X_MAX = Panel1.Width + 10;
            Y_MAX = Panel1.Height + 10;
            DELAY = 100;
            T = new PointSet();
        }

        public ClosestPair(int delay)
        {
            InitializeComponent();   
            X_MAX = Panel1.Width;
            Y_MAX = Panel1.Height;
            DELAY = delay;
            T = new PointSet();

            distance.Left = 0;
            distance.Top = 0;
        }

        public void setDelay(int delay)
        {
            DELAY = delay;
        }

        public void resetComparisons()
        {
            numComparisons = 0;
        }
        public int getComparisons()
        {
            return numComparisons;
        }

        /***********************************************************************
        *  DIVIDE-AND-CONQUER ALGORITHM + FUNCTIONS                            *
        ***********************************************************************/

        public double ClosestPairDQ(PointSet S)
        {
            if (S.points.Count <= 1)
            {
                S.dmin = inf;
            }
            else
            {
                // calculate co-ordinates of median point
                int median = (int)Math.Ceiling((decimal)S.points.Count / 2);
                Point M = S.pointAt(median - 1);

                // calculate two subproblems (median in first subset)
                PointSet S1 = subSet(S, 0, median - 1);
                PointSet S2 = subSet(S, median, S.points.Count - 1);

                // highlight the whole set
                if (DELAY > 50)
                {
                    drawField(S, Color.Cyan);
                    drawVertical(M, Color.Blue);
                    pause(DELAY);
                    eraseVertical(M);
                    eraseField(S);
                }

                // recursively calculate solutions to sub-problems
                S.dmin = Math.Min(ClosestPairDQ(S1), ClosestPairDQ(S2));

                // highlight the whole set, and solutions for each subset
                if (DELAY > 50)
                {
                    drawField(S, Color.Cyan);
                    drawVertical(M, Color.Blue);
                    pause(DELAY);
                }

                // merge two sub-solutions
                S = merge(S, S1, S2);

                // highlight set in gray b/c solution has been computed
                if (DELAY > 50)
                {
                    eraseVertical(M);
                    eraseField(S);
                    drawField(S, Color.LightGray);
                    pause(DELAY);
                }
            }
            return S.dmin;
        }

        PointSet merge(PointSet S, PointSet S1, PointSet S2)
        {
            Point M = S1.pointAt(S1.points.Count - 1);

            // draw the strip about the median
            if (DELAY > 50)
            {
                drawDQStrip(S, M);
                pause(DELAY);
            }

            for (int i = 0; i < S.points.Count; i++)
            {
                Point P = S.pointAt(i);
                if (Math.Abs(P.x - M.x) <= S.dmin)
                {

                    // P is in S1, only look in S2
                    if (S1.contains(P))
                    {
                        S = testStripPoint(S, P, S2, M, true);
                    }

                    // P is in S2, only look in S1
                    if (S2.contains(P))
                    {
                        S = testStripPoint(S, P, S1, M, false);
                    }

                    // update miniMUM distance
                    if (S.dmin < T.dmin)
                    {
                        T.dmin = S.dmin;
                        if (T.closestPair.Count == 0)
                        {
                            T.closestPair.Add(S.closestPair[0]);
                            T.closestPair.Add(S.closestPair[1]);
                        }
                        else
                        {
                            T.closestPair[0] = S.closestPair[0];
                            T.closestPair[1] = S.closestPair[1];
                        }
                    }
                }
            }
            return S;
        }

        // Test for closest pairs to P in set sS (P is a point in the strip)
        PointSet testStripPoint(PointSet S, Point P,
                    PointSet sS, Point M, Boolean lookDIR)
        {
            Point Q;

            // Draw P's bounding box
            if (DELAY > 50)
            {
                drawDQBoundingBox(S, P, M, lookDIR);
                pause(DELAY);
            }

            for (int j = 0; j < sS.points.Count; j++)
            {
                Q = sS.pointAt(j);

                // if Q is in P's bounding box
                //if ((Math.Abs(P.x - Q.x) <= S.dmin) &&
                //(Math.Abs(P.y - Q.y) <= S.dmin))
                //{

                    // draw a red segment to show that it is being compared
                    if (DELAY > 50)
                    {
                        drawSegment(P, Q, Color.Red);
                        pause(DELAY);
                    }

                    numComparisons++;
                    S = testBoundingBoxPoint(S, P, Q);

                    // erase the red segment after the comparison
                    if (DELAY > 50)
                    {
                        eraseSegment(P, Q, Color.Yellow);
                        pause(DELAY);
                    }

                //}
            }

            // Erase P's bounding box
            if (DELAY > 50) { drawDQStrip(S, M); }

            return S;
        }

        // Test a point Q in P's bounding box
        PointSet testBoundingBoxPoint(PointSet S, Point P, Point Q)
        {
            double d = dist(P, Q);

            if (d < S.dmin)
            {

                // update minimal distance
                S.dmin = d;
                if (S.closestPair.Count == 0)
                {
                    S.closestPair.Add(P);
                    S.closestPair.Add(Q);
                }
                else
                {
                    S.closestPair[0] = P;
                    S.closestPair[1] = Q;
                }

                // flash the segment to show that a new minimal distance was found
                if (DELAY > 50)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        eraseSegment(P, Q, Color.Yellow);
                        pause((int)(DELAY / 2));
                        drawSegment(P, Q, Color.Green);
                        pause((int)(DELAY / 2));
                    }
                }
            }
            return S;
        }

        /************************************************************
        *  GENERAL GRAPHICS FUNCTIONS                               *
        ************************************************************/

        public void drawPoint(Point p, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            //Pen pen = new Pen(Color.Black);
            SolidBrush brush = new SolidBrush(c);
            g.FillEllipse(brush, p.x - 3, p.y - 3, 6, 6);
            //Rectangle rect = new Rectangle(p.x - 3, p.x - 3, 6, 6);
            //g.DrawEllipse(pen, rect);
        }

        public void drawSegment(Point p1, Point p2, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            drawPoint(p1, c);
            g.DrawLine(new Pen(c), p1.x, p1.y, p2.x, p2.y);
            drawPoint(p2, c);
        }

        public void eraseSegment(Point p1, Point p2, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            Pen pen = new Pen(c);
            g.DrawLine(pen, p1.x, p1.y, p2.x, p2.y);
            drawPoint(p1, Color.Black);
            drawPoint(p2, Color.Black);
        }

        public void drawVertical(Point M, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            Pen pen = new Pen(c);
            g.DrawLine(pen, M.x, 0, M.x, Y_MAX);
        }

        public void eraseVertical(Point M)
        {
            Graphics g = Panel1.CreateGraphics();
            Pen pen = new Pen(Color.White);
            g.DrawLine(pen, M.x, 0, M.x, Y_MAX);
            drawPoint(M, Color.Black);
        }

        public void drawField(PointSet S, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            int w, x;

            x = S.first().x;
            w = S.last().x - x;

            SolidBrush brush = new SolidBrush(c);
            g.FillRectangle(brush, x, 0, w, Y_MAX);
            drawPoints(T, Color.Black);
        }

        public void eraseField(PointSet S)
        {
            Graphics g = Panel1.CreateGraphics();
            int w, x;

            x = S.first().x;
            w = S.last().x - x;

            SolidBrush brush = new SolidBrush(Color.White);
            g.FillRectangle(brush, x, 0, w, Y_MAX);
            drawPoints(T, Color.Black);
        }

        public void drawPoints(PointSet S, Color c)
        {
            for (int i = 0; i < S.points.Count; i++)
            {
                Point P = S.pointAt(i);
                drawPoint(P, c);
            }
        }

        public void reset()
        {
            T = new PointSet();
            Graphics g = Panel1.CreateGraphics();
            SolidBrush brush = new SolidBrush(Color.White);
            g.FillRectangle(brush, 0, 0, X_MAX, Y_MAX);
            distance.Text = "";
        }

        /************************************************************
        *  GRAPHICS FUNCTIONS FOR THE DIVIDE AND CONQUER ALGORITHM  *
        ************************************************************/

        public void drawDQStrip(PointSet S, Point M)
        {
            Graphics g = Panel1.CreateGraphics();
            int x, w;

            // set x
            if ((M.x - S.dmin) < S.first().x) { x = S.first().x; }
            else { x = M.x - ((int)S.dmin); }

            // set w
            if ((M.x + S.dmin) > S.last().x) { w = S.last().x - x; }
            else { w = M.x + ((int)S.dmin) - x; }

            SolidBrush brush = new SolidBrush(Color.Pink);
            g.FillRectangle(brush, x, 0, w, Y_MAX);
            drawVertical(M, Color.Blue);
            drawPoints(T, Color.Black);
        }

        public void drawDQBoundingBox(PointSet S, Point P, Point M, Boolean lookR)
        {
            Graphics g = Panel1.CreateGraphics();
            int x, y, w, h;

            // set x
            if (lookR == true) { x = P.x; }
            else
            {
                if ((P.x - S.dmin) < S.first().x) { x = S.first().x; }
                else { x = P.x - ((int)S.dmin); }
            }

            // set y
            if ((P.y - S.dmin) < 0) { y = 0; }
            else { y = P.y - ((int)S.dmin); }

            // set w
            if (lookR == true)
            {
                if ((x + S.dmin) > S.last().x) { w = S.last().x - x; }
                else { w = ((int)S.dmin); }
            }
            else
            {
                w = P.x - x;
            }

            // set h
            if ((P.y + S.dmin) > Y_MAX) { h = Y_MAX - y; }
            else { h = P.y + ((int)S.dmin) - y; }

            SolidBrush brush = new SolidBrush(Color.Yellow);
            g.FillRectangle(brush, x, y, w, h);
            drawVertical(M, Color.Blue);
            drawPoints(T, Color.Black);
        }

        /***********************************************************************
        *  GENERAL SUPPORT FUNCTIONS                                           *
        ***********************************************************************/

        // returns true if p1 and p2 are "near" eachother
        Boolean near(Point p1, Point p2)
        {
            return ((Math.Abs(p1.x - p2.x) <= 3) &&
                (Math.Abs(p1.y - p2.y) <= 3));
        }

        // returns Euclidean distance between two points
        double dist(Point p1, Point p2)
        {
            return (Math.Sqrt(square(p2.x - p1.x) + square(p2.y - p1.y)));
        }

        // returns the square of its argument
        int square(int x) { return (x * x); }

        // returns a subset of containing the elements of S from fromIndex to
        // toIndex inclusive
        public PointSet subSet(PointSet S, int fromIndex, int toIndex)
        {
            PointSet T = new PointSet();
            for (int i = fromIndex; i <= toIndex; i++)
            {
                T.add(S.pointAt(i));
            }
            return T;
        }

        // pauses the current thread for the given number of milliseconds
        void pause(int ms)
        {
            try
            {
                Thread.Sleep(ms);
            }
            catch (Exception e) { }
        }

        private void Panel1_MouseDown(object sender, MouseEventArgs e)
        {
            Point p = new Point(e.X, e.Y);
            T.add(p);
            drawPoint(p, Color.Black);
        }

        private void start_Click(object sender, EventArgs e)
        {
            double distancePoints = ClosestPairDQ(T);
            if (T.closestPair.Count != 0)
            {
                drawSegment(T.closestPair[0], T.closestPair[1], Color.Red);
                distance.Text = "Distance between points: " + distancePoints.ToString();
            }
        }

        private void rst_Click(object sender, EventArgs e)
        {
            reset();
            resetComparisons();
        }

        private void Panel1_Resize(object sender, EventArgs e)
        {
            X_MAX = Panel1.Width + 10;
            Y_MAX = Panel1.Height + 10;
        }
    }
}
