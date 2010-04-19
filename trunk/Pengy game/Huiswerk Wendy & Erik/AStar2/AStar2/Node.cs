using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AStar2
{
    public enum State
    {
        left = 1,
        right = 2,
        boot = 3
    }
    public enum Type
    {
        M = 1,
        K = 2,
        B = 3
    }
    public struct Person
    {
        public State state;
        public Type type; 
    }
    public class Node
    {
        public List<Person> persons { 
            get; 
            set; 
        }
        public int Id { get; set; }
        public Node cameFrom { get; set; }
        public double g_Score { get; set; }

        public Node(int id, List<Person> person)
        {
            this.persons = new List<Person>();
            persons.AddRange(person);
            this.Id = id;
        }

        public Node(int id, State mOne, State mTwo, State mThree, State kOne, State kTwo, State kThree, State Boat)
        {
            Id = id;
            g_Score = 0;
            persons = new List<Person>();
            persons.Add(new Person() { state = mOne, type = Type.M});
            persons.Add(new Person() { state = mTwo, type = Type.M });
            persons.Add(new Person() { state = mThree, type = Type.M });
            persons.Add(new Person() { state = kOne, type = Type.K });
            persons.Add(new Person() { state = kTwo, type = Type.K });
            persons.Add(new Person() { state = kThree, type = Type.K });
            persons.Add(new Person() { state = Boat, type = Type.B });

        }
    }
}
