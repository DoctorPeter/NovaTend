using System;
using SystemData.Common;

namespace Communication.Transport
{
    /// <summary>
    /// Base transport client class
    /// </summary>
    public abstract class TransportClient : ITransportClient
    {
        /// <summary>
        /// raises when communication error ocurred during interaction
        /// </summary>
        public event EventHandler<CommunicationErrorEventArgs> CommunicationError;

        /// <summary>
        /// current connection state
        /// </summary>
        public bool Connected = false;

        /// <summary>
        /// Constructor
        /// </summary>
        public TransportClient()
        { }

        /// <summary>
        /// provides connection procedure on transport level
        /// </summary>
        public abstract void Connect();

        /// <summary>
        /// provides connection procedure on transport level
        /// </summary>
        public abstract void Disconnect();

        /// <summary>
        /// Send data and wait for response during timeout ms
        /// </summary>
        public abstract byte[] SendReceive(byte[] messageBytes, int responseTimeout = 2000);

        /// <summary>
        /// Send data to server
        /// </summary>
        public abstract void Send(byte[] messageBytes, int timeoutMs);

        /// <summary>
        /// Wait for response from server during timeout ms
        /// </summary>
        public abstract byte[] Receive(int timeoutMs);

        /// <summary>
        /// handle exeption during communication/
        /// provides a way for seciall handling, logging, etc
        /// </summary>
        internal void HandleCommunicationException(Exception ex, byte[] message)
        {
            var args = new CommunicationErrorEventArgs()
            {
                Error = ex,
                messageBytes = message
            };

            //this.Disconnect();
            var handler = CommunicationError;
            if (handler != null)
            {
                //raise to protocol level
                CommunicationError.Raise(this, args);
            }
        }

        /// <summary>
        /// handle exeption during communication/
        /// provides a way for seciall handling, logging, etc
        /// </summary>
        internal void HandleCommunicationException(CommunicationErrorEventArgs e)
        {
            //this.Disconnect();
            var handler = CommunicationError;
            if (handler != null)
            {
                //raise to protocol level
                CommunicationError.Raise(this, e);
            }
        }


    }
}
