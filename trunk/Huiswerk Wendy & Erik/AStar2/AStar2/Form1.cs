using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AStar2
{
    public partial class Form1 : Form
    {
        private Graph graph;
        public Form1()
        {
            InitializeComponent();
            graph = new Graph();
            Node n = new Node(0, State.right, State.right, State.right, State.right, State.right, State.right, State.left);
            graph.AddNode(n);
            generateGraph(n, 0);
            bool succes = graph.HasFinish();

            AStar astar = new AStar(graph);
            bool success = astar.AStarAlgorithm(0,24);
            List<Node> path = astar.total;
        }

        private void generateGraph(Node n, int depth)
        {
            //if (depth >= 6000)
            //{
            //    return;
            //}
            Node temp = new Node(n.Id, n.persons);
            List<Node> nextNodes = getMoves(temp);
            if (nextNodes != null)
            {
                if (nextNodes.Count > 0)
                {
                    foreach (Node tempNode in nextNodes)
                    {
                        graph.AddNode(tempNode);
                        graph.AddEdge(n.Id, tempNode.Id, true, 1);
                        generateGraph(tempNode, depth + 1);
                    }
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }

        private List<Node> getMoves(Node n)
        {
            int inBoatM = 0;
            int rightM = 0;
            int leftM = 0;
            int inBoatK = 0;
            int rightK = 0;
            int leftK = 0;
            State boat = State.left;
            int id = graph.Nodes.Count;
            List<Node> nextNodes = new List<Node>();
            int i;
            foreach (Person p in n.persons)
            {
                if (p.type == Type.M)
                {
                    if (p.state == State.boot)
                    {
                        inBoatM++;
                    }
                    else if (p.state == State.left)
                    {
                        leftM++;
                    }
                    else
                    {
                        rightM++;
                    }
                }
                else if(p.type == Type.K)
                {
                    if (p.state == State.boot)
                    {
                        inBoatK++;
                    }
                    else if (p.state == State.left)
                    {
                        leftK++;
                    }
                    else
                    {
                        rightK++;
                    }
                }
                else
                {
                    boat = p.state;
                }
            }
            if (inBoatK + inBoatM == 0)
            {

            }

            #region boot
            List<Person> list;
            if (leftK + leftM < 6)
            {
                Node temp = n;
                Person b = temp.persons.Where(p => p.type == Type.B).First();
                if (boat == State.right)
                {
                    b.state = State.left;
                }
                else
                {
                    b.state = State.right;
                }
                List<Person> uit = temp.persons.Where(p => p.state == State.boot).ToList();
                uit.AddRange(temp.persons.Where(p => p.state == b.state).ToList());
                if (uit.Where(t => t.type == Type.M).Count() >= uit.Where(t => t.type == Type.K).Count())
                {
                    int aantalM = 0;
                    int aantalK = 0;
                    if (b.state == State.left)
                    {
                        aantalM = leftM + inBoatM;
                        aantalK = leftK + inBoatK;
                    }
                    else
                    {
                        aantalM = rightM + inBoatM;
                        aantalK = rightK + inBoatK;
                    }
                    if (b.state == State.left && aantalK + aantalM == 6)
                    {
                        return null;
                    }
                    List<Person> tempList = new List<Person>();
                    tempList.AddRange(temp.persons);
                    if (aantalM >= 2)
                    {
                        list = temp.persons.Where(t => t.state == State.boot).ToList();
                        foreach (Person p in list)
                        {
                            temp.persons.Remove(p);
                            Person tempPers = p;
                            tempPers.state = b.state;
                            temp.persons.Add(tempPers);
                        }
                        tempList.Clear();
                        tempList.AddRange(temp.persons);
                        //2m in boot
                        temp.persons.Clear();
                        temp.persons.AddRange(tempList);
                        i = 1;
                        list = temp.persons.Where(t => t.state == b.state && t.type == Type.M).ToList();
                        foreach (Person p in list)
                        {
                            if (i <= 2)
                            {
                                temp.persons.Remove(p);
                                Person tempPers = p;
                                tempPers.state = State.boot;
                                temp.persons.Add(tempPers);
                                i++;
                            }
                        }
                        Person boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                        temp.persons.Remove(boatPerson);
                        boatPerson.state = b.state;
                        temp.persons.Add(boatPerson);
                        Node addNode = new Node(id, temp.persons);
                        if(graph.DoesContain(addNode))
                            nextNodes.Add(addNode);
                        //1m in boot
                        temp.persons.Clear();
                        temp.persons.AddRange(tempList);
                        i = 1;
                        list = temp.persons.Where(t => t.state == b.state && t.type == Type.M).ToList();
                        foreach (Person p in list)
                        {
                            if (i <= 1)
                            {
                                temp.persons.Remove(p);
                                Person tempPers = p;
                                tempPers.state = State.boot;
                                temp.persons.Add(tempPers);
                                i++;
                            }
                        }
                        boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                        temp.persons.Remove(boatPerson);
                        boatPerson.state = b.state;
                        temp.persons.Add(boatPerson);
                        addNode = new Node(id, temp.persons);
                        if (graph.DoesContain(addNode))
                            nextNodes.Add(addNode);
                        if (aantalK >= 1)
                        {
                            //1 m in boot + 1 k in boot
                            temp.persons.Clear();
                            temp.persons.AddRange(tempList);
                            Person pM = temp.persons.FirstOrDefault(t => t.state == b.state && t.type == Type.M);
                            Person pK = temp.persons.FirstOrDefault(t => t.state == b.state && t.type == Type.K);

                            temp.persons.Remove(pM);
                            pM.state = State.boot;
                            temp.persons.Add(pM);

                            temp.persons.Remove(pK);
                            pK.state = State.boot;
                            temp.persons.Add(pK);
                             boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                            temp.persons.Remove(boatPerson);
                            boatPerson.state = b.state;
                            temp.persons.Add(boatPerson);
                            addNode = new Node(id, temp.persons);
                            if (graph.DoesContain(addNode))
                                nextNodes.Add(addNode);

                            //1k in boot
                            temp.persons.Clear();
                            temp.persons.AddRange(tempList);
                            i = 1;
                            list = temp.persons.Where(t => t.state == b.state && t.type == Type.K).ToList();
                            foreach (Person p in list)
                            {
                                if (i <= 1)
                                {

                                    temp.persons.Remove(p);
                                    Person tempPers = p;
                                    tempPers.state = State.boot;
                                    temp.persons.Add(tempPers);
                                    i++;
                                }
                            }
                             boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                            temp.persons.Remove(boatPerson);
                            boatPerson.state = b.state;
                            temp.persons.Add(boatPerson);
                            addNode = new Node(id, temp.persons);
                            if (graph.DoesContain(addNode))
                                nextNodes.Add(addNode);
                        }
                        if (aantalK >= 2)
                        {
                            //2 k in boot
                            temp.persons.Clear();
                            temp.persons.AddRange(tempList);
                            i = 1;
                            list = temp.persons.Where(t => t.state == b.state && t.type == Type.K).ToList();
                            foreach (Person p in list)
                            {
                                if (i <= 2)
                                {

                                    temp.persons.Remove(p);
                                    Person tempPers = p;
                                    tempPers.state = State.boot;
                                    temp.persons.Add(tempPers);
                                    i++;
                                }
                            }
                             boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                            temp.persons.Remove(boatPerson);
                            boatPerson.state = b.state;
                            temp.persons.Add(boatPerson);
                            addNode = new Node(id, temp.persons);
                            
                            if (graph.DoesContain(addNode))
                                nextNodes.Add(addNode);
                        }

                    }
                    else if (aantalK >= 2)
                    {
                        if (aantalM == 1)
                        {
                            //1m + 1k in boot
                            temp.persons.Clear();
                            temp.persons.AddRange(tempList);
                            Person pM = temp.persons.FirstOrDefault(t => t.state == b.state && t.type == Type.M);
                            Person pK = temp.persons.FirstOrDefault(t => t.state == b.state && t.type == Type.K);

                            temp.persons.Remove(pM);
                            pM.state = State.boot;
                            temp.persons.Add(pM);

                            temp.persons.Remove(pK);
                            pK.state = State.boot;
                            temp.persons.Add(pK);
                            Person boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                            temp.persons.Remove(boatPerson);
                            boatPerson.state = b.state;
                            temp.persons.Add(boatPerson);
                            Node addNode = new Node(id, temp.persons);
                            if (graph.DoesContain(addNode))
                                nextNodes.Add(addNode);

                            //1m in boot
                            temp.persons.Clear();
                            temp.persons.AddRange(tempList);
                            i = 1;
                            list = temp.persons.Where(t => t.state == b.state && t.type == Type.M).ToList();
                            foreach (Person p in list)
                            {
                                if (i <= 1)
                                {
                                    temp.persons.Remove(p);
                                    Person tempPers = p;
                                    tempPers.state = State.boot;
                                    temp.persons.Add(tempPers);
                                    i++;
                                }
                            }
                             boatPerson = temp.persons.FirstOrDefault(t => t.type == Type.B);
                            temp.persons.Remove(boatPerson);
                            boatPerson.state = b.state;
                            temp.persons.Add(boatPerson);
                            addNode = new Node(id, temp.persons);
                            if (graph.DoesContain(addNode))
                                nextNodes.Add(addNode);
                        }
                        //2k in boot
                        temp.persons.Clear();
                        temp.persons.AddRange(tempList);
                        i = 1;
                        list = temp.persons.Where(t => t.state == b.state && t.type == Type.K).ToList();
                        foreach (Person p in list)
                        {
                            if (i <= 2)
                            {
                                temp.persons.Remove(p);
                                Person tempPers = p;
                                tempPers.state = State.boot;
                                temp.persons.Add(tempPers);
                                i++;
                            }
                        }
                        Person boatPerson2 = temp.persons.FirstOrDefault(t => t.type == Type.B);
                        temp.persons.Remove(boatPerson2);
                        boatPerson2.state = b.state;
                        temp.persons.Add(boatPerson2);
                        Node addNode2 = new Node(id, temp.persons);
                        if (graph.DoesContain(addNode2))
                            nextNodes.Add(addNode2);
                        //1k in boot
                        temp.persons.Clear();
                        temp.persons.AddRange(tempList);
                        i = 1;
                        list = temp.persons.Where(t => t.state == b.state && t.type == Type.K).ToList();
                        foreach (Person p in list)
                        {
                            if (i <= 1)
                            {
                                temp.persons.Remove(p);
                                Person tempPers = p;
                                tempPers.state = State.boot;
                                temp.persons.Add(tempPers);
                                i++;
                            }
                        }
                        Person boatPerson3 = temp.persons.FirstOrDefault(t => t.type == Type.B);
                        temp.persons.Remove(boatPerson3);
                        boatPerson3.state = b.state;
                        temp.persons.Add(boatPerson3);
                        addNode2 = new Node(id, temp.persons);
                        if (graph.DoesContain(addNode2))
                            nextNodes.Add(addNode2);
                    }
                }
                else
                {
                    //dood
                    return null;
                }
            }
            else
            {
                return null;
            }
            #endregion
            return nextNodes;

        }
    }
}
