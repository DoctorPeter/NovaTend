using System;

namespace Communication.Exceptions
{
    /// <summary>
    /// ipc client not found
    /// </summary>
    public class ClientNotFoundException: Exception
    {
        public ClientNotFoundException(string message)
            : base(message)
        { }
    }
}
