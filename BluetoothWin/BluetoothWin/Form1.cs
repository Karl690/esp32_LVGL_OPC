using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;

namespace BluetoothWin
{
    public partial class Form1 : Form
    {
        bool _isSearchingForDevices;
        BLEScanner bleScanner = new BLEScanner();
        byte[] SendIntervalBuffer;
        bool isSendFile = false;
        string[] SendFileDataLine = null;
        public bool IsSearchingForDevices
        {
            get => _isSearchingForDevices;
            set
            {
                _isSearchingForDevices = value;
                btnScanForDevices.Enabled = !_isSearchingForDevices;
            }
        }
        
        public Form1()
        {
            InitializeComponent();
            listView1.Columns.Add("DEVICE");
            listView1.Columns[0].Width = this.listView1.Width - 100;
            listView1.Columns.Add("STATUS");
            listView1.Columns[1].Width = 90;
            bleScanner.BleDeviceAddEvent += BleScanner_BleDeviceAddEvent;

            lblID.Text = "";
            lblName.Text = "";
            UpdateControlForBleDevice(false);
        }
        public void AddBlutoothLEDevice(DeviceInformation dev)
        {
            var value = new ListViewItem();
            BLEDevice bleDev = new BLEDevice(dev);
            bleDev.dev = dev;
            value.Tag = bleDev;
            value.Text = bleDev.Name;
            var item = FindItemByName(dev.Name);
            if(item == null)
            {
                value.SubItems.Add("Disconnect");
                listView1.Items.Add(value);
                bleDev.OnDeviceConnectStatus += BleDev_OnDeviceConnectStatus;
                bleDev.OnReceivedData += BleDev_OnReceivedData;
            }
        }

        
        public ListViewItem FindItemByName(string devName)
        {
            ListViewItem findItem = null;
            if(this.InvokeRequired)
            {
                this.Invoke((MethodInvoker)delegate ()
                  {
                      foreach (ListViewItem item in listView1.Items)
                      {
                          if (item.SubItems[0].Text == devName)
                          {
                              findItem = item;
                              break;
                          }
                      }
                  });
            }else
            {
                foreach (ListViewItem item in listView1.Items)
                {
                    if (item.SubItems[0].Text == devName)
                    {
                        findItem = item;
                        break;
                    }
                }
            }
            
            return findItem;
        }

        //private void BleDev_OnReceivedData(object sender, GattCharacteristic characteristic, GattValueChangedEventArgs args)
        private void BleDev_OnReceivedData(object sender, EventArgs args)
        {

            BLEDevice dev = (BLEDevice)sender;
            string str = Encoding.ASCII.GetString(dev.RecievedBuffer);
            if (this.InvokeRequired)
            {
                
                this.Invoke((MethodInvoker)delegate ()
                {
                    richboxReceivedData.AppendText(str + "\n");
                });
            }
            else
            {
                richboxReceivedData.AppendText(str + "\n");
            }
            
        }


        private void BleDev_OnDeviceConnectStatus(object sender, EventArgs e)
        {
            BLEDevice dev = (BLEDevice)sender;
            ListViewItem item = FindItemByName(dev.Name);
            if(item != null)
            {
                if (this.InvokeRequired)
                {
                    this.Invoke((MethodInvoker)delegate ()
                    {
                        item.SubItems[1].Text = dev.isConnected ? "Connected" : "Disconnected";
                    });
                }else
                {
                    item.SubItems[1].Text = dev.isConnected ? "Connected" : "Disconnected";
                }   
            }
        }

        private void BleScanner_BleDeviceAddEvent(object sender, BleDeviceScannerEvengArgs e)
        {
            if(this.InvokeRequired)
            {
                this.Invoke((MethodInvoker)delegate ()
                {
                    AddBlutoothLEDevice(e.device);
                });
            }else 
                AddBlutoothLEDevice(e.device);
        }

        private void btnScanForDevices_Click(object sender, EventArgs e)
        {   
            listView1.Items.Clear();
            if (btnScanForDevices.Text == "Scan")
            {
                bleScanner.StartScan();
                btnScanForDevices.Text = "Stop";
            }
            else
            {
                bleScanner.StopScan();
                btnScanForDevices.Text = "Scan";
            }
        }

        private void BluetoothDeviceItem_Click(object? sender, EventArgs e)
        {
            //var deviceItem = sender as BluetoothDeviceItem;
            //var device = deviceItem!.Device;
            //MessageBox.Show($"You clicked on device: {device!.DeviceName}");
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            bleScanner.StopScan();
            Application.Exit();
        }

        private async void btnConnect_ClickAsync(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0) return;
            ListViewItem SelectedItem = listView1.SelectedItems[0];
            BLEDevice bleDev = (BLEDevice)SelectedItem.Tag;
            if (bleDev.isConnected)
            {
                bleDev.Disconnet();
                SelectedItem.SubItems[1].Text = "Disconnected";
            }
            else
            {
                SelectedItem.SubItems[1].Text = "Connecting...";
                btnConnect.Text = "Connecting...";
                try
                {
                    await bleDev.Connect();
                }catch (Exception exception)
                {
                    bleDev.isConnected = false;
                    MessageBox.Show(exception.Message);
                }
                
                SelectedItem.SubItems[1].Text = bleDev.isConnected?"Connected":"Disconnected";
            }
            UpdateControlForBleDevice(bleDev.isConnected);
            
        }

        private void DisconnectDevice(BLEDevice bleDev)
        {
            bleDev.Disconnet();
        }
        
        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0)
            {
                UpdateControlForBleDevice(false);
                lblID.Text = "";
                lblName.Text = "";
                return;
            }
            ListViewItem item = listView1.SelectedItems[0];
            BLEDevice bledev = (BLEDevice)item.Tag;
            
            lblID.Text = bledev.ID;
            lblName.Text = bledev.Name;

            btnConnect.Text = bledev.isConnected ? "Disconnect" : "Connect";

            UpdateControlForBleDevice(bledev.isConnected);
        }

        private void UpdateControlForBleDevice(bool enable)
        {
            btnConnect.Text = enable ? "Disconnect" : "Connect";
            txtboxSend.Enabled = enable;
            richboxReceivedData.Enabled = enable;
            btnSend.Enabled = enable;
        }
        
        private void btnSend_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0) return;
            ListViewItem SelectedItem = listView1.SelectedItems[0];
            BLEDevice bleDev = (BLEDevice)SelectedItem.Tag;
            string data = txtboxSend.Text;
            bleDev.SendDataAsync(data);
        }
        private DateTime startTime;
        private int totalSendBytes = 0;
        private int timerCount = 0;
        private void chkInterval_CheckedChanged(object sender, EventArgs e)
        {
            txtboxSend.Enabled = !chkInterval.Checked;
            btnSend.Enabled = !chkInterval.Checked;
            if(chkInterval.Checked)
            {
                timer.Interval = (int)nudTimer.Value;
                timer.Enabled = true;
                startTime = DateTime.Now;
                totalSendBytes = 0;
                if(SendFileDataLine == null || SendFileDataLine.Length == 0)
                {
                    SendIntervalBuffer = new byte[(int)nudBytes.Value];
                    for (int i = 0; i < nudBytes.Value; i++) SendIntervalBuffer[i] = (byte)'A';
                }
                timerCount = 0;
                
            }
            else
            {
                timer.Enabled = false;
                if (SendFileDataLine != null && SendFileDataLine.Length > 0) SendFileDataLine = null;

                GC.Collect();
                GC.WaitForPendingFinalizers();
            }
            nudBytes.Enabled = !chkInterval.Checked;
            nudTimes.Enabled = !chkInterval.Checked;
            txtboxSend.Enabled = !chkInterval.Checked;

            grpSendData.Enabled = !chkInterval.Checked;
            grpSendFIle.Enabled = !chkInterval.Checked;
        }
        
        private void timer_Tick(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count == 0) return;
            ListViewItem SelectedItem = listView1.SelectedItems[0];
            BLEDevice bleDev = (BLEDevice)SelectedItem.Tag;
            if (!bleDev.AvailableWrite) return;
            string sz = "";
            DateTime nowTime = DateTime.Now;
            TimeSpan ts = DateTime.Now - startTime;

            if (SendFileDataLine != null && SendFileDataLine.Length > 0)
            {
                StringBuilder sb = new StringBuilder();
                for(int i = 0; i < nudLines.Value; i ++)
                {
                    if (timerCount >= nudTimes.Value) break;
                    sb.AppendLine($"{timerCount + 1}: " + SendFileDataLine[timerCount]);                    
                    timerCount++;
                }
                totalSendBytes += sb.Length;
                _ = bleDev.SendDataBufferAsync(Encoding.ASCII.GetBytes(sb.ToString()));
                lblLines.Text = $"Lines: {timerCount}";
                lblLPS.Text = $"LPS: {(timerCount / ts.TotalMilliseconds * 1000.0f).ToString("0.0")} LPS";
            }
            else
            {
                totalSendBytes += SendIntervalBuffer.Length;
                sz = $"{timerCount+1}: T{totalSendBytes},S{ts.TotalSeconds.ToString("0.0")}";
                byte[] bytes = Encoding.ASCII.GetBytes(sz);
                bytes.CopyTo(SendIntervalBuffer, 0);
                _ = bleDev.SendDataBufferAsync(SendIntervalBuffer);
            }
            
            
            
            txtboxSend.Text = sz;
            lblLines.Text = $"Count: {timerCount}";
            lblDuring.Text = $"During: {ts.TotalMilliseconds.ToString("0.00")}";
            lblTotal.Text = $"Total: {totalSendBytes}";
            lblSendText.Text = sz;
            if(ts.Milliseconds > 1)            lblSpeed.Text = $"Speed: {(totalSendBytes / ts.TotalMilliseconds * 1000.0f).ToString("0.00")} BPS";

BREAK:
            if(nudTimes.Value <= timerCount)
            {
                chkInterval.Checked = false;
                //txtboxSend.Enabled = !chkInterval.Checked;
                //btnSend.Enabled = !chkInterval.Checked;
                //timer.Enabled = false;

                //nudBytes.Enabled = !chkInterval.Checked;
                //nudTimes.Enabled = !chkInterval.Checked;
            }
            timerCount++;
        }



        private void btnBrowseFile_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "GCode files (*.gcode)|*.gcode|All files (*.*)|*.*";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                txtFilePath.Text = ofd.FileName;
            }
        }

        private void btnSendFile_Click(object sender, EventArgs e)
        {
            if (!File.Exists(txtFilePath.Text))
            {
                MessageBox.Show("The file does not exist."); return;
            }
            isSendFile = true;
            nudTimer.Value = 1;
            SendFileDataLine = File.ReadAllLines(txtFilePath.Text);
            nudTimes.Value = SendFileDataLine.Length;
            chkInterval.Checked = true;
            grpSendData.Enabled = false;
            grpSendFIle.Enabled = false;
            
        }
    }

}
