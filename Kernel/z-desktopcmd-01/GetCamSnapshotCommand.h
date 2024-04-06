/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : GetCamSnapshotCommand.h

   Description :  this module defines interface of
				  class GetCamSnapshotCommand

*****************************************************************/

#include <Command.h>

#ifdef ZDESKTOPCMD01_EXPORTS
#define SNAPSHOT_CMD_API __declspec(dllexport)
#else
#define SNAPSHOT_CMD_API __declspec(dllimport)
#endif

#ifndef SNAPSHOT_CMD_H
#define SNAPSHOT_CMD_H

#include "streams.h" // from baseclasses DirectShow Samplpes
#include <windows.h>
#include <stdio.h>
#include <ObjIdl.h>
#include <tchar.h>
#include <Strsafe.h>
#include <Strmif.h>  
#include <atlbase.h>  
#include "ISampleGrabberCB.h"


// Callback info structure
typedef struct _callbackinfo 
{
	double dblSampleTime;
	long lBufferSize;
	BYTE *pBuffer;
	BITMAPINFOHEADER bih;
	DWORD biSize;
} CALLBACKINFO;

/****************************************************************

   Class : GetCamSnapshotCommand

   Description : Get camera snapshot picture.

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class SNAPSHOT_CMD_API GetCamSnapshotCommand : public Command
{
	private:
		
		// Callback info structure
		CALLBACKINFO cbInfo;		
		
		// Retrieves a pin
		HRESULT GetPin(IBaseFilter * pFilter, PIN_DIRECTION dirrequired,  int iNum, IPin **ppPin);

		// Retrieves input pin
		IPin * GetInPin(IBaseFilter *pFilter, int Num);

		// Retrieves output pin
		IPin * GetOutPin(IBaseFilter *pFilter, int Num);

		// Get default capture device
		void GetDefaultCapDevice(IBaseFilter ** ppCap);

		// Graph filter creation, selecting capture device, 
	    // attaching grab filter, run media
		size_t GrabBitmap(BITMAPINFO **);

		// Map bitmap to memory
		char * MapBitmapToMemory(PBITMAPINFO bitmap, int bmpSize, int * resBufSize);

	public:

		// Constructor
		GetCamSnapshotCommand(unsigned long dllUserID, LogWriter * logWriter);

		// Desctructor
		virtual ~GetCamSnapshotCommand(void);
		
		// Execute command
		virtual PCOMMAND_PARAMETER_LIST Execute(PCOMMAND_PARAMETER_LIST parameters);
};

#endif