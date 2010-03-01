namespace closestPair
{
    partial class ClosestPair
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.Panel1 = new System.Windows.Forms.Panel();
            this.start = new System.Windows.Forms.Button();
            this.rst = new System.Windows.Forms.Button();
            this.distance = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // Panel1
            // 
            this.Panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.Panel1.BackColor = System.Drawing.Color.White;
            this.Panel1.Location = new System.Drawing.Point(13, 13);
            this.Panel1.Name = "Panel1";
            this.Panel1.Size = new System.Drawing.Size(469, 315);
            this.Panel1.TabIndex = 0;
            this.Panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Panel1_MouseDown);
            this.Panel1.Resize += new System.EventHandler(this.Panel1_Resize);
            // 
            // start
            // 
            this.start.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.start.Location = new System.Drawing.Point(326, 334);
            this.start.Name = "start";
            this.start.Size = new System.Drawing.Size(75, 23);
            this.start.TabIndex = 1;
            this.start.Text = "Start";
            this.start.UseVisualStyleBackColor = true;
            this.start.Click += new System.EventHandler(this.start_Click);
            // 
            // rst
            // 
            this.rst.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.rst.Location = new System.Drawing.Point(407, 334);
            this.rst.Name = "rst";
            this.rst.Size = new System.Drawing.Size(75, 23);
            this.rst.TabIndex = 2;
            this.rst.Text = "reset";
            this.rst.UseVisualStyleBackColor = true;
            this.rst.Click += new System.EventHandler(this.rst_Click);
            // 
            // distance
            // 
            this.distance.AutoSize = true;
            this.distance.Location = new System.Drawing.Point(13, 287);
            this.distance.Name = "distance";
            this.distance.Size = new System.Drawing.Size(0, 13);
            this.distance.TabIndex = 3;
            // 
            // ClosestPair
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(494, 369);
            this.Controls.Add(this.distance);
            this.Controls.Add(this.rst);
            this.Controls.Add(this.start);
            this.Controls.Add(this.Panel1);
            this.Name = "ClosestPair";
            this.Text = "ClosestPair";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel Panel1;
        private System.Windows.Forms.Button start;
        private System.Windows.Forms.Button rst;
        private System.Windows.Forms.Label distance;
    }
}