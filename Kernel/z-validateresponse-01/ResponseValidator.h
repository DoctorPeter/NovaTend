/****************************************************************

   Solution : NovaTend

   Project : z-validateresponse-01.dll

   Module : ResponseValidator.h

   Description :  this module defines interface of class
				  ResponseValidator

*****************************************************************/
#include <LogWriter.h>
#include <DatabaseManager.h>
#include <ContentManager.h>
#include <Encryptor.h>
#include <time.h>
#include <LicenseManager.h>
#include "ValidationDataDef.h"


#ifdef ZVALIDATERESPONSE01_EXPORTS
#define RESPONSEVALIDATOR_API __declspec(dllexport)
#else
#define RESPONSEVALIDATOR_API __declspec(dllimport)
#endif

#ifndef RESPONSEVALIDATOR_H
#define RESPONSEVALIDATOR_H


/****************************************************************

   Class : ResponseValidator

   Description : responsible for user credential data validation

*****************************************************************/
class RESPONSEVALIDATOR_API	ResponseValidator : public SystemBase
{
	protected:
				
		// Log writer instance
		LogWriter * logWriter;

		// Database manager instance
		DatabaseManager * dbManager;

		// Encryptor instance
		Encryptor * encryptor;

		// Connect to database
		bool DatabaseConnect(void);

		// Disconnect from database
		bool DatabaseDisconnect(void);

		// Decrypt authenticate element
		bool DecryptAuthElement(PAUTH_ELEMENT pAuthElem, char * objectName, char * objectValue);

		// Decrypt encrypted string
		bool DecryptString(unsigned char * encStr, int encStrLen, char * decStr);

		// Get user name index
		int GetLoginParamID(PAUTH_CONTAINER pAuthContainer);

		// Get password index
		int GetPasswordParamID(PAUTH_CONTAINER pAuthContainer);

		// Get domain name index
		int GetDomainParamID(PAUTH_CONTAINER pAuthContainer);

		// Check all system apsswords
		int CheckAllSystemPasswords(int userID, char * sysPwd);

		// Validate main password
		int ValidateMainPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);

		// Validate temporary pasword
		int ValidateTempPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, char * userPassword, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);

		// Save password attempt information
		void SavePasswordAttemptInformation(PUSER_DESCRIPTOR pUser, int validationResult);

		// Check time period
		bool CheckTimePeriod(int period, char * data);

		// Delete temporary password
		void DeleteTempPassword(int userID);

		// Delete temporary password rules
		void DeleteTempPasswordRules(int userID);

		// Set temporary password rules
		bool SetTempPasswordRules(int userID, int * userTmpPwdConstRules, int userTmpPwdConstRulesCount);

		// Set temporary cascade string password
		int SetTempCascadeStringPassword(PUSER_DESCRIPTOR pUser, char * messageBuffer);

		// Set temporary symbol boxes password
		int SetTempOneSymbolBoxesPassword(PUSER_DESCRIPTOR pUser, char * messageBuffer);

		// Set temporary symbol boxes password
		int SetTempTwoSymbolsBoxesPassword(PUSER_DESCRIPTOR pUser, char * messageBuffer);

		// Get password type name
		char * GetPasswordTypeName(int passwordTypeID, char * passwordTypeName);

		// Prepare password reset message
		char * PreparePasswordResetMessage(PUSER_DESCRIPTOR pUser, int tmpUserToken, int * userTmpPwdConstRules, int userTmpPwdConstRulesCount, char * messageBuffer);

		// Save user reset parameters
		void SaveUserResetFlag(PUSER_DESCRIPTOR pUser, int tmpUserToken);
			

	public:

		// Constructor
		ResponseValidator(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~ResponseValidator(void);

		// Database credential records validation
		int ValidateParams(int userID, char * compName, PAUTH_CONTAINER pAuthContainer);

		// Validate user answers
		int ValidateAnswers(int userID, char * compName, PANSWER_CONTAINER pAnsCnt);

		// Validate domain name
		int ValidateDomain(PAUTH_CONTAINER pAuthContainer);

		// Validate user password
		int ValidateCustomPassword(PUSER_DESCRIPTOR pUser, PUSER_SECURITY_DATA pSecurityData, unsigned char * userPassword, int userPasswordLen, tm * timeinfo, PUTF8_STRINGS_MATRIX_LIST symbolBoxesList);
		
		// Validate user credentials
		int ValidateCredentials(unsigned char * encUserName, int encUserNameLen, unsigned char * encUserPassword, int encUserPasswordLen, int authSystemID);

		// Reset user custom password
		int ResetUserCustomPassword(PUSER_DESCRIPTOR pUser, char * email, char * phone, char * messageBuffer);

		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif