using System;
using SystemData;
using SystemData.SerializableObject;

namespace SystemData.Message
{
    /// <summary>
    /// one parameter to pass with message
    /// </summary>
    public class MessageParameter : ISerializableObject
    {
        /// <summary>
        /// Type of parameter
        /// </summary>
        public ParameterTypeEnum ParameterType { get; set; }

        /// <summary>
        /// Type of parameter data
        /// </summary>
        public ParameterDataTypeEnum ParameterDataType
        {
            get
            {
                return this.Parameter.GetDataType(_IsEncrypted);
            }
        }

        /// <summary>
        /// specifies that parameterdata is encrypted
        /// </summary>
        public bool _IsEncrypted = false;

        /// <summary>
        /// Actual message parameter as is
        /// </summary>
        public object Parameter { get; set; }

        /// <summary>
        /// creates empty messagew parameter
        /// </summary>
        public MessageParameter()
        {

        }

        /// <summary>
        /// creates parameter object from parameter type and parameter value
        /// </summary>
        /// <param name="typeOfParameter"></param>
        /// <param name="parameter"></param>
        public MessageParameter(ParameterTypeEnum typeOfParameter, object parameter, bool isEncrypted = false)
        {
            if (parameter == null)
                throw new ArgumentNullException("parameter");

            this.ParameterType = typeOfParameter;
            this.Parameter = parameter;
            this._IsEncrypted = isEncrypted;
        }

    }
}
