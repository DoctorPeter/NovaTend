/****************************************************************

   Solution : NovaTend

   Project : z-licenseman-01.dll

   Module : LicensePoint.cpp

   Description :  Implements the methods of class LicesePoint 
                  and LicensePointList

*****************************************************************/

#include "stdafx.h"

#include "LicensePoint.h"

// New license point in license string
#define NEW_LICENSE_POINT				1

// New value of current filed of license info
#define NEW_LICENSE_POINT_VALUE			2

// Last value of current filed of license info
#define LAST_LICENSE_POINT_VALUE		3


// License info fields delimits
char pointDelimit[] = {'%', '&', '$', '>', '<'};//{ '!', '(', ')', '%', '?', '{', '}' };

// License info values delimits
char valueDelimit[] = {'`', '~', '#', '@', '|'};//{'[', ']', '+', '&', '-'};


// z-licenseman-01.dll definition structure
extern DLL_COMMON_DEFINITION zLicenseManDllDefinition;


#pragma region License point methods

/****************************************************************

		Methods of class LicensePoint

*****************************************************************/


/****************************************************************

   Class : LicensePoint

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
LicensePoint :: LicensePoint(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zLicenseManDllDefinition)
{
	this -> logWriter = logWriter;

	memset(licensePointID, 0, NAME_LEN);
	memset(licensePointName, 0, NAME_LEN);
	memset(licensePointDescription, 0, NAME_LEN);
	memset(valuesList, 0, sizeof(valuesList));
	licensePointType = 0;
	valuesCount = 0;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : Constructor");
	#endif

}

/****************************************************************

   Class : LicensePoint

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance
				id - license point ID
				name - license point name
				description - license point description
				type - license point type
				valuesCount - license point values count
				... - license point values list (list of PLICENSE_POINT_VALUE)

*****************************************************************/
LicensePoint :: LicensePoint(unsigned long dllUserID, LogWriter * logWriter, char * id, char * name, char * description, int type, int valuesCount, ...) : SystemBase(dllUserID, &zLicenseManDllDefinition)
{
	this -> logWriter = logWriter;

	memset(licensePointID, 0, NAME_LEN);
	memset(licensePointName, 0, NAME_LEN);
	memset(licensePointDescription, 0, NAME_LEN);
	memset(valuesList, 0, sizeof(valuesList));
	
	if (id) strcpy(licensePointID, id);
	if (name) strcpy(licensePointName, name);
	if (description) strcpy(licensePointDescription, description);
	licensePointType = type;
	this -> valuesCount = valuesCount;

	int * pInt = &valuesCount;
	pInt++;
	PLICENSE_POINT_VALUE pLicensePointValue = (PLICENSE_POINT_VALUE)(pInt);

	for (int i = 0; i < valuesCount; i++)
	{
		valuesList[i] = pLicensePointValue;
		pLicensePointValue++;
	}
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : Constructor");
	#endif

}

/****************************************************************

   Class : LicensePoint

   Method : Destructor

*****************************************************************/
LicensePoint :: ~LicensePoint(void)
{
	ClearValuesList();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : Destructor");
	#endif
}

/****************************************************************

   Class : LicensePoint

   Method : GetID

   Parameters :
			Output : 
				outID - license point ID

	Return : license point ID

	Description : Get license point ID

*****************************************************************/
char * LicensePoint :: GetID(char * outID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetID. Start");
	#endif

	if (outID)
	{
		strcpy(outID, licensePointID);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			char message[STR_VALUE_LEN] = "";
			sprintf(message, "LicensePoint : GetID. ID = %s", outID);
			WriteToLog(message);
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : GetID. Wrong input data!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetID. Done");
	#endif

	return outID;
}

/****************************************************************

   Class : LicensePoint

   Method : SetID

   Parameters :
			Input : 
				newID - license point ID

	Return : license point ID

	Description : Set license point ID

*****************************************************************/
char * LicensePoint :: SetID(char * newID)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetID. Start");
	#endif

	if (newID)
	{
		strcpy(licensePointID, newID);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			char message[STR_VALUE_LEN] = "";
			sprintf(message, "LicensePoint : SetID. ID = %s", licensePointID);
			WriteToLog(message);
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : SetID. Wrong input data!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetID. Done");
	#endif

	return licensePointID;
}

/****************************************************************

   Class : LicensePoint

   Method : GetName

   Parameters :
			Output : 
				outName - license point name

	Return : license point name

	Description : Get license point name

*****************************************************************/
char * LicensePoint :: GetName(char * outName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetName. Start");
	#endif

	if (outName)
	{
		strcpy(outName, licensePointName);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			char message[STR_VALUE_LEN] = "";
			sprintf(message, "LicensePoint : GetName. Name = %s", outName);
			WriteToLog(message);
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : GetName. Wrong input data!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetName. Done");
	#endif

	return outName;
}

/****************************************************************

   Class : LicensePoint

   Method : SetName

   Parameters :
			Input : 
				newName - license point name

	Return : license point name

	Description : Set license point name

*****************************************************************/
char * LicensePoint :: SetName(char * newName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetName. Start");
	#endif

	if (newName)
	{
		strcpy(licensePointName, newName);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			char message[STR_VALUE_LEN] = "";
			sprintf(message, "LicensePoint : SetName. Name = %s", licensePointName);
			WriteToLog(message);
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : SetName. Wrong input data!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetName. Done");
	#endif

	return licensePointName;
}

/****************************************************************

   Class : LicensePoint

   Method : GetDescription

   Parameters :
			Output : 
				outDescription - license point description

	Return : license point description

	Description : Get license point description

*****************************************************************/
char * LicensePoint :: GetDescription(char * outDescription)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetDescription. Start");
	#endif

	if (outDescription)
	{
		strcpy(outDescription, licensePointDescription);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			char message[STR_VALUE_LEN] = "";
			sprintf(message, "LicensePoint : GetDescription. Description = %s", outDescription);
			WriteToLog(message);
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : GetDescription. Wrong input data!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetDescription. Done");
	#endif

	return outDescription;
}

/****************************************************************

   Class : LicensePoint

   Method : SetDescription

   Parameters :
			Input : 
				newDescription - license point description

	Return : license point description

	Description : Set license point description

*****************************************************************/
char * LicensePoint :: SetDescription(char * newDescription)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetDescription. Start");
	#endif

	if (newDescription)
	{
		strcpy(licensePointDescription, newDescription);
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			char message[STR_VALUE_LEN] = "";
			sprintf(message, "LicensePoint : SetDescription. Description = %s", licensePointDescription);
			WriteToLog(message);
		#endif
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : SetDescription. Wrong input data!");
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetDescription. Done");
	#endif

	return licensePointDescription;
}
		
/****************************************************************

   Class : LicensePoint

   Method : GetType

	Return : license point type

	Description : Get license point type

*****************************************************************/
int LicensePoint :: GetType(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		char message[STR_VALUE_LEN] = "";
		sprintf(message, "LicensePoint : GetType. Type = %d", licensePointType);
		WriteToLog(message);
	#endif

	return licensePointType;
}

/****************************************************************

   Class : LicensePoint

   Method : SetType

   Parameters :
			Input : 
				type - license point type

	Return : license point type

	Description : Set license point type

*****************************************************************/
int LicensePoint :: SetType(int type)
{
	licensePointType = type;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		char message[STR_VALUE_LEN] = "";
		sprintf(message, "LicensePoint : SetType. Type = %d", licensePointType);
		WriteToLog(message);
	#endif

	return licensePointType;
}

/****************************************************************

   Class : LicensePoint

   Method : CreateValue

   Parameters :
			Input : 
				type - value type
				value - string value
				access - access flag

	Return : pointer to new value descriptor

	Description : Create new value

*****************************************************************/
PLICENSE_POINT_VALUE LicensePoint :: CreateValue(int type, char * value, bool access)
{
	PLICENSE_POINT_VALUE newValue = (PLICENSE_POINT_VALUE)malloc(sizeof(LICENSE_POINT_VALUE));

	if (newValue)
	{
		newValue -> valueType = type;
		if (value) strcpy(newValue -> value, value);
		else newValue -> value[0] = 0;
		newValue -> accessible = access;
	}

	return newValue;
}


/****************************************************************

   Class : LicensePoint

   Method : AddValue

   Parameters :
			Input : 
				type - value type
				value - string value
				access - access flag

	Return : pointer to new value descriptor

	Description : Add new value to list

*****************************************************************/
PLICENSE_POINT_VALUE LicensePoint :: AddValue(int type, char * value, bool access)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : AddValue");
	#endif

	// Create new value
	PLICENSE_POINT_VALUE newValue = CreateValue(type, value, access);

	if (newValue)
	{
		valuesList[valuesCount] = newValue;
		valuesCount++;
	}

	return newValue;
}

/****************************************************************

   Class : LicensePoint

   Method : DelValue

   Parameters :
			Input : 
				value - value to delete

	Return : pointer to value descriptor

	Description : Delete value

*****************************************************************/
PLICENSE_POINT_VALUE LicensePoint :: DelValue(PLICENSE_POINT_VALUE value)
{
	if (value)
	{
		free(value);
		value = NULL;
	}

	return value;
}

/****************************************************************

   Class : LicensePoint

   Method : DelValue

   Parameters :
			Input : 
				index - index of value to delete

	Return : pointer to value descriptor

	Description : Delete value from the list by index

*****************************************************************/
bool LicensePoint :: DelValue(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : DelValue. Start");
	#endif

	bool result = false;

	if ((index >= 0) && (index < valuesCount))
	{
		valuesList[index] = DelValue(valuesList[index]);
		
		for(int i = index; i < valuesCount - 1; i++)
		   valuesList[i] = valuesList[i + 1];
		
		valuesList[valuesCount - 1] = NULL;
		valuesCount--;

		result = true;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : DelValue. Wrong input index!");

		WriteToLog("LicensePoint : DelValue. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : ClearValuesList

   Description : Clear values list

*****************************************************************/
void LicensePoint :: ClearValuesList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : ClearValuesList");
	#endif

	while(valuesCount > 0) DelValue(0);
}

/****************************************************************

   Class : LicensePoint

   Method : ValuesCount

   Returns : values count

   Description : Get values count

*****************************************************************/
int LicensePoint :: ValuesCount(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : ValuesCount");
	#endif

	return valuesCount;
}


/****************************************************************

   Class : LicensePoint

   Method : GetValueType

   Parameters :
			Input : 
				index - index of value 

	Return : value type

	Description : Get type of value

*****************************************************************/
int LicensePoint :: GetValueType(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetValueType");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
	{
		return valuesList[index] -> valueType;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : GetValueType. Wrong input index!");
	#endif

	return 0;
}
		
/****************************************************************

   Class : LicensePoint

   Method : SetValueType

   Parameters :
			Input : 
				type - value type
				index - index of value

	Return : value type

	Description : Set type of value

*****************************************************************/
int LicensePoint :: SetValueType(int type, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetValueType");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
	{
		valuesList[index] -> valueType = type;
		return valuesList[index] -> valueType;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : SetValueType. Wrong input index!");
	#endif

	return 0;
}

/****************************************************************

   Class : LicensePoint

   Method : GetValue

   Parameters :
			Output:
				outValue - string value

			Input : 
				index - index of value 

	Return : string value

	Description : Get value

*****************************************************************/
char * LicensePoint :: GetValue(char * outValue, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetValue");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]) && (outValue))
	{
		strcpy(outValue, valuesList[index] -> value);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : GetValue. Wrong input data!");
	#endif

	return outValue;
}

/****************************************************************

   Class : LicensePoint

   Method : SetValue

   Parameters :
			Input : 
				newValue - new string value
				index - index of value

	Return : new string value

	Description : Set value

*****************************************************************/
char * LicensePoint :: SetValue(char * newValue, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetValue");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]) && (newValue))
	{
		strcpy(valuesList[index] -> value, newValue);
		return valuesList[index] -> value;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : SetValue. Wrong input data!");
	#endif

	return newValue;
}

/****************************************************************

   Class : LicensePoint

   Method : GetValueAccess

   Parameters :
			Input : 
				index - index of value 

	Return : value access flag

	Description : Get access flag

*****************************************************************/
bool LicensePoint :: GetValueAccess(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : GetValueAccess");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
	{
		return valuesList[index] -> accessible;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : GetValueAccess. Wrong input index!");
	#endif

	return false;
}

/****************************************************************

   Class : LicensePoint

   Method : SetValueAccess

   Parameters :
			Input : 
				access - value access flag
				index - index of value

	Return : value access flag

	Description : Set access flag

*****************************************************************/
bool LicensePoint :: SetValueAccess(bool access, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : SetValueAccess");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
	{
		valuesList[index] -> accessible = access;
		return valuesList[index] -> accessible;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : SetValueAccess. Wrong input index!");
	#endif

	return false;
}

/****************************************************************

   Class : LicensePoint

   Method : ConvertValueToInt

   Parameters :
			Input : 
				index - index of value

	Return : int value

	Description : Convert value to integer

*****************************************************************/
int LicensePoint :: ConvertValueToInt(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : ConvertValueToInt");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]) && (valuesList[index] -> valueType == LPV_TYPE_INTEGER))
	{
		return atoi(valuesList[index] -> value);
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : ConvertValueToInt. Wrong input index!");
	#endif

	return 0;
}

/****************************************************************

   Class : LicensePoint

   Method : ConvertValueToDateTime

   Parameters :
			Output :
				outTM - datetime structure

			Input : 
				index - index of value

	Return : datetime value

	Description : Convert value to datetime

*****************************************************************/
struct tm * LicensePoint :: ConvertValueToDateTime(struct tm * outTM, int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : ConvertValueToDateTime");
	#endif

	if ((index >= 0) && (index < valuesCount) && (valuesList[index]) && (valuesList[index] -> valueType == LPV_TYPE_DATETIME) && (outTM))
	{
		int day, mon, year, hour, min, sec;

		// Retrieve date values
		sscanf_s(valuesList[index] -> value, "%d:%d:%d:%d:%d:%d", &year, &mon, &day, &hour, &min, &sec);
	
		time_t nowSeconds;
		struct tm inpTime;

		// Get current time
		time (&nowSeconds);
		inpTime = * localtime(&nowSeconds);

		// Set new values
		inpTime.tm_year = year - 1900;
		inpTime.tm_mon = mon - 1;
		inpTime.tm_mday = day;
		inpTime.tm_hour = hour;
		inpTime.tm_min = min;
		inpTime.tm_sec = sec;
		inpTime.tm_isdst = -1;

		memcpy(outTM, &inpTime, sizeof(struct tm));
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : ConvertValueToDateTime. Wrong input data!");
	#endif

	return outTM;
}

/****************************************************************

   Class : LicensePoint

   Method : CheckValue

   Parameters :
			Input : 
				strValue - value
				index - index of value
				relType - type of relation

	Return : TRUE - if this value is accessible

	Description : Check string value

*****************************************************************/
bool LicensePoint :: CheckValue(char * strValue, int index, int relType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : CheckValue. Start");
	#endif

	bool result = false;

	if (strValue)
	{
		switch (licensePointType)
		{
			//The value is checked for an exact match
			case LP_EXACT_MATCH :
			// Or point stores the specified value
			case LP_SPECIFIED :
			{
				// Index specified
				if ((index >= 0) && (index < valuesCount) && (valuesList[index]) && (strcmp(strValue, valuesList[index] -> value) == 0))
				{
					result = valuesList[index] -> accessible;
				}
				else
					// Index not specified - search value
					for (int i = 0; i < valuesCount; i++)
					{
						if ((valuesList[i]) && (strcmp(strValue, valuesList[i] -> value) == 0))
						{
							result = valuesList[i] -> accessible;
							break;
						}
					}

				break;
			}

			// The value is tested for more or less
			case LP_MORE_LESS :
			{
				if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
				{
					int cmpRes = strcmp(strValue, valuesList[index] -> value);
					if (relType == REL_TYPE_MORE)
						result = (cmpRes > 0) && valuesList[index] -> accessible;
					else
						if (relType == REL_TYPE_LESS)
							result = (cmpRes < 0) && valuesList[index] -> accessible;
				}

				break;
			}
		
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : CheckValue. Wrong input data!");

		if (result)
			WriteToLog("LicensePoint : CheckValue. Value is accessible!");
		else
			WriteToLog("LicensePoint : CheckValue. Value is not accessible!");
		
		WriteToLog("LicensePoint : CheckValue. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : CheckValue

   Parameters :
			Input : 
				intValue - value
				index - index of value
				relType - type of relation

	Return : TRUE - if this value is accessible

	Description : Check int value

*****************************************************************/
bool LicensePoint :: CheckValue(int intValue, int index, int relType)
{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : CheckValue. Start");
	#endif

	bool result = false;

	switch (licensePointType)
	{
		//The value is checked for an exact match
		case LP_EXACT_MATCH :
		// Or point stores the specified value
		case LP_SPECIFIED :
		{
			// Index specified
			if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
				result =  (ConvertValueToInt(index) == intValue) && (valuesList[index] -> accessible);
			else
				// Index not specified - search value
				for (int i = 0; i < valuesCount; i++)
				{
					if (ConvertValueToInt(i) == intValue)
					{
						result = valuesList[i] -> accessible;
						break;
					}
				}

			break;
		}

		// The value is tested for more or less
		case LP_MORE_LESS :
		{
			if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
			{
				int convRes = ConvertValueToInt(index);
				if (relType == REL_TYPE_MORE)
					result = (intValue > convRes) && valuesList[index] -> accessible;
				else
					if (relType == REL_TYPE_LESS)
						result = (intValue < convRes) && valuesList[index] -> accessible;
			}

			break;
		}
		
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		if (result)
			WriteToLog("LicensePoint : CheckValue. Value is accessible!");
		else
			WriteToLog("LicensePoint : CheckValue. Value is not accessible!");
		
		WriteToLog("LicensePoint : CheckValue. Done");
	#endif

	return result;

}

/****************************************************************

   Class : LicensePoint

   Method : CheckValue

   Parameters :
			Input : 
				tmValue - value
				index - index of value
				relType - type of relation

	Return : TRUE - if this value is accessible

	Description : Check tm value

*****************************************************************/
bool LicensePoint :: CheckValue(tm * tmValue, int index, int relType)
{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : CheckValue. Start");
	#endif

	bool result = false;

	if (tmValue)
	{
		switch (licensePointType)
		{
			//The value is checked for an exact match
			case LP_EXACT_MATCH :
			// Or point stores the specified value
			case LP_SPECIFIED :
			{
				// Index specified
				if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
				{
					struct tm inpTime;
					ConvertValueToDateTime(&inpTime, index);
					result = (difftime(mktime(tmValue), mktime(&inpTime)) == 0.0) && (valuesList[index] -> accessible);
				}
				else
					// Index not specified - search value
					for (int i = 0; i < valuesCount; i++)
					{
						struct tm inpTime;
						ConvertValueToDateTime(&inpTime, i);

						if (difftime(mktime(tmValue), mktime(&inpTime)) == 0.0)
						{
							result = valuesList[i] -> accessible;
							break;
						}
					}

				break;
			}

			// The value is tested for more or less
			case LP_MORE_LESS :
			{
				if ((index >= 0) && (index < valuesCount) && (valuesList[index]))
				{
					struct tm inpTime;
					ConvertValueToDateTime(&inpTime, index);
					double resSeconds = difftime(mktime(&inpTime), mktime(tmValue));

					if (relType == REL_TYPE_MORE)
						result = (resSeconds < 0) && valuesList[index] -> accessible;
					else
						if (relType == REL_TYPE_LESS)
							result = (resSeconds > 0) && valuesList[index] -> accessible;
				}

				break;
			}
		
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : CheckValue. Wrong input data!");

		if (result)
			WriteToLog("LicensePoint : CheckValue. Value is accessible!");
		else
			WriteToLog("LicensePoint : CheckValue. Value is not accessible!");
		
		WriteToLog("LicensePoint : CheckValue. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePoint

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  LicensePoint :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion

#pragma region License point list methods

/****************************************************************

		Methods of class LicensePointsList

*****************************************************************/


/****************************************************************

   Class : LicensePointsList

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
LicensePointsList :: LicensePointsList(unsigned long dllUserID, LogWriter * logWriter) : SystemBase(dllUserID, &zLicenseManDllDefinition)
{
	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : Constructor");
	#endif

	licensePointsCount = 0;
	memset(licensePoints, NULL, sizeof(licensePoints));
}

/****************************************************************

   Class : LicensePointsList

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				licenseString - decrypted license string
				logWriter - pointer to LogWriter instance

*****************************************************************/
LicensePointsList :: LicensePointsList(unsigned long dllUserID, char * licenseString, LogWriter * logWriter) : SystemBase(dllUserID, &zLicenseManDllDefinition)
{
	this -> logWriter = logWriter;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : Constructor");
	#endif

	licensePointsCount = 0;
	memset(licensePoints, NULL, sizeof(licensePoints));

	ParseLicenseString(licenseString);
}

/****************************************************************

   Class : LicensePointsList

   Method : Destructor

*****************************************************************/
LicensePointsList :: ~LicensePointsList(void)
{
	Clear();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : Destructor");
	#endif
}

/****************************************************************

   Class : LicensePointsList

   Method : ParseLicenseString

   Parameters :
			Input : 
				licenseString - license string

	Return : TRUE - if success

	Description : Parse license string

*****************************************************************/
bool LicensePointsList :: ParseLicenseString(char * licenseString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : ParseLicenseString. Start");
	#endif

	if (licenseString)
	{
		Clear();

		char outStr[STR_VALUE_LEN];
		int delKind = NEW_LICENSE_POINT_VALUE;
		int pos = 0;

		// While not loaded last value
		while (delKind != LAST_LICENSE_POINT_VALUE)
		{
			// Create new license point
			licensePoints[licensePointsCount] = new LicensePoint(dllUserID, logWriter);
		
			delKind = NEW_LICENSE_POINT_VALUE;
			int valNumber = 0;

			// Load values of current field
			while (delKind == NEW_LICENSE_POINT_VALUE)
			{
				// Get value
				pos = GetFieldValue(licenseString, pos, outStr, &delKind);

				// All values are strictly followed in order
				switch(valNumber)
				{
					// Get license point ID
					case 0 : {
								licensePoints[licensePointsCount] -> SetID(outStr);
								break;
							 }

					// Get license point name
					case 1 : {
								licensePoints[licensePointsCount] -> SetName(outStr);
								break;
							 }

					// Get license point description
					case 2 : {
								licensePoints[licensePointsCount] -> SetDescription(outStr);
								break;
							 }

					// Get license point type
					case 3 : {
								licensePoints[licensePointsCount] -> SetType(atoi(outStr));
								break;
							 }

					// Get count of values of license point
					case 4 : {
								int valuesCount = atoi(outStr);							
								for (int i = 0; i < valuesCount; i++)
									licensePoints[licensePointsCount] -> AddValue(0, "", false);
								break;
							 }
				
					// Get all values of license info of license point
					default : {
								 if ((valNumber % 2) == 1)
								 {
									licensePoints[licensePointsCount] -> SetValueType(atoi(outStr), (valNumber - 5) / 2);
								 }
								 else
								 {
									licensePoints[licensePointsCount] -> SetValueAccess(outStr[strlen(outStr) - 1] == '*', (valNumber - 6) / 2);
									outStr[strlen(outStr) - 1] = 0;
									licensePoints[licensePointsCount] -> SetValue(outStr, (valNumber - 6) / 2);
								 }
							  }

				}
			
				valNumber++;
			}	

			licensePointsCount++;
		}

		Del(licensePointsCount - 1);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
			WriteToLog("LicenseManager : GetLicense. Done");
		#endif

		return true;

	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : GetLicense. Wrong input license string!");

		WriteToLog("LicenseManager : GetLicense. Done");
	#endif

	return false;
}

/****************************************************************

   Class : LicensePointsList

   Method : MakeLicenseString

   Parameters :
			Output : 
				outLicenseString - license string

	Return : license string

	Description :  Make license string

*****************************************************************/
char * LicensePointsList :: MakeLicenseString(char * outLicenseString)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicenseManager : MakeLicenseString. Start");
	#endif

	if (outLicenseString)
	{
		char delStr[2] = {0, 0};
		char tmpStr[STR_VALUE_LEN] = "";
		outLicenseString[0] = 0;

		for (int i = 0; i < licensePointsCount; i++)
		{
			// License point ID
			strcat(outLicenseString, licensePoints[i] -> GetID(tmpStr));
			GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
			strcat(outLicenseString, delStr);

			// License point name
			strcat(outLicenseString, licensePoints[i] -> GetName(tmpStr));
			GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
			strcat(outLicenseString, delStr);

			// License point description
			strcat(outLicenseString, licensePoints[i] -> GetDescription(tmpStr));
			GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
			strcat(outLicenseString, delStr);
			
			// License point type
			itoa(licensePoints[i] -> GetType(), tmpStr, 10);
			strcat(outLicenseString, tmpStr);
			GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
			strcat(outLicenseString, delStr);

			// License point values count
			itoa(licensePoints[i] -> ValuesCount(), tmpStr, 10);
			strcat(outLicenseString, tmpStr);
			GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
			strcat(outLicenseString, delStr);

			// Enum values
			for (int j = 0; j < licensePoints[i] -> ValuesCount(); j++)
			{
				// Value type
				itoa(licensePoints[i] -> GetValueType(j), tmpStr, 10);
				strcat(outLicenseString, tmpStr);
				GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
				strcat(outLicenseString, delStr);

				// Value and access flag
				licensePoints[i] -> GetValue(tmpStr, j);
				int sLen = strlen(tmpStr);
				if (licensePoints[i] -> GetValueAccess(j)) tmpStr[sLen] = '*';
				else tmpStr[sLen] = '^';
				tmpStr[sLen + 1] = 0;
				strcat(outLicenseString, tmpStr);
				GenerateDelimitString(delStr, valueDelimit, sizeof(valueDelimit));
				strcat(outLicenseString, delStr);
			}

			int sLen = strlen(outLicenseString);
			outLicenseString[sLen - 1] = 0;

			GenerateDelimitString(delStr, pointDelimit, sizeof(pointDelimit));
			strcat(outLicenseString, delStr);
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicenseManager : MakeLicenseString. Wrong input data!");

		WriteToLog("LicenseManager : MakeLicenseString. Done");
	#endif

	return outLicenseString;
}

/****************************************************************

   Class : LicensePointsList

   Method : IsDelimit

   Parameters :
			Input : 
				c - input char
				delLst - delimit symbols list
				lstSize - size of delimit symbols list

	Return : checking result

	Description : Define delemit char

*****************************************************************/
bool LicensePointsList :: IsDelimit(char c, char * delLst, int lstSize)
{
	for (int i = 0; i < lstSize; i++)
		if (c == delLst[i])
			return true;

	return false;
}

/****************************************************************

   Class : LicensePointsList

   Method : GetFieldValue

   Parameters :
			Input : 
				inpStr - input string
				pos - input position
			Output:
				outStr - result string
				retFlag - kind of result

	Return : current position

	Description : Get current value of license info field

*****************************************************************/
int LicensePointsList :: GetFieldValue(char * inpStr, int pos, char * outStr, int * retFlag)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : GetFieldValue. Start");
	#endif

	int resPos = pos;
	int sLen = strlen(inpStr);

	// Pasre input string
	for(int i = pos; i < sLen; i++)
	{
		resPos = i;

		// Check field delimiters
		if (IsDelimit(inpStr[i], pointDelimit, sizeof(pointDelimit)))
		{
			outStr[i - pos] = 0;
			*retFlag = NEW_LICENSE_POINT;
			
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
				WriteToLog("LicensePointsList : GetFieldValue. New license point loaded!");
				WriteToLog("LicensePointsList : GetFieldValue. Done");
			#endif

			return resPos + 1;
		}

		// Check value delimiters
		if (IsDelimit(inpStr[i], valueDelimit, sizeof(valueDelimit)))
		{
			outStr[i - pos] = 0;
			*retFlag = NEW_LICENSE_POINT_VALUE;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
				WriteToLog("LicensePointsList : GetFieldValue. New license point value loaded!");
				WriteToLog("LicensePointsList : GetFieldValue. Done");
			#endif

			return resPos + 1;
		}

		outStr[i - pos] = inpStr[i];
	}

	// Last value
	outStr[resPos - pos + 1] = 0;
	*retFlag = LAST_LICENSE_POINT_VALUE;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : GetFieldValue. Last value loaded!");
		WriteToLog("LicensePointsList : GetFieldValue. Done");
	#endif

	return resPos + 1;
}

/****************************************************************

   Class : LicensePointsList

   Method : GenerateDelimitString

   Parameters :
			Input : 
				delList - delimiters list
				delLstSize - delimiters list size
			Output :
				delStr - result string

   Description :  Prepare delimeter as string

*****************************************************************/
void LicensePointsList :: GenerateDelimitString(char * delStr, char * delList, int delLstSize)
{
	int pos = (int)((double)Rand() / (MAX_RAND_VALUE + 1) * delLstSize);
	
	// Prepare delimiter
	delStr[0] = delList[pos];
	delStr[1] = 0;
}

/****************************************************************

   Class : LicensePointsList

   Method : Clear

   Description :  Clear list

*****************************************************************/
void LicensePointsList :: Clear(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : Clear");
	#endif

	while(licensePointsCount > 0) Del(0);
}

/****************************************************************

   Class : LicensePointsList

   Method : Add

   Parameters :
			Input : 
				licensePoint - pointer to license point instance

   Returns : pointer to license point instance

   Description :  Add license point to list

*****************************************************************/
LicensePoint * LicensePointsList :: Add(LicensePoint * licensePoint)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : Add");
	#endif

	if (licensePoint)
	{
		licensePoints[licensePointsCount] = licensePoint;
		licensePointsCount++;
	}

	return licensePoint;
}

/****************************************************************

   Class : LicensePointsList

   Method : Add

   Parameters :
			Input : 
				id - license point ID
				name - license point name
				description - license point description
				type - license point type
				valuesCount - license point values count
				... - license point values list (list of PLICENSE_POINT_VALUE)

   Returns : pointer to license point instance

   Description :  Add license point to list

*****************************************************************/
LicensePoint * LicensePointsList :: Add(char * id, char * name, char * description, int type, int valuesCount, ...)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePointsList : Add");
	#endif

	// Values list
	PLICENSE_POINT_VALUE valuesList[VALUES_COUNT];

	// Read values
	int * pInt = &valuesCount;
	pInt++;

	// Create new license point
	LicensePoint * newLicensePoint = new LicensePoint(dllUserID, logWriter, id, name, description, type, valuesCount, (PLICENSE_POINT_VALUE)(pInt));

	// Add license point
	return Add(newLicensePoint);
}

/****************************************************************

   Class : LicensePointsList

   Method : Del

   Parameters :
			Input : 
				index - index of license point

   Returns : TRUE - if success

   Description : Del license point by index

*****************************************************************/
bool LicensePointsList :: Del(int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : Del. Start");
	#endif

	bool result = false;

	if ((index >= 0) && (index < licensePointsCount))
	{
		delete licensePoints[index];
		licensePoints[index] = NULL;
		
		for(int i = index; i < licensePointsCount - 1; i++)
		   licensePoints[i] = licensePoints[i + 1];
		
		licensePoints[licensePointsCount - 1] = NULL;
		licensePointsCount--;

		result = true;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : Del. Wrong input index!");

		WriteToLog("LicensePoint : Del. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePointsList

   Method : operator []

   Parameters :
			Input : 
				index - index of license point

   Returns : pointer to license point instance

   Description : Operator []

*****************************************************************/
LicensePoint * LicensePointsList :: operator [] (int index)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : operator []. Start");
	#endif
	
	LicensePoint * result = NULL;

	if ((index >= 0) && (index < licensePointsCount))
	{
		result =  licensePoints[index];
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		else
			WriteToLog("LicensePoint : operator []. Wrong input index!");

		WriteToLog("LicensePoint : operator []. Done");
	#endif

	return result;
}

/****************************************************************

   Class : LicensePointsList

   Method : Count

   Returns : Count of license points

   Description : Get count of license points

*****************************************************************/
int LicensePointsList :: Count(void)
{
	return licensePointsCount;
}

/****************************************************************

   Class : LicensePointsList

   Method : Find

   Parameters :
			Input :
				id - license point ID

   Returns : license point index

   Description : Find license point

*****************************************************************/
int LicensePointsList :: Find(char * id)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		WriteToLog("LicensePoint : Find. Start");
	#endif

	int index = -1;

	for(int i = 0; i < licensePointsCount; i++)
	{
		char strTemp[STR_VALUE_LEN] = "";
		if (strcmp(licensePoints[i] -> GetID(strTemp), id) == 0)
		{
			index = i;
			break;
		}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_LICMAN)
		if (index == -1)
			WriteToLog("LicensePoint : Find. License point not found!");

		WriteToLog("LicensePoint : Find. Done");
	#endif

	return index;
}


/****************************************************************

   Class : LicensePointsList

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int  LicensePointsList :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;

}

#pragma endregion