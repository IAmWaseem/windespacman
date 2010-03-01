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
        PointSet North;
        PointSet South;
        PointSet West;
        PointSet East;
        Random rand;
        System.Drawing.Point isSplit;

        /************************************************************
        *  CONSTRUCTORS/DESTRUCTORS AND FIELD MANIPULATORS          *
        ************************************************************/
        public ClosestPair()
        {
            InitializeComponent();
            X_MAX = Panel1.Width + 10;
            Y_MAX = Panel1.Height + 10;
            DELAY = 100;
            North = new PointSet();
            South = new PointSet();
            East = new PointSet();
            West = new PointSet();
            rand = new Random();
            isSplit = new System.Drawing.Point();
        }

        public ClosestPair(int delay)
        {
            InitializeComponent();
            X_MAX = Panel1.Width;
            Y_MAX = Panel1.Height;
            DELAY = delay;
            North = new PointSet();
            South = new PointSet();
            East = new PointSet();
            West = new PointSet();
            rand = new Random();
            distance.Left = 0;
            distance.Top = 0;
            isSplit = new System.Drawing.Point();
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
            return ClosestPairDQ(S, ref S);
        }
        
        public double ClosestPairDQ(PointSet S, ref PointSet current)
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
                S.dmin = Math.Min(ClosestPairDQ(S1, ref current), ClosestPairDQ(S2, ref current));

                // highlight the whole set, and solutions for each subset
                if (DELAY > 50)
                {
                    drawField(S, Color.Cyan);
                    drawVertical(M, Color.Blue);
                    pause(DELAY);
                }

                // merge two sub-solutions
                S = merge(S, S1, S2, ref current);

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

        PointSet merge(PointSet S, PointSet S1, PointSet S2, ref PointSet WorkSet)
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
                    if (S.dmin < WorkSet.dmin)
                    {

                        WorkSet.dmin = S.dmin;
                        if (WorkSet.closestPair.Count == 0)
                        {
                            WorkSet.closestPair.Add(S.closestPair[0]);
                            WorkSet.closestPair.Add(S.closestPair[1]);
                        }
                        else
                        {
                            WorkSet.closestPair[0] = S.closestPair[0];
                            WorkSet.closestPair[1] = S.closestPair[1];
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
                    drawSegment(P, Q);
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
                            drawSegment(P, Q);
                            pause((int)(DELAY / 2));
                        }
                    }
                }
                
            
            return S;
        }

        /************************************************************
        *  GENERAL GRAPHICS FUNCTIONS                               *
        ************************************************************/

        public void drawPoint(Point p)
        {
            Graphics g = Panel1.CreateGraphics();
            //Pen pen = new Pen(Color.Black);
            SolidBrush brush;
            if (p.color == 0)
                brush = new SolidBrush(Color.Red);
            else
                brush = new SolidBrush(Color.Blue);
            g.FillEllipse(brush, p.x - 3, p.y - 3, 6, 6);
            //Rectangle rect = new Rectangle(p.x - 3, p.x - 3, 6, 6);
            //g.DrawEllipse(pen, rect);
        }

        public void drawSegment(Point p1, Point p2)
        {
            Graphics g = Panel1.CreateGraphics();
            drawPoint(p1);
            if (p1.color == p2.color)
            {
                if (p1.color == 0)
                    g.DrawLine(new Pen(Color.Red), p1.x, p1.y, p2.x, p2.y);
                else
                    g.DrawLine(new Pen(Color.Blue), p1.x, p1.y, p2.x, p2.y);
            }
            else
                g.DrawLine(new Pen(Color.Purple), p1.x, p1.y, p2.x, p2.y);
            drawPoint(p2);
        }

        public void eraseSegment(Point p1, Point p2, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            Pen pen = new Pen(c);
            g.DrawLine(pen, p1.x, p1.y, p2.x, p2.y);
            drawPoint(p1);
            drawPoint(p2);
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
            drawPoint(M);
        }

        public void drawField(PointSet S, Color c)
        {
            Graphics g = Panel1.CreateGraphics();
            int w, x;

            x = S.first().x;
            w = S.last().x - x;

            SolidBrush brush = new SolidBrush(c);
            g.FillRectangle(brush, x, 0, w, Y_MAX);
            drawPoints(S, Color.Black);
        }

        public void eraseField(PointSet S)
        {
            Graphics g = Panel1.CreateGraphics();
            int w, x;

            x = S.first().x;
            w = S.last().x - x;

            SolidBrush brush = new SolidBrush(Color.White);
            g.FillRectangle(brush, x, 0, w, Y_MAX);
            drawPoints(S, Color.Black);
        }

        public void drawPoints(PointSet S, Color c)
        {
            for (int i = 0; i < S.points.Count; i++)
            {
                Point P = S.pointAt(i);
                drawPoint(P);
            }
        }

        public void reset()
        {
            North = new PointSet();
            South = new PointSet();
            West = new PointSet();
            East = new PointSet();
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
            drawPoints(S, Color.Black);
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
            drawPoints(S, Color.Black);
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
        private int pairs()
        {
            int tempblue = 0;
            int tempred = 0;
            foreach (Point p in North.points)
            {
                if (p.color == 0)
                    tempred++;
                else
                    tempblue++;
            }
            if (tempblue > 1 || tempred > 1)
                return (tempblue/2) + (tempred/2);
            return 0;
        }
        private System.Drawing.Point lastPoint;
        private System.Drawing.Point homePoint = new System.Drawing.Point(0, 0);
        private System.Drawing.Point findAverage(PointSet ps, System.Drawing.Point point)
        {
            int tempx = 0;
            int tempy = 0;
            foreach (Point p in ps.points)
            {
                tempx += p.x;
                tempy += p.y;
            }
            tempx = tempx / ps.points.Count;
            tempy = tempy / ps.points.Count;
            if (lastPoint.X == tempx && lastPoint.Y == tempy)
            {
                lastPoint = point;
                homePoint.X = rand.Next(0, Panel1.Width);
                homePoint.Y = rand.Next(0, Panel1.Height);
                
                return homePoint;
            }
            else
            {
                lastPoint = point;
                return new System.Drawing.Point(tempx, tempy);
            }
        }
        private void findMidPoint(int x, int y)
        {
            if (x <= Panel1.Width || y <= Panel1.Height)
            {
                if (pairs() >= 4)
                {
                    PointSet tempNorth = new PointSet();
                    PointSet tempSouth = new PointSet();
                    PointSet tempEast = new PointSet();
                    PointSet tempWest = new PointSet();
                    System.Drawing.Point temp = new System.Drawing.Point(x, y);
                    PointSet tempSet = new PointSet();
                    tempSet.points.AddRange(North.points);
                    //North.points.Clear();
                    foreach (Point point in tempSet.points)
                    {
                        if (point.x > 0 && point.x < temp.X)
                        {
                            //west
                            if (point.y > 0 && point.y < temp.Y)
                            {
                                tempNorth.add(point);
                            }
                            else
                            {
                                tempWest.add(point);
                            }
                        }
                        else
                        {
                            //east
                            if (point.y > 0 && point.y < temp.Y)
                            {
                                tempEast.add(point);
                            }
                            else
                            {
                                tempSouth.add(point);
                            }
                        }
                    }
                    double distancePointsNorth = ClosestPairDQ(tempNorth);
                    double distancePointsSouth = ClosestPairDQ(tempSouth);
                    double distancePointsEast = ClosestPairDQ(tempEast);
                    double distancePointsWest = ClosestPairDQ(tempWest);

                    if (SameColor(tempNorth) && SameColor(tempEast) && SameColor(tempSouth) && SameColor(tempWest))
                    {

                        if (!Double.IsInfinity(distancePointsEast) && !Double.IsInfinity(distancePointsNorth)
                            && !Double.IsInfinity(distancePointsSouth) && !Double.IsInfinity(distancePointsWest))
                        {
                            isSplit = temp;
                            Graphics g = Panel1.CreateGraphics();
                            Pen p = new Pen(Color.Black);
                            g.DrawLine(p, 0, isSplit.Y, isSplit.X, isSplit.Y);
                            g.DrawLine(p, isSplit.X, 0, isSplit.X, isSplit.Y);
                            g.DrawLine(p, isSplit.X, isSplit.Y, isSplit.X, Panel1.Height);
                            g.DrawLine(p, isSplit.X, isSplit.Y, Panel1.Width, isSplit.Y);
                            tempSet.points.Clear();
                            tempSet.points.AddRange(North.points);
                            North.points.Clear();
                            foreach (Point point in tempSet.points)
                            {
                                if (point.x > 0 && point.x < isSplit.X)
                                {
                                    //west
                                    if (point.y > 0 && point.y < isSplit.Y)
                                    {
                                        North.add(point);
                                    }
                                    else
                                    {
                                        West.add(point);
                                    }
                                }
                                else
                                {
                                    //east
                                    if (point.y > 0 && point.y < isSplit.Y)
                                    {
                                        East.add(point);
                                    }
                                    else
                                    {
                                        South.add(point);
                                    }
                                }
                            }
                        }
                        else
                        {
                            System.Drawing.Point point;
                            if (tempEast.points.Count > tempNorth.points.Count)
                            {
                                if (tempEast.points.Count > tempSouth.points.Count)
                                {
                                    if (tempEast.points.Count > tempWest.points.Count)
                                        point = findAverage(tempEast, temp);
                                    else
                                        point = findAverage(tempWest, temp);
                                }
                                else if (tempSouth.points.Count > tempWest.points.Count)
                                    point = findAverage(tempSouth, temp);
                                else
                                    point = findAverage(tempWest, temp);
                            }
                            else if (tempNorth.points.Count > tempSouth.points.Count)
                            {
                                if (tempNorth.points.Count > tempWest.points.Count)
                                    point = findAverage(tempNorth, temp);
                                else
                                    point = findAverage(tempWest, temp);
                            }
                            else if (tempSouth.points.Count > tempWest.points.Count)
                            {
                                point = findAverage(tempSouth, temp);
                            }
                            else
                            {
                                point = findAverage(tempWest, temp);
                            }
                            findMidPoint(point.X, point.Y);
                        }
                    }
                    else
                    {
                        //niet dezelfde kleur
                    }
                }
                else
                {
                    //niet genoeg paren
                }
            }
            else
            {
                //niet gevonden
            }
        }

        private void Panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                Point p;
                if (isSplit.X != 0)
                {
                    if (radioButton1.Checked)
                    {
                        p = new Point(e.X, e.Y, 0);
                    }
                    else if (radioButton2.Checked)
                    {
                        p = new Point(e.X, e.Y, 1);
                    }
                    else
                    {
                        p = new Point(e.X, e.Y, rand.Next(0, 2));
                    }
                                        
                    if (e.X > 0 && e.X < isSplit.X)
                    {
                        //west
                        if (e.Y > 0 && e.Y < isSplit.Y)
                        {
                            North.add(p);
                        }
                        else
                        {
                            West.add(p);
                        }
                    }
                    else
                    {
                        //east
                        if (e.Y > 0 && e.Y < isSplit.Y)
                        {
                            East.add(p);
                        }
                        else
                        {
                            South.add(p);
                        }
                    }
                }
                else
                {
                    if (radioButton1.Checked)
                    {
                        p = new Point(e.X, e.Y, 0);
                    }
                    else if (radioButton2.Checked)
                    {
                        p = new Point(e.X, e.Y, 1);
                    }
                    else
                    {
                        p = new Point(e.X, e.Y, rand.Next(0, 2));
                    }
                    North.add(p);
                }
                drawPoint(p);
            }
            else if (e.Button == MouseButtons.Right)
            {
                if (isSplit.X == 0)
                {
                    isSplit.X = e.X;
                    isSplit.Y = e.Y;
                    Graphics g = Panel1.CreateGraphics();
                    Pen p = new Pen(Color.Black);
                    g.DrawLine(p, 0, e.Y, e.X, e.Y);
                    g.DrawLine(p, e.X, 0, e.X, e.Y);
                    g.DrawLine(p, e.X, e.Y, e.X, Panel1.Height);
                    g.DrawLine(p, e.X, e.Y, Panel1.Width, e.Y);

                    PointSet temp = new PointSet();
                    temp.points.AddRange(North.points);
                    North.points.Clear();
                    foreach (Point point in temp.points)
                    {
                        if (point.x > 0 && point.x < isSplit.X)
                        {
                            //west
                            if (point.y > 0 && point.y < isSplit.Y)
                            {
                                North.add(point);
                            }
                            else
                            {
                                West.add(point);
                            }
                        }
                        else
                        {
                            //east
                            if (point.y > 0 && point.y < isSplit.Y)
                            {
                                East.add(point);
                            }
                            else
                            {
                                South.add(point);
                            }
                        }
                    }
                }
            }

        }

        private void start_Click(object sender, EventArgs e)
        {
            System.Drawing.Point tempPoint = findAverage(North, new System.Drawing.Point(0, 0));
            findMidPoint(tempPoint.X, tempPoint.Y);
            if (isSplit.X != 0)
            {
                distance.Text = "";
                double distancePointsNorth = ClosestPairDQ(North);
                if (North.closestPair.Count != 0)
                {
                    drawSegment(North.closestPair[0], North.closestPair[1]);
                    distance.Text += "North: distance between points: " + distancePointsNorth.ToString("0.0") + Environment.NewLine;
                }
                double distancePointsSouth = ClosestPairDQ(South);
                if (South.closestPair.Count != 0)
                {
                    drawSegment(South.closestPair[0], South.closestPair[1]);
                    distance.Text += "South: distance between points: " + distancePointsSouth.ToString("0.0") + Environment.NewLine;
                }
                double distancePointsWest = ClosestPairDQ(West);
                if (West.closestPair.Count != 0)
                {
                    drawSegment(West.closestPair[0], West.closestPair[1]);
                    distance.Text += "West: distance between points: " + distancePointsWest.ToString("0.0") + Environment.NewLine;
                }
                double distancePointsEast = ClosestPairDQ(East);
                if (East.closestPair.Count != 0)
                {
                    drawSegment(East.closestPair[0], East.closestPair[1]);
                    distance.Text += "East: distance between points: " + distancePointsEast.ToString("0.0");
                }
            }
            else
            {
                double distancePoints = ClosestPairDQ(North);
                if (North.closestPair.Count != 0)
                {
                    drawSegment(North.closestPair[0], North.closestPair[1]);
                    distance.Text = "Distance between points: " + distancePoints.ToString();
                }
            }
        }

        private bool SameColor(PointSet ps)
        {
            if (ps.closestPair.Count > 1)
            {
                if (ps.closestPair[0].color == ps.closestPair[1].color)
                    return true;
            }

            return false;
        }

        private void rst_Click(object sender, EventArgs e)
        {
            reset();
            resetComparisons();
            isSplit = new System.Drawing.Point();

        }

        private void Panel1_Resize(object sender, EventArgs e)
        {
            X_MAX = Panel1.Width + 10;
            Y_MAX = Panel1.Height + 10;
        }
    }
}
