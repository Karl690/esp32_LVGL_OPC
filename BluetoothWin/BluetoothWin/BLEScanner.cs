using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;

namespace BluetoothWin
{
    public class BLEScanner
    {
    
        private BluetoothLEAdvertisementWatcher BleWatcher;

        public delegate void BLEScannerEventHandler(object sender, BluetoothLEDeviceEventArgs e);
        public event BLEScannerEventHandler AddedDeviceEvent;
        public event BLEScannerEventHandler RemovedDeviceEvent;
        public Dictionary<ulong, BLEDevice> deviceList = new Dictionary<ulong, BLEDevice>();

        public string[] AvaibleDeviceNames = new string[2] { "ESP32_S3_SC01", "TTYGO-ESP32S3" };
        public bool AvaibleChecking = true;
        private DeviceWatcher deviceWatcher;
        public BLEScanner()
        {
            // Start the watcher.
            BleWatcher = new BluetoothLEAdvertisementWatcher
            {
                ScanningMode = BluetoothLEScanningMode.Passive,
            };
            BleWatcher.AllowExtendedAdvertisements = true;
            BleWatcher.Received += BleWatcher_Received;
            

            System.Timers.Timer aTimer = new System.Timers.Timer();
            aTimer.Elapsed += new ElapsedEventHandler(OnTimedEvent);
            aTimer.Interval = 500;
            aTimer.Enabled = true;
            
        }

        public void ForceRestart()
        {
            if (BleWatcher != null && BleWatcher.Status == BluetoothLEAdvertisementWatcherStatus.Started)
            {
                BleWatcher.Received -= BleWatcher_Received;
                BleWatcher.Stop();
            }

            BleWatcher = null;
            GC.Collect();
            GC.WaitForPendingFinalizers();

            BleWatcher = new BluetoothLEAdvertisementWatcher
            {
                ScanningMode = BluetoothLEScanningMode.Passive,
            };
            BleWatcher.AllowExtendedAdvertisements = true;
            BleWatcher.Received += BleWatcher_Received;
            BleWatcher.Start();
        }

        private async void BleWatcher_Received(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementReceivedEventArgs args)
        {
            //if (!AvaibleChecing) return;
            if (Array.IndexOf(AvaibleDeviceNames, args.Advertisement.LocalName) == -1) return;
            Console.WriteLine($"-----{args.Advertisement.LocalName}");
            if (deviceList.ContainsKey(args.BluetoothAddress))
            {
                deviceList[args.BluetoothAddress].liveTime = DateTime.Now;
                return;
            }
            
            var device = await BluetoothLEDevice.FromBluetoothAddressAsync(args.BluetoothAddress);            
            if (device != null && device.ConnectionStatus == BluetoothConnectionStatus.Disconnected)
            {
                try
                {
                    BLEDevice dev = new BLEDevice(device);
                    dev.liveTime = DateTime.Now;
                    deviceList.Add(device.BluetoothAddress, dev);
                    Console.WriteLine($"ADD: {device.Name} {dev.liveTime}");
                    AddedDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(dev));
                }catch(Exception) { }
            }
        }
        private void OnTimedEvent(object source, ElapsedEventArgs e)
        {
            var now = DateTime.Now;
            if (BleWatcher.Status != BluetoothLEAdvertisementWatcherStatus.Started) return;
            foreach (var dev in deviceList)
            {
                if (dev.Value.isConnected) continue;
                TimeSpan ts = now - dev.Value.liveTime;
                if (ts.TotalSeconds > 2)
                {
                    // removed device
                    Console.WriteLine($"REMOVE: {dev.Value.Name} {dev.Value.liveTime} {ts.TotalSeconds}");
                    RemovedDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(dev.Value));
                    deviceList.Remove(dev.Key);
                }
            }
        }
        public void StartScan()
        {
            deviceList.Clear();
            BleWatcher.Start();
        }
        public void StopScan()
        {
            BleWatcher.Stop();
        }

        public void Unpair(BLEDevice dev)
        {
            dev.Disconnet();
            deviceList.Remove(dev.Address);

            ForceRestart();
        }
    }
    public class BluetoothLEDeviceEventArgs: EventArgs
    {
        public BLEDevice device { get; set;}
        public BluetoothLEDeviceEventArgs(BLEDevice dev) { this.device = dev; }
    }
}
