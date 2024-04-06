using System;
using System.Reflection;

namespace SystemData.SerializableObject
{
    public class SerializationAttributeHelper
    {
        /// <summary>
        /// try to get custom serialization attribute value
        /// </summary>
        /// <param name="property"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public bool TryGetFixedSizeSerializationAttribute(PropertyInfo property, out int value)
        {
            value = 0;
            try
            {
                object[] attrs = property.GetCustomAttributes(true);
                foreach (object attr in attrs)
                {
                    var fixedSize = attr as FixedSizeSerializationAttribute;
                    if (fixedSize != null)
                    {
                        value = fixedSize.Size;
                        return true;
                    }
                }

                return false;
            }
            catch (Exception)
            {
                return false;
            }
        }

        /// <summary>
        /// try to get custom serialization attribute value
        /// </summary>
        /// <param name="property"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public bool TryGetMaxSizeSerializationAttribute(PropertyInfo property, out int value)
        {
            value = 0;
            try
            {
                object[] attrs = property.GetCustomAttributes(true);
                foreach (object attr in attrs)
                {
                    var fixedSize = attr as MaxSizeSerializationAttribute;
                    if (fixedSize != null)
                    {
                        value = fixedSize.Size;
                        return true;
                    }
                }

                return false;
            }
            catch (Exception)
            {
                return false;
            }
        }
    }
}
