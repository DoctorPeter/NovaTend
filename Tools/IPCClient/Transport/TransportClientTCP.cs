using System;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Communication.Transport
{
    /// <summary>
    /// transport client for tcp connection
    /// inherit methods of base TranspotClient class
    /// </summary>
    public class TransportClientTCP : TransportClient, IDisposable
    {
        /// <summary>
        /// endpoint for sending data to server
        /// </summary>
        IPEndPoint connectionEndPointRemote;
        /// <summary>
        /// local endpoint to send from
        /// </summary>
        IPEndPoint connectionEndPointLocal;
                
        ///// <summary>
        ///// unfderlaying tcp client
        ///// </summary>
        //TcpClient tcpClient;

        /// <summary>
        /// client socket instance
        /// </summary>
        Socket clientSocket;

        /// <summary>
        /// stream to read/write data
        /// </summary>
        NetworkStream networkStream;
       
        /// <summary>
        /// receiver object for data sharing between threads and thread proc implementing
        /// </summary>
        Receiver Receiver;
        /// <summary>
        /// thread for listening commands from server
        /// </summary>
        Thread ReceiverThread;
        /// <summary>
        /// signal to notify of data receiving iteration completes
        /// </summary>
        AutoResetEvent DataReceived = new AutoResetEvent(false);
        /// <summary>
        /// signal for stoping processing thread
        /// </summary>
        AutoResetEvent StopReceiving = new AutoResetEvent(false);

        /// <summary>
        /// ctor
        /// </summary>
        /// <param name="localEndPoint">local endpoint</param>
        /// <param name="serverEndPoint">remote endpoint</param>
        public TransportClientTCP(IPEndPoint localEndPoint, IPEndPoint serverEndPoint)
            : base()
        {
            try
            {
                connectionEndPointRemote = serverEndPoint;
                connectionEndPointLocal = localEndPoint;

                ConfigureTCP();
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// configures underlaying tcp client
        /// </summary>
        void ConfigureTCP()
        {
            //tcpClient = new TcpClient(connectionEndPointLocal);
           
            ////using low-level algorithm with no delay packets (linghman?)
            //tcpClient.NoDelay = false;
            ////tcpClient.ReceiveBufferSize;

            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            clientSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReuseAddress, 1);
            clientSocket.Bind(connectionEndPointLocal);
        }

        /// <summary>
        /// provides connection procedure by underlaying tcp client on transport level
        /// </summary>
        public override void Connect()
        {
            try
            {
                //for reconnection purposes
                //if (tcpClient == null || tcpClient.Connected == false || this.Connected == false)
                //    ConfigureTCP();

                //tcpClient.Connect(connectionEndPointRemote);

                if (clientSocket == null || clientSocket.Connected == false || this.Connected == false)
                    ConfigureTCP();

                clientSocket.Connect(connectionEndPointRemote);

                if (networkStream != null)
                    networkStream.Flush();

                //networkStream = tcpClient.GetStream();
                networkStream = new NetworkStream(clientSocket);

                this.Connected = true;

                //after succesfull connect trying to init receiving thread
                BeginReceive();

            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// Connect via TCP hole punching
        /// </summary>
        public void ConnectTCPHP()
        {
            try
            {
                if (clientSocket == null || clientSocket.Connected == false || this.Connected == false)
                    ConfigureTCP();

                int attempts = 5;

                while (attempts > 0)
                {
                    try
                    {
                        clientSocket.Connect(connectionEndPointRemote);
                        break;
                    }
                    catch
                    {
                        attempts--;
                    }
                }

                if ((attempts <= 0) && (!clientSocket.Connected))
                    throw new Exception("TCPHP failed!");

                if (networkStream != null)
                    networkStream.Flush();

                networkStream = new NetworkStream(clientSocket);

                this.Connected = true;

                //after succesfull connect trying to init receiving thread
                BeginReceive();
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// initializes listening thread
        /// </summary>
        void BeginReceive()
        {
            try
            {
                if (Receiver != null)
                    StopReceiving.Set();

                Receiver = new Receiver(networkStream, DataReceived, StopReceiving);
                Receiver.ServerDisconnectRequest += Receiver_ServerDisconnectRequest;

                ReceiverThread = new Thread(Receiver.ThreadProc);
                ReceiverThread.Start();
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        void Receiver_ServerDisconnectRequest(object sender, CommunicationErrorEventArgs e)
        {
            try
            {
                base.HandleCommunicationException(e);
            }
            catch (Exception ex)
            {
            }
        }

        /// <summary>
        /// provides disconnection procedure by underlaying tcp client on transport level
        /// </summary>
        public override void Disconnect()
        {
            try
            {
                this.StopReceiving.Set();

                //tcpClient.Close();
                //tcpClient = null;
                clientSocket.Close();
                clientSocket = null;
                this.Connected = false;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// Send data and wait for response during timeout ms
        /// </summary>
        /// <param name="messageBytes"></param>
        /// <param name="responseTimeout">timeout to wait for response in ms</param>
        /// <returns>response or null</returns>
        public override byte[] SendReceive(byte[] messageBytes, int responseTimeout)
        {
            byte[] res = null;

            try
            {
                //connection already established

                //send message to server
                networkStream.Write(messageBytes, 0, messageBytes.Length);

                Console.WriteLine("SendReceive: sended {0} bytes", messageBytes.Length);

                //represent timeout for waiting of server response
                if (WaitHandle.WaitAny(new WaitHandle[] { DataReceived }, responseTimeout) == WaitHandle.WaitTimeout)
                    throw new Exception("timeout elapsed");
                else
                {
                    if (Receiver != null)
                        res = Receiver.ReceivedData;

                    if (res != null)
                        Console.WriteLine("SendReceive: receeived {0} bytes", res.Length);
                }

            }
            catch (Exception ex)
            {
                HandleCommunicationException(ex, messageBytes);

                res = null;
            }

            return res;
        }

        /// <summary>
        /// Wait for response from server during timeout ms
        /// </summary>
        /// <param name="responseTimeout">timeout to wait for response in ms</param>
        /// <returns>response or null</returns>
        public override byte[] Receive(int responseTimeout)
        {
            byte[] res = null;

            try
            {
                //represent timeout for waiting of server response
                if (WaitHandle.WaitAny(new WaitHandle[] { DataReceived }, responseTimeout) == WaitHandle.WaitTimeout)
                    throw new Exception("timeout elapsed");
                else
                {
                    if (Receiver != null)
                        res = Receiver.ReceivedData;

                    if (res != null)
                        Console.WriteLine("Receive: receeived {0} bytes", res.Length);
                }
            }
            catch (Exception ex)
            {
                HandleCommunicationException(ex, null);

                res = null;
            }

            return res;
        }

        /// <summary>
        /// Send data to server
        /// </summary>
        /// <param name="responseTimeout">obsolete</param>
        public override void Send(byte[] messageBytes, int responseTimeout)
        {
            try
            {
                //send message to server
                networkStream.Write(messageBytes, 0, messageBytes.Length);

                Console.WriteLine("Send: sended {0} bytes", messageBytes.Length);
            }
            catch (Exception ex)
            {
                HandleCommunicationException(ex, messageBytes);
            }
        }

        public void Dispose()
        {
            this.StopReceiving.Set();
            //this.tcpClient.Close();
            this.clientSocket.Close();
        }
    }

}