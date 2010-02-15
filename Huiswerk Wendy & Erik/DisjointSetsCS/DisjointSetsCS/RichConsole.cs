using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace DisjointSetsCS
{
    public partial class RichConsole : Form
    {
        public RichConsole()
        {
            InitializeComponent();

            // Arbitrarily preformed -> Union(2,3), union(5,6), union(7,5), union(2,5), union(0,1), union(4,0), union(0,2)
            DisjointSets d_arbit = new DisjointSets(8);
            DisjointSetsSize d_size = new DisjointSetsSize(8);
            DisjointSetsHeight d_height = new DisjointSetsHeight(8);
            //DisjointSetsSize d

            d_arbit.Union(2, 3); d_size.Union(2, 3); d_height.Union(2, 3);
            d_arbit.Union(5, 6); d_size.Union(5, 6); d_height.Union(5, 6);
            d_arbit.Union(7, 5); d_size.Union(7, 5); d_height.Union(7, 5);
            d_arbit.Union(2, 5); d_size.Union(2, 5); d_height.Union(2, 5);
            d_arbit.Union(0, 1); d_size.Union(0, 1); d_height.Union(0, 1);
            d_arbit.Union(4, 0); d_size.Union(4, 0); d_height.Union(4, 0);
            d_arbit.Union(0, 2); d_size.Union(0, 2); d_height.Union(0, 2);

            WriteConsole("Created by Wendy & Erik");
            WriteConsole();

            // print the array
            WriteConsole("Preformed arbitrarily");
            WriteConsole("Normal", true);
            WriteConsole(d_arbit.ToStringIndex(), true);
            WriteConsole(d_arbit.ToString(), true);
            WriteConsole();
            WriteConsole("After d_arbit.Find(7)", true);
            d_arbit.Find(7);
            // reprint
            WriteConsole(d_arbit.ToStringIndex(), true);
            WriteConsole(d_arbit.ToString(), true);
            WriteConsole();

            // print the array
            WriteConsole("Performed smart (by size)");
            WriteConsole("Normal", true);
            WriteConsole(d_size.ToStringIndex(), true);
            WriteConsole(d_size.ToString(), true);
            WriteConsole();
            WriteConsole("After d_size.Find(1)", true);
            d_size.Find(1);
            // reprint
            WriteConsole(d_size.ToStringIndex(), true);
            WriteConsole(d_size.ToString(), true);
            WriteConsole();

            // print the array
            WriteConsole("Performed smart (by height)");
            WriteConsole("Normal", true);
            WriteConsole(d_height.ToStringIndex(), true);
            WriteConsole(d_height.ToString(), true);
            WriteConsole();
            WriteConsole("After d_height.Find(1)", true);
            d_height.Find(1);
            // reprint
            WriteConsole(d_height.ToStringIndex(), true);
            WriteConsole(d_height.ToString(), true);
        }

        public void WriteConsole()
        {
            WriteConsole("", false, true);
        }

        public void WriteConsole(string s)
        {
            WriteConsole(s, false, true);
        }

        public void WriteConsole(string s, bool Tab)
        {
            WriteConsole(s, Tab, true);
        }

        public void WriteConsole(string s, bool Tab, bool NewLine)
        {
            if (Tab)
                richTextBox1.Text += "\t";

            richTextBox1.Text += s;

            if (NewLine)
                richTextBox1.Text += "\n";
        }        
    }
}
