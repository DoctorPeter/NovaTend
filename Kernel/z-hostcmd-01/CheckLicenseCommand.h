/****************************************************************

   Solution : NovaTend

   Project : z-hostcmd-01.dll

   Module : CheckLicenseCommand.h

   Description :  this module defines interface of
				  class CheckLicenseCommand

*****************************************************************/

#include <Command.h>
#include <LicenseManager.h>

#ifdef ZHOSTCMD01_EXPORTS
#define CHECK_LICENSE_CMD_API __declspec(dllexport)
#else
#define CHECK_LICENSE_CMD_API __declspec(dllimport)
#endif

#ifndef CHECK_LICENSE_CMD_H
#define CHECK_LICENSE_CMD_H

/****************************************************************

   Class : CheckLicenseCommand

   Description : Check license information.

*****************************************************************/
class CHECK_LICENSE_CMD_API CheckLicenseCommand : public Command
{
	private:

		// License manager instance
		LicenseManager * licenseManager;

	public:

		// Constructor
		CheckLicenseCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~CheckLicenseCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif