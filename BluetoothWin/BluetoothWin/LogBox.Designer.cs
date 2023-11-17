
namespace BluetoothWin
{
    partial class LogBox
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.RTF = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // RTF
            // 
            this.RTF.BackColor = System.Drawing.Color.Black;
            this.RTF.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.RTF.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RTF.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.RTF.Location = new System.Drawing.Point(0, 0);
            this.RTF.Name = "RTF";
            this.RTF.Size = new System.Drawing.Size(445, 371);
            this.RTF.TabIndex = 0;
            this.RTF.Text = "";
            // 
            // LogBox
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.RTF);
            this.Name = "LogBox";
            this.Size = new System.Drawing.Size(445, 371);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox RTF;
    }
}
