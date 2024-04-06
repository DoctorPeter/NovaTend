using System;
using System.Threading;
using Communication;
using SystemData.Message;

namespace Commands
{
    /// <summary>
    /// Base class for implementing wdc command under IWDCComamnd contract.
    /// Provides main execution implementation.
    /// Provides methods for validation and pre/post-execution processing as execution wrapper.
    /// Inherited classes (concrete commands) can impact on execution using Pre/Post execution ovverides.
    /// Validation occurs by ovveriding inpiut and result validation in inherited classes (concrete commands).
    /// </summary>
    public abstract class WDCCommand : IWDCCommand
    {
        /// <summary>
        /// type of stored concrete command
        /// </summary>
        internal WDCCommandType typeOfCommand;

        /// <summary>
        /// count of attempts to execute if error occurs
        /// </summary>
        int attemptMaxCount;
        /// <summary>
        /// timeout between attempts
        /// </summary>
        TimeSpan errorTimeout;

        public WDCCommand(WDCCommandType cmdType)
        {
            this.typeOfCommand = cmdType;

            //this can be taken out into settings
            attemptMaxCount = 1;
            errorTimeout = TimeSpan.FromSeconds(1);
        }

        /// <summary>
        /// Validate input params
        /// </summary>
        /// <param name="input">input params</param>
        /// <returns>true if validation sucess, false otherwise</returns>
        internal abstract bool ValidateInput(MessageParametersList input);

        /// <summary>
        /// Validate result
        /// </summary>
        /// <param name="result">resulting params</param>
        /// <returns>true if validation sucess, false otherwise</returns>
        internal abstract bool ValidateResult(MessageParametersList result);

        /// <summary>
        /// exstension of execute() method for concrete command
        /// Occurs before exact execution.
        /// </summary>
        internal abstract void PreExecute();

        /// <summary>
        /// exstension of execute() method for concrete command.
        /// Occurs after exact execution.
        /// </summary>
        internal abstract void PostExecute();

        /// <summary>
        /// Execute command.
        /// Method define execution algorithm with validaton and execution exstensions
        /// </summary>
        /// <param name="inputParameters">list of parameters to pass on server</param>
        /// <returns>resulting params or emty list if error occurs or result cannot be retrieved</returns>
        public MessageParametersList Execute(MessageParametersList inputParameters = null,
            uint? recepientID = null)
        {
            MessageParametersList result;

            try
            {
                if (!ValidateInput(inputParameters))
                    throw new FormatException("not valid input for this type of command");

                PreExecute();

                result = ExecuteInternal(inputParameters, recepientID);

                PostExecute();

                if (!ValidateResult(result))
                    throw new FormatException("not valid response for this type of command");

                return result;
            }
            catch (FormatException fex)
            {
                Console.WriteLine("validation failed");
                return new MessageParametersList();
            }
            catch (Exception ex)
            {
                Console.WriteLine("general error while executing: {0}", ex.ToString());
                return new MessageParametersList();
            }
        }

        /// <summary>
        /// internal implementation of command execution.
        /// try to execute even if error. (try attempts and timeout between attempts are limited)
        /// </summary>
        /// <param name="inputParameters">list of parameters to pass on server</param>
        /// <returns>resulting params or null if result cannot be retrieved</returns>
        MessageParametersList ExecuteInternal(MessageParametersList inputParameters,
            uint? recepientID = null)
        {
            MessageParametersList res = null;
            int attemptNumber = 0;

            try
            {
                //null input is allowed in top method
                //but it's not allowed by serialization
                //so, replacing it with empty list
                if (inputParameters == null)
                    inputParameters = new MessageParametersList();

                while (attemptNumber < attemptMaxCount)
                {
                    res = ConnectionManager.Instance.ProcessMessage(inputParameters, (int)this.typeOfCommand, 20000, recepientID);
                    if (res != null)
                        break;

                    attemptNumber += 1;
                    Thread.Sleep(errorTimeout);
                }
            }
            catch (Exception ex)
            {
                res = null;
            }

            return res;
        }
    }
}
