using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Communication.Exceptions
{
    /// <summary>
    /// exception occurs when server aborts communication
    /// </summary>
    public class CommunicationAbortedFromServerException: Exception
    {
        public CommunicationAbortedFromServerException(string message)
            : base(message)
        { }
    }
}
