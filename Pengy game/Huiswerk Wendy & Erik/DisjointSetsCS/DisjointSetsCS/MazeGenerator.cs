using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DisjointSetsCS
{
    class MazeGenerator
    {
        private uint columns;
        private uint rows;

        public uint Columns { get { return columns; } }
        public uint Rows { get { return rows; } }
        public uint Size { get { return Columns * Rows; } }

        public DisjointSets ds;
        public struct Edge
        {
            public uint Edge1;
            public uint Edge2;
        }

        public class EdgeSort : IComparer<Edge>
        {
            public int Compare(Edge x, Edge y)
            {
                return string.Compare(x.Edge1.ToString(), y.Edge1.ToString());
            }
        }
        public List<Edge> edges;
        public List<Edge> maze;
        public List<Edge> path;

        public MazeGenerator(uint Columns, uint Rows)
        {
            this.columns = Columns;
            this.rows = Rows;

            edges = new List<Edge>();
            maze = new List<Edge>();
            path = new List<Edge>();
            
            uint size = Columns * Rows;
            ds = new DisjointSets(size);

            int row = -1;
            int column = 0;

            for (int i = 0; i < size; i++)
            {
                if(i % Columns == 0)
                    row = row + 1;
                column = i % (int)Columns;

                if (column < (Columns - 1))
                {
                    AddEdge((uint)i, (uint)i + 1);
                }

                if (row < (Rows - 1))
                {
                    AddEdge((uint)i, (uint)i + Columns);
                }
            }
        }

        private Random rand = new Random();
        public void GenerateMaze()
        {
            while (edges.Count > 0)
            {
                int r = rand.Next(0, edges.Count - 1);
                Edge e = edges[r];

                uint u, v;
                u = ds.Find_(e.Edge1);
                v = ds.Find_(e.Edge2);

                if (u != v)
                {
                    ds.Union(u, v);
                    path.Add(e);
                }
                else
                    maze.Add(e);

                edges.Remove(e);
            }

            FindThePath(0);
        }

        private void FindThePath(uint elem)
        {
            aPath = new List<Edge>();
            blockedPath = new List<Edge>();
            FindPath(elem, 0);
        }

        private List<Edge> blockedPath;
        public List<Edge> aPath;
        private void FindPath(uint elem, uint prev)
        {
            Edge moveR, moveD, moveL, moveU;

            moveR = CanMove(elem, elem + 1);
            moveD = CanMove(elem, elem + Columns);
            moveL = CanMove(elem, elem - 1);
            moveU = CanMove(elem, elem - Columns);

            if(elem == (Columns * Rows) -1)
            {
                return;
            }
            else if (moveR.Edge1 != uint.MaxValue && (elem + 1 != prev) && !blockedPath.Contains(moveR))
            {
                //rechts
                aPath.Add(moveR);
                if (moveR.Edge1 == elem)
                    FindPath(moveR.Edge2, elem);
                else
                    FindPath(moveR.Edge1, elem);
            }

            else if (moveD.Edge1 != uint.MaxValue && (elem + Columns != prev) && !blockedPath.Contains(moveD))
            {
                // onder
                aPath.Add(moveD);
                if (moveD.Edge1 == elem)
                    FindPath(moveD.Edge2, elem);
                else
                    FindPath(moveD.Edge1, elem);
            }
            else if (moveL.Edge1 != uint.MaxValue && (elem - 1 != prev) && !blockedPath.Contains(moveL))
            {
                // links
                aPath.Add(moveL);
                if (moveL.Edge1 == elem)
                    FindPath(moveL.Edge2, elem);
                else
                    FindPath(moveL.Edge1, elem);
            }
            else if (moveU.Edge1 != uint.MaxValue && (elem - Columns != prev) && !blockedPath.Contains(moveU))
            {
                // boven
                aPath.Add(moveU);
                if (moveU.Edge1 == elem)
                    FindPath(moveU.Edge2, elem);
                else
                    FindPath(moveU.Edge1, elem);
            }
            else
            {                
                blockedPath.Add(aPath[aPath.Count - 1]);
                aPath.RemoveAt(aPath.Count - 1);
                FindPath(prev, elem);
            }
        }

        private Edge CanMove(uint elem1, uint elem2)
        {
            foreach(Edge e in path)
            {
                if(e.Edge1 == elem1 && e.Edge2 == elem2)
                    return e;
                if(e.Edge2 == elem1 && e.Edge1 == elem2)
                    return e;
            }
            return new Edge() { Edge1 = uint.MaxValue, Edge2 = uint.MaxValue };
        }
        
        private void AddEdge(uint edge1, uint edge2)
        {
            Edge edge = new Edge() { Edge1 = edge1, Edge2 = edge2 };
            edges.Add(edge);
        }
    }
}
