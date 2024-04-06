/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetHardwareInfoCommand.h

   Description :  this module defines interface of
				  class GetHardwareInfoCommand

*****************************************************************/

#include <Command.h>
#include <SerializationManager.h>

#define _WIN32_DCOM

#include <comdef.h>
#include <Wbemidl.h>
#include <comutil.h>

#ifdef ZHUBCMD01_EXPORTS
#define HARDWARE_CMD_API __declspec(dllexport)
#else
#define HARDWARE_CMD_API __declspec(dllimport)
#endif

#ifndef HARDWARE_CMD_H
#define HARDWARE_CMD_H

/****************************************************************

   Class : GetHardwareInfoCommand

   Description : Get client machine hardware information

*****************************************************************/
class HARDWARE_CMD_API GetHardwareInfoCommand : public Command
{
	private:
		
		// Serialization manager instance
		SerializationManager * serializationManager;

		// WMI locator interface
		IWbemLocator * m_pLoc;

		// Execute WMI query
		IEnumWbemClassObject*	ExecuteWQL(IWbemServices * pSvc, char * query);

		// Get LONG type data
		PCOMMAND_PARAMETER		GetUINTData(IEnumWbemClassObject * pEnumerator, WCHAR * wminame);

		// Get string type data
		PCOMMAND_PARAMETER		GetStringData(IEnumWbemClassObject * pEnumerator, WCHAR * wminame);

	public:

		// Constructor
		GetHardwareInfoCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetHardwareInfoCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif