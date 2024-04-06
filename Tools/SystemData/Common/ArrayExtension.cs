using System;
using System.Linq;

namespace SystemData.Common
{
    /// <summary>
    /// Extension methods for arrays
    /// </summary>
    public static class ArrayExtension
    {
        /// <summary>
        /// Extension method to convert array segment to array by Array.CopyTo()
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="arraySegment"></param>
        /// <returns></returns>
        public static T[] ToArray<T>(this ArraySegment<T> arraySegment)
        {
            try
            {
                T[] array = new T[arraySegment.Count];
                Array.Copy(arraySegment.Array, arraySegment.Offset, array, 0, arraySegment.Count);

                return array;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// Extension method to convert array of int to array of byte
        /// </summary>
        /// <param name="sourceArray"></param>
        /// <returns></returns>
        public static byte[] ToArray(this int[] sourceArray)
        {
            try
            {
                var res = new byte[sourceArray.Length * 4];

                for (int i = 0; i < sourceArray.Length; i++)
                    Array.Copy(BitConverter.GetBytes(sourceArray[i]), 0, res, i * 4, 4);

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// Extension method to convert array of byte to array of int
        /// </summary>
        /// <param name="sourceArray"></param>
        /// <returns></returns>
        public static int[] ToIntArray(this byte[] sourceArray)
        {
            try
            {
                var res = new int[sourceArray.Length / 4];

                for (int i = 0; i < sourceArray.Length; i += 4)

                    res[i / 4] = BitConverter.ToInt32(sourceArray, i);

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// Extension method to convert array of string to array of byte
        /// </summary>
        /// <param name="sourceArray"></param>
        /// <returns></returns>
        public static byte[] ToArray(this string[] sourceArray, int length = 0)
        {
            try
            {
                byte[] res = new byte[0];

                foreach (var item in sourceArray)
                {
                    var bytesStr = item.ToArray(length);
                    res = res.Concat(bytesStr).ToArray();
                }

                return res;
            }
            catch (Exception ex)
            {
                throw;
            }
        }

        /// <summary>
        /// special exstension method for serialization purposes
        /// Serialize string both as fixed size one byte per char null-teminated or first byte = size and then null terminated string
        /// </summary>
        /// <param name="param"></param>
        /// <param name="length"></param>
        /// <returns></returns>
        public static byte[] ToArray(this string param, int length = 0)
        {
            try
            {
                if (length != 0)
                {
                    var res = Array.CreateInstance(typeof(byte), length);
                    res.Initialize();

                    if (String.IsNullOrEmpty(param))
                        return (byte[])res;

                    var paramBytes = System.Text.Encoding.UTF8.GetBytes(param);

                    var validLength = length - 1;
                    if (paramBytes.Length <= length - 1)
                        validLength = paramBytes.Length;

                    Array.Copy(paramBytes, res, validLength);

                    //add null ermination at the end
                    Array.Copy(System.Text.Encoding.UTF8.GetBytes(new char[1] { Char.MinValue }), 0, res, length - 1, 1);

                    return (byte[])res;
                }
                else
                {
                    if (String.IsNullOrEmpty(param))
                        return BitConverter.GetBytes(1);

                    var res = new byte[param.Length + sizeof(int) + 1];
                    var paramBytes = System.Text.Encoding.UTF8.GetBytes(param);

                    Array.Copy(BitConverter.GetBytes(param.Length + 1), 0, res, 0, sizeof(int));
                    Array.Copy(paramBytes, 0, res, sizeof(int), paramBytes.Length);

                    //add null ermination at the end
                    Array.Copy(System.Text.Encoding.UTF8.GetBytes(new char[1] { Char.MinValue }), 0, res, res.Length - 1, 1);

                    return res;
                }
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// <summary>
        /// Prepare byte array for send to server (insert byte array representation of it's length to the begin)
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public static byte[] PrepareAsMessageToServer(this byte[] param)
        {
            if (param == null)
                throw new ArgumentNullException("param");

            byte[] res = new byte[param.Length + sizeof(int)];

            var lengthBytes = BitConverter.GetBytes(param.Length);

            Array.Copy(lengthBytes, 0, res, 0, sizeof(int));
            Array.Copy(param, 0, res, sizeof(int), param.Length);

            return res;
        }

        /// <summary>
        /// Prepare byte array for read from server (remove byte array representation of it's length in the begin)
        /// </summary>
        /// <param name="param"></param>
        /// <returns></returns>
        public static byte[] PrepareAsMessageFromServer(this byte[] param)
        {
            if (param == null)
                throw new ArgumentNullException("param");

            if (param.Length < 4)
                throw new ArgumentException("too small array to prepare");

            byte[] res = new byte[param.Length - sizeof(int)];
            byte[] lengthBytes = new byte[sizeof(int)];

            Array.Copy(param, 0, lengthBytes, 0, sizeof(int));

            if (BitConverter.ToInt32(lengthBytes, 0) != res.Length)
                throw new FormatException("format is corrupted (defined legth != actual length)");

            Array.Copy(param, sizeof(int), res, 0, res.Length);

            return res;
        }
    }
}
