/****************************************************************

   Solution : NovaTend

   Project : z-serialize-01.dll

   Module : SerializationManager.h

   Description : this module defines interface of
				  class SerializationManager

*****************************************************************/

#include <ContentDataDef.h>
#include <ValidationDataDef.h>
#include <ScreenDataDef.h>
#include <LogWriter.h>
#include <time.h>

#include "SerializationDef.h"

#ifdef ZSERIALIZE01_EXPORTS
#define SERIALIZATIONMANAGER_API __declspec(dllexport)
#else
#define SERIALIZATIONMANAGER_API __declspec(dllimport)
#endif

#ifndef SERIALIZATIONMANAGER_H
#define SERIALIZATIONMANAGER_H

/****************************************************************

   Class : SerializationManager 

   Description : responsible for data serialization and creation
                 of the request/response messages that are passed
				 between the server and the client

*****************************************************************/
class SERIALIZATIONMANAGER_API SerializationManager : public SystemBase
{
	protected:

		// Log writer instance
		LogWriter * logWriter;

		// Write message to log-file
		int  WriteToLog(char * message);

	public:

		// Constructor
		SerializationManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~SerializationManager(void);



		// Create command header
		PCOMMAND_HEADER CreateCommandHeader(void);

		// Create command header
		PCOMMAND_HEADER CreateCommandHeader(int commandCode, int commandType, unsigned int senderID, unsigned int recipientID);

		// Delete command header
		PCOMMAND_HEADER DeleteCommandHeader(PCOMMAND_HEADER header);



		// Create command parameter
		PCOMMAND_PARAMETER CreateCommandParameter(void);

		// Create command parameter
		PCOMMAND_PARAMETER CreateCommandParameter(int paramType, int paramDataType, int dataBufferSize);

		// Delete command parameter
		PCOMMAND_PARAMETER DeleteCommandParameter(PCOMMAND_PARAMETER param);

		// Get size of command parameter
		int GetCommandParameterSize(PCOMMAND_PARAMETER param);



		// Create command parameter list
		PCOMMAND_PARAMETER_LIST CreateCommandParameterList(void);

		// Create command parameter list
		PCOMMAND_PARAMETER_LIST CreateCommandParameterList(int size);

		// Delete command parameter
		PCOMMAND_PARAMETER_LIST DeleteCommandParameterList(PCOMMAND_PARAMETER_LIST cmdParameterList);

		// Get size of command parameter list
		int GetCommandParameterListSize(PCOMMAND_PARAMETER_LIST cmdParameterList);

		

		// Create request/response structure
		PCOMMAND_REQUEST_RESPONSE CreateRequestResponse(void);

		// Create request/response structure
		PCOMMAND_REQUEST_RESPONSE CreateRequestResponse(int commandType, int commandDataType, unsigned int senderID, unsigned int recipientID);

		// Delete request/response structure
		PCOMMAND_REQUEST_RESPONSE DeleteRequestResponse(PCOMMAND_REQUEST_RESPONSE cmdReqResp);

		// Get command request/response size
		int GetCommandRequestResponseSize(PCOMMAND_REQUEST_RESPONSE cmdReqResp);

		// Pack command request/response
		char * PackCommandRequestResponse(PCOMMAND_REQUEST_RESPONSE cmdReqResp, int * packageSize);

		// Unpack command request/response
		PCOMMAND_REQUEST_RESPONSE UnpackCommandRequestResponse(char * package, int packageSize);



		// Pack one byte value
		PCOMMAND_PARAMETER PackByte(unsigned char value, int paramType);

		// Unpack one byte value
		unsigned char UnpackByte(PCOMMAND_PARAMETER param);

		
		// Pack word value
		PCOMMAND_PARAMETER PackWORD(short value, int paramType);

		// Unpack word value
		short UnpackWORD(PCOMMAND_PARAMETER param);


		// Pack double word value
		PCOMMAND_PARAMETER PackDWORD(int value, int paramType);

		// Unpack double word value
		int UnpackDWORD(PCOMMAND_PARAMETER param);



		// Pack long value
		PCOMMAND_PARAMETER PackLong(long long value, int paramType);

		// Unpack long value
		long long UnpackLong(PCOMMAND_PARAMETER param);



		// Pack binary block value
		PCOMMAND_PARAMETER PackBinary(unsigned char * value, int size, int paramType);

		// Unpack binary block value
		unsigned char * UnpackBinary(PCOMMAND_PARAMETER param, int * size);



		// Pack string value
		PCOMMAND_PARAMETER PackString(char * value, int paramType);

		// Unpack string value
		int UnpackString(PCOMMAND_PARAMETER param, char * value);



		// Pack encrypted value
		PCOMMAND_PARAMETER PackEncrypted(unsigned char * value, int size, int paramType);

		// Unpack encrypted value
		unsigned char * UnpackEncrypted(PCOMMAND_PARAMETER param, int * size);



		// Pack client description value
		PCOMMAND_PARAMETER PackClientDescription(PCLIENT_DESCRIPTION value, int paramType);

		// Unpack client description value
		PCLIENT_DESCRIPTION UnpackClientDescription(PCOMMAND_PARAMETER param);

		

		// Pack server description value
		PCOMMAND_PARAMETER PackServerDescription(PSERVER_DESCRIPTION value, int paramType);

		// Unpack server description value
		PSERVER_DESCRIPTION UnpackServerDescription(PCOMMAND_PARAMETER param);



		// Pack client description list value
		PCOMMAND_PARAMETER PackClientDescriptionList(PCLIENT_DESCRIPTION_LIST value, int paramType);

		// Unpack client description value
		PCLIENT_DESCRIPTION_LIST UnpackClientDescriptionList(PCOMMAND_PARAMETER param);



		// Pack server description list value
		PCOMMAND_PARAMETER PackServerDescriptionList(PSERVER_DESCRIPTION_LIST value, int paramType);

		// Unpack server description value
		PSERVER_DESCRIPTION_LIST UnpackServerDescriptionList(PCOMMAND_PARAMETER param);



		// Pack preset container value
		PCOMMAND_PARAMETER PackPresetContainer(PPRESET_CONTAINER value, int paramType);

		// Unpack preset container value
		PPRESET_CONTAINER UnpackPresetContainer(PCOMMAND_PARAMETER param);

		// Get user content size
		int GetUserContentSize(PPRESET_CONTAINER content);



		// Pack user list value
		PCOMMAND_PARAMETER PackUserList(PUSER_LIST value, int paramType);

		// Unpack user list value
		PUSER_LIST UnpackUserList(PCOMMAND_PARAMETER param);

		// Pack simple user descriptor
		char * PackSimpleUserDescriptor(char * lstParam, PSIMPLE_USER_DESCRIPTOR pUser);

		// Unpack simple user descriptor
		PSIMPLE_USER_DESCRIPTOR UnPackSimpleUserDescriptor(char * lstParam);

		// Get simple descriptor size
		int GetSimpleUserDescriptorSize(PSIMPLE_USER_DESCRIPTOR pUser);

		// Get user descriptor size
		int GetUserListContainerSize(PUSER_LIST userList);

		

		// Pack user descriptor value
		PCOMMAND_PARAMETER PackUserDescriptor(PUSER_DESCRIPTOR value, int paramType);

		// Unpack user descriptor value
		PUSER_DESCRIPTOR UnpackUserDescriptor(PCOMMAND_PARAMETER param);

		// Get size of user descriptor
		int GetUserDescriptorSize(PUSER_DESCRIPTOR pUser);



		// Pack authenticate container value
		PCOMMAND_PARAMETER PackAuthContainer(PAUTH_CONTAINER value, int paramType);

		// Unpack authenticate container value
		PAUTH_CONTAINER UnpackAuthContainer(PCOMMAND_PARAMETER param);

		// Get size of authenticate container
		int GetAuthContainerSize(PAUTH_CONTAINER authContainer);



		// Pack answer container value
		PCOMMAND_PARAMETER PackAnswerContainer(PANSWER_CONTAINER value, int paramType);

		// Unpack answer container value
		PANSWER_CONTAINER UnpackAnswerContainer(PCOMMAND_PARAMETER param);

		// Get size of answer container
		int GetAnswerContainerSize(PANSWER_CONTAINER eduContainer);



		// Pack timeinfo value
		PCOMMAND_PARAMETER PackTimeinfo(tm * value, int paramType);

		// Unpack timeinfo value
		tm * UnpackTimeinfo(PCOMMAND_PARAMETER param);



		// Pack symbol boxes value
		PCOMMAND_PARAMETER PackSymbolBoxesList(PUTF8_STRINGS_MATRIX_LIST value, int paramType);

		// Unpack symbol boxes value
		PUTF8_STRINGS_MATRIX_LIST UnpackSymbolBoxesList(PCOMMAND_PARAMETER param);

		// Get symbol boxes list size
		int GetSymbolMatrixesListSize(PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);



		// Pack user security value
		PCOMMAND_PARAMETER PackUserSecurity(PUSER_SECURITY_DATA value, int paramType);

		// Unpack user security value
		PUSER_SECURITY_DATA UnpackUserSecurity(PCOMMAND_PARAMETER param);

		// Get size of user security data container
		int GetSecurityDataContainerSize(PUSER_SECURITY_DATA pSecurityData);



		// Pack user DB access info value
		PCOMMAND_PARAMETER PackUserDBAccessInfo(PUSER_DB_ACCESS_INFO value, int paramType);

		// Unpack user DB access info value
		PUSER_DB_ACCESS_INFO UnpackUserDBAccessInfo(PCOMMAND_PARAMETER param);

		// Get size of DB access info container
		int GetDBAccessInfoSize(PUSER_DB_ACCESS_INFO dbAccessInfo);



		// Pack enviroment info container structure
		PCOMMAND_PARAMETER PackEnviromentInfoContainer(PENVIROMENT_INFO_CONTAINER value, int paramType);

		// Unpack enviroment info container structure
		PENVIROMENT_INFO_CONTAINER UnpackEnviromentInfoContainer(PCOMMAND_PARAMETER param);

		// Get size of enviroment info container structure
		int GetEnviromentInfoContainerSize(PENVIROMENT_INFO_CONTAINER envContainer);
		


		// Pack controlled program list container structure
		PCOMMAND_PARAMETER PackControlledProgramListContainer(PCONTROL_PROGRAM_INFO_CONTAINER_LIST value, int paramType);

		// Unpack controlled program list container structure
		PCONTROL_PROGRAM_INFO_CONTAINER_LIST UnpackControlledProgramListContainer(PCOMMAND_PARAMETER param);

		// Get size of controlled program list container structure
		int GetControlledProgramListContainerSize(PCONTROL_PROGRAM_INFO_CONTAINER_LIST prgLstContainer);



		// Pack geo location data
		PCOMMAND_PARAMETER PackGeoLocationDataContainer(PGEO_LOCATION_COORDS value, int paramType);

		// Unpack geo location data
		PGEO_LOCATION_COORDS UnpackGeoLocationDataContainer(PCOMMAND_PARAMETER param);
		


		// Pack command history container structure
		PCOMMAND_PARAMETER PackCommandHistoryContainer(PCMD_HISTORY value, int paramType);

		// Unpack command history container structure
		PCMD_HISTORY UnpackCommandHistoryContainer(PCOMMAND_PARAMETER param);

		// Get size of command history container structure
		int GetCommandHistoryContainerSize(PCMD_HISTORY pHistoryCnt);



		// Pack file info container structure
		PCOMMAND_PARAMETER PackFileInfoContainer(PFILE_INFO_CONTAINER value, int paramType);

		// Unpack file info container structure
		PFILE_INFO_CONTAINER UnpackFileInfoContainer(PCOMMAND_PARAMETER param);

		// Get size of file info container structure
		int GetFileInfoContainerSize(PFILE_INFO_CONTAINER pFileInfoContainer);



		// Pack folder info container structure
		PCOMMAND_PARAMETER PackFolderInfoContainer(PFOLDER_INFO_CONTAINER value, int paramType);

		// Unpack folder info container structure
		PFOLDER_INFO_CONTAINER UnpackFolderInfoContainer(PCOMMAND_PARAMETER param);

		// Get size of folder info container structure
		int GetFolderInfoContainerSize(PFOLDER_INFO_CONTAINER pFolderInfoContainer);
		


		// Check command buffer
		int CheckCommand(char * package, unsigned int commandCode);

		// Check command buffer
		int CheckCommand(char * package, unsigned int commandCode, unsigned int commandType);

		// Check command buffer
		int CheckCommand(PCOMMAND_REQUEST_RESPONSE cmdReqResp, unsigned int commandCode);

		// Check command buffer
		int CheckCommand(PCOMMAND_REQUEST_RESPONSE cmdReqResp, unsigned int commandCode, unsigned int commandType);

		// Get command type
		unsigned int GetCommandCode(char * package);

		// Get command type
		unsigned int GetCommandCode(PCOMMAND_REQUEST_RESPONSE cmdReqResp);


		
		// Serialize connect request
		char * ConnectBufferPack(unsigned int clientID, PSERVER_DESCRIPTION serverDescr, int *packageSize);

		// Serialize connect response
		char * ConnectBufferPack(unsigned int serverID, PCLIENT_DESCRIPTION clientDescription, int *packageSize);

		// Deserialize connect response buffer 
		unsigned int ConnectInBufferUnpack(char * package, int packageSize, PSERVER_DESCRIPTION serverDecrs);

		// Deserialize connect response buffer 
		PCLIENT_DESCRIPTION ConnectRetBufferUnpack(char * package, int packageSize);


		// Serialize connect to request
		char * ConnectToReqBufferPack(unsigned int clientID, unsigned int gServerID, unsigned int serverID, int serverType, int *packageSize);

		// Serialize connect to request
		char * ConnectToReqBufferPack(unsigned int serverID, unsigned int clientID, char * ipAddress, unsigned int port, int *packageSize);

		// Serialize connect to response
		char * ConnectToRetBufferPack(unsigned int serverID, unsigned int clientID, char * ipAddress, unsigned int port, int *packageSize);

		// Deserialize connect to request
		int ConnectToReqBufferUnpack(char * package, int packageSize, int * serverID, int * serverType);

		// Deserialize connect to request
		int ConnectToReqBufferUnpack(char * package, int packageSize, char * ipAddress, unsigned int * port);

		// Deserialize connect to response
		int ConnectToRetBufferUnpack(char * package, int packageSize, char * ipAddress, unsigned int * port);


		
		// Serialize disconnect request/response
		char * DisconnectBufferPack(int commandType, unsigned int senderID, unsigned int recipientID, int *packageSize);

		// Deserialize disconnect response buffer 
		int DisconnectInBufferUnpack(int commandType, char * package, int packageSize, int * senderID, int * recipientID);

		
		// Serialize empty command
		char * EmptyCommandBufferPack(int *packageSize, unsigned int senderID, unsigned int recipientID);
};

#endif
