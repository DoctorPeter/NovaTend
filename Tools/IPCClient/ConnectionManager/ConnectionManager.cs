using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

using SystemData.Common;
using SystemData.Message;
using Communication.Client;
using Communication.Exceptions;

namespace Communication
{
    /// <summary>
    /// Class to manage ipc clients. 
    /// Implements singleton pattern.
    /// </summary>
    public class ConnectionManager : Singleton<ConnectionManager>, IConnectionManager
    {
        List<IPCClient> _clientList = new List<IPCClient>();
        /// <summary>
        /// List of available ipc clients
        /// </summary>
        public List<IPCClient> ClientList
        {
            get { return _clientList; }
            set
            {
                if (_clientList == value || _clientList.SequenceEqual(value))
                    return;
                _clientList = value;
            }
        }

        /// <summary>
        /// timeout to check for reconnection of clients
        /// </summary>
        TimeSpan ReconnectTimeout { get; set; }

        /// <summary>
        /// timer to check whether any ipc client is need to reconnect
        /// </summary>
        Timer ReconnectTimer;

        private ConnectionManager()
        {
            //set default timeout
            this.ReconnectTimeout = TimeSpan.FromMinutes(5);
            //init timer
            //this technique (infinite timeout for period) allow to ensure that timerproc will not be started while previous call isn't complete
            this.ReconnectTimer = new Timer(ReconnectProc, null, ReconnectTimeout, TimeSpan.FromMilliseconds(Timeout.Infinite));
        }

        /// <summary>
        /// provides reconnect functionality from another thread
        /// </summary>
        private void ReconnectProc(object obj)
        {
            try
            {
                var clientsToReconnect = new List<IPCClient>();
                var currentClients = new List<IPCClient>();

                lock (ClientList)
                {

                    ClientList.ForEach((client) => { currentClients.Add(client); });

                    foreach (var ipcClient in currentClients)
                    {
                        //calculate time difference between client last activity and current time
                        var dtDelta = DateTime.Now.Subtract(ipcClient.LastActivityDT).Ticks;

                        if (!ipcClient.IsBusy &&
                            dtDelta > 0 &&
                            dtDelta > ReconnectTimeout.Ticks)
                        {
                            //remove desirable client from ClientList (it's also provides disconnect internally)
                            //and prevents from calling other functionality
                            if (this.Remove(ipcClient))
                                //add this client to list of clients need to reconnect
                                clientsToReconnect.Add(ipcClient);
                        }
                    }
                }

                foreach (var clientToReconnect in clientsToReconnect)
                {
                    if (!clientToReconnect.Connect())
                    {
                        //here logging or notify somehow that connection isn't established
                        //or even canselation of adding
                    }

                    lock (ClientList)
                    {
                        ClientList.Add(clientToReconnect);
                    }
                }

                clientsToReconnect.Clear();

            }
            catch (Exception ex)
            {
            }

            //reset timer
            //this technique (infinite timeout for period) allow to ensure that timerproc will not be started while previous call isn't complete
            ReconnectTimer.Change(ReconnectTimeout, TimeSpan.FromMilliseconds(Timeout.Infinite));
        }

        /// <summary>
        /// add ipc client
        /// </summary>
        /// <param name="client"></param>
        /// <returns></returns>
        public bool Add(IPCClient client)
        {
            try
            {
                if (client == null)
                    return false;

                lock (ClientList)
                {
                    var existed = ClientList.FirstOrDefault(c => c.Equals(client));
                    if (existed != null)
                    {
                        return false;
                    }

                    ClientList.Add(client);
                }

                return true;
            }
            catch (Exception ex)
            {
                return false;
            }

        }

        /// <summary>
        /// remove ipc client
        /// </summary>
        /// <param name="client"></param>
        /// <returns></returns>
        public bool Remove(IPCClient client)
        {
            try
            {
                if (client == null)
                    return false;

                lock (ClientList)
                {
                    var existed = ClientList.FirstOrDefault(c => c.Equals(client));
                    if (existed == null)
                    {
                        return false;
                    }

                    existed.Disconnect();
                    ClientList.Remove(existed);
                }

                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        /// try get client by max server priority
        /// </summary>
        /// <param name="client">client to fill</param>
        /// <returns>true if client found, false otherwise</returns>
        internal bool TryGetClient(out IPCClient client)
        {
            client = null;

            try
            {
                var relatedClient = ClientList.OrderByDescending(c => (c.ConnectedToGlobalServer ? c.globalServerDescription.serverPriority : c.remoteServerDescription.serverPriority)).FirstOrDefault();
                if (relatedClient == null)
                {
                    throw new ClientNotFoundException(String.Format("client not forund"));
                }

                client = relatedClient;
                return true;
            }
            catch (Exception ex)
            {
                return false;
            }
        }

        /// <summary>
        /// Process message to server using mapped client
        /// </summary>
        /// <param name="inputData"></param>
        /// <param name="cmdCode"></param>
        /// <param name="timeout">how many ms to wait for server response</param>
        /// <returns>resulting params from server response or null if error occurs</returns>
        public MessageParametersList ProcessMessage(MessageParametersList inputData, int cmdCode, int timeout = 20000,
            uint? recepientID = null)
        {
            MessageParametersList res = null;

            try
            {
                IPCClient client;
                if (!TryGetClient(out client))
                    throw new ClientNotFoundException(String.Format("client with not found"));

                res = client.ProcessMessage(inputData, cmdCode, timeout, recepientID);
            }
            catch (Exception ex)
            {
                res = null;
            }

            return res;
        }

    }
}
