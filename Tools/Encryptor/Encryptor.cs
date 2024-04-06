/// <summary>
///   Solution : NovaTend
///   Project : Encryptor.dll
///   Module : Encryptor.cs
///   Description :  implements the methods of class Encryptor
/// </summary>

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

// CryptLib using
using cryptlib;

namespace Encryption
{
    /// <summary>
    /// Data encryption
    /// </summary>
    public class Encryptor
    {
        #region private

        // Maximum length of data buffer
        private int MAX_DATA_BUFFER_LEN = 65536;

        // Maximum length of key
        private int MAX_KEY_LEN = 256;

        // Type of encryption algorithm
        private int cryptAlgo;

        // Generator of random numbers
        private Random randGen;

        /// <summary>
        ///  Get place for key storage
        /// </summary>
        /// <param name="first"> defined byte </param>
        /// <returns> place index </returns>
        private int GetKeyPlace(byte first)
        {
            return first % 4 + 2;
        }

        #endregion

        #region public

        /// <summary>
        ///  Constructor
        /// </summary>
        public Encryptor()
        {
            cryptAlgo = crypt.ALGO_AES;
            randGen = new Random();
        }

        /// <summary>
        ///  Load crypt lib
        /// </summary>
        public void Init()
        {
            crypt.Init();
        }

        /// <summary>
        ///  Unload crypt lib
        /// </summary>
        public void Cleanup()
        {
            crypt.End();
        }


        /// <summary>
        ///  Encrypt data
        /// </summary>
        /// <param name="key"> encryption key </param>
        /// <param name="sourceData"> source data </param>
        /// <param name="encryptedData"> encrypted data buffer </param>
        /// <returns> encrypted data size </returns>
		public int Encrypt(byte[] key, byte[] sourceData, ref byte[] encryptedData)
        {
	        byte [] keyHash = null;
            
            // Hashing of the encryption key
            int hashLen = Hash(key, ref keyHash);
                   
            if ((sourceData == null) || (hashLen != 16))
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }

            int cryptEnvelope = 0;
            int cryptContext = 0;
            int encryptedDataLen = 0;

            try
            {
                // Create envelope
                cryptEnvelope = crypt.CreateEnvelope(crypt.UNUSED, crypt.FORMAT_CRYPTLIB);

                // Create encryption context
                cryptContext = crypt.CreateContext(crypt.UNUSED, cryptAlgo);
            
                // Add encryption key (hash-code)
                crypt.SetAttributeString(cryptContext, crypt.CTXINFO_KEY, keyHash, 0, hashLen);

                // Create the session key context and add it 
                crypt.SetAttribute(cryptEnvelope, crypt.ENVINFO_SESSIONKEY, cryptContext);
            
                // Add the data size information
                crypt.SetAttribute(cryptEnvelope, crypt.ENVINFO_DATASIZE, sourceData.Length);

                try
                {
                    // Push data to the envelope
                    crypt.PushData(cryptEnvelope, sourceData);
                }
                catch (CryptException e)
                {
                    if  (!((e.Status == crypt.ERROR_OVERFLOW) ||
                        (e.Status == crypt.ERROR_UNDERFLOW) ||
                        (e.Status == crypt.ENVELOPE_RESOURCE)))
                    {
                        throw new CryptException(crypt.ERROR_FAILED);
                    }
                }

                // Flush data
                crypt.FlushData(cryptEnvelope);

                // Pop processed data from the envelope

                try
                {
                    byte[] tmpData = new byte[MAX_DATA_BUFFER_LEN];
                    
                    // Pop encrypted data
                    encryptedDataLen = crypt.PopData(cryptEnvelope, tmpData, 0, tmpData.Length);

                    encryptedData = new byte[encryptedDataLen];
                    Array.Copy(tmpData, encryptedData, encryptedDataLen);
                }
                catch (CryptException e)
                {
                    if (!((e.Status == crypt.ERROR_OVERFLOW) ||
                        (e.Status == crypt.ERROR_UNDERFLOW) ||
                        (e.Status == crypt.ENVELOPE_RESOURCE)))
                    {
                        throw new CryptException(crypt.ERROR_FAILED);
                    }
                }

            }
            finally
            {
                try
                {
                    // Delete envelope
                    crypt.DestroyEnvelope(cryptEnvelope);
                    crypt.DestroyContext(cryptContext);
                }
                catch (CryptException)
                {
                    encryptedDataLen = 0;
                }
            }

            return encryptedDataLen;
        }

        /// <summary>
        ///  Decrypt data
        /// </summary>
        /// <param name="key"> encryption key </param>
        /// <param name="encryptedData"> encrypted data </param>
        /// <param name="decryptedData"> decrupted data buffer </param>
        /// <returns> decrypted data size </returns>
        public int Decrypt(byte[] key, byte[] encryptedData, ref byte[] decryptedData)
        {
            byte [] keyHash = null;
            // Hashing of the encryption key
            int hashLen = Hash(key, ref keyHash);

            if ((encryptedData == null) || (hashLen != 16))
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }
            
            int cryptEnvelope = 0;
            int cryptContext = 0;
            int decryptedDataLen = 0;

            try
            {
                // Create envelope
                cryptEnvelope = crypt.CreateEnvelope(crypt.UNUSED, crypt.FORMAT_AUTO);

                try
                {
                    // Push encrypted data
                    crypt.PushData(cryptEnvelope, encryptedData);
                }
                catch (CryptException e)
                {
                    if (!((e.Status == crypt.ERROR_OVERFLOW) ||
                        (e.Status == crypt.ERROR_UNDERFLOW) ||
                        (e.Status == crypt.ENVELOPE_RESOURCE)))
                    {
                        throw new CryptException(crypt.ERROR_FAILED);
                    }
                }

                // Create encryption context
                cryptContext = crypt.CreateContext(crypt.UNUSED, cryptAlgo);

                // Add encryption key
                crypt.SetAttributeString(cryptContext, crypt.CTXINFO_KEY, keyHash, 0, hashLen);

                // Add sesion key
                crypt.SetAttribute(cryptEnvelope, crypt.ENVINFO_SESSIONKEY, cryptContext);
                               
                // Flush data
                crypt.FlushData(cryptEnvelope);

                try
                {
                    byte[] tmpData = new byte[MAX_DATA_BUFFER_LEN];

                    // Pop decrypted data
                    decryptedDataLen = crypt.PopData(cryptEnvelope, tmpData, 0, tmpData.Length);

                    decryptedData = new byte[decryptedDataLen];
                    Array.Copy(tmpData, decryptedData, decryptedDataLen);
                }
                catch (CryptException e)
                {
                    if (!((e.Status == crypt.ERROR_OVERFLOW) ||
                        (e.Status == crypt.ERROR_UNDERFLOW) ||
                        (e.Status == crypt.ENVELOPE_RESOURCE)))
                    {
                        throw new CryptException(crypt.ERROR_FAILED);
                    }
                }
            }
            finally
            {
                try
                {
                    // Delete envelope
                    crypt.DestroyEnvelope(cryptEnvelope);
                    crypt.DestroyContext(cryptContext);
                }
                catch (CryptException)
                {
                    decryptedDataLen = 0;
                }
            }

            return decryptedDataLen;
        }

        /// <summary>
        ///  Generate key
        /// </summary>
        /// <param name="key"> encryption key </param>
        /// <returns> key size </returns>
        public int GenerateKey(ref byte[] key)
        {
            // Generate random key length
            int len = randGen.Next(16, MAX_KEY_LEN - 1);

            key = new byte[len];

            // Fill key buffer
            for (int i = 0; i < len; i++)
               key[i] = (byte)randGen.Next(0, 255);

            return len;
        }

        /// <summary>
        ///  Hashing of data buffer
        /// </summary>
        /// <param name="buffer"> source buffer </param>
        /// <param name="hashBuffer"> hash buffer </param>
        /// <returns> hash code size </returns>
        public int Hash(byte[] buffer, ref byte[] hashBuffer)
        {
            // Check input data
            if (buffer == null)
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }

            hashBuffer = new byte[16];
            int hashLength = 0;

            int hashContext = 0;

            try
            {
                // Create context
                hashContext = crypt.CreateContext(crypt.UNUSED, crypt.ALGO_MD5);

                // Start of buffer hashing
                crypt.Encrypt(hashContext, buffer, 0, buffer.Length);

                // End of buffer hashing
                crypt.Encrypt(hashContext, buffer, 0, 0);

                // Get hash value
                hashLength = crypt.GetAttributeString(hashContext, crypt.CTXINFO_HASHVALUE, hashBuffer);
            }
            finally
            {
                // Delete context
                try
                {
                    crypt.DestroyContext(hashContext);
                }
                catch (CryptException)
                {
                    hashLength = 0;
                }
            }

            return hashLength;
        }


        /// <summary>
        ///  Pack encrypted data and key
        /// </summary>
        /// <param name="encryptedData"> encrypted data </param>
        /// <param name="key"> encryption key </param>
        /// <param name="packedData"> packed data buffer </param>
        /// <returns> package size </returns>
        public int PackSecurityData(byte[] encryptedData, byte[] key, ref byte[] packedData)
        {
            // Check input data
            if ((encryptedData == null) || (key == null))
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }
            
            packedData = new byte [encryptedData.Length + key.Length + 1];

	        // Get place for key storage
	        int keyPlace = GetKeyPlace(encryptedData[0]);
	        int encryptedDataCounter = 0;
	        int keyCounter = 0;
	
	        // Save key length
	        packedData[0] = (byte)key.Length;
	        int packedDataCounter = 1;

	        // Joining of encrypted data and encryption key
	        while ((keyCounter < key.Length) || (encryptedDataCounter < encryptedData.Length))
	        {
		        if (packedDataCounter % keyPlace == 0)
		        {
			        if (keyCounter < key.Length)
				        packedData[packedDataCounter++] = key[keyCounter++];
			        else
				        if (encryptedDataCounter < encryptedData.Length)
					        packedData[packedDataCounter++] = encryptedData[encryptedDataCounter++];
		        }
		        else
			        if (encryptedDataCounter < encryptedData.Length)
				        packedData[packedDataCounter++] = encryptedData[encryptedDataCounter++];
			        else
				        if (keyCounter < key.Length)
					        packedData[packedDataCounter++] = key[keyCounter++];
	        }

	        // Return length of packed data
	        return packedData.Length;
        }

        /// <summary>
        ///  Unpack encrypted data and key
        /// </summary>
        /// <param name="packedData"> packed data </param>
        /// <param name="encryptedData"> encrypted data </param>
        /// <param name="key"> encryption key </param>
        /// <returns> encrypted data size </returns>                
        public int UnPackSecurityData(byte[] packedData, ref byte[] encryptedData, ref byte[] key)
        {
            // Check input data
            if (packedData == null)
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }

            // Get key length
            int kLen = packedData[0];

            key = new byte[kLen];
                        
            // Get encrypted data length
            int dLen = packedData.Length - kLen - 1;

            if (dLen <= 0)
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }

            encryptedData = new byte[dLen];

            // Get place of key storage
            int keyPlace = GetKeyPlace(packedData[1]);
            int packedDataCounter = 1;
            int encryptedDataCounter = 0;
            int keyCounter = 0;

            // Retrieve key and encrypted data from package
            while ((packedDataCounter < packedData.Length) && ((keyCounter < kLen) || (encryptedDataCounter < dLen)))
            {
                if (packedDataCounter % keyPlace == 0)
                {
                    if (keyCounter < kLen)
                        key[keyCounter++] = packedData[packedDataCounter++];
                    else
                        if (encryptedDataCounter < dLen)
                            encryptedData[encryptedDataCounter++] = packedData[packedDataCounter++];
                }
                else
                    if (encryptedDataCounter < dLen)
                        encryptedData[encryptedDataCounter++] = packedData[packedDataCounter++];
                    else
                        if (keyCounter < kLen)
                            key[keyCounter++] = packedData[packedDataCounter++];
            }

            return encryptedData.Length;
        }

        /// <summary>
        ///  Generate key, encrypt data and pack it
        /// </summary>
        /// <param name="sourceData"> source data </param>
        /// <param name="packedData"> packed data </param>
        /// <returns> packed data size </returns> 
        public int EncryptAndPackSecurityData(byte[] sourceData, ref byte[] packedData)
        {
            // Check input data
            if (sourceData == null)
            {
                throw new CryptException(crypt.ERROR_FAILED);
            }            

            byte [] key = null;
	
	        // Generate key
	        GenerateKey(ref key);
    
	        // Encrypt source data
            byte [] encryptedData = null;
            Encrypt(key, sourceData, ref encryptedData);
		    
            // Pack encrypted data and key
	        return PackSecurityData(encryptedData, key, ref packedData);
        }

        /// <summary>
        ///  Unpack data and decrypt it
        /// </summary>
        /// <param name="packedData"> packed data </param>
        /// <param name="decryptedData"> decrypted data </param>
        /// <returns> decrypted data size </returns> 
        public int UnPackAndDecryptSecurityData(byte[] packedData, ref byte[] decryptedData)
        {
            // Unpack encrypted data and key
            byte [] encryptedData = null;
            byte [] key = null;
            UnPackSecurityData(packedData, ref encryptedData, ref key);
            
            // Decrypt data
	        return Decrypt(key, encryptedData, ref decryptedData);
        }

        /// <summary>
        /// Encrypt string
        /// </summary>
        /// <param name="str">Input string</param>
        /// <returns>Encrypted data. Array of bytes</returns>
        public byte[] EncryptString(string str)
        {
            try
            {
                byte[] decData = System.Text.Encoding.ASCII.GetBytes(str);
                byte[] encData = null;
                EncryptAndPackSecurityData(decData, ref encData);
                return encData;
            }
            catch
            {
                return null;
            }
        }

        /// <summary>
        /// Decrypt string
        /// </summary>
        /// <param name="bytes">Input array of bytes</param>
        /// <returns>Decrypted string</returns>
        public string DecryptString(byte[] bytes)
        {
            try
            {
                byte[] encData = bytes;
                byte[] decData = null;
                UnPackAndDecryptSecurityData(encData, ref decData);
                return System.Text.Encoding.ASCII.GetString(decData);
            }
            catch
            {
                return String.Empty;
            }
        }

        #endregion
    }
}
