/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : DllID.h

   Description :  this module defines structure for
				  description of each DLL-module and
				  for communication between DLLs

*****************************************************************/

#ifndef DLLID_H
#define DLLID_H

#include "DllIDList.h"

// Maximum length of DLL description string
#define DESCRIPTION_SIZE 256

// Maximum count of DLL users
#define LEGAL_USER_LEN  32 

// Unique DLL identification type
typedef unsigned long DLL_ID;

// Structure for description each DLL-module 
// and for communication between DLLs
typedef struct _dllCommonDefinition
{
	DLL_ID dllID; // Unique DLL number

	unsigned int dllVersion; // Version of DLL

	char Description[DESCRIPTION_SIZE]; // DLL description

	unsigned short userCount; // Count of DLL users

	DLL_ID legalUsers[LEGAL_USER_LEN]; // List of DLL users

} DLL_COMMON_DEFINITION, * PDLL_COMMON_DEFINITION;

#endif