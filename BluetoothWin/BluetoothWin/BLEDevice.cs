using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Devices.Enumeration;
using Windows.Storage.Streams;

namespace BluetoothWin
{

    public delegate void BleDeviceEvent(object sender, EventArgs e);
    public delegate void BleDeviceDataEvent(object sender, GattCharacteristic characteristic, GattValueChangedEventArgs args);
    public class BLEDevice
    {
        public DeviceInformation dev { get; set; }
        public BluetoothLEDevice ble_dev { get; set; }
        public bool isConnected { get; set; }
        private GattCharacteristic gattReadCharacteristic;
        private GattCharacteristic gattWriteCharacteristic;

        public string ID { get { return dev.Id; } }
        public string Name { get { return dev.Name; } }


        public event BleDeviceEvent OnDeviceConnectStatus;
        public event BleDeviceDataEvent OnReceivedData;

        public BLEDevice(DeviceInformation dev)
        {
            this.dev = dev;
        }
        public async Task Connect()
        {
            ble_dev = await BluetoothLEDevice.FromIdAsync(dev.Id);
            GattDeviceServicesResult result = await ble_dev.GetGattServicesAsync();
            isConnected = false;
            if (result.Status != GattCommunicationStatus.Success) return;
            ble_dev.ConnectionStatusChanged += Ble_dev_ConnectionStatusChanged;

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
            isConnected = true;
        }

        private void Ble_dev_ConnectionStatusChanged(BluetoothLEDevice sender, object args)
        {
            if (sender.ConnectionStatus == BluetoothConnectionStatus.Disconnected) isConnected = false;
            else isConnected = true;
            if (OnDeviceConnectStatus != null) OnDeviceConnectStatus(this, EventArgs.Empty);
        }

        public void Disconnet()
        {
            ble_dev.Dispose();
            ble_dev = null;
            isConnected = false;
        }
        private void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args)
        {
            if (OnReceivedData != null) OnReceivedData(this, sender, args);

        }
        public async Task SendDataAsync(string data)
        {
            if (!isConnected || gattWriteCharacteristic == null) return;
            DataWriter writer = new DataWriter();
            writer.WriteBytes(Encoding.ASCII.GetBytes(data));
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
            //writer.Dispose();  
            buffer = null;
        }
    }
}
