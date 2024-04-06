/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : InfoWindow.cpp

   Description :  Implements methods of class
                  InfoWindow

*****************************************************************/

#include "InfoWindow.h"
#include <strsafe.h>

//#include <stdio.h>

// Custom messages for managing the behavior of the window thread.
#define WM_EXIT_THREAD              WM_USER + 1

// Self pointers

int windowPointersCount;

InfoWindow * windowPointers[MAX_SCREEN_COUNT];

InfoWindow * FindWindowPointerByHWND(HWND hWnd)
{
	InfoWindow * resWnd = NULL;

	for (int i = 0; i < windowPointersCount; i++)
		if ((windowPointers[i]) &&
			(windowPointers[i] -> _wndContainer -> hWnd == hWnd))
			{
				resWnd = windowPointers[i];
				break;
			}
	
	return resWnd;
}

/****************************************************************

   Class :  InfoWindow

   Method : Constructor
  
*****************************************************************/
InfoWindow :: InfoWindow() : _hInst(NULL), _wndContainer(NULL)
{
	hPasswordBox = NULL;
	pwdIndex = -1;
	osVersion = OS_UNKNOWN;
	SetCredentialProviderCredential(NULL, NULL);
	wcscpy(currPwdSymbols, L"");
}

/****************************************************************

   Class :  InfoWindow

   Method : Destructor
  
*****************************************************************/
InfoWindow :: ~InfoWindow()
{
	for (int i = 0; i < windowPointersCount; i++)
		if (windowPointers[i] == this)
			windowPointers[i] = NULL;

	// If we have an active window, we want to post it an exit message.
    if ((_wndContainer) && (_wndContainer -> hWnd))
    {
        // Send close message
		SendMessage(_wndContainer -> hWnd, WM_CLOSE, 0, 0);
		
		// Wait for thread infinite
		WaitForSingleObject(_hThread, INFINITE);

		// Close thread handle
		CloseHandle(_hThread);

		// Unregister class
		UnregisterClass(_wndContainer -> windowName, _hInst);
		
		// Delete objects
		for(int i = 0; i < _wndContainer -> windowObjectsCount; i++)
		{
			if(_wndContainer -> windowObjects[i] -> hBitmap)
				DeleteObject(_wndContainer -> windowObjects[i] -> hBitmap);

			if(_wndContainer -> windowObjects[i] -> hFont)
				DeleteObject(_wndContainer -> windowObjects[i] -> hFont);
		}

		DestroyWindow(_wndContainer -> hWnd);
    }
}

/****************************************************************

   Class :  InfoWindow

   Method : Initialize

   Parameters :
			Input : 
				pCredential - pointer to windows credential
			
	Return : Error code

	Description : Performs the work required to spin off our 
				  message so we can listen for events.
  
*****************************************************************/
HRESULT InfoWindow :: Initialize(__in PSUB_WINDOW pWndCnt, __in int wndPntCount, __in InfoWindow ** wndPnts)
{
    HRESULT hr = S_OK;

	_wndContainer = pWndCnt;


	windowPointersCount = wndPntCount;

	for(int i = 0; i < windowPointersCount; i++)
		windowPointers[i] = wndPnts[i];

    // Create and launch the window thread.
   _hThread = CreateThread(NULL, 0, _ThreadProc, this, 0, NULL);
   
	if (_hThread == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

/****************************************************************

   Class :  InfoWindow

   Method : SetCredentialProviderCredential

   Parameters :
			Input : 
				pCredProvCredentialEvents - pointer to credential 
											provider credential events
											instance

				pCredentialProviderCredential - pointer to credential 
												provider credential 
												instance

   Description : Set credential instance parameters
  
*****************************************************************/
void InfoWindow :: SetCredentialProviderCredential(ICredentialProviderCredentialEvents * pCredProvCredentialEvents, ICredentialProviderCredential * pCredentialProviderCredential)
{
	_pCredProvCredentialEvents = pCredProvCredentialEvents;
    _pCredentialProviderCredential = pCredentialProviderCredential;
}

/****************************************************************

   Class :  InfoWindow

   Method : _ShowWindow

   Parameters :
			Input : 
				cmdShow - show window command
			
	Return : Error code

	Description : Show and update window according to command
  
*****************************************************************/
HRESULT InfoWindow :: _ShowWindow(int cmdShow)
{
	HRESULT hr = S_OK;

	if ((_wndContainer) && (_wndContainer -> hWnd))
    {
		if (!ShowWindow(_wndContainer -> hWnd, cmdShow))
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
        }

		 if (SUCCEEDED(hr))
        {
           if (!UpdateWindow(_wndContainer -> hWnd))
		   {
              hr = HRESULT_FROM_WIN32(GetLastError());
           }
        }
	}

	return hr;
}

/****************************************************************

   Class :  InfoWindow

   Method : Show

	Return : Error code

	Description : Show window
  
*****************************************************************/
HRESULT InfoWindow :: Show()
{
	return _ShowWindow(SW_SHOW);
}

/****************************************************************

   Class :  InfoWindow

   Method : Hide

	Return : Error code

	Description : Hide window
  
*****************************************************************/
HRESULT InfoWindow :: Hide()
{
	return _ShowWindow(SW_HIDE);
}

/****************************************************************

   Class :  InfoWindow

   Method : _MyRegisterClass

	Return : Error code

	Description : Registers the window class.
				  This function and its usage are only necessary 
				  if you want this code to be compatible with Win32
				  systems prior to the 'RegisterClassEx'
				  function that was added to Windows 95. It is important
				  to call this function so that the application will get
				  'well formed' small icons associated with it.
  
*****************************************************************/
HRESULT InfoWindow :: _MyRegisterClass()
{
    WNDCLASSEX wcex = { sizeof(wcex) };
    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc      = _WndProc;
    wcex.hInstance        = _hInst;
    wcex.hIcon            = NULL;
    wcex.hCursor          = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName    = _wndContainer -> windowName;

    return RegisterClassEx(&wcex) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
}

/****************************************************************

   Class :  InfoWindow

   Method : _InitInstance

	Return : Error code

	Description : Saves instance handle and creates main window.
				  In this function, we save the instance handle
				  in a global variable and create and display 
				  the main program window.
  
*****************************************************************/
HRESULT InfoWindow :: _InitInstance()
{
    HRESULT hr = S_OK;

    // Create our window to receive events.
       
	if (!CreateInfoWindow())
		hr = HRESULT_FROM_WIN32(GetLastError());

	if (SUCCEEDED(hr))
    {
       hr = CreateWindowUI();
	}

    if (SUCCEEDED(hr))
    {
		hr = Show();
    }

    return hr;
}

/****************************************************************

   Class :  InfoWindow

   Method : CreateInfoWindow

	Return : window handle

	Description : Create window instance
  
*****************************************************************/
HWND InfoWindow :: CreateInfoWindow()
{
	DEVMODE devMode;
	devMode.dmSize = sizeof(devMode);
	
	// Get display settings
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);

	// Set window size
	SetUISize(&(_wndContainer -> widthPix), 
		      &(_wndContainer -> heightPix), 
			  _wndContainer -> widthPers,
			  _wndContainer -> heightPers, 
			  devMode.dmPelsWidth, 
			  devMode.dmPelsHeight);

	// Set window position
	SetUILocation(&(_wndContainer -> locationX), 
				  &(_wndContainer -> locationY), 
				  _wndContainer -> locationXPers,
			      _wndContainer -> locationYPers, 
				  devMode.dmPelsWidth, 
				  devMode.dmPelsHeight);
	
	// Create window
	_wndContainer -> hWnd = CreateWindowEx(WS_EX_TOPMOST, 
		_wndContainer -> windowName, 
		_wndContainer -> caption, 
		WS_POPUP,/*WS_BORDER,*/
		_wndContainer -> locationX, 
		_wndContainer -> locationY, 
		_wndContainer -> widthPix, 
		_wndContainer -> heightPix, 
		NULL,
        NULL, _hInst, NULL);

	if (_wndContainer -> windowTypeId == SOT_SYMBOL_BOXES_PWD_SCREEN)
		_wndContainer -> caption[0] = 0;
   	
	return _wndContainer -> hWnd;
}

/****************************************************************

   Class :  InfoWindow

   Method : CreateWindowUI

	Return : error code

	Description : Create window UI objects
  
*****************************************************************/
HRESULT InfoWindow :: CreateWindowUI()
{
	HRESULT hr = S_OK;
   
	for(int i = 0; i < _wndContainer -> windowObjectsCount; i++)
	{
		if (_wndContainer -> windowObjects[i])
			switch (_wndContainer -> windowObjects[i] -> objectTypeId)
			{
				case SOT_LARGE_TEXT :
				case SOT_SMALL_TEXT :
				case SOT_DATE_TIME_TEXT :
				case SOT_EDUCATION_LABEL :
				case SOT_LEGAL_DISCLAIMER_LABEL:
					{
						_wndContainer -> windowObjects[i] -> hWnd = CreateStaticTextUI(_wndContainer -> windowObjects[i], FALSE);
						break;
					}

				case SOT_BIG_TEXT_BLOCK :
				case SOT_EDU_LESSON_TEXT :
				case SOT_EDU_QUESTION_TEXT :
				case SOT_LEGAL_DISCLAIMER_TEXT :
				case SOT_SIMPLE_NOTICE_TEXT :
				case SOT_WARNING_NOTICE_TEXT :
					{
						_wndContainer -> windowObjects[i] -> hWnd = CreateStaticTextUI(_wndContainer -> windowObjects[i], TRUE);
						break;
					}
				
				case SOT_IMAGE:
				case SOT_EDU_LESSON_IMAGE:
				case SOT_LEGAL_DISCLAIMER_IMAGE:
					{
						_wndContainer -> windowObjects[i] -> hWnd = CreateImageUI(_wndContainer -> windowObjects[i]);
						break;
					}

				case SOT_BUTTON:
					{
						if (_wndContainer -> windowTypeId == SOT_SYMBOL_BOXES_PWD_SCREEN)
							_wndContainer -> windowObjects[i] -> hWnd = CreateButton(_wndContainer -> windowObjects[i]);
						break;
					}
			}
	}

	return hr;
}


/****************************************************************

   Class :  InfoWindow

   Method : SetUISize

   Parameters :
			Input : 
				widthPers - width of object in percents
				heightPers - height of object in percents
				parentWidth - parent absolute width
				parentHeight - parent absolute height

			Input/Output :
				widthPix - object absolute width
				heightPix - object absolute height

   Description : Set window UI object size
  
*****************************************************************/
void InfoWindow :: SetUISize(int *widthPix, int * heightPix, int widthPers, int heightPers, int parentWidth, int parentHeight)
{
	if ((*widthPix == 0) && (widthPers != 0))
		*widthPix = (parentWidth * widthPers)/100;
	
	if ((*widthPix != 0) && (*widthPix > parentWidth))
		*widthPix = parentWidth;

	if ((*heightPix == 0) && (heightPers != 0))
		*heightPix = (parentHeight * heightPers)/100;
	
	if ((*heightPix != 0) && (*heightPix > parentHeight))
		*heightPix = parentHeight;
}

/****************************************************************

   Class :  InfoWindow

   Method : SetUILocation

   Parameters :
			Input : 
				locationXPers - location X of object in percents
				locationYPers - location Y of object in percents
				parentWidth - parent absolute width
				parentHeight - parent absolute height

			Input/Output :
				locationX - object location X
				locationY - object location Y

   Description : Set window UI object position
  
*****************************************************************/
void InfoWindow :: SetUILocation(int * locationX, int * locationY, int locationXPers, int locationYPers, int parentWidth, int parentHeight)
{
	if (locationXPers > 0)
		*locationX = (parentWidth * locationXPers)/100;

	if (*locationX > parentWidth)
		*locationX = parentWidth - 5;

	if (locationYPers > 0)
		*locationY = (parentHeight * locationYPers)/100;

	if (*locationY > parentHeight)
		*locationY = parentHeight - 5;
}
/****************************************************************

   Class :  InfoWindow

   Method : CreateStaticTextUI

   Parameters :
			Input : 
				wndObject - window object descriptor
				large - large flag

   Return : window object handle

   Description : Create static text
  
*****************************************************************/
HWND InfoWindow :: CreateStaticTextUI(PWINDOW_OBJECT_DESCRIPTOR wndObject, BOOL large)
{
	
	// Set object size
	SetUISize(&(wndObject -> widthPix), 
			  &(wndObject -> heightPix), 
			  wndObject -> widthPers, 
			  wndObject -> heightPers, 
			  _wndContainer -> widthPix, 
			  _wndContainer -> heightPix);

	// Set window object position
	SetUILocation(&(wndObject -> locationX), 
				  &(wndObject -> locationY), 
				  wndObject -> locationXPers,
			      wndObject -> locationYPers, 
				  _wndContainer -> widthPix, 
				  _wndContainer -> heightPix);
	
	if (large)
	{
		// Create object
		wndObject -> hWnd = CreateWindow(L"EDIT", 
									 wndObject -> textValue,
									 WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
									 wndObject -> locationX,
									 wndObject -> locationY,
									 wndObject -> widthPix,
									 wndObject -> heightPix,
									 _wndContainer -> hWnd, 
									NULL,
									_hInst,
									NULL);

	}
	else
	{
		// Create object
		wndObject -> hWnd = CreateWindow(L"STATIC", 
									 wndObject -> strValue,
									 WS_CHILD | WS_VISIBLE | SS_LEFT,
									 wndObject -> locationX,
									 wndObject -> locationY,
									 wndObject -> widthPix,
									 wndObject -> heightPix,
									 _wndContainer -> hWnd, 
									NULL,
									_hInst,
									NULL);
	}

	
	if (wndObject -> hWnd) // Set font
	{
		HFONT hFont, hNewFont;
		LOGFONT lf;
		HDC hDC;
		
		// Get current font
		hFont = (HFONT)SendMessage(wndObject -> hWnd, WM_GETFONT, 0, 0);
		hDC = GetDC(wndObject -> hWnd);
		if(hDC)
		{
			if (hFont == NULL)
			{
				hFont = (HFONT) GetStockObject(SYSTEM_FONT);
				GetObject(hFont, sizeof(LOGFONT), &lf);
				lf.lfQuality = DEFAULT_QUALITY;
				lf.lfWidth = 0;
			}
			else
				GetObject(hFont, sizeof(LOGFONT),&lf);

			// Change font settings
			lf.lfHeight = -MulDiv(wndObject -> fontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
			wcscpy_s(lf.lfFaceName, L"Arial");
			
			// Create new font
			hNewFont = CreateFontIndirect(&lf);
			
			// Set new font
			SendMessage(wndObject -> hWnd, WM_SETFONT, (WPARAM)hNewFont, FALSE);
			ReleaseDC(wndObject -> hWnd, hDC);
		}
	}
	
	
	return wndObject -> hWnd;
        
}

/****************************************************************

   Class :  InfoWindow

   Method : CreateImageUI

   Parameters :
			Input : 
				wndObject - window object descriptor
				
   Return : window object handle

   Description : Create static image
  
*****************************************************************/
HWND InfoWindow :: CreateImageUI(PWINDOW_OBJECT_DESCRIPTOR wndObject)
{
	// set object size
	SetUISize(&(wndObject -> widthPix), 
			  &(wndObject -> heightPix), 
			  wndObject -> widthPers, 
			  wndObject -> heightPers, 
			  _wndContainer -> widthPix, 
			  _wndContainer -> heightPix);

	// Set window object position
	SetUILocation(&(wndObject -> locationX), 
				  &(wndObject -> locationY), 
				  wndObject -> locationXPers,
			      wndObject -> locationYPers, 
				  _wndContainer -> widthPix, 
				  _wndContainer -> heightPix);

	// create object
	wndObject -> hWnd = CreateWindow(L"STATIC", 
									 L"",
									 SS_CENTERIMAGE | SS_REALSIZEIMAGE /*SS_REALSIZECONTROL*/ | SS_BITMAP | WS_CHILD | WS_VISIBLE,
									 wndObject -> locationX,
									 wndObject -> locationY,
									 wndObject -> widthPix,
									 wndObject -> heightPix,
									_wndContainer -> hWnd, 
									NULL,
									_hInst,
									NULL);

	if (wndObject -> imgValue)
	{
		// Load image
		wndObject -> hBitmap = LoadBmpImage((char *) wndObject -> imgValue);
		SendMessage(wndObject -> hWnd, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)wndObject -> hBitmap);
	}

	return wndObject -> hWnd;
}

/****************************************************************

   Class :  InfoWindow

   Method : CreateButton

   Parameters :
			Input : 
				wndObject - window object descriptor
				
   Return : window object handle

   Description : Create button
  
*****************************************************************/
HWND InfoWindow :: CreateButton(PWINDOW_OBJECT_DESCRIPTOR wndObject)
{
	// set object size
	SetUISize(&(wndObject -> widthPix), 
			  &(wndObject -> heightPix), 
			  wndObject -> widthPers, 
			  wndObject -> heightPers, 
			  _wndContainer -> widthPix, 
			  _wndContainer -> heightPix);

	// Set window object position
	SetUILocation(&(wndObject -> locationX), 
				  &(wndObject -> locationY), 
				  wndObject -> locationXPers,
			      wndObject -> locationYPers, 
				  _wndContainer -> widthPix, 
				  _wndContainer -> heightPix);

	// create object
	wndObject -> hWnd = CreateWindow(L"BUTTON", 
									 wndObject -> caption,
									 WS_CHILD | BS_PUSHBUTTON | BS_FLAT | WS_VISIBLE,
									 wndObject -> locationX,
									 wndObject -> locationY,
									 wndObject -> widthPix,
									 wndObject -> heightPix,
									 _wndContainer -> hWnd, 
									 (HMENU)wndObject -> objectID,
									 _hInst,
									 NULL);

	return wndObject -> hWnd;
}

/****************************************************************

   Class :  InfoWindow

   Method : _ProcessNextMessage

	Return : exit flag

	Description : Called from the separate thread to process
				  the next message in the message queue. If
				  there are no messages, it'll wait for one.
  
*****************************************************************/
BOOL InfoWindow :: _ProcessNextMessage()
{
    // Grab, translate, and process the message.
    MSG msg;
	GetMessage(&(msg), _wndContainer -> hWnd, 0, 0);
    TranslateMessage(&(msg));
    DispatchMessage(&(msg));

    // This section performs some "post-processing" of the message. It's easier to do these
    // things here because we have the handles to the window, its button, and the provider
    // handy.
    switch (msg.message)
    {
    // Return to the thread loop and let it know to exit.
    case WM_EXIT_THREAD: return FALSE;

    // Toggle the connection status, which also involves updating the UI.
	}

    return TRUE;
}

/****************************************************************

   Class :  InfoWindow

   Method : _WndProc

   Parameters :
			Input : 
				hWnd - window handle
				message - message code
				wParam - additional message information
				lParam - additional message information
   
   Return :  result of the message processing

   Description : Manages window messages on the window thread.
  
*****************************************************************/
LRESULT CALLBACK InfoWindow :: _WndProc(__in HWND hWnd, __in UINT message, __in WPARAM wParam, __in LPARAM lParam)
{
	InfoWindow * _this = FindWindowPointerByHWND(hWnd);

    switch (message)
    {

		// Create message
		case WM_CREATE	:
			{
				break;
			}


		// Disable window manual closing
		case WM_SYSCOMMAND:
			{
				if(wParam == SC_CLOSE)
					if((GetAsyncKeyState(VK_MENU)) && (GetAsyncKeyState(VK_F4)))
         			 return NULL;
			
				break;
			}
       
		
		// Button click. Only for symbol boxes passwords windows
		case WM_COMMAND:
			{
				if (HIWORD(wParam) == 0) 
				{
					if (_this)
					{
						for(int i = 0; i < _this -> _wndContainer -> windowObjectsCount; i++)
						{
							if ((_this -> _wndContainer -> windowObjects[i] -> objectTypeId == SOT_BUTTON) &&
								(_this -> _wndContainer -> windowObjects[i] -> objectID == LOWORD(wParam)))
							{
								_this -> SymbolButtonClick(wParam, _this -> _wndContainer -> windowObjects[i] -> caption);
								/*MessageBox(hWnd, _this -> _wndContainer -> caption, L"MessageBox", MB_OK|MB_ICONWARNING);*/
								break;
							}
						}
					}
				}

				break;
			}
			

		// Set color of static text
		case WM_CTLCOLORSTATIC:
			{
				if (_this)
				{
					for(int i = 0; i < _this -> _wndContainer -> windowObjectsCount; i++)
						if ((HWND)lParam == _this -> _wndContainer -> windowObjects[i] -> hWnd)
						{
							HDC hdcStatic = (HDC)wParam;
							SetTextColor(hdcStatic, _this -> _wndContainer -> windowObjects[i] -> textColor);
							SetBkMode(hdcStatic, TRANSPARENT);
							return (LONG)GetStockObject(DC_BRUSH);
						}
				}

				return TRUE;
			}

		// To play it safe, we hide the window when "closed" and post a message telling the 
		// thread to exit.
		case WM_CLOSE :
			{
				PostMessage(hWnd, WM_EXIT_THREAD, 0, 0);
				break;
			}

		default:
				return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

/****************************************************************

   Class :  InfoWindow

   Method : SymbolButtonClick

   Description : Symbol button click
  
*****************************************************************/
void InfoWindow :: SymbolButtonClick(WPARAM wParam, WCHAR * symbolStr)
{
	/*if (hPasswordBox)
		SendMessage(hPasswordBox, WM_GETTEXT, (WPARAM)STR_VALUE_LEN, (LPARAM)_currPwdSymbols);*/

	switch(LOWORD(wParam))
	{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7: // Symbol buttons
				wcscat_s(currPwdSymbols, symbolStr);
				break;

		case 8: // Backspace button
				size_t sLen = wcsnlen_s(currPwdSymbols, STR_VALUE_LEN);
				if (sLen > 0) currPwdSymbols[sLen - 1] = 0;
				break;
	}

	switch(osVersion)
	{
		case OS_WIN_7_X32 : 
		case OS_WIN_7_X64 : 
			{
				if (hPasswordBox)
					SendMessage(hPasswordBox, WM_SETTEXT, (WPARAM)STR_VALUE_LEN, (LPARAM)currPwdSymbols);
				break;
			}

		case OS_UNKNOWN : 
		case OS_WIN_8_X32 : 
		case OS_WIN_8_X64 : 
		case OS_WIN_10_X32 : 
		case OS_WIN_10_X64 : 
			{
				if ((_pCredentialProviderCredential) &&	(_pCredProvCredentialEvents) &&	(pwdIndex != -1))
					_pCredProvCredentialEvents -> SetFieldString(_pCredentialProviderCredential, pwdIndex, currPwdSymbols);
				break;
			}
	}
}

/****************************************************************

   Class :  InfoWindow

   Method : _ThreadProc

   Parameters :
			Input : 
				lpParameter - pointer to CInfoWindow
				
   
   Return :  eror code

   Description : Our thread procedure. We actually do a lot 
				 of work here that could be put back on the 
				 main thread, such as setting up the window, etc.
  
*****************************************************************/
DWORD WINAPI InfoWindow :: _ThreadProc(__in LPVOID lpParameter)
{
    InfoWindow *pInfoWindow = static_cast<InfoWindow *>(lpParameter);

    if (pInfoWindow == NULL)
    {
        // TODO: What's the best way to raise this error?
        return 0;
    }

    HRESULT hr = S_OK;

    // Create the window.
    pInfoWindow ->_hInst = GetModuleHandle(NULL);

    if (pInfoWindow -> _hInst != NULL)
    {            
        hr = pInfoWindow -> _MyRegisterClass();

        if (SUCCEEDED(hr))
        {
            hr = pInfoWindow -> _InitInstance();
        }
    }
    else
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    // ProcessNextMessage will pump our message pump and return false if it comes across
    // a message telling us to exit the thread.
    if (SUCCEEDED(hr))
    {        
        while (pInfoWindow -> _ProcessNextMessage()) 
        {
        }
    }
    else
    {
		if (pInfoWindow -> _wndContainer -> hWnd != NULL)
        {
            pInfoWindow -> _wndContainer -> hWnd = NULL;
        }
    }

    return 0;
}

