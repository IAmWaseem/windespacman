using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AStar2
{
    public class Graph
    {
        public List<Edge> Edges { get; set; }
        public List<Node> Nodes { get; set; }
        public Graph()
        {
            Edges = new List<Edge>();
            Nodes = new List<Node>();
        }
        public Graph(List<Edge> edges, List<Node> nodes)
        {
            Edges = edges;
            Nodes = nodes;
        }
        public void AddEdge(Edge e)
        {
            Edges.Add(e);
        }
        public void AddNode(Node n)
        {
            Nodes.Add(n);
        }
        public void AddEdge(int fromNode, int toNode, bool directed, int weight)
        {
            Edge e = new Edge(fromNode, toNode, directed, weight);
            Edges.Add(e);
        }
        public void AddNode(int id, State mOne, State mTwo, State mThree, State kOne, State kTwo, State kThree, State Boat)
        {
            Node n = new Node(id, mOne, mTwo, mThree, kOne, kTwo, kThree, Boat);
            Nodes.Add(n);
        }
        public bool HasFinish()
        {
            
            foreach (Node n in Nodes)
            {
                bool finish = true;
                foreach (Person p in n.persons)
                {
                    if (p.state != State.left)
                        finish = false;
                }
                if (finish)
                    return true;

            }
            return false;
        }

        public bool DoesContain(Node n)
        {
            //bool total = true;
            foreach (Node temp in Nodes)
            {
                bool t = true;
                List<Person> tempList = new List<Person>();
                tempList.AddRange(temp.persons);
                foreach (Person p in n.persons)
                {
                    Person tempPerson = tempList.FirstOrDefault(per => per.type == p.type && per.state == p.state);
                    if (!(tempPerson.state == p.state && tempPerson.type == p.type))
                    {
                        //t = true;
                        //else
                        t = false;
                    }
                    tempList.Remove(tempPerson);
                }
                if (t)
                    return false;
            }
            return true;
        }
    }
}
