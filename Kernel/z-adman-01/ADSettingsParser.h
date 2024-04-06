/****************************************************************

   Solution : NovaTend

   Project : z-adman-01.dll

   Module : ADSettingsParser.h

   Description : this module defines interface of
				  class ADSettingsParser

*****************************************************************/

#include "stdafx.h"
#include <LogWriter.h>


#ifdef ZADMAN01_EXPORTS
#define ADMANAGER_API __declspec(dllexport)
#else
#define ADMANAGER_API __declspec(dllimport)
#endif

#ifndef ADSETTINGSPARSER_H
#define ADSETTINGSPARSER_H

// Settings string length
#define SETTINGS_STRING_LEN		512

/****************************************************************

   Class : ADSettingsParser 

   Description : responsible for parsing of ActiveDirectory
				 settings string

*****************************************************************/
class ADMANAGER_API ADSettingsParser : public SystemBase
{
	private:

		// Log writer instance
		LogWriter * logWriter;
		
		// Write message to Log-file
		int WriteToLog(char * message);

		// Get index of substring
		int SubStringIndex(char * source, char * substr);

		// Remove substring
		char * RemoveSubString(char * source, char * substr);

		// Remove all white spaces
		char * RemoveWhiteSpaces(char * source, char * target);

		// Get field string
		char * GetField(char * settingsString, char * fieldString);

		// Get field string by key string
		char * GetFieldByKey(char * settingsString, char * keyString, char * fieldString);

		// Check field settings string. Compare it with key marked field string
		int CheckField(char * fieldString, char * fieldKey);

	public:

		// Constructor
		ADSettingsParser(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		~ADSettingsParser(void);

		// Get AD service user name
		char * GetServiceUserName(char * settingsString, char * sUserName);

		// Get AD service user password
		char * GetServiceUserPassword(char * settingsString, char * sUserPassword);

		// Get AD domain name
		char * GetDomainName(char * settingsString, char * domainName);

		// Get AD default OU
		char * GetDefaultOU(char * settingsString, char * defaultOU);

		// Get AD default root OU
		char * GetDefaultRootOU(char * settingsString, char * defaultRootOU);

		// Get AD group scope
		char * GetGroupScopeName(char * settingsString, char * groupScope);

		// Get AD group type
		char * GetGroupTypeName(char * settingsString, char * groupType);

};

#endif