using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BluetoothWin
{
    public partial class BleCommTool : UserControl, IDisposable
    {
        const int SHOWUP_STATUS_COUNT = 10;
        private BLEScanner scanner = new BLEScanner();
        private BLEDevice selectedDevice;
        int isReceiving = 0;
        int isSending = 0;
        public BleCommTool()
        {
            InitializeComponent();
            scanner.ReceivedDataDeviceEvent += Scanner_ReceivedDataDeviceEvent;
            scanner.PairedDeviceEvent += Scanner_PairedDeviceEvent;
            scanner.UnpairedDeviceEvent += Scanner_UnpairedDeviceEvent;
            UpdateDeviceDropDownMenu();
        }

        private void Scanner_UnpairedDeviceEvent(object sender, BluetoothLEDeviceEventArgs e)
        {
            BLEDevice dev = (BLEDevice)e.device;
            if (this.InvokeRequired)
            {
                this.Invoke((MethodInvoker)delegate ()
                {
                    RemoveDeviceDropDownMenu(dev);
                });
            }
            else
                RemoveDeviceDropDownMenu(dev);
        }

        private void Scanner_PairedDeviceEvent(object sender, BluetoothLEDeviceEventArgs e)
        {
            BLEDevice dev = (BLEDevice)e.device;
            if (this.InvokeRequired)
            {
                this.Invoke((MethodInvoker)delegate ()
                {
                    AddDeviceDropDownMenu(dev);
                });
            }
            else
                AddDeviceDropDownMenu(dev);
        }

        public void Dispose()
        {
            scanner.Dispose();
        }

        public void ProcessHyrelMessage(BLEDevice dev, string response)
        {
            if (response.StartsWith("RI:Soap:"))
            {
                //processIncomingSoapString(response);
                return;
            }
            if (response.Length > 3 && response[0] != '>')
            {
                Console.WriteLine("Invalid string");
                return;
            }
            response = response.Remove(0, 1); // remove '>'            
            string[] ResponeParameters = response.Split(':');
            if (ResponeParameters.Length < 2)
            {
                return;
            }
            if (ResponeParameters[1].Length < 2) return; // invalid value
                string value;
            switch (ResponeParameters[0])
            {
                case "RG":                    
                    value = ResponeParameters[1];
                    int.TryParse(value, out dev.HeadIndex);
                    dev.HeadIndex = dev.HeadIndex == 0 ? 99 : dev.HeadIndex;
                    break;
                case "RT":
                    break;
            }
        }

        private void Scanner_ReceivedDataDeviceEvent(object sender, BluetoothLEDeviceEventArgs e)
        {
            BLEDevice device = (BLEDevice)e.device;
            string data = Encoding.ASCII.GetString(device.ReceivedBuffer);

            ProcessHyrelMessage(device, data);
            // Console.WriteLine($"Received data: from { device.Name}[{device.HeadIndex}] => {data} ");
            if (selectedDevice != null && selectedDevice.Address == device.Address)
            {
                isReceiving = SHOWUP_STATUS_COUNT;
                if (this.InvokeRequired)
                {
                    this.Invoke((MethodInvoker)delegate ()
                    {
                        if (data.StartsWith(">RG:"))
                        {
                            NUDHeadIndex.Value = device.HeadIndex;
                            logbox.AddNotification($"The selected device's head index is Updated as {selectedDevice.HeadIndex}");
                        }
                        if(CBShowRecieveCharacters.Checked) logbox.AddData($"{data}", Color.White, CBShowHex.Checked);
                        labelAcknowledesReceviedSinceHardReset.Text = selectedDevice.totalReceivedBytes.ToString();
                    });                    
                }else
                {
                    if (data.StartsWith(">RG:"))
                    {
                        NUDHeadIndex.Value = device.HeadIndex;
                        logbox.AddNotification($"The selected device's head index is Updated as {selectedDevice.HeadIndex}");
                    }
                    if (CBShowRecieveCharacters.Checked) logbox.AddData($"{data}", Color.White, CBShowHex.Checked);
                    labelAcknowledesReceviedSinceHardReset.Text = selectedDevice.totalReceivedBytes.ToString();
                }
            }
        }
        public void AddDeviceDropDownMenu (BLEDevice dev)
        {
            ToolStripMenuItem tsmi;
            string name = $"{ dev.Name }";
            BLEDevice dropDev;
            foreach(ToolStripMenuItem item in bLEToolStripMenuItem.DropDownItems)
            {
                dropDev = (BLEDevice)item.Tag;
                if(dev.Address == dropDev.Address)
                {
                    return;
                }
            }
            tsmi = new ToolStripMenuItem(name, null, bleDeviceSelectionEventHandler);
            tsmi.Tag = dev;
            bLEToolStripMenuItem.DropDownItems.Add(tsmi);
        }

        public void RemoveDeviceDropDownMenu(BLEDevice dev)
        {
            ToolStripMenuItem tsmi;
            string name = $"{ dev.Name }";
            BLEDevice dropDev;
            foreach (ToolStripMenuItem item in bLEToolStripMenuItem.DropDownItems)
            {
                dropDev = (BLEDevice)item.Tag;
                if (dev.Address == dropDev.Address)
                {
                    bLEToolStripMenuItem.DropDownItems.Remove(item);
                    if (selectedDevice != null && selectedDevice.Address == dropDev.Address)
                    {
                        selectedDevice = null;
                        updateDeviceInfo();
                    }
                    return;
                }
            }
            
        }
        public void UpdateDeviceDropDownMenu()
        {
            ToolStripMenuItem tsmi;
            bLEToolStripMenuItem.DropDownItems.Clear();
            foreach (var dev in scanner._devices)
            {
                string name = $"{ dev.Name }";
                tsmi = new ToolStripMenuItem(name, null, bleDeviceSelectionEventHandler);
                tsmi.Tag = dev;
                bLEToolStripMenuItem.DropDownItems.Add(tsmi);
            }            
        }
        private void bLEToolStripMenuItem_MouseDown(object sender, MouseEventArgs e)
        {   
            if(bLEToolStripMenuItem.DropDownItems.Count == 0)
            {
                logbox.AddWarning("There is no paried Device.");
            }
        }

        public void bleDeviceSelectionEventHandler(Object sender, EventArgs e)
        {
            BLEDevice dev = (BLEDevice)((ToolStripMenuItem)sender).Tag;
            selectedDevice = dev;
            selectedDevice.SendDataAsync("B10\n");
            updateDeviceInfo();
        }
        public void updateDeviceInfo()
        {
            if(selectedDevice == null)
            {
                lblName.Text = "Unselected";
                lblAddress.Text = "";
                NUDHeadIndex.Value = 99;

                logbox.AddWarning("There is no selected Device.\n");
            }
            else
            {
                lblName.Text = selectedDevice.Name;
                lblAddress.Text = selectedDevice.Address.ToString();
                NUDHeadIndex.Value = selectedDevice.HeadIndex;

                logbox.AddNotification($"{selectedDevice.Name}[{selectedDevice.HeadIndex}] is selected.");
            }
        }
        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (selectedDevice == null) return;
            if (MessageBox.Show("Do you want to set the head index on this device?", "Question", MessageBoxButtons.YesNo) == DialogResult.No) return;
            string bcode = $"B11 T{NUDHeadIndex.Value}\n";
            //if (CBAddbackslashR.Checked) bcode += "\r";
            //if (CBAddbackslashN.Checked) bcode += "\n";
            
            _ = selectedDevice.SendDataBufferAsync(Encoding.ASCII.GetBytes(bcode));
            if(CBShowTransmitCharacters.Checked)
            {
                logbox.AddData($"{bcode}", Color.Red, CBShowHex.Checked);
            }

            labelAcknowledesSentSinceHardReset.Text = selectedDevice.totalSentBytes.ToString();
            isSending = SHOWUP_STATUS_COUNT;
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            if(isSending > 0)
            {
                labelTransmitIndicator.ForeColor = isSending % 2 == 0? Color.Cyan : Color.DarkGray;
                isSending--;
                if (isSending == 0) labelTransmitIndicator.ForeColor = Color.DarkGray;
            }
            if (isReceiving > 0)
            {
                labelReceiveIndicator.ForeColor = isReceiving % 2 == 0 ? Color.Cyan : Color.DarkGray;
                isReceiving--;
                if (isReceiving == 0) labelReceiveIndicator.ForeColor = Color.DarkGray;
            }
        }

        private void aPPLYToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (selectedDevice == null) return;
            if (CBShowTransmitCharacters.Checked) logbox.AddData($"PING 0x7\n", Color.Red, false);
            selectedDevice.SendBufferAsync(new byte[] { 0x7 });
        }
    }
}
