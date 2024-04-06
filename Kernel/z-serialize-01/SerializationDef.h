/****************************************************************

   Solution : NovaTend

   Project : z-serialize-01.dll

   Module : SerializationDef.h

   Description : this module defines stucture
				 of respond/request buffers

*****************************************************************/
#include <time.h>
#include <ContentDataDef.h>

#ifndef SERIALIZATION_DEF_H
#define SERIALIZATION_DEF_H

// Error codes

// Error of data serialization
#define SERIALIZE_DATA_ERROR						-1

// Successfull data serialization
#define SERIALIZE_DATA_SUCCESS						1



// Serialize data restrictions

// Maximum count of command parameters
#define MAX_CMD_PARAMS_COUNT						32

// Maximum lenght of client name
#define MAX_CLIENT_NAME_LEN							64

// Maximum lenght of server name
#define MAX_SERVER_NAME_LEN							64

// Maximum count of clients in list
#define MAX_CLIENT_DESCRIPTION_COUNT				1024

// Maximum count of servers in list
#define MAX_SERVER_DESCRIPTION_COUNT				1024

// Maximum count of command parameters
#define MAX_PARAMETERS_COUNT						64

// Maximum size of command parameters value
#define MAX_PARAMETER_SIZE							10485760


// Commands data types

// Input data
#define INPUT_CMD_DATA								1

// Output data
#define RETURN_CMD_DATA								2


// Request data
#define REQUEST_CMD									1

// Response data
#define RESPONSE_CMD								2


// Wrong data
#define WRONG_DATA									0

// One byte
#define BYTE_DATA									1

// Word (2 bytes)
#define WORD_DATA									2

// Double word (4 bytes)
#define DWORD_DATA									3

// Long number (8 bytes)
#define LONG_DATA									4

// Binary block
#define BINARY_DATA									5

// String
#define STRING_DATA									6

// Encrypted data
#define ENCRYPTED_DATA								7

// Client description
#define CLIENT_DESCRIPTION_DATA						8

// Client description list
#define CLIENT_DESCRIPTION_LIST_DATA				9

// Server description
#define SERVER_DESCRIPTION_DATA						10

// Server description list
#define SERVER_DESCRIPTION_LIST_DATA				11

// Preset container
#define PRESET_CONTAINER_DATA						12

// User list
#define USER_LIST_DATA								13

// User descriptor
#define USER_DESCRIPTOR_DATA						14

// Authentication container
#define AUTH_CONTAINER_DATA							15

// Answer container
#define ANSWER_CONTAINER_DATA						16

// Time info
#define TIMEINFO_DATA								17

// Symbol boxes list
#define SYMBOL_BOXES_DATA							18

// User security data
#define USER_PRIVATE_DATA							19

// User DB access info
#define USER_DB_ACCESS_DATA							20

// Enviroment info container structure
#define ENVIROMENT_INFO_CONTAINER_DATA				21

// Controlled program list container structure
#define CTRL_PRG_INFO_LIST_DATA						22

// Geo location data
#define GEO_LOCATION_DATA							23

// Command history container structure
#define CMD_HIST_CONTAINER_DATA						24

// File info container
#define FILE_INFO_CONTAINER_DATA					25

// Folder info container
#define FOLDER_INFO_CONTAINER_DATA					26


// Commands types

// Empty command
#define CMD_EMPTY									0

// Connect
#define CMD_CONNECT									1

// Disconnect
#define CMD_DISCONNECT								2

// Check license
#define CMD_CHECK_LICENSE							3

// Get content
#define CMD_GET_CONTENT								4

// Get user list container
#define CMD_GET_USER_LIST							5

// Get user list container
#define CMD_GET_USER_DESCRIPTOR						6

// Check access possibility
#define CMD_CHECK_ACCESS							7

// Validate user params
#define CMD_VALIDATE_PARAMS							8

// Validate education data
#define CMD_VALIDATE_ANSWERS						9

// Validate user custom passwords
#define CMD_VALIDATE_USER_CUSTOM_PASSWORDS			10

// Set user signin date
#define CMD_SET_USER_SIGNIN_DATE					11

// Save user notification history
#define CMD_SAVE_NOTIFICATION_HISTORY				12

// Get DB access
#define CMD_GET_DB_ACCESS							13

// Get authentication system
#define CMD_GET_AUTH_SYSTEM							14

// Check sign in date
#define CMD_CHECK_SIGN_IN_DATE						15

// Validate user account and create new if needed
#define CMD_VALIDATE_USER_ACCOUNT					16

// Reset user password
#define CMD_RESET_USER_PASSWORD						17

// Lock actions on CTRL + ALT + DEL
#define CMD_LOCK_USER_CAD_ACTIONS					18

// Create back connection
#define CMD_CREATE_BACK_CONNECTION					19

// Get HUB-servers list
#define CMD_GET_HUB_SERVERS_LIST					20

// Get screenshot
#define CMD_GET_CLIENT_SCREEN_SHOT					21

// Get snapshot
#define CMD_GET_CLIENT_CAM_SNAPSHOT					22

// Get user enviroment info
#define CMD_GET_USER_ENV_INFO						23

// Get client machine hardware info
#define CMD_GET_HARDWARE_INFO						24

// Get ID user logged on user
#define CMD_GET_LOGGED_USER_NAME					25

// Get computer name
#define CMD_GET_COMPUTER_NAME						26

// Get user info and auth sys info
#define CMD_GET_AUTH_SYS_USER_INFO					27

// Get full client info
#define CMD_GET_FULL_CLIENT_INFO					28

// Check schedule records
#define CMD_CHECK_SCHEDULE							29

// Check programs
#define CMD_CHECK_PROGRAMS							30

// Get geo location
#define CMD_GET_GEO_LOCATION						31

// File transer
#define CMD_FILE_TRANSFER							32

// Get command history
#define CMD_GET_CMD_HISTORY							33


// User database access permissions

// System admininstrator
#define DB_ACCESS_SYS_ADMIN							1

// Screen designer
#define DB_ACCESS_SCREEN_DESIGNER					2

// Education manager
#define DB_ACCESS_EDU_MANAGER						3

// Notification manager
#define DB_ACCESS_NOTICE_MANAGER					4

// License manager
#define DB_ACCESS_LICENSE_MANAGER					5

// Dashboard manager
#define DASHBOARD_ACCESS_MANAGER					6

// Schedule manager
#define SCHEDULE_MANAGER							7


// Maximum permisions count
#define MAX_PERMISSIONS_COUNT						32


#pragma pack(push, 1)

// Cleint description structure
typedef struct clientDescription
{
	// Client ID
	unsigned int clientID;

	// Client ID
	unsigned int ownClientID;

	// Type of client
	int clientType;
	
	// OS version
	int osVersion;

	// Private IP
	char privateIP[16];

	// Private port
	unsigned int privatePort;

	// Public IP
	char publicIP[16];

	// Public port
	unsigned int publicPort;

	// Software version
	int version;

	// Client name
	char clientName[MAX_CLIENT_NAME_LEN];

} CLIENT_DESCRIPTION, *PCLIENT_DESCRIPTION;

#pragma pack(pop)

#pragma pack(push, 1)

// Server description structure
typedef struct serverDescription
{
	// Server ID
	unsigned int serverID;

	// Type of server
	int serverType;

	// Priority of server
	int serverPriority;
	
	// IP
	char ipAddress[16];

	// Port
	unsigned int port;

	// Server name
	char serverName[MAX_SERVER_NAME_LEN];

} SERVER_DESCRIPTION, *PSERVER_DESCRIPTION;

#pragma pack(pop)

#pragma pack(push, 1)

// Cleint description list structure
typedef struct clientDescriptionList
{
	// Count of clients
	int clientsCount;

	// Clients array
	PCLIENT_DESCRIPTION clientsList[MAX_CLIENT_DESCRIPTION_COUNT];

} CLIENT_DESCRIPTION_LIST, *PCLIENT_DESCRIPTION_LIST;

#pragma pack(pop)

#pragma pack(push, 1)

// Server description list structure
typedef struct serverDescriptionList
{
	// Count of servers
	int serversCount;

	// Server array
	PSERVER_DESCRIPTION serversList[MAX_SERVER_DESCRIPTION_COUNT];

} SERVER_DESCRIPTION_LIST, *PSERVER_DESCRIPTION_LIST;

#pragma pack(pop)

#pragma pack(push, 1)

// User database access information structure
typedef struct userDBAccessInfo
{
	// Encrypted DB server name
	unsigned char dbServerName[ENCRYPTED_DATA_SIZE];

	// DB server name length
	int dbServerNameLen;

	// Encrypted DB name
	unsigned char dbName[ENCRYPTED_DATA_SIZE];

	// DB name length
	int dbNameLen;

	// Encrypted DB user name
	unsigned char dbUserName[ENCRYPTED_DATA_SIZE];

	// DB user name length
	int dbUserNameLen;

	// Encrypted DB password
	unsigned char dbPassword[ENCRYPTED_DATA_SIZE];

	// DB password length
	int dbPasswordLen;
	
	// Count of user permissions
	int userPermissionsCount;

	// User permissions list
	int userPermissions[MAX_PERMISSIONS_COUNT];

} USER_DB_ACCESS_INFO, *PUSER_DB_ACCESS_INFO;

#pragma pack(pop)

#define MAX_PROGRAMS_COUNT		256

#pragma pack(push, 1)

// Enviroment info container structure
typedef struct enviromentInfoContainer 
{
	// Name of foreground window
	char activeProgramName[NAME_LEN];

	// User downtime value
	int userDowntime;

	// Count of programs
	int programNamesListCount;

	// List of program names
	char programNamesList[MAX_PROGRAMS_COUNT][NAME_LEN];

} ENVIROMENT_INFO_CONTAINER, *PENVIROMENT_INFO_CONTAINER;

#pragma pack(pop)

#pragma pack(push, 1)

// Controlled programm info container
typedef struct controlledProgramInfoContainer 
{
	// Process ID
	int pid;

	// Allow flag
	bool allowed;

	// Module name
	char moduleName[NAME_LEN];

	// Program name (window name)
	char programName[NAME_LEN];

}CONTROL_PROGRAM_INFO_CONTAINER, *PCONTROL_PROGRAM_INFO_CONTAINER;

#pragma pack(pop)

// Programs list
#define MAX_PROGRAMS_LIST		1024

#pragma pack(push, 1)

// Controlled programm info container list
typedef struct controlledProgramInfoContainerList 
{
	// List size
	int programListSize;

	// Program list
	PCONTROL_PROGRAM_INFO_CONTAINER programList[MAX_PROGRAMS_LIST];

}CONTROL_PROGRAM_INFO_CONTAINER_LIST, *PCONTROL_PROGRAM_INFO_CONTAINER_LIST;

#pragma pack(pop)

#pragma pack(push, 1)

// Geo location data
typedef struct geoLocationCoords 
{
	// Latitude
	double latitude;

	// Longtitude
	double longitude;

}GEO_LOCATION_COORDS, *PGEO_LOCATION_COORDS;

#pragma pack(pop)

#pragma pack(push, 1)

// Command history item
typedef struct cmdHistoryItem 
{
	// Command ID
	int cmdID;

	// User ID
	int userID;

	// Execute time
	char execTime[DATE_STR_LEN];

}CMD_HISTORY_ITEM, *PCMD_HISTORY_ITEM;

#pragma pack(pop)

// Maximum count of command history list
#define MAX_CMD_HIST_SIZE		32768

#pragma pack(push, 1)

// Command history structure
typedef struct cmdHistoryContainer 
{
	// List size
	int size;

	// History items
	PCMD_HISTORY_ITEM historyItems[MAX_CMD_HIST_SIZE];

}CMD_HISTORY, *PCMD_HISTORY;

#pragma pack(pop)

#pragma pack(push, 1)

// File description container
typedef struct fileInfoContainer 
{
	// File name
	char fileName[NAME_LEN];

	// Time of last update
	struct tm updateTime;

	// Dize
	long long fileSize;

	// Dir flag
	bool isDir;

}FILE_INFO_CONTAINER, *PFILE_INFO_CONTAINER;

#pragma pack(pop)

// Maximum count of files in directory
#define MAX_DIR_FILES_COUNT			4096

#pragma pack(push, 1)

// Folder description container
typedef struct folderInfoContainer 
{
	// Dir name
	char dirName[NAME_LEN];

	// Count of files
	int filesCount;

	// Files list
	PFILE_INFO_CONTAINER filesList[MAX_DIR_FILES_COUNT];

}FOLDER_INFO_CONTAINER, *PFOLDER_INFO_CONTAINER;

#pragma pack(pop)

#pragma pack(push, 1)

// Command header structure
typedef struct commandHeader
{
	// command type (command code)
	unsigned int commandCode;

	// command type (request/response)
	unsigned int commandType;

	// ID of message sender
	unsigned int senderID;

	// ID of message recipient
	unsigned int recipientID;

} COMMAND_HEADER, *PCOMMAND_HEADER;

#pragma pack(pop)

#pragma pack(push, 1)

// Structute of command parameter
typedef struct commandParameter
{
	// Type of command parameter
	int paramType;

	// Type of parameter data
	int paramDataType;
	
	// Size of data buffer
	unsigned int dataBufferSize;

	// Data buffer
	char * dataBuffer;

} COMMAND_PARAMETER, *PCOMMAND_PARAMETER;

#pragma pack(pop)

#pragma pack(push, 1)

// Structute of command parameter list
typedef struct commandParameterList
{
	// Count of parameters
	int paramCount;

	// List of parameters
	PCOMMAND_PARAMETER paramList[MAX_PARAMETERS_COUNT];

} COMMAND_PARAMETER_LIST, *PCOMMAND_PARAMETER_LIST;

#pragma pack(pop)

#pragma pack(push, 1)

// Structute of command request/response
typedef struct commandRequestResponse
{
  // Command header
  PCOMMAND_HEADER header;

  // Command parameters list
  PCOMMAND_PARAMETER_LIST parameters;

} COMMAND_REQUEST_RESPONSE, *PCOMMAND_REQUEST_RESPONSE;

#pragma pack(pop)

#endif