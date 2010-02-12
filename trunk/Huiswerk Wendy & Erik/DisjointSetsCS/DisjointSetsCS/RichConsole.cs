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

            WLConsole("Created by Wendy & Erik");
            WLConsole();

            // print the array
            WLConsole("Preformed arbitrarily");
            WLConsole("Normal", true);
            WLConsole(d_arbit.ToStringIndex(), true);
            WLConsole(d_arbit.ToString(), true);
            WLConsole();
            WLConsole("After d_arbit.Find(7)", true);
            d_arbit.Find(7);
            // reprint
            WLConsole(d_arbit.ToStringIndex(), true);
            WLConsole(d_arbit.ToString(), true);
            WLConsole();

            // print the array
            WLConsole("Performed smart (by size)");
            WLConsole("Normal", true);
            WLConsole(d_size.ToStringIndex(), true);
            WLConsole(d_size.ToString(), true);
            WLConsole();
            WLConsole("After d_size.Find(1)", true);
            d_size.Find(1);
            // reprint
            WLConsole(d_size.ToStringIndex(), true);
            WLConsole(d_size.ToString(), true);
            WLConsole();

            // print the array
            WLConsole("Performed smart (by height)");
            WLConsole("Normal", true);
            WLConsole(d_height.ToStringIndex(), true);
            WLConsole(d_height.ToString(), true);
            WLConsole();
            WLConsole("After d_height.Find(1)", true);
            d_height.Find(1);
            // reprint
            WLConsole(d_height.ToStringIndex(), true);
            WLConsole(d_height.ToString(), true);
        }

        public void WLConsole()
        {
            WLConsole("", false, true);
        }

        public void WLConsole(string s)
        {
            WLConsole(s, false, true);
        }

        public void WLConsole(string s, bool Tab)
        {
            WLConsole(s, Tab, true);
        }

        public void WLConsole(string s, bool Tab, bool NewLine)
        {
            if (Tab)
                richTextBox1.Text += "\t";

            richTextBox1.Text += s;

            if (NewLine)
                richTextBox1.Text += "\n";
        }        
    }
}
