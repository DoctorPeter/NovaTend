namespace Communication
{
    /// <summary>
    /// type of transpot used to deliver/retrieve messages to/from server
    /// </summary>
    public enum TransportType
    {
        /// <summary>
        /// default transport type. (Same as tcp client)
        /// </summary>
        DEFAULT,
        /// <summary>
        /// specify that transport client should use tcpclient to establish connection
        /// </summary>
        TCPClientStream,
    }
}
