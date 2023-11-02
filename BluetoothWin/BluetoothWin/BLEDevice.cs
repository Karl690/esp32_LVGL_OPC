using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Security.Cryptography;
using Windows.Storage.Streams;

namespace BluetoothWin
{

    public delegate void BleDeviceEvent(object sender, EventArgs e);
    public delegate void BleDeviceDataEvent(object sender, EventArgs e); //; GattCharacteristic characteristic, GattValueChangedEventArgs args);

    public class BLEDevice
    {
        public BluetoothLEDevice ble_dev { get; set; }
        public bool isConnected; 
        private GattCharacteristic gattReadCharacteristic;
        private GattCharacteristic gattWriteCharacteristic;

        public string ID;
        public ulong Address;
        public string Name;


        public event BleDeviceEvent OnDeviceConnectStatus;
        public event BleDeviceDataEvent OnReceivedData;
        
        public byte[] RecievedBuffer = new byte[1024];
        public uint RecievedLength = 0;
        public DateTime liveTime;

        GattDeviceServicesResult result;
       
        public BLEDevice(BluetoothLEDevice dev)
        {
            this.ble_dev = dev;
            ID = dev.DeviceId;
            Name = dev.Name;
            Address = dev.BluetoothAddress;
            ble_dev.ConnectionStatusChanged += Ble_dev_ConnectionStatusChanged;            
        }
        public async Task Connect()
        {
            //ble_dev = await BluetoothLEDevice.FromIdAsync(dev.Id);
            result = await ble_dev.GetGattServicesAsync();
            
            if (result.Status != GattCommunicationStatus.Success)
            {
                this.isConnected = false;
                return;
            }
            this.isConnected = true;
            foreach (var service in result.Services)
            {   
                GattCharacteristicsResult charactiristicResult = await service.GetCharacteristicsAsync();
                
                if (charactiristicResult.Status == GattCommunicationStatus.Success)
                {
                    foreach (var characteristic in charactiristicResult.Characteristics)
                    {   
                        byte[] uuid = characteristic.Uuid.ToByteArray();
                        GattCharacteristicProperties properties = characteristic.CharacteristicProperties;
                        if (properties.HasFlag(GattCharacteristicProperties.WriteWithoutResponse))
                        {
                            if (uuid[0] == 0xF1 && uuid[1] == 0xAB) gattWriteCharacteristic = characteristic;
                        }
                        if (properties.HasFlag(GattCharacteristicProperties.Notify))
                        {
                            GattCommunicationStatus status = await characteristic.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue.Notify);
                            if (status == GattCommunicationStatus.Success && uuid[0] == 0xF2 && uuid[1] == 0xAB)
                            {
                                gattReadCharacteristic = characteristic;
                                characteristic.ValueChanged += Characteristic_ValueChanged;
                            }
                        }
                            
                    }
                }
            }
            
        }

        private void Ble_dev_ConnectionStatusChanged(BluetoothLEDevice sender, object args)
        {
            if(sender.ConnectionStatus == BluetoothConnectionStatus.Disconnected)
            {
                Console.WriteLine($"Disconnected {sender.Name}");
            }
            if (OnDeviceConnectStatus != null) OnDeviceConnectStatus(this, EventArgs.Empty);
            isConnected = sender.ConnectionStatus == BluetoothConnectionStatus.Connected ? true : false;
        }

        public async void Disconnet()
        {
            bool success = true;

            try
            {
                gattReadCharacteristic.ValueChanged -= Characteristic_ValueChanged;
                
                var servicesResult = await ble_dev.GetGattServicesAsync();
                if (servicesResult.Status == GattCommunicationStatus.Success)
                {
                    foreach (var service in servicesResult.Services)
                    {   
                        service.Dispose();
                    }
                }
                ble_dev.Dispose();
                ble_dev = null;
                //ble_dev = null;
                //GC.Collect();
                //GC.WaitForPendingFinalizers();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                success = false;
            }
        }

        private void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {   
            if (args.CharacteristicValue.Length == 0) return;
            CryptographicBuffer.CopyToByteArray(args.CharacteristicValue, out RecievedBuffer);
            RecievedLength = args.CharacteristicValue.Length;
            
            if (OnReceivedData != null) OnReceivedData(this, EventArgs.Empty);

        }
        public async Task SendDataBufferAsync(byte[] buf)
        {
            if (!isConnected || gattWriteCharacteristic == null) return;
            DataWriter writer = new DataWriter();
            writer.WriteBytes(buf);
            IBuffer buffer = writer.DetachBuffer();

            GattCommunicationStatus status = await gattWriteCharacteristic.WriteValueAsync(buffer, GattWriteOption.WriteWithoutResponse);
            if (status != GattCommunicationStatus.Success)
            {
                Console.WriteLine($"send error");
            }
            else
            {
                Console.WriteLine($"send success");
            }
            
            buffer = null;
        }
        public Task SendDataAsync(string data)
        {
            _ = SendDataBufferAsync(Encoding.ASCII.GetBytes(data));
            return Task.CompletedTask;
        }

    }
}
