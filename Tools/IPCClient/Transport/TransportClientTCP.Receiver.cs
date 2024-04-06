using System;
using System.Linq;
using System.Net.Sockets;
using System.Threading;
using SystemData.Common;

namespace Communication.Transport
{
    /// <summary>
    /// Object to implement independent reading functionnality of transport
    /// supports data-sharing between threaads
    /// </summary>
    public class Receiver
    {
        /// <summary>
        /// stream to read from
        /// </summary>
        NetworkStream stream;
        /// <summary>
        /// event to signal if data received
        /// </summary>
        AutoResetEvent dataReceived;
        /// <summary>
        /// event to wait for stopping the thread
        /// </summary>
        AutoResetEvent closingEvent;

        /// <summary>
        /// inner timeout for reading to the end of message ()
        /// </summary>
        TimeSpan readToEndTimeout;

        private byte[] _receivedData;
        /// <summary>
        /// receiving buffer
        /// </summary>
        public byte[] ReceivedData
        {
            get
            {
                return (byte[])_receivedData.Clone();
            }
            set { _receivedData = value; }
        }

        /// <summary>
        /// raises when server wants disconnect by it's own initiative
        /// </summary>
        public event EventHandler<CommunicationErrorEventArgs> ServerDisconnectRequest;

        /// <summary>
        /// ctor
        /// </summary>
        /// <param name="streamToRead"></param>
        /// <param name="signal"></param>
        /// <param name="cansellation"></param>
        /// <param name="readToEndTimeoutMs"></param>
        public Receiver(NetworkStream streamToRead, AutoResetEvent signal, AutoResetEvent cansellation, int readToEndTimeoutMs = 10000)
        {
            this.stream = streamToRead;

            this.dataReceived = signal;
            this.closingEvent = cansellation;
            this.readToEndTimeout = TimeSpan.FromMilliseconds(readToEndTimeoutMs);
        }

        public void Stop()
        {
            closingEvent.Set();
        }

        /// <summary>
        /// proc to execute on independent thread
        /// </summary>
        public void ThreadProc()
        {
            try
            {
                //wait for firing signal to stop processing
                while (!closingEvent.WaitOne(0, false))
                {
                    var data = ReadDataFromServer();

                    if (data != null)
                    {
                        this.ReceivedData = data;

                        if (!CheckDisconnectCommand(data))
                        {
                            dataReceived.Set();
                        }
                        else
                        {
                            var handler = ServerDisconnectRequest;
                            if (handler != null)
                                ServerDisconnectRequest.Raise(
                                    this,
                                    new CommunicationErrorEventArgs()
                                    {
                                        Error = new Exception("server request disconnect"),
                                        messageBytes = data,
                                        ServerDisconnectRequest = true
                                    });

                            closingEvent.Set();
                        }
                    }
                }

                //for testing purposes
                Console.WriteLine("ThreadProc stopped");
            }
            catch (Exception ex)
            {
            }
        }

        /// <summary>
        /// read data from server
        /// (internally implement read until eof or timeout)
        /// </summary>
        /// <returns></returns>
        byte[] ReadDataFromServer()
        {
            byte[] res = null;

            try
            {
                if (stream == null)
                    return null;

                if (!stream.DataAvailable)
                {
                    // Give up the remaining time slice.
                    Thread.Sleep(1);
                }
                else
                {
                    var lengthBytes = new byte[sizeof(int)];
                    stream.Read(lengthBytes, 0, sizeof(int));
                    int length = BitConverter.ToInt32(lengthBytes, 0);

                    //whole message to receive
                    var message = new byte[length];

                    //procedure to receive exact amount of bytes
                    var buffer = new byte[length];
                    int offset = 0;
                    int count = length;
                    int receivedLegth = 0;

                    Console.WriteLine("length: {0}", length);
                    Console.WriteLine("offset: {0}, count: {1}", offset, count);

                    //init timeout variable
                    var timeoutElapsedDT = DateTimeOffset.UtcNow.Add(readToEndTimeout);

                    while (count > 0 && (receivedLegth = stream.Read(buffer, 0, count)) > 0)
                    {
                        Console.WriteLine("received length: {0}", receivedLegth);

                        Array.Copy(buffer, 0, message, offset, receivedLegth);

                        offset += receivedLegth;
                        count -= receivedLegth;

                        Console.WriteLine("offset: {0}, count: {1}", offset, count);

                        //check timeout while retrieving big amount of data
                        if (DateTimeOffset.UtcNow > timeoutElapsedDT)
                            throw new Exception("wait for response timeout elapsed");
                    }

                    //maybe it's neccesary
                    //if (count != 0) 
                    //throw new FormatException("message is bigger than expected");

                    res = lengthBytes.Concat(message).ToArray();

                }
            }
            catch (Exception ex)
            {
                res = null;
            }

            return res;
        }

        /// <summary>
        /// check that byte data represents server disconnect command
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        bool CheckDisconnectCommand(byte[] data)
        {
            try
            {
                //validation:
                //byte[] data should be more than 12 bytes and bytes 5-8 is command code
                //command code for server is 2

                if (data != null && data.Length > 12)
                {
                    var isDisconnect =
                        BitConverter.ToInt32(
                            new ArraySegment<byte>(data, sizeof(int), sizeof(int)).ToArray(), 0) == 2;
                    return isDisconnect;
                }

                throw new Exception("invalid CheckDisconnectCommand parameter argument");

            }
            catch (Exception ex)
            {
                return false;
            }
        }
    }
}
