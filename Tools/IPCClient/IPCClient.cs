using System;
using System.Linq;
using System.Net;
using Communication.Transport;
using SystemData;
using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;
using SystemData.Message;
using Serialization;

namespace Communication.Client
{
    /// <summary>
    /// Represents client for ipc
    /// </summary>
    public class IPCClient
    {
        /// <summary>
        /// Client Description
        /// </summary>
        internal CLIENT_DESCRIPTION clientDescription { get; set; }

        /// <summary>
        /// Remote Server Description
        /// </summary>
        internal SERVER_DESCRIPTION remoteServerDescription { get; set; }
        
        /// <summary>
        /// Global Server Description
        /// </summary>
        internal SERVER_DESCRIPTION globalServerDescription { get; set; }

        /// <summary>
        /// ipc client is connected to server
        /// </summary>
        public bool ConnectedToGlobalServer { get; set; }

        /// <summary>
        /// Client to transporting messages to/from server
        /// </summary>
        ITransportClient transportClient;

        /// <summary>
        /// ipc client is connected to server
        /// </summary>
        public bool IsConnected { get; set; }

        /// <summary>
        /// ipc client is in busy state
        /// </summary>
        public bool IsBusy { get; set; }

        /// <summary>
        /// last time when client succesefully (!) processed any message
        /// </summary>
        public DateTime LastActivityDT { get; set; }
                
        /// <summary>
        /// Transport type
        /// </summary>
        public TransportType transportType { get; set; }
        
        /// <summary>
        /// ipc client Constructor
        /// </summary>
        /// <param name="clientInfo"></param>
        /// <param name="serverInfo"></param>
        /// <param name="keepAliveTimeout">timeout to wait for server response</param>
        /// <param name="transportType">type of message transporting between client and server</param>
        public IPCClient(
            CLIENT_DESCRIPTION clientInfo,
            SERVER_DESCRIPTION remoteServerInfo,
            SERVER_DESCRIPTION globalServerInfo,
            TimeSpan keepAliveTimeout,
            TransportType transportType = TransportType.DEFAULT)
        {
            this.clientDescription = clientInfo;
            this.clientDescription.PrivatePort = Convert.ToUInt32(new Random(DateTime.Now.Millisecond).Next(1024, 65535));
            this.clientDescription.OwnClientID = 0;

            this.remoteServerDescription = remoteServerInfo;
            this.globalServerDescription = globalServerInfo;

            this.transportType = transportType;
            this.LastActivityDT = DateTime.Now;
            this.IsBusy = false;

            transportClient = TransportFactory.GenerateTransport(
                new IPEndPoint(IPAddress.Parse(clientDescription.PrivateIP), (int)clientDescription.PrivatePort),
                new IPEndPoint(IPAddress.Parse(remoteServerDescription.ipAddress), (int)remoteServerDescription.port),
                transportType);

            transportClient.CommunicationError += transportClient_CommunicationError;
        }

        /// <summary>
        /// Implements procedure of connection on protocol-level
        /// </summary>
        /// <returns>true if connection is established, false otherwise</returns>
        internal bool Connect()
        {
            this.IsBusy = true;
            bool res = false;
            ConnectedToGlobalServer = false;

            try
            {
                Console.WriteLine("Connecting");

                try
                {
                    Console.WriteLine("request connection to remote server");
                    transportClient.Connect();
                    res = ProcessConnectionRequest(remoteServerDescription);
                }
                catch
                {
                    transportClient.Disconnect();
                }

                if ((!(transportClient as TransportClient).Connected) && (!res))
                {
                    transportClient = TransportFactory.GenerateTransport(
                        new IPEndPoint(IPAddress.Parse(clientDescription.PrivateIP), (int)clientDescription.PrivatePort),
                        new IPEndPoint(IPAddress.Parse(globalServerDescription.ipAddress), (int)globalServerDescription.port),
                        this.transportType);

                    Console.WriteLine("request connection to global server");
                    transportClient.Connect();
                    res = ProcessConnectionRequest(globalServerDescription);


                    if (((transportClient as TransportClient).Connected) && res)
                    {
                        ConnectedToGlobalServer = true;

                        string publicIP = "";
                        int publicPort = 0;
                        
                        if (GetPublicServerAddress(ref publicIP, ref publicPort))
                        {
                            Disconnect();
                            ConnectedToGlobalServer = false;

                            if (transportClient is TransportClientTCP)
                            {
                                transportClient = TransportFactory.GenerateTransport(
                                    new IPEndPoint(IPAddress.Parse(clientDescription.PrivateIP), (int)clientDescription.PrivatePort),
                                    new IPEndPoint(IPAddress.Parse(publicIP), (int)publicPort),
                                    this.transportType);

                                (transportClient as TransportClientTCP).ConnectTCPHP();
                                res = ProcessConnectionRequest(remoteServerDescription);
                            }
                        }
                        else
                        {
                            Disconnect();
                            ConnectedToGlobalServer = false;
                            res = false;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                this.IsBusy = false;
                res = false;
            }

            Console.WriteLine("Connect done. Result: {0}", res);
            return res;
        }

        /// <summary>
        /// Process connection request according to IPc protocol
        /// </summary>
        /// <returns>connection result</returns>
        private bool ProcessConnectionRequest(SERVER_DESCRIPTION ServerDescription)
        {
            this.IsBusy = true;
            bool res = false;

            try
            {
                Console.WriteLine("waiting for server callback");
                var serverConnectCmdBytes = transportClient.Receive(5000);

                if (serverConnectCmdBytes == null)
                    throw new Exception("command connect didn't getted from server during timeout");

                var serverConnectCmd = SerializationManager.Deserialize(serverConnectCmdBytes);

                Console.WriteLine("server callback getted: {0}", serverConnectCmd.ToString());

                //simple validation
                if (serverConnectCmd.HEADER != null &&
                    serverConnectCmd.HEADER.CommandCode == 1 &&
                    serverConnectCmd.HEADER.CommandType == CommandTypeEnum.REQUEST &&
                    serverConnectCmd.LISTOFPARAMETERS != null &&
                    serverConnectCmd.LISTOFPARAMETERS.Count > 0 &&
                    serverConnectCmd.LISTOFPARAMETERS.First().ParameterDataType == ParameterDataTypeEnum.SERVER_DESCRIPTION_DATA)
                {
                    this.clientDescription.ClientID = serverConnectCmd.HEADER.recipientID;
                    if (ServerDescription.serverID != serverConnectCmd.HEADER.senderID)
                        throw new Exception("Wrong server ID!");


                    var serverConnectCmdResponse =
                        new Message(
                            new MessageHeader(1, CommandTypeEnum.RESPONSE, this.clientDescription.ClientID, ServerDescription.serverID),
                            new MessageParametersList() { new MessageParameter(ParameterTypeEnum.OUTPUTPARAMETER, this.clientDescription, false) });

                    Console.WriteLine("sending client description: {0}", serverConnectCmdResponse.ToString());

                    var serverConnectCmdResponseBytes = SerializationManager.Serialize(serverConnectCmdResponse);

                    transportClient.Send(serverConnectCmdResponseBytes, 5000);
                    
                    Console.WriteLine("Connected");
                    res = true;
                }

                this.IsConnected = true;
                this.IsBusy = false;
            }
            catch (Exception ex)
            {
                this.IsConnected = false;
                this.IsBusy = false;
                res = false;
            }

            return res;
        }

        /// <summary>
        /// Get public IP:port of remote server
        /// </summary>
        /// <returns>TRUE - if success</returns>
        bool GetPublicServerAddress(ref string publicIP, ref int publicPort)
        {
            bool res = false;

            try
            {
                var serverConnectCmdRequest =
                        new Message(
                            new MessageHeader(1, CommandTypeEnum.REQUEST, this.clientDescription.ClientID, globalServerDescription.serverID),
                            new MessageParametersList() { new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, remoteServerDescription.serverID, false),
                                                      new MessageParameter(ParameterTypeEnum.INPUTPARAMETER, remoteServerDescription.serverType, false) });

                Console.WriteLine("sending client description: {0}", serverConnectCmdRequest.ToString());

                var serverConnectCmdRequestBytes = SerializationManager.Serialize(serverConnectCmdRequest);

                var serverConnectCmdResponseBytes = transportClient.SendReceive(serverConnectCmdRequestBytes, 5000);

                if (serverConnectCmdResponseBytes == null)
                    throw new Exception("command connect didn't getted from server during timeout");

                var serverConnectCmd = SerializationManager.Deserialize(serverConnectCmdResponseBytes);

                Console.WriteLine("server callback getted: {0}", serverConnectCmd.ToString());

                //simple validation
                if (serverConnectCmd.HEADER != null &&
                    serverConnectCmd.HEADER.CommandCode == 1 &&
                    serverConnectCmd.HEADER.CommandType == CommandTypeEnum.RESPONSE &&
                    serverConnectCmd.LISTOFPARAMETERS != null &&
                    serverConnectCmd.LISTOFPARAMETERS.Count > 0 &&
                    serverConnectCmd.LISTOFPARAMETERS[0].ParameterDataType == ParameterDataTypeEnum.STRING_DATA &&
                    serverConnectCmd.LISTOFPARAMETERS[1].ParameterDataType == ParameterDataTypeEnum.DWORD_DATA)
                {
                    publicIP = (string)serverConnectCmd.LISTOFPARAMETERS[0].Parameter;
                    publicPort = (int)serverConnectCmd.LISTOFPARAMETERS[0].Parameter;

                    res = true;
                }

            }
            catch
            {
                res = false;
            }

            return res;
        }

        /// <summary>
        /// Implements procedure of disconnection on protocol-level
        /// </summary>
        internal void Disconnect(bool clientInitiative = true)
        {
            this.IsBusy = true;

            try
            {
                //prepare disconnect request/response
                var clientDisconnectCmd =
                        new Message(
                            new MessageHeader(2, CommandTypeEnum.REQUEST, this.clientDescription.ClientID, ConnectedToGlobalServer ? globalServerDescription.serverID : remoteServerDescription.serverID),
                            new MessageParametersList() { });
                var clientDisconnectCmdBytes = SerializationManager.Serialize(clientDisconnectCmd);

                if (clientInitiative)
                {
                    //disconnect is initiative from client
                    var serverDisconnectCmdBytes = transportClient.SendReceive(clientDisconnectCmdBytes, 5000);
                    if (serverDisconnectCmdBytes == null)
                    {
                        Console.WriteLine("command disconnect didn't getted from server during timeout");
                    }
                    else
                    {
                        var serverDisconnectCmd = SerializationManager.Deserialize(serverDisconnectCmdBytes);

                        //simple validation
                        bool isValidServerResponse =
                            (serverDisconnectCmd.HEADER != null &&
                            serverDisconnectCmd.HEADER.CommandCode == 2 &&
                            serverDisconnectCmd.HEADER.CommandType == CommandTypeEnum.RESPONSE &&
                            serverDisconnectCmd.LISTOFPARAMETERS != null &&
                            serverDisconnectCmd.LISTOFPARAMETERS.Count == 0);

                        //response for disconnect getted but not valid for protocol
                        if (!isValidServerResponse)
                            Console.WriteLine("invalid server response for disconnect command");
                    }
                }
                else
                {
                    //disconnect is initiative from server
                    transportClient.Send(clientDisconnectCmdBytes, 5000);
                }

                this.transportClient.Disconnect();
                this.transportClient.CommunicationError -= transportClient_CommunicationError;
                this.IsConnected = false;
            }
            catch (Exception ex)
            {
            }

            this.IsBusy = false;

            Console.WriteLine("Disconnect done");
        }

        /// <summary>
        /// Processes message to server
        /// </summary>
        /// <param name="inputData"></param>
        /// <param name="comdCode"></param>
        /// <param name="responseTimeout"></param>
        /// <returns>resulting params from server response, null if error occurs</returns>
        internal MessageParametersList ProcessMessage(MessageParametersList inputData, int comdCode, int responseTimeout,
            uint? recepientID = null)
        {
            this.IsBusy = true;

            try
            {
                if (!this.IsConnected)
                {
                    bool connectAttemptRes = this.Connect();
                    if (!connectAttemptRes)
                        throw new Exception("can't connect");
                }

                var messageRecepinetID =
                    recepientID.HasValue ?
                    recepientID.Value :
                    (ConnectedToGlobalServer ? globalServerDescription.serverID : remoteServerDescription.serverID);

                var messageToServer =
                    new Message(
                        new MessageHeader(comdCode, CommandTypeEnum.REQUEST, this.clientDescription.ClientID, messageRecepinetID),
                        inputData);

                Console.WriteLine("sending message: {0}", messageToServer.ToString());

                var messageBytes = SerializationManager.Serialize(messageToServer);

                var resBytes = transportClient.SendReceive(messageBytes, responseTimeout);

                if (resBytes != null)
                {
                    var res = SerializationManager.Deserialize(resBytes);

                    Console.WriteLine("message sended. response: {0}", res.ToString());

                    //refresh last activity field
                    this.LastActivityDT = DateTime.Now;
                    this.IsBusy = false;

                    return res.LISTOFPARAMETERS;
                }

                this.IsBusy = false;
                return null;
            }
            catch (Exception ex)
            {
                this.IsBusy = false;
                throw;
            }
        }

        /// <summary>
        /// Provides advanced error handling of communication process/
        /// (notify observers, log on connection faults, etc)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void transportClient_CommunicationError(object sender, CommunicationErrorEventArgs e)
        {
            if (e.ServerDisconnectRequest)
            {
                //handle disconnect
                Disconnect(false);
            }
            else
            {
                if (e.messageBytes != null)
                {
                    var message = SerializationManager.Deserialize(e.messageBytes);

                    Console.WriteLine("fail for message: {0}", message);
                }
                Console.WriteLine(e.Error.ToString());
            }
        }

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            if (obj is IPCClient)
            {
                var client = obj as IPCClient;

                return client.clientDescription.Equals(clientDescription) && client.globalServerDescription.Equals(globalServerDescription) && client.remoteServerDescription.Equals(remoteServerDescription);
            }

            return base.Equals(obj);
        }
    }
}
