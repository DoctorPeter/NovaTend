/****************************************************************

   Solution : NovaTend

   Project : z-licenseman-01.dll

   Module : LicenseManager.h

   Description :  Defines the interface of class LicenseManager

*****************************************************************/

#include <LogWriter.h>
#include <ContentDataDef.h>
#include <DatabaseManager.h>

#include "LicensePoint.h"
#include "LicenseDataDef.h"

#ifdef ZLICENSEMAN01_EXPORTS
#define LICENSEMAN_API __declspec(dllexport)
#else
#define LICENSEMAN_API __declspec(dllimport)
#endif

#ifndef LICENSEMAN_H
#define LICENSEMAN_H

/****************************************************************

   Class : LicenseManager

   Description : Responsible for licensing management

*****************************************************************/
class LICENSEMAN_API LicenseManager : public SystemBase
{
	private:
	
		// Log writer instance
		LogWriter * logWriter;

		// database manager instance
		DatabaseManager * dbManager;


		// Pointer to license point list
		LicensePointsList * licensePointsList;

		
	public:


		// Constructor
		LicenseManager(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~LicenseManager(void);
				
		// Read license info
		bool ReadLicenseInfo(void);

		// Save license info
		bool WriteLicenseInfo(void);

		// Add license point to list
		bool AddLicensePoint(LicensePoint * licensePoint);

		// Add license point to list
		bool AddLicensePoint(char * id, char * name, char * description, int type, int valuesCount, ...);

		// Delete license point to list
		bool DelLicensePoint(int index);

		// Delete license point to list
		bool DelLicensePoint(char * id);

		// Check licene point value
		bool CheckLicensePointValue(char * id, char * strValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Check licene point value
		bool CheckLicensePointValue(char * id, int intValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Check licene point value
		bool CheckLicensePointValue(char * id, tm * tmValue, int index = -1, int relType = REL_TYPE_EQUAL);

		// Get license point value value
		char * GetLicensePointValue(char * id, char * outValue, int index = 0);

		// Get license point value value
		int GetLicensePointValue(char * id, int index = 0);

		// Get license point value value
		tm * GetLicensePointValue(char * id, tm * outValue, int index = 0);
		
		// Write message to Log-file
		int WriteToLog(char * message);
};

#endif