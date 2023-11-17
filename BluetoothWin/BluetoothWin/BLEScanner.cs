using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Threading;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.Advertisement;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;
using Windows.UI.Core;

namespace BluetoothWin
{
    public class BLEScanner : IDisposable
    {

        readonly BluetoothLEAdvertisementWatcher BleWatcher;
        
        public readonly ObservableCollection<BLEDevice> _devices = new ObservableCollection<BLEDevice>();
        public readonly ObservableCollection<BleDeviceInfo> _devicesWaitting = new ObservableCollection<BleDeviceInfo>();

        public delegate void BLEScannerEventHandler(object sender, BluetoothLEDeviceEventArgs e);
        public event BLEScannerEventHandler FoundDeviceEvent;
        public event BLEScannerEventHandler PairedDeviceEvent;
        public event BLEScannerEventHandler UnpairedDeviceEvent;
        public event BLEScannerEventHandler ReceivedDataDeviceEvent;
        public Dictionary<ulong, BLEDevice> deviceList = new Dictionary<ulong, BLEDevice>();

        public string[] AvaibleDeviceNames = new string[2] { "ESP32_S3_SC01", "TTYGO-ESP32S3" };
        public bool AvaibleChecking = true;
        public Thread Connectthread;
        public BLEScanner()
        {
            BleWatcher = new BluetoothLEAdvertisementWatcher()
            {
                ScanningMode = BluetoothLEScanningMode.Passive,
            };
            // Start the watcher.
            // BleWatcher.ScanningMode = BluetoothLEScanningMode.Passive;
            //BleWatcher.AllowExtendedAdvertisements = true;
            BleWatcher.Received += BleWatcher_Received;
            BleWatcher.Stopped += BleWatcher_Stopped;
            BleWatcher.Start();

            System.Timers.Timer aTimer = new System.Timers.Timer();
            // aTimer.Elapsed += new ElapsedEventHandler(OnTimedEvent);
            aTimer.Interval = 1000;
            //aTimer.Enabled = true;

            //Connectthread = new Thread(() => ThreadConnectDeviceAsync());
            //Connectthread.Start();
        }
        public void Dispose()
        {
            //Connectthread.Abort();
        }

        private void BleWatcher_Stopped(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementWatcherStoppedEventArgs args)
        {
            // StopeWatcherEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(null));
            Console.WriteLine("Ble watcher stopped");
            //BleWatcher.Start();
        }

        private void BleWatcher_Received(BluetoothLEAdvertisementWatcher sender, BluetoothLEAdvertisementReceivedEventArgs args)
        {
            //if (!AvaibleChecing) return;
            Console.WriteLine($"-----{args.Advertisement.LocalName}");
            if (Array.IndexOf(AvaibleDeviceNames, args.Advertisement.LocalName) == -1) return;
            
            if (args.AdvertisementType == BluetoothLEAdvertisementType.ConnectableUndirected)
            {
                if (_devicesWaitting.All(d => d.address != args.BluetoothAddress))
                {
                    _devicesWaitting.Add(new BleDeviceInfo(args.BluetoothAddress, DateTime.Now, args.Advertisement.LocalName));
                    _ = pair(args.BluetoothAddress);
                }
            }
        }
        private void BleDev_OnReceivedData(object sender, EventArgs e)
        {
            BLEDevice dev = (BLEDevice)sender;
            ReceivedDataDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(dev));
        }

        private void BleDev_OnDeviceConnectStatus(object sender, EventArgs e)
        {
            BLEDevice dev = (BLEDevice)sender;
            Console.WriteLine("Connection status : ", dev.Name, dev.ble_dev.ConnectionStatus.ToString());
            if(dev.ble_dev.ConnectionStatus == BluetoothConnectionStatus.Disconnected)
            {
                dev.OnReceivedData -= BleDev_OnReceivedData;
                _devices.Remove(dev);
                foreach(var d in _devicesWaitting)
                {
                    if(d.address == dev.Address)
                    {
                        _devicesWaitting.Remove(d);
                        return;
                    }
                }
                UnpairedDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(dev));
                dev.Dispose();
            }
        }

        private static void OnPairingRequested(DeviceInformationCustomPairing pairing, DevicePairingRequestedEventArgs args)
        {
            args.Accept("0");
        }
        public BLEDevice GetBLEDevice(ulong address)
        {
            foreach(var dev in _devices)
            {
                if (dev.Address == address) return dev;
            }
            return null;
        }
        public async Task pair(ulong address)
        {
            var device = await BluetoothLEDevice.FromBluetoothAddressAsync(address);
            if (device.ConnectionStatus == BluetoothConnectionStatus.Disconnected)
            {
                BLEDevice bleDev = new BLEDevice(device);

                Console.WriteLine($"Paring : {device.Name}");
                await bleDev.Connect();                
                if (bleDev.ble_dev.ConnectionStatus == BluetoothConnectionStatus.Connected)
                {
                    Console.WriteLine($"ADD: {device.Name}");
                    FoundDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(bleDev));
                    bleDev.OnDeviceConnectStatus += BleDev_OnDeviceConnectStatus;
                    bleDev.OnReceivedData += BleDev_OnReceivedData;

                    _devices.Add(bleDev);
                    PairedDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(bleDev));
                    await bleDev.SendDataAsync("B10\n"); // request get head index
                }
                else
                {
                    Console.WriteLine($"Can't connected: { device.Name}");
                    
                }
            }            
        }

        public async Task unpair(BluetoothLEDevice device)
        {
            if (device != null)
            {
                var result = await device.DeviceInformation.Pairing.UnpairAsync();
                if (result.Status == DeviceUnpairingResultStatus.Failed)
                {
                    Console.WriteLine("Device unpair falied");
                }
                if (result.Status == DeviceUnpairingResultStatus.Unpaired)
                {
                    Console.WriteLine("Device unpair successful");
                    UnpairedDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(new BLEDevice(device)));
                }
            }
        }

        
        // UNUSED ANYMORE BUT, I will keep this, it should be used in furture 
        async Task ThreadConnectDeviceAsync()
        {
            while(true)
            {
                var now = DateTime.Now;
                foreach (var d in _devicesWaitting)
                {
                    try
                    {
                        TimeSpan  t = now - d.at;
                        if (t.TotalMilliseconds < 1000) continue;
                        var device = await BluetoothLEDevice.FromBluetoothAddressAsync(d.address);
                        if (device.ConnectionStatus == BluetoothConnectionStatus.Disconnected)
                        {
                            BLEDevice bleDev = new BLEDevice(device);

                            Console.WriteLine($"Paring : {device.Name}");
                            await bleDev.Connect();
                            Console.WriteLine("sssssssssssssss");
                            if (bleDev.ble_dev.ConnectionStatus == BluetoothConnectionStatus.Connected)
                            {
                                Console.WriteLine($"ADD: {device.Name}");
                                FoundDeviceEvent?.Invoke(this, new BluetoothLEDeviceEventArgs(bleDev));
                                bleDev.OnDeviceConnectStatus += BleDev_OnDeviceConnectStatus;
                                bleDev.OnReceivedData += BleDev_OnReceivedData;
                                _devices.Add(bleDev);
                            }
                            else
                            {
                                Console.WriteLine($"Can't connected: { device.Name}");
                                _devicesWaitting.Remove(d);
                            }
                            break;
                        }
                    }
                    catch (Exception  )
                    {
                        Console.WriteLine("aaadsfdssssssssss");
                    }
                }
                if (BleWatcher.Status == BluetoothLEAdvertisementWatcherStatus.Stopped || BleWatcher.Status == BluetoothLEAdvertisementWatcherStatus.Aborted)
                {
                    //BleWatcher.Start();
                }
                Thread.Sleep(500);
            }
            
        }

        
        public bool StartScan()
        {
            _devices.Clear();
            try
            {
                BleWatcher.Start();
            }catch (Exception e)
            {
                Console.WriteLine(e.Message);
                return false;
            }
            return true;
            
        }
        public void StopScan()
        {
            BleWatcher.Stop();
        }
    }
    public class BluetoothLEDeviceEventArgs: EventArgs
    {
        public BLEDevice device { get; set;}
        public BluetoothLEDeviceEventArgs(BLEDevice dev) { this.device = dev; }
    }

    public class BleDeviceInfo
    {
        public ulong address;
        public DateTime at;
        public string name; 
        public BleDeviceInfo (ulong addres, DateTime at, string name)
        {
            this.address = addres;
            this.at = at;
            this.name = name;
        }
    }
}
