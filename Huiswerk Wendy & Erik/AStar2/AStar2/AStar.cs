using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AStar2
{
    class AStar
    {
        private List<Node> closedSet;// The set of nodes already evaluated. 
        private List<Node> openSet;// The set of tentative nodes to be evaluated.
        public List<Node> total { get; set; }
        private Graph graph;
        public AStar(Graph graph)
        {
            total = new List<Node>();
            this.graph = graph;
            openSet = graph.Nodes;
            closedSet = new List<Node>();
        }
        public bool AStarAlgorithm(int startId, int goalId)
        {
            Node start = graph.Nodes.FirstOrDefault(n=>n.Id == startId);
            Node goal = graph.Nodes.FirstOrDefault(n => n.Id == goalId);
            double g_Score = 0;// Distance from start along optimal path.
            double h_Score = heuristic_estimate_of_distance(start, goal);
            double f_Score = h_Score;// Estimated total distance from start to goal through y.
            Node lastNode = null;

            while (openSet.Count != 0)
            {
                Node x = lowestF_Score(goal, g_Score);//the node in openset having the lowest f_score[] value
                if (x == goal)
                {
                    if (x.cameFrom == null)
                    {
                        if (isNeighbour(lastNode, x))
                            x.cameFrom = lastNode;
                        else
                            return false;
                    }
                    bool succes = reconstruct_path(x.cameFrom, start);
                    total.Add(goal);
                    return succes;
                }
                openSet.Remove(x);
                closedSet.Add(x);
                foreach (int yId in neighbour_nodes(x))
                {
                    Node y = openSet.FirstOrDefault(n => n.Id == yId);
                    if (closedSet.FirstOrDefault(n=>n.Id == yId)!=null)
                        break;
                    double tentative_g_score = g_Score + dist_between(x, y);
                    Boolean tentative_is_better = false;
                    if (!openSet.Contains(y))
                    {
                        openSet.Add(y);
                        tentative_is_better = true;
                    }
                    else if (tentative_g_score < y.g_Score || g_Score == 0 || y.g_Score == 0)
                        tentative_is_better = true;
                    if (tentative_is_better)
                    {
                        y.cameFrom = x;
                        g_Score = tentative_g_score;
                        y.g_Score = tentative_g_score;
                        h_Score = heuristic_estimate_of_distance(y, goal);
                        f_Score = g_Score + h_Score;
                        lastNode = y;
                    }
                }
            }
            return false;
        }

        public bool reconstruct_path(Node current_node, Node start)
        {
            if (current_node.cameFrom != null)
            {
                reconstruct_path(current_node.cameFrom, start);
                total.Add(current_node);
                return true;
            }
            else
            {
                total.Add(current_node);
                if (current_node == start)
                    return true;
                return false;
            }
        }
        private double heuristic_estimate_of_distance(Node start, Node goal)
        {
            //manhattan distance
            //return (start.position.x - goal.position.x) + (start.position.y - goal.position.y);
            return 0;
        }
        private double dist_between(Node x, Node y)
        {
            return 0;
            //return Math.Sqrt(Math.Pow(x.position.Length(), 2) + Math.Pow(y.position.Length(), 2));
        }
        private List<int> neighbour_nodes(Node x)
        {
            List<int> neighbours = new List<int>();
            foreach (Edge edge in graph.Edges)
            {
                if (edge.isDirected)
                {
                    if (edge.FromNode == x.Id)
                        neighbours.Add(edge.ToNode);
                }
                else 
                {
                    if (edge.FromNode == x.Id)
                        neighbours.Add(edge.ToNode);
                    else if (edge.ToNode == x.Id)
                        neighbours.Add(edge.FromNode);
                }
            }
            return neighbours;
        }
        private Node lowestF_Score(Node goal, double g_Score)
        {
            double f_score = 0;
            Node lowest = null;
            foreach (Node temp in openSet)
            {
                if (lowest == null)
                {
                    lowest = temp;
                    double tempg_Score = g_Score + dist_between(temp, goal);
                    double temph_Score = heuristic_estimate_of_distance(temp, goal);
                    f_score = tempg_Score + temph_Score;
                }
                else
                {
                    double tempg_Score = g_Score + dist_between(temp, goal);
                    double temph_Score = heuristic_estimate_of_distance(temp, goal);
                    double tempf_score = tempg_Score + temph_Score;
                    if (tempf_score < f_score)
                    {
                        lowest = temp;
                        f_score = tempf_score;
                    }
                }
            }
            return lowest;
        }
        private bool isNeighbour(Node neighbour, Node current)
        {
            foreach (Edge edge in graph.Edges)
            {
                if (edge.isDirected)
                {
                    if (edge.FromNode == neighbour.Id && edge.ToNode == current.Id)
                        return true;
                        
                }
                else
                {
                    if (edge.FromNode == neighbour.Id && edge.ToNode == current.Id)
                        return true;
                    else if (edge.ToNode == neighbour.Id && edge.FromNode == current.Id)
                        return true;
                }
            }
            return false;
        }
    }
}
    
 

