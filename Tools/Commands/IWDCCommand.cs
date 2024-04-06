using SystemData.Message;

namespace Commands
{
    /// <summary>
    /// Contract for implementing command
    /// </summary>
    public interface IWDCCommand
    {
        /// <summary>
        /// Execute command
        /// </summary>
        /// <param name="inputParameters">command parameters</param>
        /// <returns>resulting parameters</returns>
        MessageParametersList Execute(MessageParametersList inputParameters = null, uint? recepientID = null);
    }
}
