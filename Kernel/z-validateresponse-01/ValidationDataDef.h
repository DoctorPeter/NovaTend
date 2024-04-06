/****************************************************************

   Solution : NovaTend

   Project : z-validateresponse-01.dll

   Module : ValidationDataDef.h

   Description :  this module defines structure of
				  validation containers

*****************************************************************/

#include <ContentDataDef.h>


#ifndef VALIDATION_DATA_DEF_H
#define VALIDATION_DATA_DEF_H


// Error codes

// Succesful authentication container creation
#define AUTH_CNT_CREATION_OK	1

// Error of authentication container creation
#define AUTH_CNT_CREATION_BAD	0


// Succesful answer container creation
#define ANS_CNT_CREATION_OK		1

// Error of answer container creation
#define ANS_CNT_CREATION_BAD	0


// Successful response validation
#define RESPONSE_OK						0

// Fail response validation
#define RESPONSE_BAD					-1

// Password expired
#define RESPONSE_PWD_EXPIRED			-2

// Account locked
#define RESPONSE_ACCOUNT_LOCKED			-3


// User not found
#define RESET_PWD_USER_NOT_FOUND		-4

// User password already resetted
#define RESET_PWD_ALREADY_RESETTED		-5

// Wrong user email address
#define RESET_PWD_WRONG_EMAIL_ADDRESS	-6

// Wrong user phone number
#define RESET_PWD_WRONG_PHONE_NUMBER	-7

// Email sending error
#define RESET_PWD_EMAIL_SEND_ERROR		-8

// SMS sending error
#define RESET_PWD_SMS_SEND_ERROR		-9


// Structure of authenticate
// container item

#pragma pack(push, 1)

typedef struct authElement
{
	// validation parameter ID
	int objectID; 

	// validation parameter type
	int objectTypeID;

	// validation parameter name
	unsigned char objectName[ENCRYPTED_DATA_SIZE];

	// validation parameter name length
	int objectNameLen;

	// validation parameter value
	unsigned char objectValue[ENCRYPTED_DATA_SIZE];

	// validation parameter value length
	int objectValueLen;

} AUTH_ELEMENT, *PAUTH_ELEMENT;

#pragma pack(pop)

#pragma pack(push, 1)

// Structure of authentication container
typedef struct authContainer
{
	// Container size
	int authElementCount;

	// List of container items
	PAUTH_ELEMENT authElements[MAX_SCR_OBJ_COUNT];

} AUTH_CONTAINER, *PAUTH_CONTAINER;

#pragma pack(pop)

#pragma pack(push, 1)

// Structure of user anwser descriptor
typedef struct answerDescriptor
{
	// Answer text
	char answerValue[STR_VALUE_LEN];

	// Right answer ID
	int rightAnswerID;

	// Question ID
	int questionID;

} ANSWER_DESCRIPTOR, *PANSWER_DESCRIPTOR;

#pragma pack(pop)

#pragma pack(push, 1)

// Structure of answer container
typedef struct answerContainer
{
	// count of user answers
	int answersCount;

	// list of answers
	PANSWER_DESCRIPTOR answers[MAX_SCR_OBJ_COUNT];

}ANSWER_CONTAINER, *PANSWER_CONTAINER;

#pragma pack(pop)

#endif