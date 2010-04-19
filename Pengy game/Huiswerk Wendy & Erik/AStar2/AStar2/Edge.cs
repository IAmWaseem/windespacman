using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AStar2
{
    public class Edge
    {
        public int FromNode{ get; set; }
        public int ToNode{ get; set; }
        public bool isDirected { get; set; }
        public int weight { get; set; }

        public Edge(int fromNode, int toNode, bool directed, int weight)
        {
            isDirected = directed;
            FromNode = fromNode;
            ToNode = toNode;
            this.weight = weight;
        }
    }
}
