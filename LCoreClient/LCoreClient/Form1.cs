using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LCoreClient
{
    public partial class Form1 : Form
    {
        Socket clientSocket;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void btConnect_Click(object sender, EventArgs e)
        {
            if(btConnect.Text == "Connect")
            {
                string ip = cmbIPAddress.Text;
                if(ConnectClient(ip))
                {
                    cmbIPAddress.Items.Add(ip);
                    cmbIPAddress.SelectedItem = ip;
                    btConnect.Text = "Disconnect";
                }
            }else
            {
                DisconnectClient();
            }
        }

        void DisconnectClient()
        {
            if (clientSocket != null && clientSocket.Connected)
            {
                clientSocket.Shutdown(SocketShutdown.Both);
                clientSocket.Close();
            }
            btConnect.Text = "Connect";
        }

        bool ConnectClient(string ipaddress)
        {
            DisconnectClient();
            try
            {
            
                // Create a TCP/IP  socket.

                var endPoint = new IPEndPoint(IPAddress.Parse(ipaddress), 5000);
                clientSocket = new Socket(endPoint.AddressFamily,
                    SocketType.Stream, ProtocolType.Tcp);

                // Connect the socket to the remote endpoint. Catch any errors.
                try
                {
                    // Connect to Remote EndPoint
                    clientSocket.Connect(endPoint);

                    Console.WriteLine("Socket connected to {0}",
                        clientSocket.RemoteEndPoint.ToString());

                    Thread backgroundThread = new Thread(this.ReceiveThreadHandle);
                    backgroundThread.Start(clientSocket);
                    return true;

                }
                catch (ArgumentNullException ane)
                {
                    Console.WriteLine("ArgumentNullException : {0}", ane.ToString());
                }
                catch (SocketException se)
                {
                    Console.WriteLine("SocketException : {0}", se.ToString());
                }
                catch (Exception e)
                {
                    Console.WriteLine("Unexpected exception : {0}", e.ToString());
                }

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
            return false;
        }

        public void ReceiveThreadHandle(object obj)
        {
            byte[] bytes = new byte[1024];
            bool isCrash = false;
            while (clientSocket.Connected)
            {
                try
                {
                    int bytesRec = clientSocket.Receive(bytes);
                    if (bytesRec == 0) break;
                    string data = Encoding.ASCII.GetString(bytes, 0, bytesRec);
                    LOG("REV: " + data); 
                }
                catch(Exception)
                {
                    isCrash = true;
                    break;
                }   
            }
            if(!isCrash)
            {
                clientSocket.Shutdown(SocketShutdown.Both);
                clientSocket.Close();
                this.Invoke(new MethodInvoker(() => { btConnect.Text = "Conenct"; }));
            }
        }

        public void LOG(string log)
        {
            if (this.InvokeRequired)
            {
                this.Invoke(new MethodInvoker(() => { richTextBox1.AppendText($"{DateTime.Now.ToString("hh:mm:ss")} {log}\n"); }));
            }
            else
            {
                richTextBox1.AppendText($"{DateTime.Now.ToString("hh:mm:ss")} {log}\n");
            }
        }

        public void sendMessage(string msg)
        {
            LOG("SEND: " + msg);
            byte[] bytes = Encoding.ASCII.GetBytes(msg);
            try
            {
                if (clientSocket.Connected)
                    clientSocket.Send(bytes);
            }catch(Exception)
            {

            }
            
        }

        private void btSend_Click(object sender, EventArgs e)
        {
            if (!clientSocket.Connected) return;
            string msg = txtSendString.Text;
            if (msg.Length == 0) return;

            sendMessage(msg);
        }
    }
}
