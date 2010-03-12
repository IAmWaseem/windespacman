namespace TicTacToe
{
    partial class TicTacForm
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.player1AI = new System.Windows.Forms.RadioButton();
            this.player1Human = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.player2AI = new System.Windows.Forms.RadioButton();
            this.player2Human = new System.Windows.Forms.RadioButton();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.GameWithATwist = new System.Windows.Forms.RadioButton();
            this.GameClassic = new System.Windows.Forms.RadioButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.CurrentPlayerLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.player1AI);
            this.groupBox1.Controls.Add(this.player1Human);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(81, 68);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Player 1";
            // 
            // player1AI
            // 
            this.player1AI.AutoSize = true;
            this.player1AI.Enabled = false;
            this.player1AI.Location = new System.Drawing.Point(6, 42);
            this.player1AI.Name = "player1AI";
            this.player1AI.Size = new System.Drawing.Size(35, 17);
            this.player1AI.TabIndex = 1;
            this.player1AI.Text = "AI";
            this.player1AI.UseVisualStyleBackColor = true;
            // 
            // player1Human
            // 
            this.player1Human.AutoSize = true;
            this.player1Human.Checked = true;
            this.player1Human.Location = new System.Drawing.Point(6, 19);
            this.player1Human.Name = "player1Human";
            this.player1Human.Size = new System.Drawing.Size(59, 17);
            this.player1Human.TabIndex = 0;
            this.player1Human.TabStop = true;
            this.player1Human.Text = "Human";
            this.player1Human.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.player2AI);
            this.groupBox2.Controls.Add(this.player2Human);
            this.groupBox2.Location = new System.Drawing.Point(99, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(81, 68);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Player 2";
            // 
            // player2AI
            // 
            this.player2AI.AutoSize = true;
            this.player2AI.Enabled = false;
            this.player2AI.Location = new System.Drawing.Point(6, 42);
            this.player2AI.Name = "player2AI";
            this.player2AI.Size = new System.Drawing.Size(35, 17);
            this.player2AI.TabIndex = 1;
            this.player2AI.Text = "AI";
            this.player2AI.UseVisualStyleBackColor = true;
            // 
            // player2Human
            // 
            this.player2Human.AutoSize = true;
            this.player2Human.Checked = true;
            this.player2Human.Location = new System.Drawing.Point(6, 19);
            this.player2Human.Name = "player2Human";
            this.player2Human.Size = new System.Drawing.Size(59, 17);
            this.player2Human.TabIndex = 0;
            this.player2Human.TabStop = true;
            this.player2Human.Text = "Human";
            this.player2Human.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.GameWithATwist);
            this.groupBox3.Controls.Add(this.GameClassic);
            this.groupBox3.Location = new System.Drawing.Point(186, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(96, 68);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Game options";
            // 
            // GameWithATwist
            // 
            this.GameWithATwist.AutoSize = true;
            this.GameWithATwist.Checked = true;
            this.GameWithATwist.Location = new System.Drawing.Point(6, 42);
            this.GameWithATwist.Name = "GameWithATwist";
            this.GameWithATwist.Size = new System.Drawing.Size(85, 17);
            this.GameWithATwist.TabIndex = 1;
            this.GameWithATwist.TabStop = true;
            this.GameWithATwist.Text = "With A Twist";
            this.GameWithATwist.UseVisualStyleBackColor = true;
            // 
            // GameClassic
            // 
            this.GameClassic.AutoSize = true;
            this.GameClassic.Location = new System.Drawing.Point(6, 19);
            this.GameClassic.Name = "GameClassic";
            this.GameClassic.Size = new System.Drawing.Size(58, 17);
            this.GameClassic.TabIndex = 0;
            this.GameClassic.Text = "Classic";
            this.GameClassic.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(12, 86);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(400, 400);
            this.panel1.TabIndex = 4;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            // 
            // CurrentPlayerLabel
            // 
            this.CurrentPlayerLabel.AutoSize = true;
            this.CurrentPlayerLabel.Location = new System.Drawing.Point(288, 12);
            this.CurrentPlayerLabel.Name = "CurrentPlayerLabel";
            this.CurrentPlayerLabel.Size = new System.Drawing.Size(35, 13);
            this.CurrentPlayerLabel.TabIndex = 5;
            this.CurrentPlayerLabel.Text = "Now: ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(288, 33);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Now: ";
            // 
            // TicTacForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(424, 498);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CurrentPlayerLabel);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(440, 534);
            this.MinimumSize = new System.Drawing.Size(440, 534);
            this.Name = "TicTacForm";
            this.Text = "Tic-Tac-Toe";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton player1AI;
        private System.Windows.Forms.RadioButton player1Human;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton player2AI;
        private System.Windows.Forms.RadioButton player2Human;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RadioButton GameWithATwist;
        private System.Windows.Forms.RadioButton GameClassic;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label CurrentPlayerLabel;
        private System.Windows.Forms.Label label1;
    }
}

