using System;
using System.Collections.Generic;

namespace SystemData.SerializableObject
{
    public abstract class SerializableListFixedItems<T> : List<T>, ISerializableObject where T : ISerializableObjectFixedSize
    {
        public SerializableListFixedItems()
        { }

        public int GetBytesLength()
        {
            try
            {
                var res = 0;
                res += sizeof(int);

                this.ForEach((param) =>
                {
                    res += param.GetBytesLength();
                });

                return res;
            }
            catch (Exception)
            {
                return 0;
            }
        }
    }
}
