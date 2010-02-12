using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DisjointSetsCS
{
    class DisjointSets
    {
        protected int[] SetArray;

        public DisjointSets()
        {
            this.SetArray = new int[] { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        }

        public DisjointSets(int[] SetArray)
        {
            this.SetArray = SetArray;
        }

        public DisjointSets(uint Size)
        {
            int[] NewArray = new int[Size];
            for (int i = 0; i < NewArray.Length; i++)
                NewArray[i] = -1;

            this.SetArray = NewArray;
        }

        public DisjointSets(DisjointSets ds)
        {
            this.SetArray = ds.SetArray;
        }

        public override string ToString()
        {
            string back = "| ";

            foreach (int i in SetArray)
                back += i + " | ";

            return back;
        }

        public string ToStringIndex()
        {
            string back = "| ";

            for (int i = 0; i < SetArray.Length; i++)
            {
                if(SetArray[i] < 0)
                    back += " " + i + " | ";
                else
                    back += "" + i + " | ";
            }

            return back;
        }

        public virtual uint Find(uint elem)
        {
            if (SetArray[elem] < 0)
                return elem;
            else
            {
                // Recursively set array to whatever Find returns.  Find will
                // return the root, thus each node from this one up is set to 	// root.
                SetArray[elem] = (int)(Find((uint)SetArray[elem]));
                return (uint)SetArray[elem];
            }
        }

        public virtual void Union(uint elem1, uint elem2)
        {
            uint root1, root2;

            // check if elem1 is root, if not, find the root
            if (SetArray[elem1] >= 0)
                root1 = Find(elem1);
            else
                root1 = elem1;

            // same for elem2
            if (SetArray[elem2] >= 0)
                root2 = Find(elem2);
            else
                root2 = elem2;

            // set root2 to be child of root1
            SetArray[root2] = (int)root1;
        }
    }
}
