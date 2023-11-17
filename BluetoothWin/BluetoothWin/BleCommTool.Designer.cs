
namespace BluetoothWin
{
    partial class BleCommTool
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
            this.components = new System.ComponentModel.Container();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.bLEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.aPPLYToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.NUDHeadIndex = new System.Windows.Forms.NumericUpDown();
            this.lblName = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.CB_CanComTest = new System.Windows.Forms.CheckBox();
            this.CBAddbackslashN = new System.Windows.Forms.CheckBox();
            this.CBAddbackslashR = new System.Windows.Forms.CheckBox();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.CBAddChecksum = new System.Windows.Forms.CheckBox();
            this.labelAcknowledesSentSinceHardReset = new System.Windows.Forms.Label();
            this.labelAcknowledesReceviedSinceHardReset = new System.Windows.Forms.Label();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.LabelAckCounter = new System.Windows.Forms.Label();
            this.checkBox3 = new System.Windows.Forms.CheckBox();
            this.CBShowHex = new System.Windows.Forms.CheckBox();
            this.CBShowRecieveCharacters = new System.Windows.Forms.CheckBox();
            this.CBShowTransmitCharacters = new System.Windows.Forms.CheckBox();
            this.checkBox4 = new System.Windows.Forms.CheckBox();
            this.checkBox5 = new System.Windows.Forms.CheckBox();
            this.checkBox6 = new System.Windows.Forms.CheckBox();
            this.checkBox7 = new System.Windows.Forms.CheckBox();
            this.checkBox8 = new System.Windows.Forms.CheckBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.checkBox10 = new System.Windows.Forms.CheckBox();
            this.checkBox11 = new System.Windows.Forms.CheckBox();
            this.labelReceiveIndicator = new System.Windows.Forms.Label();
            this.labelTransmitIndicator = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lblAddress = new System.Windows.Forms.Label();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.logbox = new BluetoothWin.LogBox();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NUDHeadIndex)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bLEToolStripMenuItem,
            this.toolStripMenuItem1,
            this.aPPLYToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(9, 3, 0, 3);
            this.menuStrip1.Size = new System.Drawing.Size(624, 72);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // bLEToolStripMenuItem
            // 
            this.bLEToolStripMenuItem.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bLEToolStripMenuItem.Image = global::BluetoothWin.Properties.Resources.ble;
            this.bLEToolStripMenuItem.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.bLEToolStripMenuItem.Name = "bLEToolStripMenuItem";
            this.bLEToolStripMenuItem.Size = new System.Drawing.Size(58, 66);
            this.bLEToolStripMenuItem.Text = "BLE";
            this.bLEToolStripMenuItem.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.bLEToolStripMenuItem.MouseDown += new System.Windows.Forms.MouseEventHandler(this.bLEToolStripMenuItem_MouseDown);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.toolStripMenuItem1.Image = global::BluetoothWin.Properties.Resources.save_32x32;
            this.toolStripMenuItem1.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(84, 66);
            this.toolStripMenuItem1.Text = "APPLY";
            this.toolStripMenuItem1.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
            // 
            // aPPLYToolStripMenuItem
            // 
            this.aPPLYToolStripMenuItem.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.aPPLYToolStripMenuItem.Image = global::BluetoothWin.Properties.Resources.ping_32x32;
            this.aPPLYToolStripMenuItem.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
            this.aPPLYToolStripMenuItem.Name = "aPPLYToolStripMenuItem";
            this.aPPLYToolStripMenuItem.Size = new System.Drawing.Size(73, 66);
            this.aPPLYToolStripMenuItem.Text = "PING";
            this.aPPLYToolStripMenuItem.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageAboveText;
            this.aPPLYToolStripMenuItem.Click += new System.EventHandler(this.aPPLYToolStripMenuItem_Click);
            // 
            // NUDHeadIndex
            // 
            this.NUDHeadIndex.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NUDHeadIndex.Location = new System.Drawing.Point(117, 88);
            this.NUDHeadIndex.Maximum = new decimal(new int[] {
            99,
            0,
            0,
            0});
            this.NUDHeadIndex.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.NUDHeadIndex.Name = "NUDHeadIndex";
            this.NUDHeadIndex.Size = new System.Drawing.Size(98, 29);
            this.NUDHeadIndex.TabIndex = 570;
            this.NUDHeadIndex.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // lblName
            // 
            this.lblName.AutoSize = true;
            this.lblName.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblName.ForeColor = System.Drawing.Color.Aqua;
            this.lblName.Location = new System.Drawing.Point(120, 127);
            this.lblName.Name = "lblName";
            this.lblName.Size = new System.Drawing.Size(54, 24);
            this.lblName.TabIndex = 567;
            this.lblName.Text = "xxxx";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.Aqua;
            this.label2.Location = new System.Drawing.Point(24, 127);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 24);
            this.label2.TabIndex = 568;
            this.label2.Text = "Name:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Aqua;
            this.label1.Location = new System.Drawing.Point(24, 87);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 24);
            this.label1.TabIndex = 569;
            this.label1.Text = "Head:";
            // 
            // CB_CanComTest
            // 
            this.CB_CanComTest.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CB_CanComTest.Appearance = System.Windows.Forms.Appearance.Button;
            this.CB_CanComTest.AutoSize = true;
            this.CB_CanComTest.BackColor = System.Drawing.Color.DimGray;
            this.CB_CanComTest.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CB_CanComTest.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CB_CanComTest.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CB_CanComTest.Location = new System.Drawing.Point(335, 582);
            this.CB_CanComTest.Name = "CB_CanComTest";
            this.CB_CanComTest.Size = new System.Drawing.Size(109, 30);
            this.CB_CanComTest.TabIndex = 616;
            this.CB_CanComTest.Text = "CAN_TEST";
            this.CB_CanComTest.UseVisualStyleBackColor = false;
            // 
            // CBAddbackslashN
            // 
            this.CBAddbackslashN.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CBAddbackslashN.Appearance = System.Windows.Forms.Appearance.Button;
            this.CBAddbackslashN.AutoSize = true;
            this.CBAddbackslashN.BackColor = System.Drawing.Color.DimGray;
            this.CBAddbackslashN.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CBAddbackslashN.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CBAddbackslashN.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CBAddbackslashN.Location = new System.Drawing.Point(300, 582);
            this.CBAddbackslashN.Name = "CBAddbackslashN";
            this.CBAddbackslashN.Size = new System.Drawing.Size(34, 30);
            this.CBAddbackslashN.TabIndex = 615;
            this.CBAddbackslashN.Text = "\\n";
            this.CBAddbackslashN.UseVisualStyleBackColor = false;
            // 
            // CBAddbackslashR
            // 
            this.CBAddbackslashR.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CBAddbackslashR.Appearance = System.Windows.Forms.Appearance.Button;
            this.CBAddbackslashR.AutoSize = true;
            this.CBAddbackslashR.BackColor = System.Drawing.Color.DimGray;
            this.CBAddbackslashR.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CBAddbackslashR.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CBAddbackslashR.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CBAddbackslashR.Location = new System.Drawing.Point(267, 582);
            this.CBAddbackslashR.Name = "CBAddbackslashR";
            this.CBAddbackslashR.Size = new System.Drawing.Size(30, 30);
            this.CBAddbackslashR.TabIndex = 614;
            this.CBAddbackslashR.Text = "\\r";
            this.CBAddbackslashR.UseVisualStyleBackColor = false;
            // 
            // button4
            // 
            this.button4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button4.BackColor = System.Drawing.Color.Yellow;
            this.button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button4.ForeColor = System.Drawing.Color.Black;
            this.button4.Location = new System.Drawing.Point(498, 619);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(119, 32);
            this.button4.TabIndex = 613;
            this.button4.Text = "History";
            this.button4.UseVisualStyleBackColor = false;
            // 
            // button5
            // 
            this.button5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button5.BackColor = System.Drawing.Color.Yellow;
            this.button5.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button5.ForeColor = System.Drawing.Color.Black;
            this.button5.Location = new System.Drawing.Point(498, 582);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(119, 31);
            this.button5.TabIndex = 612;
            this.button5.Text = "SYNC";
            this.button5.UseVisualStyleBackColor = false;
            // 
            // checkBox1
            // 
            this.checkBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox1.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBox1.AutoSize = true;
            this.checkBox1.BackColor = System.Drawing.Color.DimGray;
            this.checkBox1.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.checkBox1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.checkBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox1.Location = new System.Drawing.Point(6, 654);
            this.checkBox1.MaximumSize = new System.Drawing.Size(55, 30);
            this.checkBox1.MinimumSize = new System.Drawing.Size(55, 30);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(55, 30);
            this.checkBox1.TabIndex = 611;
            this.checkBox1.Text = "Log";
            this.checkBox1.UseVisualStyleBackColor = false;
            // 
            // CBAddChecksum
            // 
            this.CBAddChecksum.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CBAddChecksum.Appearance = System.Windows.Forms.Appearance.Button;
            this.CBAddChecksum.AutoSize = true;
            this.CBAddChecksum.BackColor = System.Drawing.Color.DimGray;
            this.CBAddChecksum.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CBAddChecksum.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CBAddChecksum.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CBAddChecksum.Location = new System.Drawing.Point(6, 618);
            this.CBAddChecksum.MaximumSize = new System.Drawing.Size(55, 30);
            this.CBAddChecksum.MinimumSize = new System.Drawing.Size(55, 30);
            this.CBAddChecksum.Name = "CBAddChecksum";
            this.CBAddChecksum.Size = new System.Drawing.Size(55, 30);
            this.CBAddChecksum.TabIndex = 610;
            this.CBAddChecksum.Text = "Sum";
            this.CBAddChecksum.UseVisualStyleBackColor = false;
            // 
            // labelAcknowledesSentSinceHardReset
            // 
            this.labelAcknowledesSentSinceHardReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelAcknowledesSentSinceHardReset.AutoSize = true;
            this.labelAcknowledesSentSinceHardReset.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelAcknowledesSentSinceHardReset.ForeColor = System.Drawing.Color.Aqua;
            this.labelAcknowledesSentSinceHardReset.Location = new System.Drawing.Point(66, 611);
            this.labelAcknowledesSentSinceHardReset.Name = "labelAcknowledesSentSinceHardReset";
            this.labelAcknowledesSentSinceHardReset.Size = new System.Drawing.Size(21, 24);
            this.labelAcknowledesSentSinceHardReset.TabIndex = 609;
            this.labelAcknowledesSentSinceHardReset.Text = "0";
            // 
            // labelAcknowledesReceviedSinceHardReset
            // 
            this.labelAcknowledesReceviedSinceHardReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelAcknowledesReceviedSinceHardReset.AutoSize = true;
            this.labelAcknowledesReceviedSinceHardReset.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelAcknowledesReceviedSinceHardReset.ForeColor = System.Drawing.Color.Aqua;
            this.labelAcknowledesReceviedSinceHardReset.Location = new System.Drawing.Point(142, 613);
            this.labelAcknowledesReceviedSinceHardReset.Name = "labelAcknowledesReceviedSinceHardReset";
            this.labelAcknowledesReceviedSinceHardReset.Size = new System.Drawing.Size(21, 24);
            this.labelAcknowledesReceviedSinceHardReset.TabIndex = 608;
            this.labelAcknowledesReceviedSinceHardReset.Text = "0";
            // 
            // checkBox2
            // 
            this.checkBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox2.AutoSize = true;
            this.checkBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox2.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox2.Location = new System.Drawing.Point(267, 618);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(222, 24);
            this.checkBox2.TabIndex = 607;
            this.checkBox2.Text = "0x0200 Save CrashData";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // LabelAckCounter
            // 
            this.LabelAckCounter.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.LabelAckCounter.AutoSize = true;
            this.LabelAckCounter.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelAckCounter.ForeColor = System.Drawing.Color.Aqua;
            this.LabelAckCounter.Location = new System.Drawing.Point(93, 586);
            this.LabelAckCounter.Name = "LabelAckCounter";
            this.LabelAckCounter.Size = new System.Drawing.Size(21, 24);
            this.LabelAckCounter.TabIndex = 606;
            this.LabelAckCounter.Text = "0";
            // 
            // checkBox3
            // 
            this.checkBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox3.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBox3.AutoSize = true;
            this.checkBox3.BackColor = System.Drawing.Color.DimGray;
            this.checkBox3.Checked = true;
            this.checkBox3.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox3.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.checkBox3.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.checkBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox3.Location = new System.Drawing.Point(6, 690);
            this.checkBox3.MaximumSize = new System.Drawing.Size(55, 30);
            this.checkBox3.MinimumSize = new System.Drawing.Size(55, 30);
            this.checkBox3.Name = "checkBox3";
            this.checkBox3.Size = new System.Drawing.Size(55, 30);
            this.checkBox3.TabIndex = 605;
            this.checkBox3.Text = "Strip";
            this.checkBox3.UseVisualStyleBackColor = false;
            // 
            // CBShowHex
            // 
            this.CBShowHex.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CBShowHex.Appearance = System.Windows.Forms.Appearance.Button;
            this.CBShowHex.AutoSize = true;
            this.CBShowHex.BackColor = System.Drawing.Color.DimGray;
            this.CBShowHex.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CBShowHex.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CBShowHex.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CBShowHex.Location = new System.Drawing.Point(206, 582);
            this.CBShowHex.Name = "CBShowHex";
            this.CBShowHex.Size = new System.Drawing.Size(56, 30);
            this.CBShowHex.TabIndex = 604;
            this.CBShowHex.Text = "HEX";
            this.CBShowHex.UseVisualStyleBackColor = false;
            // 
            // CBShowRecieveCharacters
            // 
            this.CBShowRecieveCharacters.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CBShowRecieveCharacters.Appearance = System.Windows.Forms.Appearance.Button;
            this.CBShowRecieveCharacters.AutoSize = true;
            this.CBShowRecieveCharacters.BackColor = System.Drawing.Color.DimGray;
            this.CBShowRecieveCharacters.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CBShowRecieveCharacters.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CBShowRecieveCharacters.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CBShowRecieveCharacters.Location = new System.Drawing.Point(145, 582);
            this.CBShowRecieveCharacters.Name = "CBShowRecieveCharacters";
            this.CBShowRecieveCharacters.Size = new System.Drawing.Size(56, 30);
            this.CBShowRecieveCharacters.TabIndex = 603;
            this.CBShowRecieveCharacters.Text = "RCV";
            this.CBShowRecieveCharacters.UseVisualStyleBackColor = false;
            // 
            // CBShowTransmitCharacters
            // 
            this.CBShowTransmitCharacters.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.CBShowTransmitCharacters.Appearance = System.Windows.Forms.Appearance.Button;
            this.CBShowTransmitCharacters.AutoSize = true;
            this.CBShowTransmitCharacters.BackColor = System.Drawing.Color.DimGray;
            this.CBShowTransmitCharacters.FlatAppearance.CheckedBackColor = System.Drawing.Color.Lime;
            this.CBShowTransmitCharacters.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.CBShowTransmitCharacters.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CBShowTransmitCharacters.Location = new System.Drawing.Point(7, 582);
            this.CBShowTransmitCharacters.MaximumSize = new System.Drawing.Size(55, 30);
            this.CBShowTransmitCharacters.MinimumSize = new System.Drawing.Size(55, 30);
            this.CBShowTransmitCharacters.Name = "CBShowTransmitCharacters";
            this.CBShowTransmitCharacters.Size = new System.Drawing.Size(55, 30);
            this.CBShowTransmitCharacters.TabIndex = 602;
            this.CBShowTransmitCharacters.Text = "Xmit";
            this.CBShowTransmitCharacters.UseVisualStyleBackColor = false;
            // 
            // checkBox4
            // 
            this.checkBox4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox4.AutoSize = true;
            this.checkBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox4.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox4.Location = new System.Drawing.Point(80, 633);
            this.checkBox4.Name = "checkBox4";
            this.checkBox4.Size = new System.Drawing.Size(163, 24);
            this.checkBox4.TabIndex = 601;
            this.checkBox4.Text = "0x01 DX,Y Scale";
            this.checkBox4.UseVisualStyleBackColor = true;
            // 
            // checkBox5
            // 
            this.checkBox5.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox5.AutoSize = true;
            this.checkBox5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox5.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox5.Location = new System.Drawing.Point(80, 656);
            this.checkBox5.Name = "checkBox5";
            this.checkBox5.Size = new System.Drawing.Size(161, 24);
            this.checkBox5.TabIndex = 600;
            this.checkBox5.Text = "0x02 ---------------";
            this.checkBox5.UseVisualStyleBackColor = true;
            // 
            // checkBox6
            // 
            this.checkBox6.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox6.AutoSize = true;
            this.checkBox6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox6.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox6.Location = new System.Drawing.Point(80, 699);
            this.checkBox6.Name = "checkBox6";
            this.checkBox6.Size = new System.Drawing.Size(145, 24);
            this.checkBox6.TabIndex = 598;
            this.checkBox6.Text = "0x08 Steps/NL";
            this.checkBox6.UseVisualStyleBackColor = true;
            // 
            // checkBox7
            // 
            this.checkBox7.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox7.AutoSize = true;
            this.checkBox7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox7.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox7.Location = new System.Drawing.Point(80, 677);
            this.checkBox7.Name = "checkBox7";
            this.checkBox7.Size = new System.Drawing.Size(187, 24);
            this.checkBox7.TabIndex = 599;
            this.checkBox7.Text = "0x04 Adj_FeedRate";
            this.checkBox7.UseVisualStyleBackColor = true;
            // 
            // checkBox8
            // 
            this.checkBox8.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox8.AutoSize = true;
            this.checkBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox8.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox8.Location = new System.Drawing.Point(267, 678);
            this.checkBox8.Name = "checkBox8";
            this.checkBox8.Size = new System.Drawing.Size(108, 24);
            this.checkBox8.TabIndex = 597;
            this.checkBox8.Text = "0x40 Flow";
            this.checkBox8.UseVisualStyleBackColor = true;
            // 
            // checkBox9
            // 
            this.checkBox9.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox9.AutoSize = true;
            this.checkBox9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox9.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox9.Location = new System.Drawing.Point(267, 658);
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.Size = new System.Drawing.Size(159, 24);
            this.checkBox9.TabIndex = 596;
            this.checkBox9.Text = "0x20 F & E Prams";
            this.checkBox9.UseVisualStyleBackColor = true;
            // 
            // checkBox10
            // 
            this.checkBox10.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox10.AutoSize = true;
            this.checkBox10.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox10.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox10.Location = new System.Drawing.Point(267, 698);
            this.checkBox10.Name = "checkBox10";
            this.checkBox10.Size = new System.Drawing.Size(220, 24);
            this.checkBox10.TabIndex = 595;
            this.checkBox10.Text = "0x80 Extrusion>>Device";
            this.checkBox10.UseVisualStyleBackColor = true;
            // 
            // checkBox11
            // 
            this.checkBox11.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox11.AutoSize = true;
            this.checkBox11.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.checkBox11.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.checkBox11.Location = new System.Drawing.Point(267, 638);
            this.checkBox11.Name = "checkBox11";
            this.checkBox11.Size = new System.Drawing.Size(162, 24);
            this.checkBox11.TabIndex = 594;
            this.checkBox11.Text = "0x10 LookAhead";
            this.checkBox11.UseVisualStyleBackColor = true;
            // 
            // labelReceiveIndicator
            // 
            this.labelReceiveIndicator.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelReceiveIndicator.BackColor = System.Drawing.Color.Black;
            this.labelReceiveIndicator.Font = new System.Drawing.Font("Times New Roman", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelReceiveIndicator.ForeColor = System.Drawing.Color.DimGray;
            this.labelReceiveIndicator.Location = new System.Drawing.Point(107, 582);
            this.labelReceiveIndicator.Name = "labelReceiveIndicator";
            this.labelReceiveIndicator.Size = new System.Drawing.Size(32, 24);
            this.labelReceiveIndicator.TabIndex = 592;
            this.labelReceiveIndicator.Text = "▲";
            // 
            // labelTransmitIndicator
            // 
            this.labelTransmitIndicator.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelTransmitIndicator.BackColor = System.Drawing.Color.Black;
            this.labelTransmitIndicator.Font = new System.Drawing.Font("Times New Roman", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelTransmitIndicator.ForeColor = System.Drawing.Color.DimGray;
            this.labelTransmitIndicator.Location = new System.Drawing.Point(58, 582);
            this.labelTransmitIndicator.Name = "labelTransmitIndicator";
            this.labelTransmitIndicator.Size = new System.Drawing.Size(33, 24);
            this.labelTransmitIndicator.TabIndex = 593;
            this.labelTransmitIndicator.Text = "▼";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Aqua;
            this.label3.Location = new System.Drawing.Point(263, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(93, 24);
            this.label3.TabIndex = 568;
            this.label3.Text = "Address:";
            // 
            // lblAddress
            // 
            this.lblAddress.AutoSize = true;
            this.lblAddress.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblAddress.ForeColor = System.Drawing.Color.Aqua;
            this.lblAddress.Location = new System.Drawing.Point(359, 93);
            this.lblAddress.Name = "lblAddress";
            this.lblAddress.Size = new System.Drawing.Size(54, 24);
            this.lblAddress.TabIndex = 567;
            this.lblAddress.Text = "xxxx";
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Interval = 500;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // logbox
            // 
            this.logbox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.logbox.Location = new System.Drawing.Point(7, 160);
            this.logbox.Margin = new System.Windows.Forms.Padding(14, 21, 14, 21);
            this.logbox.MaxLinesToDisplay = 1000;
            this.logbox.Name = "logbox";
            this.logbox.Size = new System.Drawing.Size(610, 414);
            this.logbox.TabIndex = 617;
            // 
            // BleCommTool
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.Color.Black;
            this.Controls.Add(this.logbox);
            this.Controls.Add(this.CB_CanComTest);
            this.Controls.Add(this.CBAddbackslashN);
            this.Controls.Add(this.CBAddbackslashR);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.CBAddChecksum);
            this.Controls.Add(this.labelAcknowledesSentSinceHardReset);
            this.Controls.Add(this.labelAcknowledesReceviedSinceHardReset);
            this.Controls.Add(this.checkBox2);
            this.Controls.Add(this.LabelAckCounter);
            this.Controls.Add(this.checkBox3);
            this.Controls.Add(this.CBShowHex);
            this.Controls.Add(this.CBShowRecieveCharacters);
            this.Controls.Add(this.CBShowTransmitCharacters);
            this.Controls.Add(this.checkBox4);
            this.Controls.Add(this.checkBox5);
            this.Controls.Add(this.checkBox6);
            this.Controls.Add(this.checkBox7);
            this.Controls.Add(this.checkBox8);
            this.Controls.Add(this.checkBox9);
            this.Controls.Add(this.checkBox10);
            this.Controls.Add(this.checkBox11);
            this.Controls.Add(this.labelReceiveIndicator);
            this.Controls.Add(this.labelTransmitIndicator);
            this.Controls.Add(this.NUDHeadIndex);
            this.Controls.Add(this.lblAddress);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.lblName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "BleCommTool";
            this.Size = new System.Drawing.Size(624, 729);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.NUDHeadIndex)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem bLEToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem aPPLYToolStripMenuItem;
        private System.Windows.Forms.NumericUpDown NUDHeadIndex;
        private System.Windows.Forms.Label lblName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox CB_CanComTest;
        public System.Windows.Forms.CheckBox CBAddbackslashN;
        public System.Windows.Forms.CheckBox CBAddbackslashR;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        public System.Windows.Forms.CheckBox checkBox1;
        public System.Windows.Forms.CheckBox CBAddChecksum;
        public System.Windows.Forms.Label labelAcknowledesSentSinceHardReset;
        public System.Windows.Forms.Label labelAcknowledesReceviedSinceHardReset;
        private System.Windows.Forms.CheckBox checkBox2;
        private System.Windows.Forms.Label LabelAckCounter;
        public System.Windows.Forms.CheckBox checkBox3;
        private System.Windows.Forms.CheckBox CBShowHex;
        private System.Windows.Forms.CheckBox CBShowRecieveCharacters;
        private System.Windows.Forms.CheckBox CBShowTransmitCharacters;
        private System.Windows.Forms.CheckBox checkBox4;
        private System.Windows.Forms.CheckBox checkBox5;
        private System.Windows.Forms.CheckBox checkBox6;
        private System.Windows.Forms.CheckBox checkBox7;
        private System.Windows.Forms.CheckBox checkBox8;
        private System.Windows.Forms.CheckBox checkBox9;
        private System.Windows.Forms.CheckBox checkBox10;
        private System.Windows.Forms.CheckBox checkBox11;
        private System.Windows.Forms.Label labelReceiveIndicator;
        private System.Windows.Forms.Label labelTransmitIndicator;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label lblAddress;        
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private LogBox logbox;
        private System.Windows.Forms.Timer timer;
    }
}
