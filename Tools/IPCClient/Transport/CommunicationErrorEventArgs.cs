using System;

namespace Communication.Transport
{
    /// <summary>
    /// Event args for communication error
    /// </summary>
    public class CommunicationErrorEventArgs : EventArgs
    {
        private byte[] _messageBytes;
        /// <summary>
        /// message which initiates error in byte array representation
        /// </summary>
        public byte[] messageBytes
        {
            get
            {
                if (_messageBytes == null)
                    return null;
                return (byte[])_messageBytes.Clone();
            }
            set
            {
                _messageBytes = value;
            }
        }

        /// <summary>
        /// error which is occured
        /// </summary>
        public Exception Error { get; set; }

        private bool _serverDisconnectRequest = false;
        /// <summary>
        /// represents flag to notify if this args refer to server disconnect request
        /// </summary>
        public bool ServerDisconnectRequest
        {
            get { return _serverDisconnectRequest; }
            set { _serverDisconnectRequest = value; }
        }

    }
}
