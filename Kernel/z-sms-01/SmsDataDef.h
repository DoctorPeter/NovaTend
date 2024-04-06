/****************************************************************

   Solution : NovaTend

   Project : z-sms-01.dll

   Module : SmsDataDef.h

   Description :  this module defines structure of
                  main sms containers

*****************************************************************/

#ifndef SMS_DATA_DEF_H
#define SMS_DATA_DEF_H


// Restriction definitions

// Phone number maximum length
#define PHONE_NUMBER_LEN			16

// SMS message maximum length
#define SMS_MESSAGE_MAX_LENGTH		1024

// Maximum length of time string
#define MESSAGE_TIME_LENGTH			24

// Maximum count of messages in list
#define MAX_SMS_COUNT				256

// Maximum count of messages in list
#define MAX_SMS_COUNT				256

// Maximum count of sms threads
#define MAX_THREADS_COUNT			256


// SMS message structure
typedef struct _smsMessage
{
	// Phone number of sender
	char fromPhoneNumber[PHONE_NUMBER_LEN];

	// Phone number of reciever
	char toPhoneNumber[PHONE_NUMBER_LEN];

	// Text of SMS
	char messageText[SMS_MESSAGE_MAX_LENGTH];

	// Time of SMS
	char messageTime[MESSAGE_TIME_LENGTH];

} SMS_MESSAGE, *PSMS_MESSAGE;


// SMS messages list structure
typedef struct _smsMassagesList
{
	// Size of list
	int size;

	// List items
	PSMS_MESSAGE messages[MAX_SMS_COUNT];

}SMS_MESSAGES_LIST, *PSMS_MESSAGES_LIST;


// SMS threads structure
typedef struct _smsMessageThreads
{
	// Count of threads
	int count;

	// List of SMS threads
	PSMS_MESSAGES_LIST threads[MAX_THREADS_COUNT];

} SMS_THREADS, *PSMS_THREADS;

#endif