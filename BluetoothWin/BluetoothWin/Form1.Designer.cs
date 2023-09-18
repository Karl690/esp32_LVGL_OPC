
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
            this.nudTimes = new System.Windows.Forms.NumericUpDown();
            this.nudBytes = new System.Windows.Forms.NumericUpDown();
            this.nudTimer = new System.Windows.Forms.NumericUpDown();
            this.chkInterval = new System.Windows.Forms.CheckBox();
            this.txtboxSend = new System.Windows.Forms.TextBox();
            this.richboxReceivedData = new System.Windows.Forms.RichTextBox();
            this.btnSend = new System.Windows.Forms.Button();
            this.lblName = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lblTotal = new System.Windows.Forms.Label();
            this.lblSpeed = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lblDuring = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.lblCount = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lblID = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btnConnect = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.groupBox1.SuspendLayout();
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
            this.listView1.Size = new System.Drawing.Size(388, 484);
            this.listView1.TabIndex = 2;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.Details;
            this.listView1.SelectedIndexChanged += new System.EventHandler(this.listView1_SelectedIndexChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.nudTimes);
            this.groupBox1.Controls.Add(this.nudBytes);
            this.groupBox1.Controls.Add(this.nudTimer);
            this.groupBox1.Controls.Add(this.chkInterval);
            this.groupBox1.Controls.Add(this.txtboxSend);
            this.groupBox1.Controls.Add(this.richboxReceivedData);
            this.groupBox1.Controls.Add(this.btnSend);
            this.groupBox1.Controls.Add(this.lblName);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.lblTotal);
            this.groupBox1.Controls.Add(this.lblSpeed);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.lblDuring);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.lblCount);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.lblID);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(429, 50);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(621, 449);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Bluetooth LE Device";
            // 
            // nudTimes
            // 
            this.nudTimes.Location = new System.Drawing.Point(117, 358);
            this.nudTimes.Maximum = new decimal(new int[] {
            1000,
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
            this.nudTimes.TabIndex = 4;
            this.nudTimes.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // nudBytes
            // 
            this.nudBytes.Location = new System.Drawing.Point(117, 326);
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
            this.nudBytes.TabIndex = 4;
            this.nudBytes.Value = new decimal(new int[] {
            30,
            0,
            0,
            0});
            // 
            // nudTimer
            // 
            this.nudTimer.Location = new System.Drawing.Point(117, 294);
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
            this.nudTimer.TabIndex = 4;
            this.nudTimer.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // chkInterval
            // 
            this.chkInterval.AutoSize = true;
            this.chkInterval.Location = new System.Drawing.Point(35, 295);
            this.chkInterval.Name = "chkInterval";
            this.chkInterval.Size = new System.Drawing.Size(76, 21);
            this.chkInterval.TabIndex = 3;
            this.chkInterval.Text = "Interval";
            this.chkInterval.UseVisualStyleBackColor = true;
            this.chkInterval.CheckedChanged += new System.EventHandler(this.chkInterval_CheckedChanged);
            // 
            // txtboxSend
            // 
            this.txtboxSend.Location = new System.Drawing.Point(29, 418);
            this.txtboxSend.Margin = new System.Windows.Forms.Padding(4);
            this.txtboxSend.Name = "txtboxSend";
            this.txtboxSend.Size = new System.Drawing.Size(435, 22);
            this.txtboxSend.TabIndex = 2;
            // 
            // richboxReceivedData
            // 
            this.richboxReceivedData.Location = new System.Drawing.Point(29, 148);
            this.richboxReceivedData.Margin = new System.Windows.Forms.Padding(4);
            this.richboxReceivedData.Name = "richboxReceivedData";
            this.richboxReceivedData.Size = new System.Drawing.Size(583, 131);
            this.richboxReceivedData.TabIndex = 1;
            this.richboxReceivedData.Text = "";
            // 
            // btnSend
            // 
            this.btnSend.Location = new System.Drawing.Point(473, 415);
            this.btnSend.Margin = new System.Windows.Forms.Padding(4);
            this.btnSend.Name = "btnSend";
            this.btnSend.Size = new System.Drawing.Size(140, 28);
            this.btnSend.TabIndex = 0;
            this.btnSend.Text = "Send";
            this.btnSend.UseVisualStyleBackColor = true;
            this.btnSend.Click += new System.EventHandler(this.btnSend_Click);
            // 
            // lblName
            // 
            this.lblName.Location = new System.Drawing.Point(97, 81);
            this.lblName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(192, 16);
            this.lblName.TabIndex = 0;
            this.lblName.Text = "ID:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(25, 117);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(101, 17);
            this.label4.TabIndex = 0;
            this.label4.Text = "Received Data";
            // 
            // lblTotal
            // 
            this.lblTotal.AutoSize = true;
            this.lblTotal.Location = new System.Drawing.Point(428, 299);
            this.lblTotal.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblTotal.Name = "lblTotal";
            this.lblTotal.Size = new System.Drawing.Size(91, 17);
            this.lblTotal.TabIndex = 0;
            this.lblTotal.Text = "Total: 0Bytes";
            this.lblTotal.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblSpeed
            // 
            this.lblSpeed.AutoSize = true;
            this.lblSpeed.Location = new System.Drawing.Point(428, 335);
            this.lblSpeed.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSpeed.Name = "lblSpeed";
            this.lblSpeed.Size = new System.Drawing.Size(53, 17);
            this.lblSpeed.TabIndex = 0;
            this.lblSpeed.Text = "Speed:";
            this.lblSpeed.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(30, 360);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(46, 17);
            this.label6.TabIndex = 0;
            this.label6.Text = "Times";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblDuring
            // 
            this.lblDuring.AutoSize = true;
            this.lblDuring.Location = new System.Drawing.Point(249, 331);
            this.lblDuring.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblDuring.Name = "lblDuring";
            this.lblDuring.Size = new System.Drawing.Size(89, 17);
            this.lblDuring.TabIndex = 0;
            this.lblDuring.Text = "During Time:";
            this.lblDuring.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(30, 328);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(80, 17);
            this.label5.TabIndex = 0;
            this.label5.Text = "Send Bytes";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // lblCount
            // 
            this.lblCount.AutoSize = true;
            this.lblCount.Location = new System.Drawing.Point(249, 299);
            this.lblCount.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblCount.Name = "lblCount";
            this.lblCount.Size = new System.Drawing.Size(61, 17);
            this.lblCount.TabIndex = 0;
            this.lblCount.Text = "Count: 0";
            this.lblCount.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(26, 385);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(75, 17);
            this.label3.TabIndex = 0;
            this.label3.Text = "Send Data";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(25, 81);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "Name:";
            // 
            // lblID
            // 
            this.lblID.Location = new System.Drawing.Point(97, 48);
            this.lblID.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblID.Name = "lblID";
            this.lblID.Size = new System.Drawing.Size(173, 16);
            this.lblID.TabIndex = 0;
            this.lblID.Text = "ID:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(25, 48);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "ID:";
            // 
            // btnConnect
            // 
            this.btnConnect.Location = new System.Drawing.Point(943, 507);
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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1067, 554);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.btnConnect);
            this.Controls.Add(this.btnScanForDevices);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
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
        private System.Windows.Forms.TextBox txtboxSend;
        private System.Windows.Forms.RichTextBox richboxReceivedData;
        private System.Windows.Forms.Button btnSend;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown nudTimer;
        private System.Windows.Forms.CheckBox chkInterval;
        private System.Windows.Forms.Label lblTotal;
        private System.Windows.Forms.Label lblCount;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label lblSpeed;
        private System.Windows.Forms.Label lblDuring;
        private System.Windows.Forms.NumericUpDown nudBytes;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown nudTimes;
        private System.Windows.Forms.Label label6;
    }
}

