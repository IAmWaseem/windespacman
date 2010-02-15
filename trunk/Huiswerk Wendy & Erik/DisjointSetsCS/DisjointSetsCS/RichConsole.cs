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
        public void huiswerk()
        {
            // Arbitrarily preformed -> Union(2,3), union(5,6), union(7,5), union(2,5), union(0,1), union(4,0), union(0,2)
            DisjointSets d_arbit = new DisjointSets(8);
            DisjointSetsSize d_size = new DisjointSetsSize(8);
            DisjointSetsHeight d_height = new DisjointSetsHeight(8);
            //DisjointSetsSize d
            richTextBox1.Visible = true;
            richTextBox1.Dock = DockStyle.Fill;
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

        MazeGenerator mg = null;
        public void practicum()
        {
            //panel1.Visible = true;
            //panel1.Dock = DockStyle.Fill;

            mg = new MazeGenerator(6, 6);
            mg.GenerateMaze();

            richTextBox1.Visible = true;
            richTextBox1.Dock = DockStyle.Fill;
            foreach (MazeGenerator.Edge edge in mg.aPath)
            {
                WriteConsole(edge.Edge1 + " - " + edge.Edge2);

            }

            //MazeGenerator.EdgeSort es = new MazeGenerator.EdgeSort();
            //mg.maze.Sort(es);
            //foreach (MazeGenerator.Edge edge in mg.maze)
            //{
            //    if (edge.Edge1 + 1 == edge.Edge2 || edge.Edge2 + 1 == edge.Edge1)

            //        WriteConsole(" | ", false, false);


            //}


        }

        public RichConsole()
        {
            InitializeComponent();
            richTextBox1.Visible = false;
            panel1.Visible = false;

            //huiswerk();
            
            practicum();
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

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            PointF startP = new PointF(0, 0);
            if (mg != null)
            {
                int boxSize = 25;
                float row1 = 0;
                float column1 = 0;
                float row2 = 0;
                float column2 = 0;
                int offsetX = 50;
                int offsetY = 50;

                foreach (MazeGenerator.Edge edge in mg.maze)
                {
                    row1 = (int)edge.Edge1 / (int)mg.Rows;
                    column1 = (int)edge.Edge1 % (int)mg.Columns;
                    row2 = (int)edge.Edge2 / (int)mg.Rows;
                    column2 = (int)edge.Edge2 % (int)mg.Columns;
                    //g.DrawLine(Pens.Black, offsetX, offsetY, 
                    g.DrawLine(Pens.Black, offsetX + column1 * boxSize, offsetY + row1 * boxSize, offsetX + column2 * boxSize, offsetY + row2 * boxSize);
                }
            }
        }        
    }
}
