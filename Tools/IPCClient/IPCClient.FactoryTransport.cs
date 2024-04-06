using System.Net;
using Communication.Transport;

namespace Communication.Client
{
    /// <summary>
    /// factory to produce transport for ipc client, based on transport type
    /// </summary>
    public static class TransportFactory
    {
        /// <summary>
        /// Produces transport for ipc client, based on transport type
        /// </summary>
        /// <param name="localEndPoint"></param>
        /// <param name="serverEndPoint"></param>
        /// <param name="transportType"></param>
        /// <returns></returns>
        public static ITransportClient GenerateTransport(
            IPEndPoint localEndPoint,
            IPEndPoint serverEndPoint,
            TransportType transportType)
        {
            switch (transportType)
            {
                case TransportType.DEFAULT:
                case TransportType.TCPClientStream:
                    return new TransportClientTCP(localEndPoint, serverEndPoint);
                default:
                    return null;
            }
        }
    }
}
