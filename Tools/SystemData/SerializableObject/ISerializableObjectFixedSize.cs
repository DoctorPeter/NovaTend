
namespace SystemData.SerializableObject
{
    public interface ISerializableObjectFixedSize: ISerializableObject
    {
        /// <summary>
        /// method to get object length in bytes after serialization
        /// </summary>
        /// <returns></returns>
        int GetBytesLength();
    }
}
