using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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
                bleDev.OnReceivedData += BleDev_OnReceivedData1;
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

        private void BleDev_OnReceivedData1(object sender, GattCharacteristic characteristic, GattValueChangedEventArgs args)
        {
            var reader = DataReader.FromBuffer(args.CharacteristicValue);
            uint len = args.CharacteristicValue.Length;
            string data = reader.ReadString(len);
            if (this.InvokeRequired)
            {
                this.Invoke((MethodInvoker)delegate ()
                {
                    richboxReceivedData.AppendText(data + "\n");
                });
            }
            else
            {
                richboxReceivedData.AppendText(data + "\n");
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
                await bleDev.Connect();
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
    }

}
