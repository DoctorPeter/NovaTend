/****************************************************************

   Solution : NovaTend

   Project : z-content-01.dll

   Module : ContentDataDef.h

   Description :  this module defines structure of
                  main containers

*****************************************************************/

#ifndef CONTENT_DATA_DEF_H
#define CONTENT_DATA_DEF_H

// Screen object types definition

// User screen types ([0..255])

// Main user screen
#define SOT_MAIN_SCREEN							0

// Additional user sub screen
#define SOT_SUB_SCREEN							1

// Sub window for studying
#define SOT_STUDY_SCREEN						2

// Sub window for user notification
#define SOT_NOTIFICATION_SCREEN					3

// Sub window for legal disclaimer
#define SOT_LEGAL_DISCLAIMER_SCREEN				4

// Sub window for symbol boxes password
#define SOT_SYMBOL_BOXES_PWD_SCREEN				5

// Post login process main screen
#define SOT_POST_LOGIN_MAIN_SCREEN				6


// User screen objects ([256..511])

// Picture
#define SOT_IMAGE								256

// Lagre text (font size = 14)
#define SOT_LARGE_TEXT							257

// Small text (font size = 12)
#define SOT_SMALL_TEXT							258

// Big text block
#define SOT_BIG_TEXT_BLOCK						259

// Text box
#define SOT_TEXT_BOX							260

// Text box with password char *
#define SOT_PASSWORD_BOX						261

// Submit button
#define SOT_BUTTON								262

// Check box
#define SOT_CHECKBOX							263

// Combo box
#define SOT_COMBOBOX							264

// Command link
#define SOT_COMMAND_LINK						265

// Small text with current date and time
#define SOT_DATE_TIME_TEXT						266

// Text box for user name
#define SOT_USER_NAME_BOX						267

// Combo box for list of domain names
#define SOT_DOMAIN_NAME_BOX						268

// Lagre text for study questions
#define SOT_EDU_QUESTION_TEXT					269

// Combo box for study answers
#define SOT_EDU_ANSWER_BOX						270

// Small text for education
#define SOT_EDUCATION_LABEL						271

// Text block for lesson text
#define SOT_EDU_LESSON_TEXT						272

// Picture for lesson
#define SOT_EDU_LESSON_IMAGE					273

// Lagre text for legal disclaimer
#define SOT_LEGAL_DISCLAIMER_TEXT				274

// Picture for legal disclaimer
#define SOT_LEGAL_DISCLAIMER_IMAGE				275

// Small text for legal disclaimer
#define SOT_LEGAL_DISCLAIMER_LABEL				276

// Combo box for legal disclaimer
#define SOT_LEGAL_DISCLAIMER_COMBOBOX			277

// Large text for simple notification
#define SOT_SIMPLE_NOTICE_TEXT					278

// Large text for warning notification
#define SOT_WARNING_NOTICE_TEXT					279

// Password reset button
#define SOT_PASSWORD_RESET_BUTTON				280


// Screen objects scopes

// Screen object for logon screen
#define SO_SCOPE_LOGON_SCREEN					1

// Screen object for post login process
#define SO_SCOPE_POST_LOGIN_SCREEN				2

// Screen object for bith process
#define SO_SCOPE_BOTH							3


// Notification types definition

// Simple notification
#define NT_SIMPLE_NOTICE						1

// Simple notification
#define NT_WARNING_NOTICE						2

// Legal disclaimer
#define NT_LEGAL_DISCLAIMER						3




// Notification display types definition

// Show notice only once
#define NDT_SHOW_ONLY_ONCE						1

// Show notice one time per day
#define NDT_SHOW_ONCE_PER_DAY					2

// Always show notice
#define NDT_ALWAYS_SHOW							3



// Notification scopes definition

// Private notice
#define NS_PRIVATE								1

// Public notice
#define NS_PUBLIC								2



// Restrictions definition

// Maximum length of screen object name
#define NAME_LEN								256

// Maximum length of string object value
#define STR_VALUE_LEN							256

// Maximum length of string of date
#define DATE_STR_LEN							32

// Maximum length of BLOB value
#define BLOB_VALUE_LEN							262144

// Maximum size of list (combobox)
#define LIST_VALUES_SET_MAX_SIZE				32

// Maximum count of scren object for one screen
#define MAX_SCR_OBJ_COUNT						64

// Maximum count of user screens
#define MAX_SCREEN_COUNT						32

// Maximum count of users
#define MAX_USERS_COUNT							1024

// Maximum temporary buffer size
#define BUF_SIZE								32

// Maximum sql query text size
#define SQL_SIZE								1024

// Maximum count of password construction rules
#define MAX_PWD_CONSTR_RULES_COUNT				64

// Maximum size of security data
#define ENCRYPTED_DATA_SIZE						4096


// Password types

// Cascade string password
#define CASCADE_STRING_PWD						1

// Symbol box password (two symbols per cell)
#define TWO_SYMBOL_BOX_PWD						2

// Symbol box password (one symbol per cell)
#define ONE_SYMBOL_BOX_PWD						3



// Cascade string password rule range
#define CASCADE_STRING_PWD_MIN					1
#define CASCADE_STRING_PWD_MAX					10

// Symbol box rules range

// Joker 1
#define ONE_SYM_PWD_JOKER_1_MIN						127
#define ONE_SYM_PWD_JOKER_1_MAX						132

// Joker 2
#define ONE_SYM_PWD_JOKER_2_MIN						133
#define ONE_SYM_PWD_JOKER_2_MAX						138

// Formula
#define ONE_SYM_PWD_FORMULA_MIN						139
#define ONE_SYM_PWD_FORMULA_MAX						142

//One symbol location
#define ONE_SYM_PWD_SYMBOL_LOCATION_MIN				143
#define ONE_SYM_PWD_SYMBOL_LOCATION_MAX				150

// Joker 1
#define TWO_SYM_PWD_JOKER_1_MIN						101
#define TWO_SYM_PWD_JOKER_1_MAX						106

// Joker 2
#define TWO_SYM_PWD_JOKER_2_MIN						107
#define TWO_SYM_PWD_JOKER_2_MAX						112

// Formula
#define TWO_SYM_PWD_FORMULA_MIN						113
#define TWO_SYM_PWD_FORMULA_MAX						116

//Pair location
#define TWO_SYM_PWD_PAIR_LOCATION_MIN				117
#define TWO_SYM_PWD_PAIR_LOCATION_MAX				124

//Symbol location
#define TWO_SYM_PWD_SYMBOL_LOCATION_MIN				125
#define TWO_SYM_PWD_SYMBOL_LOCATION_MAX				126


// Pair location values
#define PAIR_LOCATION_UPPER_LEFT				0
#define PAIR_LOCATION_UPPER						1
#define PAIR_LOCATION_UPPER_RIGHT				2
#define PAIR_LOCATION_RIGHT						3
#define PAIR_LOCATION_LOWER_RIGHT				4
#define PAIR_LOCATION_LOWER						5
#define PAIR_LOCATION_LOWER_LEFT				6
#define PAIR_LOCATION_LEFT						7

//Symbol location values
#define SYMBOL_LOCATION_LEFT					0
#define SYMBOL_LOCATION_RIGHT					1
#define SYMBOL_LOCATION_UPPER_LEFT				2
#define SYMBOL_LOCATION_UPPER					3
#define SYMBOL_LOCATION_UPPER_RIGHT				4
#define SYMBOL_LOCATION_LOWER_LEFT				5
#define SYMBOL_LOCATION_LOWER					6
#define SYMBOL_LOCATION_LOWER_RIGHT				7


#pragma pack(push, 1)

// Structure of set of list values
typedef struct listValuesSet
{
	// Size of values set
	int valuesCount;

	// Values array
	char listValues[LIST_VALUES_SET_MAX_SIZE][STR_VALUE_LEN];

}LIST_VALUES_SET, *PLIST_VALUES_SET;

#pragma pack(pop)

#pragma pack(push, 1)

// Screen object structure
typedef struct screenObject
{
	// Screen object unique number
	int objID;

	// Screen object name
	char objName[NAME_LEN];

	// Screen object type ID
	int objTypeId;

	// Screen object scope
	int objScope;

	// Screen object name
	char objCaption[NAME_LEN];

	// Screen object position X
	int locationX;

	// Screen object position Y
	int locationY;

	// Screen object position X in percents
	int locationXPers;

	// Screen object position Y in percents
	int locationYPers;

	// Screen object width in pixels
	int widthPix;
	
	// Screen object height in pixels
	int heightPix;

	// Screen object width in percents
	int widthPers;
	
	// Screen object height in percents
	int heightPers;

	// Font size
	int fontSize;

	// Color of text
	unsigned int textColor;

	// Color of background
	unsigned int backgroundColor;

	// Object order values
	int order;

	// ID of right answer (for SOT_EDU_QUESTION_TEXT)
	int rightAnswerID;
	
	// ID of question (for SOT_EDU_QUESTION_TEXT)
	int questionID;

	// ID of lesson (for SOT_EDU_LESSON_TEXT)
	int lessonID;

	// Object string value
	char strValue[STR_VALUE_LEN];

	// Object text value size
	int textValueSize;

	// Object text value
	char * textValue;

	// Object image value size
	int imgValueSize;

	// Object image value
	void * imgValue;
	
	// Values set
    PLIST_VALUES_SET listValuesSet;

}SCREEN_OBJECT, *PSCREEN_OBJECT;

#pragma pack(pop)

#pragma pack(push, 1)

// Structure of user screen
typedef struct userScreen
{
	// Screen unique number
	int screenID;

	// Screen name
	char Name[NAME_LEN];

	// Screen object type
	int screenTypeID;

	// Screen scope
	int screenScope;

	// Screen caption
	char screenCaption[NAME_LEN];

	// Screen position X
	int locationX;

	// Screen position Y
	int locationY;

	// Screen position X in percents
	int locationXPers;

	// Screen position Y in percents
	int locationYPers;

	// Screen width in pixels
	int widthPix;
	
	// Screen height in pixels
	int heightPix;

	// Screen width in percents
	int widthPers;
	
	// Screen height in percents
	int heightPers;

	// Screen color
	unsigned int color;
	
	// Screen objects count
	int scrObjCount;

	// Screen objects array
	PSCREEN_OBJECT screenObjects[MAX_SCR_OBJ_COUNT];

} USER_SCREEN, *PUSER_SCREEN;

#pragma pack(pop)


#pragma pack(push, 1)

// Container of preset parameters
typedef struct presetContainer
{
	// Preset unique number
	int presetID;

	// Preset name
	char presetName[NAME_LEN];

	// User screens count
	int userScreensCount;

	// User screens list
    PUSER_SCREEN userScreens[MAX_SCREEN_COUNT];

}PRESET_CONTAINER, *PPRESET_CONTAINER;

#pragma pack(pop)

#pragma pack(push, 1)

// Structure of user descriptor
typedef struct userDescriptor
{
	// user ID
	int userID;

	// Encrypted name length
	int encNameLen;

	// Encrypted name 
	unsigned char encName[ENCRYPTED_DATA_SIZE];

	// Encrypted user name length
	int encUserNameLen;

	// Encrypted user name 
	unsigned char encUserName[ENCRYPTED_DATA_SIZE];
	
	// Account lock flag
	bool locked;

	// last log on date
	char lastLogOnDate[DATE_STR_LEN];

	// Study flag
	bool needStudy;

	// Question category
	int eduCategotyID;

	// Question random flag
	bool eduQuestionRandom;

	// Question category random flag
	bool randomEduCateg;

	// Type of password
	int pwdType;
	
	// Pawwsord reset flag
	bool pwdReseted;

	// Reset date
	char pwdResetDate[DATE_STR_LEN];

	// Reset period
	int pwdResetPeriod;

	// Reset password by email
	bool emailPwdReset;

	// Reset password by phone
	bool smsPwdReset;

	// Email length
	int encEmailAddressLen;

	// Email address
	unsigned char encEmailAddress[ENCRYPTED_DATA_SIZE];

	// Phone number length
	int encPhoneNumberLen;

	// Phone number
	unsigned char encPhoneNumber[ENCRYPTED_DATA_SIZE];
	
	// Password attempts count
	int pwdAttemptsCount;

	// Maximum password attempts count
	int maxPwdAttemptsCount;

}USER_DESCRIPTOR, *PUSER_DESCRIPTOR;

#pragma pack(pop)

#pragma pack(push, 1)

// Structure of user security data
typedef struct userSecurityData
{
	// user ID
	int userID;

	// Type of authentication system
	int authSystemID;

	// Encrypted system user name length
	int encSystemUserNameLen;

	// Encrypted system user name 
	unsigned char encSystemUserName[ENCRYPTED_DATA_SIZE];
	
	// Encrypted system password length
	int encSystemPasswordLen;

	// Encrypted system password value
	unsigned char encSystemPassword[ENCRYPTED_DATA_SIZE];

	// Password pass thru flag
	bool passThru;

	// last log on date
	char lastLogOnDate[DATE_STR_LEN];

	// User personal number
	int userToken;

	// User temporary token
	int tmpUserToken;
		
	// Type of password
	int pwdType;

	// Password construction rules count
	int pwdConstRulesCount;

	// Password construction rules list
	int pwdConstRules[MAX_PWD_CONSTR_RULES_COUNT];

	// Temp password construction rules count
	int tmpPwdConstRulesCount;

	// Temp password construction rules list
	int tmpPwdConstRules[MAX_PWD_CONSTR_RULES_COUNT];
	
}USER_SECURITY_DATA, *PUSER_SECURITY_DATA;

#pragma pack(pop)

#pragma pack(push, 1)

// Simple user descriptor structure
typedef struct simpleUserDescriptor
{
	// User ID
	int userID;

	// Encrypted user name length
	int encUserNameLen;

	// Encrypted user name 
	unsigned char encUserName[ENCRYPTED_DATA_SIZE];

}SIMPLE_USER_DESCRIPTOR, *PSIMPLE_USER_DESCRIPTOR;

#pragma pack(pop)


#pragma pack(push, 1)

// Structure of list of users
typedef struct userList
{
	// list size
	int usersCount;

	// List items
	PSIMPLE_USER_DESCRIPTOR users[MAX_USERS_COUNT];

}USER_LIST, *PUSER_LIST;

#pragma pack(pop)


// Maximum length of UTF8 char in bytes
#define UTF8_CODE_MAX_LENGTH		6

#pragma pack(push, 1)

// Structure of UTF8 char
typedef struct utf8Char
{
	// Bytes count
	int bytesCount;

	// Bytes of UTF8 char code
	char bytes[UTF8_CODE_MAX_LENGTH];

} UTF8_CHAR, * PUTF8_CHAR;

#pragma pack(pop)


#pragma pack(push, 1)

// Structure of UTF8 string
typedef struct utf8String
{
	// String length
	int length;

	// Chars
	PUTF8_CHAR chars[STR_VALUE_LEN];

}UTF8_STRING, *PUTF8_STRING;

#pragma pack(pop)


// Maximum size of symbol image table
#define UTF8_SYMBOL_MATRIX_MAX_SIZE		3

#pragma pack(push, 1)

// Symbol matrix structure
typedef struct utf8StringsMatrix
{
	// Square matrix size
	int size;

	// Symbols strings matrix
	PUTF8_STRING strings[UTF8_SYMBOL_MATRIX_MAX_SIZE][UTF8_SYMBOL_MATRIX_MAX_SIZE];

}UTF8_STRINGS_MATRIX, *PUTF8_STRINGS_MATRIX;

#pragma pack(pop)


// Maximum count of symbol boxes
#define MAX_SYMBOL_BOXES_COUNT		15

#pragma pack(push, 1)

// Symbol boxes list
typedef struct utf8StringsMatrixList
{
	// List length
	int size;
	
	// List items
	PUTF8_STRINGS_MATRIX matrixes[MAX_SYMBOL_BOXES_COUNT];

}UTF8_STRINGS_MATRIX_LIST, *PUTF8_STRINGS_MATRIX_LIST;

#pragma pack(pop)

#endif