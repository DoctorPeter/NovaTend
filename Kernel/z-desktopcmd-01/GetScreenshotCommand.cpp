/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : GetScreenshotCommand.cpp

   Description :  this module implements methods of
				  class GetScreenshotCommand

*****************************************************************/

#include "stdafx.h"
#include "GetScreenshotCommand.h"
#include <CommandHistoryManager.h>

// z-desktopcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zDesktopCmdDllDefinition;
 
/****************************************************************

   Class : GetScreenshotCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetScreenshotCommand :: GetScreenshotCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetScreenshotCommand : constructor");
	#endif
}

/****************************************************************

   Class : GetScreenshotCommand

   Method : Destructor

*****************************************************************/
GetScreenshotCommand :: ~GetScreenshotCommand(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetScreenshotCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetScreenshotCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetScreenshotCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetScreenshotCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) ||
		(parameters) &&
	   ((parameters -> paramCount == 0) ||
		(parameters -> paramCount == 1)))
	{
		// Get screenshot
        int screenShotBufferSize = 0;
		char * screenShotBuffer = ScreenToBmp24Stretch(2, &screenShotBufferSize);
		
		// Create serialization manager instance
		SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);
		
		// Create result parameters list
		result = serializationManager -> CreateCommandParameterList();

		if ((result) && (screenShotBuffer) && (screenShotBufferSize > 0))
		{
			result -> paramCount = 1;
			result -> paramList[0] = serializationManager -> PackBinary((unsigned char*)screenShotBuffer, screenShotBufferSize, RETURN_CMD_DATA);

			free(screenShotBuffer);
		}
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			else
				WriteToLog("GetScreenshotCommand : Execute. Can't create result parameters list!");
		#endif

		// Save command to history
		if ((parameters -> paramCount == 1) &&
			(parameters -> paramList[0]) &&
			(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
			(parameters -> paramList[0] -> paramDataType == DWORD_DATA))

		{
			int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
			CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zDesktopCmdDllDefinition.dllID, logWriter);
			commandHistoryManager -> SaveCommand(CMD_GET_CLIENT_SCREEN_SHOT, userID, parameters, result);
			delete commandHistoryManager;
		}

		// Delete serialization manager instance
		delete serializationManager;
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		else
			WriteToLog("GetScreenshotCommand : Execute. Wrong input parameters!");

		WriteToLog("GetScreenshotCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetScreenshotCommand

   Method : ScreenToBmp24Stretch

   Parameters :
			Input : 
				bZoomOut - zoom value
			Output:
				resBufSize - size of result bmp
	
   Return : bmp image buffer

   Description : Get screen shot and put it to memory
				 in BMP format

*****************************************************************/
char * GetScreenshotCommand :: ScreenToBmp24Stretch(BYTE bZoomOut, int * resBufSize)
{
	// Zoom correction
	if (bZoomOut < 1) bZoomOut = 1;
	if (bZoomOut > 8) bZoomOut = 8;

	// Calculate image size
	DWORD width  = GetSystemMetrics(SM_CXSCREEN) / bZoomOut;
	DWORD height = GetSystemMetrics(SM_CYSCREEN) / bZoomOut;

	// Get display DC
	HDC hDCScr = GetDC(NULL);

	// Create compatible DC
	HDC hDCMem = CreateCompatibleDC(hDCScr);

	// Create compatible bitmap 
	HBITMAP hBmMem = CreateCompatibleBitmap(hDCScr, width, height);
	
	// Select the bitmap into the compatible DC
	HBITMAP hBmOld = (HBITMAP)SelectObject(hDCMem, hBmMem);

	// Set the bitmap stretching mode in the specified device context
	if (!SetStretchBltMode(hDCMem, HALFTONE))
		SetStretchBltMode(hDCMem, COLORONCOLOR);

	// Stretch source bitmap in memory
	StretchBlt(hDCMem, 0, 0, width, height, hDCScr, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SRCCOPY);
	
	// Delete display device context
	ReleaseDC(NULL, hDCScr);

	// Allocate memory for bitmap info structure
	PBITMAPINFO pBmInf = (PBITMAPINFO)calloc(1, sizeof(BITMAPINFO));
	
	// Result data
	char * fResult = NULL;
	*resBufSize = 0;

	// Validate pointers
	if ((hDCMem != NULL) && (hBmMem != NULL) && (pBmInf != NULL))
	{
		// Fill bitmap info structure
		pBmInf -> bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		pBmInf -> bmiHeader.biWidth = width;
		pBmInf -> bmiHeader.biHeight = height;
		pBmInf -> bmiHeader.biCompression = BI_RGB;
		pBmInf -> bmiHeader.biBitCount = 24;
		pBmInf -> bmiHeader.biClrUsed = 16777216; // 2 ^ 24
		pBmInf -> bmiHeader.biPlanes = 1;
		pBmInf -> bmiHeader.biSizeImage = (width + 7) / 8 * height * 24;

		// Allocate bitmap data buffer
		PBYTE pBmData = (PBYTE)calloc(pBmInf -> bmiHeader.biSizeImage, 1);

		// Validate allocation result
		if (pBmData != NULL)
		{
			// Get bitmap data
			if (GetDIBits(hDCMem, hBmMem, 0, height, pBmData, pBmInf, DIB_RGB_COLORS))
			{
				// Create bitmap header
				BITMAPFILEHEADER BmFileHdr;
				BmFileHdr.bfType = 0x4D42; // "BM"
				BmFileHdr.bfReserved1 = 0;
				BmFileHdr.bfReserved2 = 0;
				BmFileHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
				BmFileHdr.bfSize = BmFileHdr.bfOffBits + pBmInf -> bmiHeader.biSizeImage;

				// Allocate memory for all bitmap image
				fResult = (char *)malloc(sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pBmInf -> bmiHeader.biSizeImage);

				// Check allocation result
				if(fResult)
				{
					*resBufSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pBmInf -> bmiHeader.biSizeImage;

					// Copy bmp file header
					char * pTmp = fResult;
					memcpy(pTmp, &BmFileHdr, sizeof(BITMAPFILEHEADER));
					pTmp += sizeof(BITMAPFILEHEADER);

					// Copy bmp info header structure
					memcpy(pTmp, pBmInf, sizeof(BITMAPINFOHEADER));
					pTmp += sizeof(BITMAPINFOHEADER);

					// Copy bmp data
					memcpy(pTmp, pBmData, pBmInf -> bmiHeader.biSizeImage);
					pTmp += pBmInf -> bmiHeader.biSizeImage;
				} 
			} 
			
			// Free bmp data
			free(pBmData);
		} 
	} 

	// Free bmp info header structure
	if(pBmInf != NULL) 
		free(pBmInf);
	
	// Delete objects
	SelectObject(hDCMem, hBmOld);
	DeleteDC(hDCMem);
	DeleteObject(hBmMem);
	
	// Return bitmap buffer
	return fResult;
}