/****************************************************************

   Solution : NovaTend

   Project : z-licenseman-01.dll

   Module : LicensePoint.h

   Description :  Defines the interface of classes LicensePoint 
				  and LicensePointList

*****************************************************************/

#include <LogWriter.h>
#include <ContentDataDef.h>

#include "LicenseDataDef.h"

#ifdef ZLICENSEMAN01_EXPORTS
#define LICENSEPOINT_API __declspec(dllexport)
#else
#define LICENSEPOINT_API __declspec(dllimport)
#endif

#ifndef LICENSEPOINT_H
#define LICENSEPOINT_H

/****************************************************************

   Class : LicensePoint

   Description : Describes one item of license info

*****************************************************************/
class LICENSEPOINT_API LicensePoint : public SystemBase
{
	private :

		// License point ID
		char licensePointID[NAME_LEN];

		// License point name
		char licensePointName[NAME_LEN];

		// License point name
		char licensePointDescription[NAME_LEN];
		
		// License point type
		int licensePointType;
				
		// Values count
		int valuesCount;

		// Values list
		PLICENSE_POINT_VALUE valuesList[VALUES_COUNT];
		
		// Log writer instance
		LogWriter * logWriter;

		// Write message to Log-file
		int WriteToLog(char * message);

	public :

		// Constructor
		LicensePoint(unsigned long dllUserID, LogWriter * logWriter);

		// Constructor
		LicensePoint(unsigned long dllUserID, LogWriter * logWriter, char * id, char * name, char * description, int type, int valuesCount, ...);

		// Destructor
		virtual ~LicensePoint(void);

		// Get license point ID
		char * GetID(char * outID);

		// Set license point ID
		char * SetID(char * newID);

		// Get license point name
		char * GetName(char * outName);

		// Set license point name
		char * SetName(char * newName);

		// Get license point description
		char * GetDescription(char * outDescription);

		// Set license point description
		char * SetDescription(char * newDescription);
		
		// Get license point type
		int GetType(void);

		// Set license point type
		int SetType(int type);

		// Create new value
		static PLICENSE_POINT_VALUE CreateValue(int type, char * value, bool access);

		// Add new value to list
		PLICENSE_POINT_VALUE AddValue(int type, char * value, bool access);

		// Delete value
		static PLICENSE_POINT_VALUE DelValue(PLICENSE_POINT_VALUE value);

		// Delete value from the list by index
		bool DelValue(int index);

		// Clear values list
		void ClearValuesList(void);

		// Get values count
		int ValuesCount(void);

		// Get type of value
		int GetValueType(int index = 0);
		
		// Set type of value
		int SetValueType(int type, int index = 0);

		// Get value
		char * GetValue(char * outValue, int index = 0);

		// Set value
		char * SetValue(char * newValue, int index = 0);

		// Get access flag
		bool GetValueAccess(int index = 0);
		
		// Set access flag
		bool SetValueAccess(bool access, int index = 0);
		
		// Convert value to integer
		int ConvertValueToInt(int index = 0);

		// Convert value to integer
		struct tm * ConvertValueToDateTime(struct tm * outTM, int index = 0);

		// Check string value
		bool CheckValue(char * strValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Check int value
		bool CheckValue(int intValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Check tm value
		bool CheckValue(tm * tmValue, int index = -1, int relType = REL_TYPE_EQUAL);
};


/****************************************************************

   Class : LicensePointList

   Description : Describes list of items of license info

*****************************************************************/
class LICENSEPOINT_API LicensePointsList : public SystemBase
{
	private: 

		// Count of license points
		int licensePointsCount;

		// License points List
		LicensePoint * licensePoints[VALUES_COUNT];

		// Log writer instance
		LogWriter * logWriter;

		// Write message to Log-file
		int WriteToLog(char * message);


		// Define delemit char
		bool IsDelimit(char c, char * delLst, int lstSize);

		// Get current value of license info field
		int GetFieldValue(char * inpStr, int pos, char * outStr, int * retFlag);
		
		// Prepare delimeter as string
		void GenerateDelimitString(char * delStr, char * delList, int delLstSize);


	public:

		// Constructor
		LicensePointsList(unsigned long dllUserID, LogWriter * logWriter);

		// Constructor
		LicensePointsList(unsigned long dllUserID, char * licenseString, LogWriter * logWriter);

		// Destructor
		virtual ~LicensePointsList(void);

		// Parse license string
		bool ParseLicenseString(char * licenseString);

		// Make license string
		char * MakeLicenseString(char * outLicenseString);
		
		// Clear list
		void Clear(void);

		// Add license point to list
		LicensePoint * Add(LicensePoint * licensePoint);

		// Add license point to list
		LicensePoint * Add(char * id, char * name, char * description, int type, int valuesCount, ...);

		// Del license point by index
		bool Del(int index);

		// Operator []
		LicensePoint * operator [] (int index);

		// Count of license points
		int Count(void);

		// Find license point
		int Find(char * id);
};


#endif