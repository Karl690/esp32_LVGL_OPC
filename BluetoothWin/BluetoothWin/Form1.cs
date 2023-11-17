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
        
        public Form1()
        {
            InitializeComponent();
        
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            bleCommTool1.Dispose();
        }
    }

}
