using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DisjointSetsCS
{
    class DisjointSetsHeight : DisjointSets
    {
        public DisjointSetsHeight()
        {
            this.SetArray = new int[] { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
        }

        public DisjointSetsHeight(int[] SetArray)
        {
            this.SetArray = SetArray;
        }

        public DisjointSetsHeight(uint Size)
        {
            int[] NewArray = new int[Size];
            for (int i = 0; i < NewArray.Length; i++)
                NewArray[i] = -1;

            this.SetArray = NewArray;
        }

        public DisjointSetsHeight(DisjointSetsHeight ds)
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
                // root2 has greater height, since height is given as
                // the negation of actual height
                // find the height of the union, and make root1 the child of root2
                if (SetArray[root2] > (SetArray[root1] - 1))
                    SetArray[root2] = SetArray[root1] - 1;      
                SetArray[root1] = (int)root2;
            }
            else
            {
                // root1 has greater height  or they have equal height
                // find the height of the union, and make root2 the child of root1
                if (SetArray[root1] > (SetArray[root2] - 1))
                    SetArray[root1] = SetArray[root2] - 1;                
                SetArray[root2] = (int)root1;
            }
        }
    }
}
