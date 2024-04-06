using System;

namespace Communication.Exceptions
{
    /// <summary>
    /// exception occurs during communication between client and server
    /// </summary>
    public class CommunicationException: Exception
    {
        public CommunicationException(string message, Exception innerException)
            : base(message, innerException)
        { }
    }
}
