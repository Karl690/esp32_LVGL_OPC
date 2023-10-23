
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
            this.btnScanForDevices = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.grpSendData = new System.Windows.Forms.GroupBox();
            this.txtboxSend = new System.Windows.Forms.TextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.grpSendFIle = new System.Windows.Forms.GroupBox();
            this.nudLines = new System.Windows.Forms.NumericUpDown();
            this.txtFilePath = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.grpSendInterval = new System.Windows.Forms.GroupBox();
            this.nudTimes = new System.Windows.Forms.NumericUpDown();
            this.nudBytes = new System.Windows.Forms.NumericUpDown();
            this.nudTimer = new System.Windows.Forms.NumericUpDown();
            this.chkInterval = new System.Windows.Forms.CheckBox();
            this.lblTotal = new System.Windows.Forms.Label();
            this.lblSpeed = new System.Windows.Forms.Label();
            this.lblSendText = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lblDuring = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblLines = new System.Windows.Forms.Label();
            this.richboxReceivedData = new System.Windows.Forms.RichTextBox();
            this.lblName = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblID = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnConnect = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.lblLPS = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.grpSendData.SuspendLayout();
            this.grpSendFIle.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudLines)).BeginInit();
            this.grpSendInterval.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudTimes)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudBytes)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTimer)).BeginInit();
            this.SuspendLayout();
            // 
            // btnScanForDevices
            // 
            this.btnScanForDevices.Location = new System.Drawing.Point(279, 15);
            this.btnScanForDevices.Margin = new System.Windows.Forms.Padding(4);
            this.btnScanForDevices.Name = "btnScanForDevices";
            this.btnScanForDevices.Size = new System.Drawing.Size(100, 28);
            this.btnScanForDevices.TabIndex = 0;
            this.btnScanForDevices.Text = "Scan";
            this.btnScanForDevices.UseVisualStyleBackColor = true;
            this.btnScanForDevices.Click += new System.EventHandler(this.btnScanForDevices_Click);
            // 
            // listView1
            // 
            this.listView1.Alignment = System.Windows.Forms.ListViewAlignment.Default;
            this.listView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.listView1.HideSelection = false;
            this.listView1.Location = new System.Drawing.Point(16, 50);
            this.listView1.Margin = new System.Windows.Forms.Padding(4);
            this.listView1.MultiSelect = false;
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(388, 584);
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.grpSendData);
            this.groupBox1.Controls.Add(this.grpSendFIle);
            this.groupBox1.Controls.Add(this.grpSendInterval);
            this.groupBox1.Controls.Add(this.richboxReceivedData);
            this.groupBox1.Controls.Add(this.lblName);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.lblID);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(429, 50);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(621, 548);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Bluetooth LE Device";
            // 
            // grpSendData
            // 
            this.grpSendData.Controls.Add(this.txtboxSend);
            this.grpSendData.Controls.Add(this.btnSend);
            this.grpSendData.Location = new System.Drawing.Point(23, 485);
            this.grpSendData.Name = "grpSendData";
            this.grpSendData.Size = new System.Drawing.Size(601, 56);
            this.grpSendData.TabIndex = 6;
            this.grpSendData.TabStop = false;
            this.grpSendData.Text = "Send Data";
            // 
            // txtboxSend
            // 
            this.txtboxSend.Location = new System.Drawing.Point(15, 28);
            this.txtboxSend.Margin = new System.Windows.Forms.Padding(4);
            this.txtboxSend.Name = "txtboxSend";
            this.txtboxSend.Size = new System.Drawing.Size(426, 22);
            this.txtboxSend.TabIndex = 4;
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(447, 25);
            this.btnSend.Margin = new System.Windows.Forms.Padding(4);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(140, 28);
            this.btnSend.TabIndex = 3;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            // 
            // grpSendFIle
            // 
            this.grpSendFIle.Controls.Add(this.nudLines);
            this.grpSendFIle.Controls.Add(this.txtFilePath);
            this.grpSendFIle.Controls.Add(this.button2);
            this.grpSendFIle.Controls.Add(this.button1);
            this.grpSendFIle.Controls.Add(this.label8);
            this.grpSendFIle.Controls.Add(this.lblLPS);
            this.grpSendFIle.Controls.Add(this.label9);
            this.grpSendFIle.Location = new System.Drawing.Point(25, 377);
            this.grpSendFIle.Name = "grpSendFIle";
            this.grpSendFIle.Size = new System.Drawing.Size(599, 99);
            this.grpSendFIle.TabIndex = 4;
            this.grpSendFIle.TabStop = false;
            this.grpSendFIle.Text = "Send File";
            // 
            // nudLines
            // 
            this.nudLines.Location = new System.Drawing.Point(103, 65);
            this.nudLines.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nudLines.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudLines.Name = "nudLines";
            this.nudLines.Size = new System.Drawing.Size(72, 22);
            this.nudLines.TabIndex = 12;
            this.nudLines.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // txtFilePath
            // 
            this.txtFilePath.Location = new System.Drawing.Point(20, 36);
            this.txtFilePath.Margin = new System.Windows.Forms.Padding(4);
            this.txtFilePath.Name = "txtFilePath";
            this.txtFilePath.Size = new System.Drawing.Size(377, 22);
            this.txtFilePath.TabIndex = 5;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(406, 36);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(33, 28);
            this.button2.TabIndex = 3;
            this.button2.Text = "...";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.btnBrowseFile_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(447, 36);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(140, 28);
            this.button1.TabIndex = 4;
            this.button1.Text = "Send";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.btnSendFile_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(18, 67);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(42, 17);
            this.label8.TabIndex = 9;
            this.label8.Text = "Lines";
            this.label8.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(217, 70);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(42, 17);
            this.label9.TabIndex = 0;
            this.label9.Text = "Lines";
            // 
            // grpSendInterval
            // 
            this.grpSendInterval.Controls.Add(this.nudTimes);
            this.grpSendInterval.Controls.Add(this.nudBytes);
            this.grpSendInterval.Controls.Add(this.nudTimer);
            this.grpSendInterval.Controls.Add(this.chkInterval);
            this.grpSendInterval.Controls.Add(this.lblTotal);
            this.grpSendInterval.Controls.Add(this.lblSpeed);
            this.grpSendInterval.Controls.Add(this.lblSendText);
            this.grpSendInterval.Controls.Add(this.label7);
            this.grpSendInterval.Controls.Add(this.label6);
            this.grpSendInterval.Controls.Add(this.lblDuring);
            this.grpSendInterval.Controls.Add(this.label3);
            this.grpSendInterval.Controls.Add(this.label5);
            this.grpSendInterval.Controls.Add(this.lblLines);
            this.grpSendInterval.Location = new System.Drawing.Point(23, 246);
            this.grpSendInterval.Name = "grpSendInterval";
            this.grpSendInterval.Size = new System.Drawing.Size(591, 125);
            this.grpSendInterval.TabIndex = 5;
            this.grpSendInterval.TabStop = false;
            this.grpSendInterval.Text = "Interval Send";
            // 
            // nudTimes
            // 
            this.nudTimes.Location = new System.Drawing.Point(105, 92);
            this.nudTimes.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.nudTimes.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nudTimes.Name = "nudTimes";
            this.nudTimes.Size = new System.Drawing.Size(72, 22);
            this.nudTimes.TabIndex = 12;
            this.nudTimes.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // nudBytes
            // 
            this.nudBytes.Location = new System.Drawing.Point(105, 60);
            this.nudBytes.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nudBytes.Minimum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.nudBytes.Name = "nudBytes";
            this.nudBytes.Size = new System.Drawing.Size(72, 22);
            this.nudBytes.TabIndex = 13;
            this.nudBytes.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
            // 
            // nudTimer
            // 
            this.nudTimer.Location = new System.Drawing.Point(105, 28);
            this.nudTimer.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.nudTimer.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudTimer.Name = "nudTimer";
            this.nudTimer.Size = new System.Drawing.Size(82, 22);
            this.nudTimer.TabIndex = 14;
            this.nudTimer.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // chkInterval
            // 
            this.chkInterval.AutoSize = true;
            this.chkInterval.Location = new System.Drawing.Point(23, 29);
            this.chkInterval.Name = "chkInterval";
            this.chkInterval.Size = new System.Drawing.Size(76, 21);
            this.chkInterval.TabIndex = 11;
            this.chkInterval.Text = "Interval";
            this.chkInterval.UseVisualStyleBackColor = true;
            this.chkInterval.CheckedChanged += new System.EventHandler(this.chkInterval_CheckedChanged);
            // 
            // lblTotal
            // 
            this.lblTotal.AutoSize = true;
            this.lblTotal.Location = new System.Drawing.Point(416, 33);
            this.lblTotal.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTotal.Name = "lblTotal";
            this.lblTotal.Size = new System.Drawing.Size(91, 17);
            this.lblTotal.TabIndex = 5;
            this.lblTotal.Text = "Total: 0Bytes";
            this.lblTotal.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblSpeed
            // 
            this.lblSpeed.AutoSize = true;
            this.lblSpeed.Location = new System.Drawing.Point(416, 69);
            this.lblSpeed.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSpeed.Name = "lblSpeed";
            this.lblSpeed.Size = new System.Drawing.Size(53, 17);
            this.lblSpeed.TabIndex = 6;
            this.lblSpeed.Text = "Speed:";
            this.lblSpeed.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblSendText
            // 
            this.lblSendText.Location = new System.Drawing.Point(324, 94);
            this.lblSendText.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSendText.Name = "lblSendText";
            this.lblSendText.Size = new System.Drawing.Size(255, 17);
            this.lblSendText.TabIndex = 0;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(237, 94);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(79, 17);
            this.label7.TabIndex = 0;
            this.label7.Text = "Send Data:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(-64, 80);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(46, 17);
            this.label6.TabIndex = 7;
            this.label6.Text = "Times";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblDuring
            // 
            this.lblDuring.AutoSize = true;
            this.lblDuring.Location = new System.Drawing.Point(237, 65);
            this.lblDuring.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblDuring.Name = "lblDuring";
            this.lblDuring.Size = new System.Drawing.Size(89, 17);
            this.lblDuring.TabIndex = 8;
            this.lblDuring.Text = "During Time:";
            this.lblDuring.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(20, 94);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 17);
            this.label3.TabIndex = 9;
            this.label3.Text = "Times";
            this.label3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(18, 62);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(80, 17);
            this.label5.TabIndex = 9;
            this.label5.Text = "Send Bytes";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblLines
            // 
            this.lblLines.AutoSize = true;
            this.lblLines.Location = new System.Drawing.Point(237, 33);
            this.lblLines.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblLines.Name = "lblLines";
            this.lblLines.Size = new System.Drawing.Size(61, 17);
            this.lblLines.TabIndex = 10;
            this.lblLines.Text = "Count: 0";
            this.lblLines.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // richboxReceivedData
            // 
            this.richboxReceivedData.Location = new System.Drawing.Point(28, 108);
            this.richboxReceivedData.Margin = new System.Windows.Forms.Padding(4);
            this.richboxReceivedData.Name = "richboxReceivedData";
            this.richboxReceivedData.Size = new System.Drawing.Size(583, 131);
            this.richboxReceivedData.TabIndex = 1;
            this.richboxReceivedData.Text = "";
            // 
            // lblName
            // 
            this.lblName.Location = new System.Drawing.Point(389, 32);
            this.lblName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(192, 16);
            this.lblName.TabIndex = 0;
            this.lblName.Text = "ID:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(24, 77);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(101, 17);
            this.label4.TabIndex = 0;
            this.label4.Text = "Received Data";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(317, 32);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "Name:";
            // 
            // lblID
            // 
            this.lblID.Location = new System.Drawing.Point(97, 33);
            this.lblID.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblID.Name = "lblID";
            this.lblID.Size = new System.Drawing.Size(173, 16);
            this.lblID.TabIndex = 0;
            this.lblID.Text = "ID:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 31);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "ID:";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(950, 606);
            this.btnConnect.Margin = new System.Windows.Forms.Padding(4);
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(100, 28);
            this.btnConnect.TabIndex = 0;
            this.btnConnect.Text = "Connect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_ClickAsync);
            // 
            // timer
            // 
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // lblLPS
            // 
            this.lblLPS.AutoSize = true;
            this.lblLPS.Location = new System.Drawing.Point(403, 70);
            this.lblLPS.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblLPS.Name = "lblLPS";
            this.lblLPS.Size = new System.Drawing.Size(34, 17);
            this.lblLPS.TabIndex = 0;
            this.lblLPS.Text = "LPS";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1067, 652);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnScanForDevices);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.grpSendData.ResumeLayout(false);
            this.grpSendData.PerformLayout();
            this.grpSendFIle.ResumeLayout(false);
            this.grpSendFIle.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudLines)).EndInit();
            this.grpSendInterval.ResumeLayout(false);
            this.grpSendInterval.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudTimes)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudBytes)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudTimer)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnScanForDevices;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblID;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.RichTextBox richboxReceivedData;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.GroupBox grpSendData;
        private System.Windows.Forms.TextBox txtboxSend;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.GroupBox grpSendFIle;
        private System.Windows.Forms.TextBox txtFilePath;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox grpSendInterval;
        private System.Windows.Forms.NumericUpDown nudTimes;
        private System.Windows.Forms.NumericUpDown nudBytes;
        private System.Windows.Forms.NumericUpDown nudTimer;
        private System.Windows.Forms.CheckBox chkInterval;
        private System.Windows.Forms.Label lblTotal;
        private System.Windows.Forms.Label lblSpeed;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label lblDuring;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label lblLines;
        private System.Windows.Forms.Label lblSendText;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown nudLines;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label lblLPS;
    }
}

