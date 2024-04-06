/****************************************************************

   Solution : NovaTend

   Project : z-hubcmd-01.dll

   Module : GetGeoLocationCommand.h

   Description :  this module defines interface of
				  class GetGeoLocationCommand

*****************************************************************/

#include <Command.h>


#ifdef ZHUBCMD01_EXPORTS
#define GET_GEO_LOCATION_CMD_API __declspec(dllexport)
#else
#define GET_GEO_LOCATION_CMD_API __declspec(dllimport)
#endif

#ifndef GET_GEO_LOCATION_CMD_H
#define GET_GEO_LOCATION_CMD_H

/****************************************************************

   Class : GetGeoLocationCommand

   Description : Get geo location coords

*****************************************************************/
class GET_GEO_LOCATION_CMD_API GetGeoLocationCommand : public Command
{
	public:

		// Constructor
		GetGeoLocationCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetGeoLocationCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif