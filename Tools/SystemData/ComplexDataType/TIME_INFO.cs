using SystemData.SerializableObject;

namespace SystemData.ComplexDataType
{
    public class TIME_INFO : ISerializableObjectFixedSize
    {
        /// <summary>
        /// seconds after the minute
        /// </summary>
        public int tm_sec { get; set; }

        /// <summary>
        /// minutes after the hour
        /// </summary>
        public int tm_min { get; set; }

        /// <summary>
        /// hours since midnight
        /// </summary>
        public int tm_hour { get; set; }

        /// <summary>
        /// day of the month	
        /// </summary>
        public int tm_mday { get; set; }

        /// <summary>
        /// months since January
        /// </summary>
        public int tm_mon { get; set; }

        /// <summary>
        /// years since 1900
        /// </summary>
        public int tm_year { get; set; }

        /// <summary>
        /// days since Sunday
        /// </summary>
        public int tm_wday { get; set; }

        /// <summary>
        /// days since January 1
        /// </summary>
        public int tm_yday { get; set; }

        /// <summary>
        /// Daylight saving time flag
        /// </summary>
        public int tm_isdst { get; set; }

        public TIME_INFO()
        { }

        public int GetBytesLength()
        {
            return sizeof(int) * 9;
        }

    }
}
