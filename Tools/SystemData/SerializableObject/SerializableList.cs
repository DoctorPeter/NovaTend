using System.Collections.Generic;

namespace SystemData.SerializableObject
{
    public abstract class SerializableList<T> : List<T>, ISerializableObject where T : ISerializableObject
    {

    }
}
