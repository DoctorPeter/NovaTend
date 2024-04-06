/****************************************************************

   Solution : NovaTend

   Project : z-encryption-01.dll

   Module : Encryptor.h

   Description :  Defines the interface of class Encryptor

*****************************************************************/

#include <SystemBase.h>

#ifdef ZENCRYPTION01_EXPORTS
#define ENCRYPTOR_API __declspec(dllexport)
#else
#define ENCRYPTOR_API __declspec(dllimport)
#endif

#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

// Maximum length of key
#define MAX_KEY_LEN				256

// Maximum length of data buffer
#define MAX_DATA_BUFFER_LEN		65536

/****************************************************************

   Class : Encryptor

   Description : data encryption

*****************************************************************/
class ENCRYPTOR_API Encryptor : public SystemBase
{
	private:
		// Type of encryption algorithm
		unsigned int cryptAlgo;
		
		// Get place for key storage
		int GetKeyPlace(unsigned char first);

	public:
		// constructor
		Encryptor(unsigned long dllUserID);

		// destructor
		virtual ~Encryptor(void);

		// Init crypt lib
		void Init(void);

		// Unload crypt lib
		void Cleanup(void);

		// Generator of random numbers
		int RangedRand(int range_min, int range_max);

		// Encrypt data
		int Encrypt(unsigned char * key, int keyLen, unsigned char * sourceData, int sourceDataLen, unsigned char * encryptedData, int encryptedDataBufSize, int * encryptedDataLen);

		//Decrypt data
		int Decrypt(unsigned char * key, int keyLen, unsigned char * encryptedData, int encryptedDataLen, unsigned char * decryptedData, int decryptedDataBufSize, int * decryptedDataLen);

		// Generate key
		int GenerateKey(unsigned char * key, int keyBufSizeLen, int * keyLen);

		// Hashing of data buffer
		int Hash(unsigned char * buffer, int buffSize, unsigned char * hashBuffer, int hashBufferSize, int * hashLength);

		// Pack encrypted data and key
		int PackSecurityData(unsigned char * encryptedData, int endcryptedDataLen, unsigned char * key, int keyLen, unsigned char * packedData, int packedDataSize, int * packedDataLen);

		// Unpack encrypted data and key
		int UnPackSecurityData(unsigned char * packedData, int packedDataLen, unsigned char * encryptedData, int encryptedDataSize, int * endcryptedDataLen, unsigned char * key, int keySize, int * keyLen);

		// Generate key, encrypt data and pack it
		int EncryptAndPackSecurityData(unsigned char * sourceData, int sourceDataLen, unsigned char * packedData, int packedDataSize, int * packedDataLen);

		// Unpack data and decrypt it
		int UnPackAndDecryptSecurityData(unsigned char * packedData, int packedDataLen, unsigned char * decryptedData, int decryptedDataBufSize, int * decryptedDataLen);

		// Convert binary data to hex string
		bool BinToHexStr(unsigned char * binaryData, int binaryDataLen, char * hexStr, int hexStrSize);
};

#endif