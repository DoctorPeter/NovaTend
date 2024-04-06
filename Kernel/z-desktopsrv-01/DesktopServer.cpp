/****************************************************************

   Solution : NovaTend

   Project : z-desktopsrv-01.exe

   Module : DesktopServer.cpp

   Description :  DesktopServer implements Desktop-server 
				  subsystem of NovaTend 
				  authentication system

				  This code is designed only for the 
				  Windows operating systems.

*****************************************************************/
#include "stdafx.h"
#include "DesktopServerService.h"

// z-desktopsrv-01.exe definition structure
DLL_COMMON_DEFINITION zDesktopServerServiceDefinition =
{
	Z_DESKTOP_SERVER_ID,
	0x00010000,
	"z-desktopsrv-01.exe - application DESKTOP-server",
	0,
	{}
};

// DESKTOP-server instance
DesktopServerService * desktopServerService = NULL;

// Window callback procedure
static LRESULT CALLBACK _WndProc(__in HWND hWnd, __in UINT message, __in WPARAM wParam, __in LPARAM lParam);

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Prepare window class
	WNDCLASSEX wcex = { sizeof(wcex) };
    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc      = _WndProc;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = NULL;
    wcex.hCursor          = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName    = L"DESKTOP_server_invisible_window";

	// Register window class
	HRESULT hr = RegisterClassEx(&wcex);
	
	// Window handler
	HWND hWnd = NULL;

    if (SUCCEEDED(hr))
	{
		// Create window
		hWnd = CreateWindowEx(WS_EX_TOOLWINDOW, L"DESKTOP_server_invisible_window", L"HELPER", WS_POPUP, 0, 0, 100, 100, NULL, NULL, hInstance, NULL);

		if (!hWnd) 
			return 0;
	}

	// Messages processing
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	
	return msg.wParam; 
}

/****************************************************************

   Function : _WndProc

   Parameters :
			Input : 
				hWnd - window handle
				message - message code
				wParam - additional message information
				lParam - additional message information
   
   Return :  result of the message processing

   Description : Manages window messages on the window thread.
  
*****************************************************************/
LRESULT CALLBACK _WndProc(__in HWND hWnd, __in UINT message, __in WPARAM wParam, __in LPARAM lParam)
{
    switch (message)
    {

		// Create message
		case WM_CREATE	:
			{
				// Create service
				desktopServerService = new DesktopServerService("NovaTend_DESKTOP_Server");

				if (!(desktopServerService -> Start()))
				{
					desktopServerService -> Stop();
					delete desktopServerService;
					desktopServerService = NULL;
					PostQuitMessage(0);
				}

				break;
			}

		// Close session
		case WM_QUERYENDSESSION :
			{	
				if (desktopServerService)
				{
					desktopServerService -> Stop();
					delete desktopServerService;
					desktopServerService = NULL;
				}

				break;
			}

 		// To play it safe, we hide the window when "closed" and post a message telling the 
		// thread to exit.
		case WM_DESTROY :
		case WM_CLOSE :
			{
				if (desktopServerService)
				{
					desktopServerService -> Stop();
					delete desktopServerService;
					desktopServerService = NULL;
				}

				PostQuitMessage(0);
				break;
			}

		default:
				return DefWindowProc(hWnd, message, wParam, lParam);
    }

	return 0;
}