/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : CriticalSection.cpp

   Description :  this module implements methods of 
				  class CriticalSection and CriticalSectionManager

*****************************************************************/

#include "stdafx.h"
#include "CriticalSection.h"


/****************************************************************

		Methods of class CriticalSection

*****************************************************************/

/****************************************************************

   Class : CriticalSection

   Method : Constructor

*****************************************************************/
CriticalSection :: CriticalSection(void)
{
	InitializeCriticalSection(&internalCriticalSection); 
}
		
/****************************************************************

   Class : CriticalSection

   Method : Destructor

*****************************************************************/
CriticalSection :: ~CriticalSection(void)
{
	DeleteCriticalSection(&internalCriticalSection); 
}

/****************************************************************

   Class : CriticalSection

   Method : Enter

   Description : Enter to critical section

*****************************************************************/
void CriticalSection :: Enter(void)
{
	EnterCriticalSection(&internalCriticalSection);
}

/****************************************************************

   Class : CriticalSection

   Method : Leave

   Description : Leave critical section

*****************************************************************/
void CriticalSection :: Leave(void)
{
	LeaveCriticalSection(&internalCriticalSection);
}


/****************************************************************

		Methods of class CriticalSectionManager

*****************************************************************/

/****************************************************************

   Class : CriticalSectionManager

   Method : Constructor

*****************************************************************/
CriticalSectionManager :: CriticalSectionManager(CriticalSection * section) : criticalSection(section)
{
	criticalSection -> Enter();
}
		
/****************************************************************

   Class : CriticalSectionManager

   Method : Destructor

*****************************************************************/
CriticalSectionManager :: ~CriticalSectionManager(void)
{
	criticalSection -> Leave();
}