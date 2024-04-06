/****************************************************************

   Solution : NovaTend

   Project : z-desktopcmd-01.dll

   Module : GetCamSnapshotCommand.cpp

   Description :  this module implements methods of
				  class GetCamSnapshotCommand

*****************************************************************/

#include "stdafx.h"
#include "GetCamSnapshotCommand.h"
#include "ISampleGrabberCB.h"
#include <CommandHistoryManager.h>

// z-desktopcmd-01.dll definition structure
extern DLL_COMMON_DEFINITION zDesktopCmdDllDefinition;
 
/****************************************************************

   Class : GetCamSnapshotCommand

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
GetCamSnapshotCommand :: GetCamSnapshotCommand(unsigned long dllUserID, LogWriter * logWriter) : Command(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : constructor");
	#endif

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);   
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : Destructor

*****************************************************************/
GetCamSnapshotCommand :: ~GetCamSnapshotCommand(void)
{
	CoUninitialize();

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : destructor");
	#endif
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : Execute

   Parameters :
			Input : 
				parameters - list of commands parameters

	Return : list of result commands parameters

	Description : Execte command

*****************************************************************/
PCOMMAND_PARAMETER_LIST GetCamSnapshotCommand :: Execute(PCOMMAND_PARAMETER_LIST parameters)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : Execute. Start");
	#endif

	PCOMMAND_PARAMETER_LIST result = NULL;

	// Check input parameters list
	if ((!parameters) ||
		(parameters) &&
	   ((parameters -> paramCount == 0) ||
		(parameters -> paramCount == 1)))
	{
		// Try to run grabber
		PBITMAPINFO pResultBitmap;
		size_t lBufferSize = GrabBitmap(&pResultBitmap);
		
		if (lBufferSize != 0)
		{
			// Create serialization manager instance
			SerializationManager * serializationManager = new SerializationManager(zDesktopCmdDllDefinition.dllID, logWriter);
		
			// Get snapshot
			int snapShotBufferSize = 0;
			char * snapShotBuffer = MapBitmapToMemory(pResultBitmap, lBufferSize, &snapShotBufferSize);
			
			if (snapShotBuffer)
			{
				// Create result parameters list
				result = serializationManager -> CreateCommandParameterList();

				if (result)
				{
					result -> paramCount = 1;
					result -> paramList[0] = serializationManager -> PackBinary((unsigned char*)snapShotBuffer, snapShotBufferSize, RETURN_CMD_DATA);

					free(snapShotBuffer);
				}
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
					else
						WriteToLog("GetCamSnapshotCommand : Execute. Can't create result parameters list!");
				#endif
			}

			// Save command to history
			if ((parameters -> paramCount == 1) &&
				(parameters -> paramList[0]) &&
				(parameters -> paramList[0] -> paramType == INPUT_CMD_DATA) &&
				(parameters -> paramList[0] -> paramDataType == DWORD_DATA))
			{
				int userID = serializationManager -> UnpackDWORD(parameters -> paramList[0]);
				CommandHistoryManager * commandHistoryManager = new CommandHistoryManager(zDesktopCmdDllDefinition.dllID, logWriter);
				commandHistoryManager -> SaveCommand(CMD_GET_CLIENT_CAM_SNAPSHOT, userID, parameters, result);
				delete commandHistoryManager;
			}

			// Delete serialization manager instance
			delete serializationManager;

			free(pResultBitmap);
		}
	}
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		else
			WriteToLog("GetCamSnapshotCommand : Execute. Wrong input parameters!");

		WriteToLog("GetCamSnapshotCommand : Execute. Done");
	#endif

	return result;
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : GrabBitmap

   Parameters :
			Output : 
				pBitmap - bitmap info structure

	Return : size of bitmap info structure

	Description : Graph filter creation, selecting capture device, 
	              attaching grab filter, run media

*****************************************************************/
size_t GetCamSnapshotCommand :: GrabBitmap(BITMAPINFO ** pBitmap)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : GrabBitmap. Start");
	#endif

    USES_CONVERSION;
    CComPtr<IBaseFilter>    pSource;
    CComPtr<IVideoWindow>   pVideoWindow;
    CComPtr<ISampleGrabber> pGrabber;
    CComPtr<IGraphBuilder>  pGraph;
    HRESULT hr;

	ZeroMemory(&cbInfo, sizeof(CALLBACKINFO));

    // Create the sample grabber
    pGrabber.CoCreateInstance( CLSID_SampleGrabber );
    if( !pGrabber )
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Can't create grabber!");
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Done");
		#endif

        return 0;
    }

    CComQIPtr< IBaseFilter, &IID_IBaseFilter > pGrabberBase( pGrabber );

    // Get whatever capture device exists (we get first device)
	GetDefaultCapDevice(&pSource);
	if( !pSource )
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. No capture device!");
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Done");
		#endif

        return 0;
    }

    // Create the filter graph
    pGraph.CoCreateInstance( CLSID_FilterGraph );
    if( !pGraph )
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Can't create graph filter!");
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Done");
		#endif

        return 0;
    }

    // Put them in the graph
    hr = pGraph -> AddFilter( pSource, L"Source" );
    hr = pGraph -> AddFilter( pGrabberBase, L"Grabber" );

    // Tell the grabber to grab 24-bit video
    CMediaType GrabType;
    GrabType.SetType( &MEDIATYPE_Video );
	GrabType.SetSubtype( &MEDIASUBTYPE_RGB24 );
    hr = pGrabber -> SetMediaType( &GrabType );

    // Get the output pin and the input pin
    CComPtr< IPin > pSourcePin;
    CComPtr< IPin > pGrabPin;

    pSourcePin = GetOutPin( pSource, 0 );
    pGrabPin   = GetInPin( pGrabberBase, 0 );

    // Connect webcamera and greabber
    hr = pGraph -> Connect( pSourcePin, pGrabPin );
    if( FAILED( hr ) )
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Can't connect to camera!");
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Done");
		#endif

        return 0;
    }

    // Ask for the connection media type
    AM_MEDIA_TYPE mt;
    hr = pGrabber -> GetConnectedMediaType( &mt );
	
	// Write the bitmap format
    VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat;
    memset( &(cbInfo.bih), 0, sizeof( cbInfo.bih ) );
    cbInfo.bih.biSize = sizeof( cbInfo.bih );
    cbInfo.bih.biWidth = vih -> bmiHeader.biWidth;
    cbInfo.bih.biHeight = vih -> bmiHeader.biHeight;
    cbInfo.bih.biPlanes = 1;
    cbInfo.bih.biBitCount = 24;
	
	FreeMediaType( mt );

    // Render the grabber output pin (to a video renderer)
    CComPtr <IPin> pGrabOutPin = GetOutPin( pGrabberBase, 0 );
    hr = pGraph -> Render( pGrabOutPin );
    if( FAILED( hr ) )
    {
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Can't render the grabber output pin!");
			WriteToLog("GetCamSnapshotCommand : GrabBitmap. Done");
		#endif

        return 0;
    }

    // Buffer the samples
    hr = pGrabber -> SetBufferSamples( TRUE );

    // Only grab one at a time, stop stream after grabbing one sample
    hr = pGrabber -> SetOneShot( TRUE );

    // Set the callback, so we can grab the one sample
    //////hr = pGrabber->SetCallback( &CallbackGrabberObject, 1 );

    // Query the graph for the IVideoWindow interface and use it to
    // disable AutoShow.  This will prevent the ActiveMovie window from
    // being displayed while we grab bitmaps from the running movie.
    CComQIPtr< IVideoWindow, &IID_IVideoWindow > pWindow = pGraph;
    if (pWindow)
    {
        hr = pWindow -> put_AutoShow(OAFALSE);
    }


    // Activate the threads
    CComQIPtr< IMediaControl, &IID_IMediaControl > pControl( pGraph );
    hr = pControl -> Run( );
	
	// Wait for the graph to settle
    CComQIPtr< IMediaEvent, &IID_IMediaEvent > pEvent( pGraph );
    long EvCode = 0;
    hr = pEvent -> WaitForCompletion( INFINITE, &EvCode );

	// Find the required buffer size.
    hr = pGrabber -> GetCurrentBuffer(&cbInfo.lBufferSize, NULL);
    if (FAILED(hr))
    {
		return 0;
    }

    cbInfo.pBuffer = (BYTE*)CoTaskMemAlloc(cbInfo.lBufferSize);
    if (!cbInfo.pBuffer) 
    {
        hr = E_OUTOFMEMORY;
		return 0;
    }

    hr = pGrabber -> GetCurrentBuffer(&cbInfo.lBufferSize, (long*)cbInfo.pBuffer);
    if (FAILED(hr))
    {
		CoTaskMemFree(cbInfo.pBuffer);
		return 0;
    }

	// Calc bitmap info size
    UINT bmiSize = (cbInfo.bih.biSize != 0) ? cbInfo.bih.biSize : sizeof(BITMAPINFOHEADER);
    cbInfo.biSize =  bmiSize + cbInfo.bih.biClrUsed * sizeof(RGBQUAD);

    ULONG Size = cbInfo.biSize + cbInfo.lBufferSize;
    // If we should return BITMAPINFO
    if(pBitmap) 
    {
		*pBitmap = (BITMAPINFO *)malloc(sizeof(BYTE) * Size);
		if(*pBitmap) 
		{
			(**pBitmap).bmiHeader = cbInfo.bih;
			CHAR *pBitmapData = (CHAR *)(*pBitmap) + cbInfo.biSize;
			memcpy(pBitmapData, cbInfo.pBuffer, cbInfo.lBufferSize);
		}
    }

	CoTaskMemFree(cbInfo.pBuffer);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : GrabBitmap. Done");
	#endif

    return Size;
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : GetPin

   Parameters :
			Input:
				pFilter - graph filter
				dirrequired - pin direction type

			Output : 
				ppPin - result pin

	Return : error code

	Description : retrieves a pin

*****************************************************************/
HRESULT GetCamSnapshotCommand :: GetPin( IBaseFilter * pFilter, PIN_DIRECTION dirrequired, int iNum, IPin **ppPin)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : GetPin. Start");
	#endif

    CComPtr< IEnumPins > pEnum;
    *ppPin = NULL;

    HRESULT hr = pFilter -> EnumPins(&pEnum);
    if(FAILED(hr))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GetPin. Error of pins enumeration");
			WriteToLog("GetCamSnapshotCommand : GetPin. Done");
		#endif

        return hr;
	}

    ULONG ulFound;
    IPin *pPin;
    hr = E_FAIL;

    while(S_OK == pEnum -> Next(1, &pPin, &ulFound))
    {
        PIN_DIRECTION pindir = (PIN_DIRECTION)3;

        pPin -> QueryDirection(&pindir);
        if(pindir == dirrequired)
        {
            if(iNum == 0)
            {
				// Return the pin's interface
                *ppPin = pPin;  

				// Found requested pin, so clear error
                hr = S_OK;      

                break;
            }
            iNum--;
        } 

        pPin -> Release();
    } 

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : GetPin. Done");
	#endif

    return hr;
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : GetInPin

   Parameters :
			Input:
				pFilter - graph filter
				nPin - pins number

	Return : result pin

	Description : retrieves input pin

*****************************************************************/
IPin * GetCamSnapshotCommand :: GetInPin( IBaseFilter * pFilter, int nPin )
{
    CComPtr<IPin> pComPin = 0;
    GetPin(pFilter, PINDIR_INPUT, nPin, &pComPin);
    return pComPin;
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : GetOutPin

   Parameters :
			Input:
				pFilter - graph filter
				nPin - pins number

	Return : result pin

	Description : retrieves output pin

*****************************************************************/
IPin * GetCamSnapshotCommand :: GetOutPin( IBaseFilter * pFilter, int nPin )
{
    CComPtr<IPin> pComPin = 0;
    GetPin(pFilter, PINDIR_OUTPUT, nPin, &pComPin);
    return pComPin;
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : GetDefaultCapDevice

   Parameters :
			Output:
				ppCap - base capture device graph filter

  Description : get default capture device

*****************************************************************/
void GetCamSnapshotCommand :: GetDefaultCapDevice(IBaseFilter **ppCap)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Start");
	#endif

	HRESULT hr;

	ASSERT(ppCap);

	if (!ppCap)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Can't get capture device graph filter");
			WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Done");
		#endif

		return;
	}

	*ppCap = NULL;
	
	// Create an enumerator
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	pCreateDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
	
	ASSERT(pCreateDevEnum);
	if(!pCreateDevEnum)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Can't get capture device enumerator");
			WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Done");
		#endif

		return;
	}

	// Enumerate video capture devices
	CComPtr<IEnumMoniker> pEm;
	pCreateDevEnum -> CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);

	ASSERT(pEm);
	if(!pEm)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Capture device not found!");
			WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Done");
		#endif

		return;
	}

	pEm -> Reset();

	// Go through and find first capture device
	//
	while (true)
	{
		ULONG ulFetched = 0;
		CComPtr<IMoniker> pM;
		hr = pEm -> Next(1, &pM, &ulFetched);
		if(hr != S_OK)
			break;

		// Ask for the actual filter
		hr = pM -> BindToObject(0,0,IID_IBaseFilter, (void **)ppCap);
		if(*ppCap)
			break;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : GetDefaultCapDevice. Done");
	#endif
}

/****************************************************************

   Class : GetCamSnapshotCommand

   Method : MapBitmapToMemory

   Parameters :
			Input:
				pBmpInf - bitmap info structure
				bmpSize - bitmap size

			Output:
				resBufSize - result buffer size

	Return : buffer with BMP image

	Description : Map bitmap to memory

*****************************************************************/
char * GetCamSnapshotCommand :: MapBitmapToMemory(PBITMAPINFO pBmpInf, int bmpSize, int * resBufSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : MapBitmapToMemory. Start");
	#endif

	*resBufSize = 0;
	char * fResult = NULL;

	try
	{
		*resBufSize = sizeof(BITMAPFILEHEADER) + sizeof(pBmpInf -> bmiHeader) + (bmpSize - sizeof(BITMAPINFOHEADER));
		fResult = (char *)malloc(*resBufSize);

		if (fResult)
		{
			int bufferSize = bmpSize - sizeof(BITMAPINFOHEADER);		    

			BITMAPFILEHEADER bfh;
			memset(&bfh, 0, sizeof(bfh));
			bfh.bfType = 'MB';
			bfh.bfSize = sizeof(bfh) + bufferSize + sizeof(BITMAPINFOHEADER);
			bfh.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
	
			char * pTmp = fResult;
			memcpy(pTmp, &bfh, sizeof(bfh));
			pTmp += sizeof(bfh);

			memcpy(pTmp, &pBmpInf -> bmiHeader, sizeof(pBmpInf -> bmiHeader));
			pTmp += sizeof(pBmpInf -> bmiHeader);
	
			memcpy(pTmp, ((char *)pBmpInf + sizeof(BITMAPINFOHEADER)), bufferSize);
			pTmp += bufferSize;

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
				WriteToLog("GetCamSnapshotCommand : MapBitmapToMemory. Result bitmap created successfully!");
			#endif
		}
		else
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
				WriteToLog("GetCamSnapshotCommand : MapBitmapToMemory. Can't allocate memory for result buffer!");
			#endif

			*resBufSize = 0;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
			WriteToLog("GetCamSnapshotCommand : MapBitmapToMemory. Error of bitmap creation!");
		#endif

		*resBufSize = 0;
		fResult = NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_DESKTOP_CMD)
		WriteToLog("GetCamSnapshotCommand : MapBitmapToMemory. Done");
	#endif

	return fResult;
}