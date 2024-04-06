/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : CriticalSection.h

   Description :  Wrapper for critical sections management.

*****************************************************************/
#include <windows.h>

#ifdef ZSYSTEMBASE01_EXPORTS
#define CRITICAL_SECTION_API __declspec(dllexport)
#else
#define CRITICAL_SECTION_API __declspec(dllimport)
#endif

#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

/****************************************************************

   Class : CriticalSection

   Description : Wrappper of critical sections
                
*****************************************************************/
class CRITICAL_SECTION_API CriticalSection	
{
	private:
		
		// Disable copy constructor
		CriticalSection(const CriticalSection&) = delete;
		
		// Disable operator =
		CriticalSection& operator=(const CriticalSection&) = delete;
    
		// Critical section descriptor
		CRITICAL_SECTION internalCriticalSection;

	public:

		// Constructor
		CriticalSection(void);
		
		// Destructor
		virtual ~CriticalSection(void);

		// Enter to critical section
		void Enter(void);
    
		// Leave critical section
		void Leave(void);
};


/****************************************************************

   Class : CriticalSectionManager

   Description : Critical sections manager
                
*****************************************************************/
class CRITICAL_SECTION_API CriticalSectionManager	
{
	private:
		
		// Disable copy constructor
		CriticalSectionManager(const CriticalSectionManager&) = delete;
		
		// Disable operator =
		CriticalSectionManager& operator=(const CriticalSectionManager&) = delete;
    
		// Critical section instance
		CriticalSection * criticalSection;

	public:

		// Constructor
		CriticalSectionManager(CriticalSection * section);
		
		// Destructor
		~CriticalSectionManager(void);
};

// Macros for using of critical section manager
#define LOCK_SECTION(x) CriticalSectionManager criticalSectionManager(x);

#endif