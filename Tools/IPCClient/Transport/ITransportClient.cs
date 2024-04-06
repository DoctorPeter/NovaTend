using System;

namespace Communication.Transport
{
    /// <summary>
    /// contract for transport client implementation
    /// </summary>
    public interface ITransportClient
    {
        /// <summary>
        /// send and wait for response
        /// </summary>
        /// <param name="messageBytes"></param>
        /// <param name="timeoutMs"></param>
        /// <returns></returns>
        byte[] SendReceive(byte[] messageBytes, int timeoutMs);

        /// <summary>
        /// send only
        /// </summary>
        /// <param name="messageBytes"></param>
        /// <param name="timeoutMs"></param>
        void Send(byte[] messageBytes, int timeoutMs);

        /// <summary>
        /// wait for response
        /// </summary>
        /// <param name="timeoutMs"></param>
        /// <returns></returns>
        byte[] Receive(int timeoutMs);

        /// <summary>
        /// connect to server
        /// </summary>
        void Connect();

        /// <summary>
        /// disconnect from server
        /// </summary>
        void Disconnect();

        /// <summary>
        /// signals if communication error occurs
        /// </summary>
        event EventHandler<CommunicationErrorEventArgs> CommunicationError;
    }
}
