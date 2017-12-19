namespace WindowsFormsApp1
{
    partial class Form1
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
            this.pnlCenter = new System.Windows.Forms.Panel();
            this.btnStopCenter = new System.Windows.Forms.Button();
            this.pnlLeft = new System.Windows.Forms.Panel();
            this.btnStopLeft = new System.Windows.Forms.Button();
            this.splitter1 = new System.Windows.Forms.Splitter();
            this.button1 = new System.Windows.Forms.Button();
            this.txtCenter = new System.Windows.Forms.TextBox();
            this.txtLeft = new System.Windows.Forms.TextBox();
            this.pnlCenter.SuspendLayout();
            this.pnlLeft.SuspendLayout();
            this.SuspendLayout();
            // 
            // pnlCenter
            // 
            this.pnlCenter.BackColor = System.Drawing.SystemColors.Control;
            this.pnlCenter.Controls.Add(this.txtCenter);
            this.pnlCenter.Controls.Add(this.button1);
            this.pnlCenter.Controls.Add(this.btnStopCenter);
            this.pnlCenter.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pnlCenter.Location = new System.Drawing.Point(203, 0);
            this.pnlCenter.Name = "pnlCenter";
            this.pnlCenter.Size = new System.Drawing.Size(571, 484);
            this.pnlCenter.TabIndex = 0;
            this.pnlCenter.Resize += new System.EventHandler(this.pnlCenter_Resize);
            // 
            // btnStopCenter
            // 
            this.btnStopCenter.Location = new System.Drawing.Point(63, 44);
            this.btnStopCenter.Name = "btnStopCenter";
            this.btnStopCenter.Size = new System.Drawing.Size(75, 23);
            this.btnStopCenter.TabIndex = 0;
            this.btnStopCenter.Text = "StopCenter";
            this.btnStopCenter.UseVisualStyleBackColor = true;
            this.btnStopCenter.Click += new System.EventHandler(this.btnStopCenter_Click);
            // 
            // pnlLeft
            // 
            this.pnlLeft.Controls.Add(this.txtLeft);
            this.pnlLeft.Controls.Add(this.btnStopLeft);
            this.pnlLeft.Dock = System.Windows.Forms.DockStyle.Left;
            this.pnlLeft.Location = new System.Drawing.Point(0, 0);
            this.pnlLeft.Name = "pnlLeft";
            this.pnlLeft.Size = new System.Drawing.Size(200, 484);
            this.pnlLeft.TabIndex = 1;
            this.pnlLeft.Resize += new System.EventHandler(this.pnlLeft_Resize);
            // 
            // btnStopLeft
            // 
            this.btnStopLeft.Location = new System.Drawing.Point(36, 44);
            this.btnStopLeft.Name = "btnStopLeft";
            this.btnStopLeft.Size = new System.Drawing.Size(75, 23);
            this.btnStopLeft.TabIndex = 0;
            this.btnStopLeft.Text = "StopLeft";
            this.btnStopLeft.UseVisualStyleBackColor = true;
            this.btnStopLeft.Click += new System.EventHandler(this.btnStopLeft_Click);
            // 
            // splitter1
            // 
            this.splitter1.Location = new System.Drawing.Point(200, 0);
            this.splitter1.Name = "splitter1";
            this.splitter1.Size = new System.Drawing.Size(3, 484);
            this.splitter1.TabIndex = 2;
            this.splitter1.TabStop = false;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(250, 44);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // txtCenter
            // 
            this.txtCenter.Location = new System.Drawing.Point(6, 12);
            this.txtCenter.Name = "txtCenter";
            this.txtCenter.Size = new System.Drawing.Size(100, 20);
            this.txtCenter.TabIndex = 2;
            // 
            // txtLeft
            // 
            this.txtLeft.Location = new System.Drawing.Point(11, 3);
            this.txtLeft.Name = "txtLeft";
            this.txtLeft.Size = new System.Drawing.Size(100, 20);
            this.txtLeft.TabIndex = 3;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(774, 484);
            this.Controls.Add(this.pnlCenter);
            this.Controls.Add(this.splitter1);
            this.Controls.Add(this.pnlLeft);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.pnlCenter.ResumeLayout(false);
            this.pnlCenter.PerformLayout();
            this.pnlLeft.ResumeLayout(false);
            this.pnlLeft.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlCenter;
        private System.Windows.Forms.Button btnStopCenter;
        private System.Windows.Forms.Panel pnlLeft;
        private System.Windows.Forms.Button btnStopLeft;
        private System.Windows.Forms.Splitter splitter1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox txtCenter;
        private System.Windows.Forms.TextBox txtLeft;
    }
}

