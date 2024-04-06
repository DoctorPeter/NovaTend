
namespace SystemData.SerializableObject
{
    /// <summary>
    /// Attribute for marking field as field with max size after serialization
    /// </summary>
    [System.AttributeUsage(System.AttributeTargets.Property)]
    public class MaxSizeSerializationAttribute : System.Attribute
    {
        public int Size;

        public MaxSizeSerializationAttribute(int size)
        {
            this.Size = size;
        }
    }
}
