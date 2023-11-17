
namespace BluetoothWin
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
            this.components = new System.ComponentModel.Container();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.bleCommTool1 = new BluetoothWin.BleCommTool();
            this.SuspendLayout();
            // 
            // bleCommTool1
            // 
            this.bleCommTool1.BackColor = System.Drawing.Color.Black;
            this.bleCommTool1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bleCommTool1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bleCommTool1.Location = new System.Drawing.Point(0, 0);
            this.bleCommTool1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bleCommTool1.Name = "bleCommTool1";
            this.bleCommTool1.Size = new System.Drawing.Size(639, 739);
            this.bleCommTool1.TabIndex = 4;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(639, 739);
            this.Controls.Add(this.bleCommTool1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private BleCommTool bleCommTool1;
    }
}

