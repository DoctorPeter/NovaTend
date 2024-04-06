/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : ResetUserPwdCommand.cpp

   Description :  this module implements methods of
				  class ResetUserPwdCommand

*****************************************************************/

#include "stdafx.h"
#include "ResetUserPwdCommand.h"
#include <ResponseValidator.h>
#include <SmtpClient.h>
#include <GoogleVoiceSMSManager.h>
#include <SettingsManager.h>

// z-hostcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zHostCmdDllDefinition;
 
/****************************************************************

   Class : ResetUserPwdCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				
*****************************************************************/
ResetUserPwdCommand :: ResetUserPwdCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ResetUserPwdCommand : constructor");
	#endif

	licenseManager = new LicenseManager(zHostCmdDllDefinition.dllID, logWriter);
}

/****************************************************************

   Class : ResetUserPwdCommand

   Method : Destructor

*****************************************************************/
ResetUserPwdCommand :: ~ResetUserPwdCommand(void)
{
	delete licenseManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ResetUserPwdCommand : destructor");
	#endif
}

/****************************************************************

   Class : ResetUserPwdCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST ResetUserPwdCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ResetUserPwdCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((parameters) &&
		(parameters -> paramCount == 1) &&
		(parameters -> paramList[0]) &&
		(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
	{
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zHostCmdDllDefinition.dllID, logWriter);
					
		// Unpack data
		int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
						
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if (result)
		{
			int resetResult = ResetUserCustomPassword(userID);

			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackDWORD(resetResult, RETURN_CMD_DATA);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			else
				WriteToLog("ResetUserPwdCommand : Execute. Can't create result parameters list!");
		#endif
		
		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		else
			WriteToLog("ResetUserPwdCommand : Execute. Wrong input parameters!");

		WriteToLog("ResetUserPwdCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : ResetUserPwdCommand

   Method : ResetUserCustomPassword

   	Parameters :
			Input : 
				userID - user ID

   Return : Error code

   Description : Reset user password

*****************************************************************/
int ResetUserPwdCommand :: ResetUserCustomPassword(int userID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ResetUserPwdCommand: ResetUserCustomPassword. Start");
	#endif

	int resetResult = RESPONSE_BAD;
	char phoneNumber[PHONE_NUMBER_LEN] = "";
	char emailAddress[EMAIL_LENGTH * 2] = "";
	char message[1024] = "";


	// Get user descriptor
	ContentManager * contentManager = new ContentManager(zHostCmdDllDefinition.dllID, logWriter);
	PUSER_DESCRIPTOR pUser = contentManager -> GetUserDescriptor(userID);
	
	if (pUser)
	{
		// Reset password
		ResponseValidator * responseValidator = new ResponseValidator(zHostCmdDllDefinition.dllID, logWriter);
		resetResult = responseValidator -> ResetUserCustomPassword(pUser, emailAddress, phoneNumber, message);
		delete responseValidator;
			
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog(message);
			WriteToLog(emailAddress);
			WriteToLog(phoneNumber);
		#endif

		if ((resetResult != RESPONSE_OK) && (resetResult != RESET_PWD_ALREADY_RESETTED))
		{
			pUser = contentManager -> RemoveUserDescriptor(pUser);
			delete contentManager;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("ResetUserPwdCommand: ResetUserCustomPassword. Done");
			#endif
						
			return resetResult - dllUserCheckResult;
		}

		// Send email
		if ((pUser -> emailPwdReset) && (licenseManager -> CheckLicensePointValue("MESSAGETYPE", "EMAIL")))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("ServerAuthManager: ResetUserCustomPassword. Sending email...");
			#endif

			char host[STR_VALUE_LEN] = "";
			unsigned int port = 0, secType = 0;
			bool auth = false;
			char emailLogin[NAME_LEN] = "";
			char emailPassword[STR_VALUE_LEN] = "";
			char sender[STR_VALUE_LEN] = "";

			// Get email sending settings
			SettingsManager * settingsManager = new SettingsManager(zHostCmdDllDefinition.dllID);

			if (settingsManager -> GetEmailHost(host) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP host! ");
	
			if (settingsManager -> GetEmailPort(&port) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP port! ");

			if (settingsManager -> GetEmailSecurityType(&secType) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP security type! ");

			if (settingsManager -> GetEmailAuthFlag(&auth) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP authentication flag! ");

			if (settingsManager -> GetEmailLogin(emailLogin) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP server login! ");

			if (settingsManager -> GetEmailPassword(emailPassword) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP server password! ");

			if (settingsManager -> GetEmailSenderAddress(sender) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get SMTP sender! ");

			delete settingsManager;

			// Send message
			SmtpClient * smtpClient = new SmtpClient(zHostCmdDllDefinition.dllID, host, port, (SMTP_SECURITY_TYPE)secType, auth, emailLogin, emailPassword);

			bool sendResult = smtpClient -> Send(sender, emailAddress, "Password reset", message);

			delete smtpClient;

			if (!sendResult) resetResult = RESET_PWD_EMAIL_SEND_ERROR;
		}

		// Send SMS
		if ((pUser -> smsPwdReset) && (licenseManager -> CheckLicensePointValue("MESSAGETYPE", "SMS")))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
				WriteToLog("ResetUserPwdCommand: ResetUserCustomPassword. Sending SMS...");
			#endif

			char gvoiceLogin[NAME_LEN] = "";
			char gvoicePwd[STR_VALUE_LEN] = "";

			// Get google voice settings
			SettingsManager * settingsManager = new SettingsManager(zHostCmdDllDefinition.dllID);

			if (settingsManager -> GetGoogleVoiceLogin(gvoiceLogin) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get Google Voice login! ");
	
			if (settingsManager -> GetGoogleVoicePassword(gvoicePwd) != ERROR_SUCCESS)
				WriteToLog("Server command manager : ResetUserCustomPassword --> Can't get Google Voice password! ");

			delete settingsManager;

			// Send message
			SMSManager * smsManager = new GoogleVoiceSMSManager(zHostCmdDllDefinition.dllID, logWriter);

			if (smsManager -> Login(gvoiceLogin, gvoicePwd) == GVOICE_OK)
			{
				if (smsManager -> SendSMS(phoneNumber, message) != GVOICE_OK)
					resetResult = RESET_PWD_SMS_SEND_ERROR;

				smsManager -> Logout();
			}
			else
				resetResult = RESET_PWD_SMS_SEND_ERROR;
		
			delete smsManager;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
			WriteToLog("ResetUserPwdCommand: ResetUserCustomPassword. User not found!");
			WriteToLog("ResetUserPwdCommand: ResetUserCustomPassword. Done");
		#endif

		return RESET_PWD_USER_NOT_FOUND;
	}

	pUser = contentManager -> RemoveUserDescriptor(pUser);
	delete contentManager;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_HOST_CMD)
		WriteToLog("ResetUserPwdCommand: ResetUserCustomPassword. Done");
	#endif
			
	return resetResult - dllUserCheckResult;
}
