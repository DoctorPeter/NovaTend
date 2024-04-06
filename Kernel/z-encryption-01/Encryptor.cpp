/****************************************************************

   Solution : NovaTend

   Project : z-encryption-01.dll

   Module : Encryptor.cpp

   Description :  implements the methods of class Encryptor

*****************************************************************/

#include "stdafx.h"

#include "Encryptor.h"
#include <crypt.h>

// z-encryption-01.dll definition structure
extern DLL_COMMON_DEFINITION zEncryptionDllDefinition;


/****************************************************************

   Class : Encryptor

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user

*****************************************************************/
Encryptor :: Encryptor(unsigned long dllUserID) : SystemBase(dllUserID, &zEncryptionDllDefinition)
{
	// Initialize cryptLib instance
	//cryptInit();

	// Set encryption algorithm
	cryptAlgo = CRYPT_ALGO_AES;
}

/****************************************************************

   Class : Encryptor

   Method : Destructor

*****************************************************************/
Encryptor :: ~Encryptor(void)
{
	// Cleanup cryptLib instance
	//cryptEnd();
}


/****************************************************************

   Class : Encryptor

   Method : Init

   Description : Init crypt lib

*****************************************************************/
void Encryptor :: Init(void)
{
	cryptInit();
}

/****************************************************************

   Class : Encryptor

   Method : Cleanup

   Description : Unload crypt lib

*****************************************************************/
void Encryptor :: Cleanup(void)
{
	cryptEnd();
}


/****************************************************************

   Class : Encryptor

   Method : RangedRand

   Parameters :
			Input : 
				range_min - left bound
				range_max - right bound
	
	Return: random number

	Description : Generator of random numbers

*****************************************************************/
int Encryptor :: RangedRand(int range_min, int range_max)
{
	return (int)((double)Rand() / (MAX_RAND_VALUE + 1) * (range_max - range_min) + range_min);
}

/****************************************************************

   Class : Encryptor

   Method : Encrypt

   Parameters :
			Input : 
				key - encryption key
				keyLen - encryption key lenght
				sourceData - source data
				sourceDataLen - source data length
				encryptedDataBufSize - size of buffer for encrypted data
			Output:
				encryptedData - encrypted data buffer
				encryptedDataLen - encrypted data lenght

	Return: error code

	Description : Encrypt data

*****************************************************************/
int Encryptor :: Encrypt(unsigned char * key, int keyLen, unsigned char * sourceData, int sourceDataLen, unsigned char * encryptedData, int encryptedDataBufSize, int * encryptedDataLen)
{
	unsigned char keyHash[16];
	int hashLen = 0;

	// Hashing of the encryption key
	int status = Hash(key, keyLen, keyHash, 16, &hashLen);
	
	if (cryptStatusError(status) || hashLen != 16) 
		return CRYPT_ERROR_FAILED;

	CRYPT_ENVELOPE cryptEnvelope;
	CRYPT_CONTEXT cryptContext;
	
	int bytesCopied;
	
	// Create envelope

	status = cryptCreateEnvelope(&cryptEnvelope, CRYPT_UNUSED, CRYPT_FORMAT_CRYPTLIB);
	if (cryptStatusError(status)) return status;

	// Create encryption context
	status = cryptCreateContext(&cryptContext, CRYPT_UNUSED, (CRYPT_ALGO_TYPE)cryptAlgo); 
	if (cryptStatusError(status)) 
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Add encryption key (hash-code)
	status = cryptSetAttributeString(cryptContext, CRYPT_CTXINFO_KEY, keyHash, hashLen);
	if (cryptStatusError(status)) 
	{
		cryptDestroyEnvelope(cryptEnvelope);
		cryptDestroyContext(cryptContext);
		return status;
	}

	// Create the session key context and add it 
	status = cryptSetAttribute(cryptEnvelope, CRYPT_ENVINFO_SESSIONKEY, cryptContext);
	if (cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		cryptDestroyContext(cryptContext);
		return status;
	}
	
	// Delete encryption context
	cryptDestroyContext(cryptContext);
		
	// Add the data size information
	status = cryptSetAttribute(cryptEnvelope, CRYPT_ENVINFO_DATASIZE, sourceDataLen);
	if (cryptStatusError(status)) 
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}
	
	// Push data to the envelope
	status = cryptPushData(cryptEnvelope, sourceData, sourceDataLen, &bytesCopied);
	if ((status != CRYPT_ERROR_OVERFLOW) && 
		(status != CRYPT_ERROR_UNDERFLOW) && 
		(status != CRYPT_ENVELOPE_RESOURCE) &&
		(cryptStatusError(status) || (bytesCopied != sourceDataLen)))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return CRYPT_ERROR_FAILED;
	}

	// Flush data
	status = cryptFlushData(cryptEnvelope);
	if (cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Pop processed data from the envelope
	status = cryptPopData(cryptEnvelope, encryptedData, encryptedDataBufSize, encryptedDataLen);
	if ((status != CRYPT_ERROR_OVERFLOW) && 
		(status != CRYPT_ERROR_UNDERFLOW) && 
		(status != CRYPT_ENVELOPE_RESOURCE) &&
		 cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Delete envelope
	cryptDestroyEnvelope(cryptEnvelope);
	
	return status;
}

/****************************************************************

   Class : Encryptor

   Method :  Decrypt

   Parameters :
			Input : 
				key - encryption key
				keyLen - encryption key lenght
				encryptedData - encrypted data
				encryptedDataLen - encrypted data length
				decryptedDataBufSize - size of buffer for decrypted data
			Output:
				decryptedData - decrypted data buffer
				decryptedDataLen - decrypted data lenght

	Return: error code

	Description :  Decrypt data

*****************************************************************/
int Encryptor :: Decrypt(unsigned char * key, int keyLen, unsigned char * encryptedData, int encryptedDataLen, unsigned char * decryptedData, int decryptedDataBufSize, int * decryptedDataLen)
{
	unsigned char keyHash[16];
	int hashLen = 0;
	
	// Hashing of the encryption key
	int status = Hash(key, keyLen, keyHash, 16, &hashLen);
	
	if (cryptStatusError(status) || hashLen != 16) 
		return CRYPT_ERROR_FAILED;

	CRYPT_ENVELOPE cryptEnvelope;
    CRYPT_CONTEXT cryptContext;
    int bytesCopied;

	// Create envelope
	status = cryptCreateEnvelope(&cryptEnvelope, CRYPT_UNUSED, CRYPT_FORMAT_AUTO);
	if (cryptStatusError(status)) return status;

	// Push encrypted data
	status = cryptPushData(cryptEnvelope, encryptedData, encryptedDataLen, &bytesCopied);
	if ((status != CRYPT_ERROR_OVERFLOW) && 
		(status != CRYPT_ERROR_UNDERFLOW) && 
		(status != CRYPT_ENVELOPE_RESOURCE) &&
		cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Create encryption context
	status = cryptCreateContext(&cryptContext, CRYPT_UNUSED, (CRYPT_ALGO_TYPE)cryptAlgo);
	if (cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Add encryption key
	status = cryptSetAttributeString(cryptContext, CRYPT_CTXINFO_KEY, keyHash, hashLen);
	if (cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		cryptDestroyContext(cryptContext);
		return status;
	}

	// Add session key
	status = cryptSetAttribute(cryptEnvelope, CRYPT_ENVINFO_SESSIONKEY, cryptContext);
	if (cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		cryptDestroyContext(cryptContext);
		return status;
	}

	// Delete context
	cryptDestroyContext(cryptContext);
	
	// Flush data
	status = cryptFlushData(cryptEnvelope);
	if (cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Pop decrypted data
	status = cryptPopData(cryptEnvelope, decryptedData, decryptedDataBufSize, decryptedDataLen);
	if ((status != CRYPT_ERROR_OVERFLOW) && 
		(status != CRYPT_ERROR_UNDERFLOW) && 
		(status != CRYPT_ENVELOPE_RESOURCE) &&
		cryptStatusError(status))
	{
		cryptDestroyEnvelope(cryptEnvelope);
		return status;
	}

	// Delete envelope
	cryptDestroyEnvelope(cryptEnvelope);

	return status;
}

/****************************************************************

   Class : Encryptor

   Method :  GenerateKey

   Parameters :
			Input : 
				keyBufSizeLen - size of key buffer
			Output:
				key - key buffer
				keyLen - length of the key

	Return: error code

	Description :  Generate encryption key

*****************************************************************/
int Encryptor :: GenerateKey(unsigned char * key, int keyBufSizeLen, int * keyLen)
{
	// Check input data
	if ((key) && (keyBufSizeLen > 0))
	{
		// Generate random key length
		int len = RangedRand(16, 255);
		
		// Check result
		if (len > keyBufSizeLen) len = keyBufSizeLen;

		// Fill key buffer
		for(int i = 0; i < len; i++)
			key[i] = (unsigned char)RangedRand(0, 255);
		
		// Return key length
		*keyLen = len;

		return CRYPT_OK;
	}
	else
		return CRYPT_ERROR_FAILED;
}

/****************************************************************

   Class : Encryptor

   Method :  Hash

   Parameters :
			Input : 
				buffer - data buffer
				buffSize - data buffer size
				hashBufferSize - hash buffer size
			Output:
				hashBuffer - hash buffer
				hashLength - length of the hash buffer

	Return: error code

	Description :  Hashing of data buffer

*****************************************************************/
int Encryptor :: Hash(unsigned char * buffer, int buffSize, unsigned char * hashBuffer, int hashBufferSize, int * hashLength)
{
	CRYPT_CONTEXT hashContext;

	// Check hash buffer size
	if (hashBufferSize < 16)
		return CRYPT_ERROR_FAILED;

	// Create context
	int status = cryptCreateContext(&hashContext, CRYPT_UNUSED, CRYPT_ALGO_MD5);
	if (cryptStatusError(status)) return status;

	// Start of buffer hashing
	status = cryptEncrypt(hashContext, buffer, buffSize);
	if (cryptStatusError(status)) 
	{
		cryptDestroyContext(hashContext);
		return status;
	}

	// End of buffer hashing
	status = cryptEncrypt(hashContext, buffer, 0);
	if (cryptStatusError(status)) 
	{
		cryptDestroyContext(hashContext);
		return status;
	}

	// Get hash value
	status = cryptGetAttributeString(hashContext, CRYPT_CTXINFO_HASHVALUE, hashBuffer, hashLength);
	if (cryptStatusError(status)) 
	{
		cryptDestroyContext(hashContext);
		return status;
	}
	
	// Delete context
	cryptDestroyContext(hashContext);

	return status;
}

/****************************************************************

   Class : Encryptor

   Method :  GetKeyPlace

   Parameters :
			Input : 
				first - defined byte

   Return: place index

   Description :  Get place for key storage

*****************************************************************/
int Encryptor :: GetKeyPlace(unsigned char first)
{
	return first % 4 + 2;
}

/****************************************************************

   Class : Encryptor

   Method :  PackSecurityData

   Parameters :
			Input : 
				encryptedData - encrypted data
				endcryptedDataLen - encrypted data length
				key - encryption key
				keyLen - encryption key length
				packedDataSize - size of buffer for packed data
			Output:
				packedData - packed data buffer
				packedDataLen - packed data buffer length

	Return: error code

	Description :  Pack encrypted data and key

*****************************************************************/
int Encryptor :: PackSecurityData(unsigned char * encryptedData, int endcryptedDataLen, unsigned char * key, int keyLen, unsigned char * packedData, int packedDataSize, int * packedDataLen)
{
	// Check input data

	if ((!encryptedData) || (!key) || (!packedData))
		return CRYPT_ERROR_FAILED;

	if ((endcryptedDataLen <= 0) || (keyLen <= 0) || (packedDataSize <= 0))
		return CRYPT_ERROR_FAILED;

	if (packedDataSize < (endcryptedDataLen + keyLen + 1))
		return CRYPT_ERROR_FAILED;

	// Get place for key storage
	int keyPlace = GetKeyPlace(encryptedData[0]);
	int encryptedDataCounter = 0;
	int keyCounter = 0;
	
	// Save key length
	packedData[0] = (unsigned char)keyLen;
	int packedDataCounter = 1;

	// Joining of encrypted data and encryption key
	while ((keyCounter < keyLen) || (encryptedDataCounter < endcryptedDataLen))
	{
		if (packedDataCounter % keyPlace == 0)
		{
			if (keyCounter < keyLen)
				packedData[packedDataCounter++] = key[keyCounter++];
			else
				if (encryptedDataCounter < endcryptedDataLen)
					packedData[packedDataCounter++] = encryptedData[encryptedDataCounter++];
		}
		else
			if (encryptedDataCounter < endcryptedDataLen)
				packedData[packedDataCounter++] = encryptedData[encryptedDataCounter++];
			else
				if (keyCounter < keyLen)
					packedData[packedDataCounter++] = key[keyCounter++];
	}

	// Return length of packed data
	*packedDataLen = endcryptedDataLen + keyLen + 1;

	return CRYPT_OK;
}

/****************************************************************

   Class : Encryptor

   Method :  UnPackSecurityData

   Parameters :
			Input : 
				packedData - packed data buffer
				packedDataLen - packed data buffer length
				encryptedDataSize - size of the encrypted data buffer
				keySize  - size of the key buffer
			Output:
				encryptedData - encrypted data
				endcryptedDataLen - encrypted data length
				key - encryption key
				keyLen - encryption key length

	Return: error code

	Description :  Unpack encrypted data and key

*****************************************************************/
int Encryptor :: UnPackSecurityData(unsigned char * packedData, int packedDataLen, unsigned char * encryptedData, int encryptedDataSize, int * endcryptedDataLen, unsigned char * key, int keySize, int * keyLen)
{
	// Check input data

	if ((!encryptedData) || (!key) || (!packedData))
		return CRYPT_ERROR_FAILED;

	if ((encryptedDataSize <= 0) || (keySize <= 0) || (packedDataLen <= 0))
		return CRYPT_ERROR_FAILED;

	if ((encryptedDataSize + keySize) < packedDataLen - 1)
		return CRYPT_ERROR_FAILED;

	// Get key length
	int kLen = 	packedData[0];
	
	// Check key length
	if (keySize < kLen)
		return CRYPT_ERROR_FAILED;

	// Get encrypted data length
	int dLen = packedDataLen - kLen - 1;

	// Check encrypted data length
	if (encryptedDataSize < dLen)
		return CRYPT_ERROR_FAILED;

	// Get place of key storage
	int keyPlace = GetKeyPlace(packedData[1]);
	int packedDataCounter = 1;
	int encryptedDataCounter = 0;
	int keyCounter = 0;

	// Retrieve key and encrypted data from package
	while ((packedDataCounter < packedDataLen) && ((keyCounter < kLen) || (encryptedDataCounter < dLen)))
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

	// Return encrypted data length
	*endcryptedDataLen = encryptedDataCounter;

	// Return key length
	*keyLen = keyCounter;

	return CRYPT_OK;
}


/****************************************************************

   Class : Encryptor

   Method :  EncryptAndPackSecurityData

   Parameters :
			Input : 
				sourceData - source data buffer
				sourceDataLen - source data buffer length
				packedDataSize - size of the packed data buffer
			Output:
				packedData - packed data buffer
				packedDataLen - packed data buffer length

	Return: error code

	Description :  Generate key, encrypt data and pack it

*****************************************************************/
int Encryptor :: EncryptAndPackSecurityData(unsigned char * sourceData, int sourceDataLen, unsigned char * packedData, int packedDataSize, int * packedDataLen)
{
	unsigned char key[MAX_KEY_LEN];
	int keyLen;
	
	// Generate key
	int status = GenerateKey(key, MAX_KEY_LEN, &keyLen);
	if (status != CRYPT_OK) return CRYPT_ERROR_FAILED;

	unsigned char encryptedData[MAX_DATA_BUFFER_LEN];
	int encryptedDataLen;
	
	// Encrypt source data
	status = Encrypt(key, keyLen, sourceData, sourceDataLen, encryptedData, MAX_DATA_BUFFER_LEN, &encryptedDataLen);
	if (status != CRYPT_OK) return CRYPT_ERROR_FAILED;

	// Pack encrypted data and key
	status = PackSecurityData(encryptedData, encryptedDataLen, key, keyLen, packedData, packedDataSize, packedDataLen);
	if (status != CRYPT_OK) return CRYPT_ERROR_FAILED;

	return CRYPT_OK;
}

/****************************************************************

   Class : Encryptor

   Method :  UnPackAndDecryptSecurityData

   Parameters :
			Input : 
				packedData - packed data buffer
				packedDataLen - packed data buffer length
				decryptedDataBufSize - size of buffer for decrypted data
			Output:
				decryptedData - decrypted data buffer
				decryptedDataLen - decrypted data lenght

	Return: error code

	Description :  Unpack data and decrypt it

*****************************************************************/
int Encryptor :: UnPackAndDecryptSecurityData(unsigned char * packedData, int packedDataLen, unsigned char * decryptedData, int decryptedDataBufSize, int * decryptedDataLen)
{
	unsigned char encryptedData[MAX_DATA_BUFFER_LEN];
	int encryptedDataLen;

	unsigned char key[MAX_KEY_LEN];
	int keyLen;

	// Unpack encrypted data and key
	int status = UnPackSecurityData(packedData, packedDataLen, encryptedData, MAX_DATA_BUFFER_LEN, &encryptedDataLen, key, MAX_KEY_LEN, &keyLen);
	if (status != CRYPT_OK) return CRYPT_ERROR_FAILED;

	// Decrypt data
	status = Decrypt(key, keyLen, encryptedData, encryptedDataLen, decryptedData, decryptedDataBufSize, decryptedDataLen);
	if (status != CRYPT_OK) return CRYPT_ERROR_FAILED;

	return CRYPT_OK;
}


/****************************************************************

   Class : Encryptor

   Method : BinToHexStr

   Parameters :
			Input : 
				binaryData - binary data buffer
				binaryDataLen - binary data length
			Output:
				hexStr - output string
				hexStrSize - output string size

	Return : error code

	Description : Convert binary data to hex string

*****************************************************************/
bool Encryptor :: BinToHexStr(unsigned char * binaryData, int binaryDataLen, char * hexStr, int hexStrSize)
{
	// Check input data
	if ((!binaryData) || 
		(!hexStr) || 
		(binaryDataLen <= 0) || 
		(hexStrSize <= 0) || 
		(hexStrSize < (binaryDataLen * 2 + 2)))
			return false;

	strcpy(hexStr, "0x");
	char * result = hexStr + 2;

	char * hexNumbers = "0123456789ABCDEF";
	for (int i = 0; i < binaryDataLen; i++)
    {
		result[i * 2 + 0] = hexNumbers[(binaryData[i] >> 4) & 0x0F];
		result[i * 2 + 1] = hexNumbers[(binaryData[i]     ) & 0x0F];
    }  

	hexStr[binaryDataLen * 2 + 2] = 0;

	//// Convert binary to hex form string
	//char hexByteStr[5];
	//strcpy(hexStr, "0x");
	//for (int i = 0; i < binaryDataLen; i++)
	//{
	//	sprintf(hexByteStr, "%02X", binaryData[i]);
	//	strcat(hexStr, hexByteStr);
	//}

	return true;
}