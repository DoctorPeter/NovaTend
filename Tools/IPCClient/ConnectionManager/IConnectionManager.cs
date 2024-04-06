using Communication.Client;
using SystemData.Message;

namespace Communication
{
    /// <summary>
    /// Contract for implementing connection manager
    /// </summary>
    public interface IConnectionManager
    {
        /// <summary>
        /// add ipc client to list of available clients
        /// </summary>
        /// <param name="client"></param>
        /// <returns></returns>
        bool Add(IPCClient client);

        /// <summary>
        /// remove ipc client from list of available clients
        /// </summary>
        bool Remove(IPCClient client);

        /// <summary>
        /// process message to server
        /// </summary>
        MessageParametersList ProcessMessage(MessageParametersList inputData, int cmdCode, int timeout, uint? recepientID = null);
    }
}
