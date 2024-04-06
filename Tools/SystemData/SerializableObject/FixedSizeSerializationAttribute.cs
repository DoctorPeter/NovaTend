
namespace SystemData.SerializableObject
{
    /// <summary>
    /// Attribute for marking field as fixed-size for serialization
    /// </summary>
    [System.AttributeUsage(System.AttributeTargets.Property)]
    public class FixedSizeSerializationAttribute : System.Attribute
    {
        public int Size;

        public FixedSizeSerializationAttribute(int size)
        {
            this.Size = size;
        }
    }
}
