/****************************************************************

   Solution : NovaTend

   Project : z-adman-01.dll

   Module : ADSettingsParser.cpp

   Description : this module implements methods of
				  class ADSettingsParser

*****************************************************************/

#include "stdafx.h"
#include "ADSettingsParser.h"
#include <ContentDataDef.h>
#include <ctype.h>
#include <string.h>


// z-adman-01.dll definition structure
extern DLL_COMMON_DEFINITION zADManDllDefinition;

/****************************************************************

   Class : ADAccountManager

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - LOG writer instance
				
*****************************************************************/
ADSettingsParser :: ADSettingsParser(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zADManDllDefinition)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADSettingsParser : constructor");
	#endif	
}

/****************************************************************

   Class : ADSettingsParser

   Method : Destructor

*****************************************************************/
ADSettingsParser :: ~ADSettingsParser(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("ADSettingsParser : destructor");
	#endif
}

/****************************************************************

   Class : ADSettingsParser

   Method : SubStringIndex

   Parameters :
			Input : 
				source - source string
				substr - sub string

	Return : substring index

	Description : Get index of substring

*****************************************************************/
int ADSettingsParser :: SubStringIndex(char * source, char * substr)
{
	int index = -1;
		
	if (source)
	{
		if (substr) 
		{
			char * str = strstr(source, substr);
			if ((str - source) >= 0)	
				index = str - source;
		}
	}

	return index;
}

/****************************************************************

   Class : ADSettingsParser

   Method : RemoveSubString

   Parameters :
			Input : 
				source - source string
				substr - sub string

	Return : result string

	Description : Remove substring

*****************************************************************/
char * ADSettingsParser :: RemoveSubString(char * source, char * substr)
{
	char dest[STR_VALUE_LEN];

	char * str = strstr(source, substr);

	if (str)
	{
		memcpy(dest, source, str - source);
		dest[str - source] = '\0';
		strcat(dest, str + strlen(substr));
		strcpy(source, dest);
		return source;
	}
	else
		return NULL;
}


/****************************************************************

   Class : ADSettingsParser

   Method : RemoveWhiteSpaces

   Parameters :
			Input : 
				source - source string
			Output:
				target - result string

	Return : result string

	Description : Remove all white spaces

*****************************************************************/
char * ADSettingsParser :: RemoveWhiteSpaces(char * source, char * target)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("RemoveWhiteSpaces : Start");
	#endif	

	if (!(source) || !(target)) 
		return NULL;
	
	int c = 0;

	for (unsigned int i = 0; i < strlen(source); i++)
	{
		if (!isspace(source[i]))
			target[c++] = source[i];
    }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("RemoveWhiteSpaces : Done");
	#endif	
	
	return target;
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetField

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				fieldString - result field string

	Return : result string

	Description : Get field string

*****************************************************************/
char * ADSettingsParser :: GetField(char * settingsString, char * fieldString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("GetField : Start");
	#endif	

	int beginPos = SubStringIndex(settingsString, "<");
	int endPos = SubStringIndex(settingsString, ">");

	if ((beginPos != -1) && (endPos != -1) && (beginPos < endPos))
    {
		int fieldLength = endPos - beginPos + 1;
		strncpy(fieldString, settingsString + beginPos, fieldLength);
		fieldString[fieldLength] = '\0';
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("GetField : Done");
	#endif	

	return fieldString;
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetFiledByKey

   Parameters :
			Input : 
				settingsString - source settings string
				keyString - key string
			Output:
				fieldString - result field string

	Return : result string

	Description : Get key field string

*****************************************************************/
char * ADSettingsParser :: GetFieldByKey(char * settingsString, char * keyString, char * fieldString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("GetFiledByKey : Start");
	#endif	

	char _settingsString[SETTINGS_STRING_LEN] = "";
	char valueString[STR_VALUE_LEN] = "";
	RemoveWhiteSpaces(settingsString, _settingsString);
		
    bool found = false;
    int pos = -1;

	do
    {
		GetField(_settingsString, fieldString);
        pos = CheckField(fieldString, keyString);

        if (pos != -1)
        {
			pos += strlen(keyString);
			int len = strlen(fieldString) - strlen(keyString) - 2;
			strncpy(valueString, fieldString + pos, len);
			strcpy(fieldString, valueString);
           	found = true;
        }
        else
        {
			RemoveSubString(_settingsString, fieldString);
        }
                               
	} while ((!found) && (strlen(_settingsString) > 0));

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_ADMAN)
		WriteToLog("GetFiledByKey : Done");
	#endif	

	return fieldString;
}

/****************************************************************

   Class : ADSettingsParser

   Method : CheckField

   Parameters :
			Input : 
				fieldString - source settings string
				fieldKey - result field string
			
	Return : substring index

	Description : Check field settings string. Compare it with key marked field string

*****************************************************************/
int ADSettingsParser :: CheckField(char * fieldString, char * fieldKey)
{
	return SubStringIndex(fieldString, fieldKey);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetServiceUserName

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				sUserName - user name

	Return : result string

	Description : Get AD service user name

*****************************************************************/
char * ADSettingsParser :: GetServiceUserName(char * settingsString, char * sUserName)
{
	return GetFieldByKey(settingsString, "sUserName:", sUserName);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetServiceUserPassword

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				sUserPassword - user password

	Return : result string

	Description : Get AD service user password

*****************************************************************/
char * ADSettingsParser :: GetServiceUserPassword(char * settingsString, char * sUserPassword)
{
	return GetFieldByKey(settingsString, "sUserPassword:", sUserPassword);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetDomainName

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				domainName - domain name

	Return : result string

	Description : Get AD domain name

*****************************************************************/
char * ADSettingsParser :: GetDomainName(char * settingsString, char * domainName)
{
	return GetFieldByKey(settingsString, "domain:", domainName);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetDefaultOU

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				defaultOU - default OU

	Return : result string

	Description : Get AD default OU

*****************************************************************/
char * ADSettingsParser :: GetDefaultOU(char * settingsString, char * defaultOU)
{
	return GetFieldByKey(settingsString, "defaultOU:", defaultOU);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetDefaultRootOU

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				defaultRootOU - default root OU

	Return : result string

	Description : Get AD default root OU

*****************************************************************/
char * ADSettingsParser :: GetDefaultRootOU(char * settingsString, char * defaultRootOU)
{
	return GetFieldByKey(settingsString, "defaultRootOU:", defaultRootOU);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetGroupScopeName

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				groupScope - group scope name

	Return : result string

	Description : Get AD group scope name

*****************************************************************/
char * ADSettingsParser :: GetGroupScopeName(char * settingsString, char * groupScope)
{
	return GetFieldByKey(settingsString, "groupScope:", groupScope);
}

/****************************************************************

   Class : ADSettingsParser

   Method : GetGroupTypeName

   Parameters :
			Input : 
				settingsString - source settings string
			Output:
				groupType - group type name

	Return : result string

	Description : Get AD group type name

*****************************************************************/
char * ADSettingsParser :: GetGroupTypeName(char * settingsString, char * groupType)
{
	return GetFieldByKey(settingsString, "groupType:", groupType);
}

/****************************************************************

   Class : ADSettingsParser

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  ADSettingsParser :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

