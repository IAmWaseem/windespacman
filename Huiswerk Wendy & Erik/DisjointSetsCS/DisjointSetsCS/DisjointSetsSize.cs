using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DisjointSetsCS
{
    class DisjointSetsSize : DisjointSets
    {
        public DisjointSetsSize()
        {
            this.SetArray = new int[] { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        }

        public DisjointSetsSize(int[] SetArray)
        {
            this.SetArray = SetArray;
        }

        public DisjointSetsSize(uint Size)
        {
            int[] NewArray = new int[Size];
            for (int i = 0; i < NewArray.Length; i++)
                NewArray[i] = -1;

            this.SetArray = NewArray;
        }

        public DisjointSetsSize(DisjointSetsSize ds)
        {
            this.SetArray = ds.SetArray;
        }

        public override uint Find(uint elem)
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

        public override uint Find_(uint elem)
        {
            if (SetArray[elem] < 0)
                return elem;
            else
            {
                // Recursively set array to whatever Find returns.  Find will
                // return the root, thus each node from this one up is set to 	// root.
                return (Find((uint)SetArray[elem]));
            }
        }

        public override void Union(uint elem1, uint elem2)
        {
            uint root1, root2;

            // check if elem1 is root, if not, find the root
            if (SetArray[elem1] < 0)
                root1 = elem1;
            else
                root1 = Find(elem1);

            // same
            if (SetArray[elem2] < 0)
                root2 = elem2;
            else
                root2 = Find(elem2);

            if (SetArray[root2] < SetArray[root1])
            {
                // root2 has greater size, since size is given as
                // the negation of actual size
                // find the size of the union, and make root1 the child of root2
                SetArray[root2] += SetArray[root1];
                SetArray[root1] = (int)root2;
            }
            else
            {
                // root1 has greater size  or they have equal sizes
                // find the size of the union, and make root2 the child of root1
                SetArray[root1] += SetArray[root2];
                SetArray[root2] = (int)root1;
            }
        }
    }
}
