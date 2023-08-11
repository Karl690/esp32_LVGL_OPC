using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LCoreClient
{
    public partial class Form1 : Form
    {
        Socket clientSocket;
        Bitmap bmpScreen = new Bitmap(480, 320, PixelFormat.Format16bppRgb565);
        MemoryStream ms = new MemoryStream();
        Thread backgroundReceiveThread;
        public Form1()
        {
            InitializeComponent();
            BitmapData bData = bmpScreen.LockBits(new Rectangle(0, 0, bmpScreen.Width, bmpScreen.Height), ImageLockMode.ReadWrite, bmpScreen.PixelFormat);

            byte bitsPerPixel = 16;
            unsafe
            {
                /*This time we convert the IntPtr to a ptr*/
                byte* scan0 = (byte*)bData.Scan0.ToPointer();

                for (int i = 0; i < bData.Height; ++i)
                {
                    for (int j = 0; j < bData.Width; ++j)
                    {
                        byte* data = scan0 + i * bData.Stride + j * bitsPerPixel / 8;

                        //data is a pointer to the first byte of the 3-byte color data
                        data[0] = 0;
                        data[1] = 0;
                    }
                }
            }

            bmpScreen.UnlockBits(bData);
            pictureBox1.Image = bmpScreen;
            pictureBox1.Refresh();


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
            if (backgroundReceiveThread != null && backgroundReceiveThread.IsAlive)
                backgroundReceiveThread.Abort();
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
                    IAsyncResult result = clientSocket.BeginConnect(endPoint, null, null);

                    bool success = result.AsyncWaitHandle.WaitOne(2000, true);

                    if (!clientSocket.Connected)
                    {
                        // NOTE, MUST CLOSE THE SOCKET

                        clientSocket.Close();
                        throw new ApplicationException("Failed to connect server.");
                    }
                    //clientSocket.Connect(endPoint);

                    Console.WriteLine("Socket connected to {0}",
                        clientSocket.RemoteEndPoint.ToString());

                    backgroundReceiveThread = new Thread(this.ReceiveThreadHandle);
                    backgroundReceiveThread.Start(clientSocket);
                    
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
        public void updateScreenBuffer(byte[] buf, int pos, int len)
        {
            /*This time we convert the IntPtr to a ptr*/
           
            for(int i = 0; i < len; i +=2)
            {
                screenbuffer[pos+i] = buf[i+1];
                screenbuffer[pos+i+1] = buf[i];
            }
           
        }
        public void updateScreen()
        {
            BitmapData bData = bmpScreen.LockBits(new Rectangle(0, 0, bmpScreen.Width, bmpScreen.Height), ImageLockMode.ReadWrite, bmpScreen.PixelFormat);
            unsafe
            {
                /*This time we convert the IntPtr to a ptr*/
                byte* scan = (byte*)bData.Scan0.ToPointer();
                
                for (int i = 0; i < SCREEN_PIXELS; i += 2)
                {
                    scan[i] = screenbuffer[i];
                    scan[i + 1] = screenbuffer[i + 1];
                }
            }

            bmpScreen.UnlockBits(bData);
            pictureBox1.Image = bmpScreen;
            
        }
        const int SCREEN_WIDTH = 480;
        const int SCREEN_HEIGHT = 320;
        const int SCREEN_COLOR_DEEP = 2;
        const int SCREEN_PIXELS = SCREEN_COLOR_DEEP * SCREEN_HEIGHT * SCREEN_WIDTH;
        byte[] screenbuffer = new byte[SCREEN_PIXELS];
        public void ReceiveThreadHandle(object obj)
        {
            byte[] bytes = new byte[SCREEN_COLOR_DEEP * SCREEN_WIDTH * 10];
            bool isCrash = false;
            int ScreenReceiveCount = -1;
            int ScreenYPos = 0;
            while (clientSocket.Connected)
            {
                try
                {
                    int bytesReceived = clientSocket.Receive(bytes);
                    if (bytesReceived == 0) break;
                    if(bytesReceived < 40)
                    {
                        string data = Encoding.ASCII.GetString(bytes, 0, bytesReceived);
                        if(data.StartsWith("SCREEN_START"))
                        {
                            ScreenReceiveCount = 0;
                            //string[] param = data.Substring("SCREEN_START=".Length).Split(',');
                            //if(param.Length == 5)
                            //{
                            //    ScreenReceiveCount = 0;
                            //    int width = 480; //default is 480;
                            //    int.TryParse(param[1], out ScreenYPos);
                            //    int.TryParse(param[2], out width);
                            //    ScreenReceiveCount = ScreenYPos * width * 2;
                            //}
                        }
                        else if(data == "SCREEN_END")
                        {
                            updateScreen(); 
                            ScreenReceiveCount = -1;
                        }
                        LOG("REV: " + data);
                    }else
                    {
                        if (ScreenReceiveCount >= 0 && ScreenReceiveCount+bytesReceived < SCREEN_PIXELS)
                        {
                            updateScreenBuffer(bytes, ScreenReceiveCount, bytesReceived);
                            ScreenReceiveCount += bytesReceived;
                        }
                        LOG($"REV: {bytesReceived} bytes received");
                    }
                    clientSocket.ReceiveBufferSize = 0;
                }
                catch(Exception e)
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
            if (clientSocket == null) return;
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

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            sendMessage($"TOUCH={e.X},{e.Y},DOWN");
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            sendMessage($"TOUCH={e.X},{e.Y},UP");
        }
    }
}
