namespace Karo.Gui
{
    partial class KaroGui
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
            this.mStatusStrip = new System.Windows.Forms.StatusStrip();
            this.mEngineVersionLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.mStatusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // mStatusStrip
            // 
            this.mStatusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mEngineVersionLabel});
            this.mStatusStrip.Location = new System.Drawing.Point(0, 242);
            this.mStatusStrip.Name = "mStatusStrip";
            this.mStatusStrip.Size = new System.Drawing.Size(284, 22);
            this.mStatusStrip.TabIndex = 0;
            this.mStatusStrip.Text = "mStatusStrip";
            // 
            // mEngineVersionLabel
            // 
            this.mEngineVersionLabel.Name = "mEngineVersionLabel";
            this.mEngineVersionLabel.Size = new System.Drawing.Size(121, 17);
            this.mEngineVersionLabel.Text = "mEngineVersionLabel";
            // 
            // KaroGui
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 264);
            this.Controls.Add(this.mStatusStrip);
            this.Name = "KaroGui";
            this.Text = "Form1";
            this.mStatusStrip.ResumeLayout(false);
            this.mStatusStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip mStatusStrip;
        private System.Windows.Forms.ToolStripStatusLabel mEngineVersionLabel;
    }
}

