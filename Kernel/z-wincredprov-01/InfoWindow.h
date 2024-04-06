/****************************************************************

   Solution : NovaTend

   Project : z-wincredprov-01.dll

   Module : CInfoWindo.h

   Description :  Defines the interface of class of 
				  additional information window

				  This class is designed only for the 
				  Windows operating systems.

*****************************************************************/

#pragma once

#include <WinCPScreenBuilder.h>
#include "helpers.h"

#include <windows.h>
#include <credentialprovider.h>

/****************************************************************

   Class : CInfoWindow

   Description : additional informational window

*****************************************************************/
class InfoWindow
{
	public:
		
		// Constructor
		InfoWindow();

		// Destructor
		~InfoWindow();

		// Initialize window class
		HRESULT Initialize(__in PSUB_WINDOW pWndCnt, __in int wndPntCount, __in InfoWindow ** wndPnts);

		// Show window
		HRESULT Show();

		// Hide window
		HRESULT Hide();

		// Window container
		PSUB_WINDOW	_wndContainer;

		// Main window password box handle
		HWND hPasswordBox;

		// Index of password box control
		int	pwdIndex;

		// Current password string
		WCHAR currPwdSymbols[STR_VALUE_LEN];

		// Current OS ver
		int osVersion;

		// Set credential instance parameters
		void SetCredentialProviderCredential(ICredentialProviderCredentialEvents * pCredProvCredentialEvents, ICredentialProviderCredential * pCredentialProviderCredential);

	private:

		// Regster window class
		HRESULT _MyRegisterClass();

		// Initialize window instance
		HRESULT _InitInstance();

		// Process window messages
		BOOL _ProcessNextMessage();

		// Show window commands
		HRESULT _ShowWindow(int cmdShow);

		// Create window instance
		HWND CreateInfoWindow();

		// Create window UI objects
		HRESULT CreateWindowUI();

		// Set window UI object size
		void SetUISize(int *widthPix, int * heightPix, int widthPers, int heightPers, int parentWidth, int parentHeight);

		// Set window UI object position
		void SetUILocation(int * locationX, int * locationY, int locationXPers, int locationYPers, int parentWidth, int parentHeight);

		// Create static text
		HWND CreateStaticTextUI(PWINDOW_OBJECT_DESCRIPTOR wndObject, BOOL large);

		// Create static image
		HWND CreateImageUI(PWINDOW_OBJECT_DESCRIPTOR wndObject);

		// Create button
		HWND CreateButton(PWINDOW_OBJECT_DESCRIPTOR wndObject);

		// Window thread procedure
		static DWORD WINAPI _ThreadProc(__in LPVOID lpParameter);

		// Window callback procedure
		static LRESULT CALLBACK    _WndProc(__in HWND hWnd, __in UINT message, __in WPARAM wParam, __in LPARAM lParam);
    				
		// Thread handle
		HANDLE						_hThread;
		
		// Current instance
		HINSTANCE                   _hInst;            

		// Credential provider credential events instance
		ICredentialProviderCredentialEvents * _pCredProvCredentialEvents;

		// Credential provider instance
		ICredentialProviderCredential * _pCredentialProviderCredential;

		// Symbol button click
		void SymbolButtonClick(WPARAM wParam, WCHAR * symbolStr);
};
