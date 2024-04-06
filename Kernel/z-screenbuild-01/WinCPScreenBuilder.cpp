/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : WinCPScreenBuilder.cpp

   Description :  this module implements methods of
				  class WinCPScreenBuilder

*****************************************************************/

#include "stdafx.h"
#include "WinCPScreenBuilder.h"
#include <LicenseDataDef.h>

#include <stdlib.h>
#include <stdio.h>

/****************************************************************

   Class : WinCPScreenBuilder

   Method : Constructor

   Parameters :
			Input : 
				dllUserID - ID of DLL user
				logWriter - pointer to LogWriter instance

*****************************************************************/
WinCPScreenBuilder :: WinCPScreenBuilder(unsigned long dllUserID, LogWriter * logWriter) : ScreenBuilder(dllUserID, logWriter)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : constructor");
	#endif
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : Destructor

*****************************************************************/
WinCPScreenBuilder :: ~WinCPScreenBuilder(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : destructor");
	#endif
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : CreateLocalScreenContainer
   
   Return : Pointer to user screen container
	
   Description :  Create user screen container for local sign in

*****************************************************************/
PUSER_SCREEN_CONTAINER WinCPScreenBuilder :: CreateLocalScreenContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Start");
	#endif

	// Allocate memory for user screen container
	PUSER_SCREEN_CONTAINER userScreenContainer = CreateScreenContainer();

	// Check allocation result
	if (!userScreenContainer)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return userScreenContainer;
	}

	userScreenContainer -> subWindowCount = 0;
	userScreenContainer -> screenObjectsCount = 0;

	// Allocate memory for screen object
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

	// Validate allocation result
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error screen object memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	// Create logo image
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = 1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_IMAGE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, L"LogoImage");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

	userScreenContainer -> screenObjectsCount++;

	// Allocate memory for screen object
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

	// Validate allocation result
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error screen object memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	// Create time label
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = 2;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_DATE_TIME_TEXT;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 2;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, L"TimeLabel");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
	
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error label memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	time_t seconds = time(NULL);
	tm * timeinfo = localtime(&seconds);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = (tm *)malloc(sizeof(tm));
	memcpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo, timeinfo, sizeof(tm));
	wcsftime(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, STR_VALUE_LEN, L"%A, %m/%d/%y, %H:%M:%S"/*L"%H:%M:%S on %A, %B %d"*/, userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo);
	wcsftime(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> strValue, STR_VALUE_LEN, L"%A, %m/%d/%y, %H:%M:%S"/*L"%H:%M:%S on %A, %B %d"*/, userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo);

	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

	userScreenContainer -> screenObjectsCount++;

	// Allocate memory for screen object
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

	// Validate allocation result
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error screen object memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	// Create label
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = 3;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_LARGE_TEXT;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 3;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, L"WarningLabel");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
	
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error label memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, L"Server is not available now! You can sign in only as local user!");
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> strValue, L"Server is not available now! You can sign in only as local user!");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

	userScreenContainer -> screenObjectsCount++;

	// Allocate memory for screen object
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

	// Validate allocation result
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error screen object memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	// Create user name box
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = 4;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_USER_NAME_BOX;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 4;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, L"UserNameBox");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
	
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error label memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, L"User name");
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> strValue, L"");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

	userScreenContainer -> screenObjectsCount++;

	// Allocate memory for screen object
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

	// Validate allocation result
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error screen object memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	// Create password box
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = 5;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_PASSWORD_BOX;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 5;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, L"PasswordBox");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
	
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error label memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, L"Password");
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> strValue, L"");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

	userScreenContainer -> screenObjectsCount++;

	// Allocate memory for screen object
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

	// Validate allocation result
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error screen object memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	// Create submit button
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = 6;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_BUTTON;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 6;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, L"SubmitButton");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
	
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
	if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Error label memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
		#endif

		return ClearScreenContainer(userScreenContainer);
	}

	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, L"OK");
	wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> strValue, L"");
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
	userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

	userScreenContainer -> screenObjectsCount++;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Screen container successfully created!");
		WriteToLog("WinCPScreenBuilder : CreateLocalScreenContainer. Done");
	#endif

	return userScreenContainer;
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : CreateUserScreen
   
   Parameters :
			Input : 
				content - pointer to user screen container
				
   Return : Pointer to user screen container
	
   Description :  Create user screen container

*****************************************************************/
void * WinCPScreenBuilder :: CreateUserScreen(PPRESET_CONTAINER content)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateUserScreen. Start");
		WriteToLog("WinCPScreenBuilder : CreateUserScreen. Personal screen creation");
	#endif

	// Check legal DLL user
	content -= dllUserCheckResult;
	PUSER_SCREEN_CONTAINER userScreenContainer = NULL;

	if (content)
	{
		// Allocate memory for user screen container
		userScreenContainer = CreateScreenContainer();
		
		// Create objects of main screen
		if (!FillMainScreen(content, userScreenContainer))
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : CreateUserScreen. User screen container was not created");
				WriteToLog("WinCPScreenBuilder : CreateUserScreen. Done");
			#endif

			return ClearScreenContainer(userScreenContainer);
		}

		// Create additional windows
		for(int i = 0; i < content -> userScreensCount; i++)
			if  ((content -> userScreens[i]) && 
				((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) || 
				 (content -> userScreens[i] -> screenScope == SO_SCOPE_BOTH)) &&
				((content -> userScreens[i] -> screenTypeID == SOT_SUB_SCREEN) ||
				 (content -> userScreens[i] -> screenTypeID == SOT_STUDY_SCREEN) ||
				 (content -> userScreens[i] -> screenTypeID == SOT_NOTIFICATION_SCREEN) ||
				 (content -> userScreens[i] -> screenTypeID == SOT_LEGAL_DISCLAIMER_SCREEN)))
			{
				if (!AddSubWindow(content -> userScreens[i], userScreenContainer))
				{
					#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
						WriteToLog("WinCPScreenBuilder : CreateUserScreen. User screen container was not created");
						WriteToLog("WinCPScreenBuilder : CreateUserScreen. Done");
					#endif

					return ClearScreenContainer(userScreenContainer);
				}
			}
	}
	else 
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateUserScreen. Empty user content!");
			WriteToLog("WinCPScreenBuilder : CreateUserScreen. Done");
		#endif

		return NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateUserScreen. Done");
	#endif

	return userScreenContainer;
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : CreateSymbolBoxPasswordWindow

   Parameters:
			Input:
				pMatrixes - pointer to symbol matrixes list
				symbolBoxesType - type of symbol boxes password
			Output:
				userScreenContainer - pointer to user
									  screen container

   Return : TRUE - if success
	
   Description :  Add symbol boxes password window

*****************************************************************/
bool WinCPScreenBuilder :: AddSymbolBoxesPasswordWindow(PUTF8_STRINGS_MATRIX_LIST pMatrixes, int symbolBoxesType, PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Start");
	#endif

	if ((!pMatrixes) || (!userScreenContainer))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Wrong input data");
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Done");
		#endif

		return false;
	}


	LoadScreenSize();

	PSUB_WINDOW pSubWindow = CreateSymbolBoxPasswordWindow(GetPwdSymbolBoxImageSize(symbolBoxesType), symbolBoxesType, pMatrixes);

	if (!pSubWindow)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Wrong input data");
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Done");
		#endif

		return false;
	}

	if(AddSubWindow(pSubWindow, userScreenContainer))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Window successfully added!");
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Done");
		#endif

		return true;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Can't add window!");
			WriteToLog("WinCPScreenBuilder : AddSymbolBoxesPasswordWindow. Done");
		#endif

		return false;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : FillMainScreen
   
   Parameters:
			Input : 
				content - pointer to user container
			Output:
				userScreenContainer - pointer to user
									  screen container

   Return : Success flag
	
	Description : Creates list of main screen objects

*****************************************************************/
BOOL WinCPScreenBuilder :: FillMainScreen(PPRESET_CONTAINER content, PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : FillMainScreen. Start");
	#endif

	// Validate critical parameters
	if ((userScreenContainer) && (content) && (content -> userScreensCount > 0))
	{
		// Find main screen index
		int mainScreenInd = -1;
		
		for(int i = 0; i < content -> userScreensCount; i++)
		{
			if ((content -> userScreens[i] -> screenTypeID == SOT_MAIN_SCREEN) &&
				((content -> userScreens[i] -> screenScope == SO_SCOPE_LOGON_SCREEN) || 
				 (content -> userScreens[i] -> screenScope == SO_SCOPE_BOTH)))
			{
				mainScreenInd = i;
				break;
			}
		}

		if (mainScreenInd == -1)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : FillMainScreen. Can not find main screen! Done");
				WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
			#endif

			return FALSE;
		}

		// Get main screen pointer
		PUSER_SCREEN mainScreen = content -> userScreens[mainScreenInd];
		
		// Tile image flag
		BOOL tileIamgeFound = FALSE;

		// Submit button flag
		BOOL submitButtonFound = FALSE;

		// Get objects
		for(int i = 0; i < mainScreen -> scrObjCount; i++)
		{
			// Check screen object scope
			if (!((mainScreen -> screenObjects[i] -> objScope == SO_SCOPE_LOGON_SCREEN) || 
				  (mainScreen -> screenObjects[i] -> objScope == SO_SCOPE_BOTH)))
					continue;

			// Allocate memory for object descriptor
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

			// Validate allocation result
			if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount])
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Error descriptor memory allocation!");
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
				#endif

				return FALSE;
			}

			// Get descriptor values
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = mainScreen -> screenObjects[i] -> objID;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = mainScreen -> screenObjects[i] -> objTypeId;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = mainScreen -> screenObjects[i] -> order;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = mainScreen -> screenObjects[i] -> questionID;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = mainScreen -> screenObjects[i] -> rightAnswerID;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> timeinfo = NULL;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = mainScreen -> screenObjects[i] -> imgValueSize;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = mainScreen -> screenObjects[i] -> textValueSize * 2;
			mbstowcs(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, mainScreen -> screenObjects[i] -> objName, NAME_LEN);
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
			
			// Allocate memory for label
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;

			// Validate allocation result
			if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Error label memory allocation!");
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
				#endif

				return FALSE;
			}
			
			// Get field state
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

			// Get field interactive state
			userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

			// Set field values
			SetFieldValues(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount], mainScreen -> screenObjects[i]);

			// Check tile image flag
			if ((userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID == SOT_IMAGE) ||
				(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID == SOT_EDU_LESSON_IMAGE)) tileIamgeFound = TRUE;

			// Check submit button flag
			if (userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID == SOT_BUTTON) submitButtonFound = TRUE;

			// Check drop down list field
			if (((userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID == SOT_COMBOBOX) ||
				 (userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID == SOT_EDU_ANSWER_BOX) ||
				 (userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID == SOT_LEGAL_DISCLAIMER_COMBOBOX)) &&
				 (mainScreen -> screenObjects[i] -> listValuesSet))
			{
				userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = mainScreen -> screenObjects[i] -> listValuesSet -> valuesCount;

				// Get list values
				for(int j = 0; j < userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount; j++)
					mbstowcs(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValues[j],  mainScreen -> screenObjects[i] -> listValuesSet -> listValues[j], STR_VALUE_LEN);
				
				// Set first value as default
				if (userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount > 0)
					mbstowcs(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> strValue, mainScreen -> screenObjects[i] -> listValuesSet -> listValues[0], STR_VALUE_LEN);
			}

			userScreenContainer -> screenObjectsCount++;
		}

		// If not found tile image then add it
		if (!tileIamgeFound)
		{
			if (!AddTileImage(userScreenContainer))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Error of tile image appending!");
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
				#endif

				return FALSE;
			}
		}

		// If not found submit button then add it
		if (!submitButtonFound)
		{
			if (!AddSubmitButton(userScreenContainer))
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Error of submit button aapending");
					WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
				#endif

				return FALSE;
			}
		}

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
		#endif

		return TRUE;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : Error of FillMainScreen using!");
			WriteToLog("WinCPScreenBuilder : FillMainScreen. Done");
		#endif

		return FALSE;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : AddSubWindow
   
   Parameters:
			Input : 
				screen - pointer to user screen
			Output:
				userScreenContainer - pointer to user
									  screen container
   
   Return : Success flag
	
	Description : Create and add sub window to list

*****************************************************************/
BOOL WinCPScreenBuilder :: AddSubWindow(PUSER_SCREEN screen, PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : AddSubWindow. Start");
	#endif

	// Validate critical parameters
	if ((userScreenContainer) && (screen))
	{
		// Allocate memory for window descriptor
		userScreenContainer -> subWindows[userScreenContainer ->subWindowCount] = (PSUB_WINDOW)malloc(sizeof(SUB_WINDOW));

		// Validate allocation result
		if(!userScreenContainer -> subWindows[userScreenContainer ->subWindowCount])
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : AddSubWindow. Error of sub window memory allocation! Done");
				WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
			#endif

			return FALSE;
		}

		// Get window parameters
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowID = screen -> screenID;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowTypeId = screen -> screenTypeID;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> locationX = screen -> locationX;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> locationY = screen -> locationY;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> locationXPers = screen -> locationXPers;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> locationYPers = screen -> locationYPers;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> widthPix = screen -> widthPix;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> widthPers = screen -> widthPers;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> heightPix = screen -> heightPix;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> heightPers = screen -> heightPers;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> color = screen -> color;
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> hWnd = NULL;
		mbstowcs(userScreenContainer -> subWindows[userScreenContainer ->subWindowCount] -> windowName, screen -> Name, NAME_LEN);
		mbstowcs(userScreenContainer -> subWindows[userScreenContainer ->subWindowCount] -> caption, screen -> screenCaption, NAME_LEN);
		
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjectsCount = 0;
		int * objCounter = &(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjectsCount);

		// Get window objects list
		for(int i = 0; i < screen -> scrObjCount; i++)
		{
			// Check screen object scope
			if (!((screen -> screenObjects[i] -> objScope == SO_SCOPE_LOGON_SCREEN) || 
				  (screen -> screenObjects[i] -> objScope == SO_SCOPE_BOTH)))
					continue;

			// Alocate memory for window object descriptor
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] = (PWINDOW_OBJECT_DESCRIPTOR)malloc(sizeof(WINDOW_OBJECT_DESCRIPTOR));

			// Validate allocation result
			if(!userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter])
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : AddSubWindow. Error of sub window object descriptor memory allocation!");
					WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
				#endif

				return FALSE;
			}

			// Set window parameters
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> objectID = screen -> screenObjects[i] -> objID;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> objectTypeId = screen -> screenObjects[i] -> objTypeId;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> locationX = screen -> screenObjects[i] -> locationX;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> locationY = screen -> screenObjects[i] -> locationY;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> locationXPers = screen -> screenObjects[i] -> locationXPers;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> locationYPers = screen -> screenObjects[i] -> locationYPers;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> heightPix = screen -> screenObjects[i] -> heightPix;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> heightPers = screen -> screenObjects[i] -> heightPers;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> widthPix = screen -> screenObjects[i] -> widthPix;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> widthPers = screen -> screenObjects[i] -> widthPers;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> fontSize = screen -> screenObjects[i] -> fontSize;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> questionID = screen -> screenObjects[i] -> questionID;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> rightAnswerID = screen -> screenObjects[i] -> rightAnswerID;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> chbChecked = FALSE;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> comboBoxIndex = 0;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> comboBoxValuesCount = 0;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> textColor = screen -> screenObjects[i] -> textColor;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> backgroundColor = screen -> screenObjects[i] -> backgroundColor;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> imgValue = NULL;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> textValue = NULL;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> imgValueSize = screen -> screenObjects[i] -> imgValueSize;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> textValueSize = screen -> screenObjects[i] -> textValueSize * 2;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> timeinfo = NULL;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> hWnd = NULL;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> hBitmap = NULL;
			userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> hFont = NULL;
			mbstowcs(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> objectName, screen -> screenObjects[i] -> objName, NAME_LEN);
			mbstowcs(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> caption, screen -> screenObjects[i] -> objCaption, NAME_LEN);
			mbstowcs(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> strValue, screen -> screenObjects[i] -> strValue, NAME_LEN);

			// Is it image ?
			if (screen -> screenObjects[i] -> imgValueSize > 0)
			{
			  // Allocate memory for image
			  userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> imgValue = malloc(screen -> screenObjects[i] -> imgValueSize);

			  // Validate allocation result
			  if (!userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> imgValue)
			  {
				 #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : AddSubWindow. Error of image memory allocation!");
					WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
				#endif

				 return FALSE;
			  }

			  // Copy image
			  memcpy(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> imgValue, screen -> screenObjects[i] -> imgValue, screen -> screenObjects[i] -> imgValueSize);
			}

			// If it is big text
			if (screen -> screenObjects[i] -> textValueSize > 0)
			{
			  // Allocate memory for text
			  userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> textValue = (WCHAR *)malloc(screen -> screenObjects[i] -> textValueSize * 2);

			  // Validate allocation result
			  if (!userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> textValue)
			  {
				 #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("WinCPScreenBuilder : AddSubWindow. Error of image memory allocation!");
					WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
				 #endif

				 return FALSE;
			  }

			  // Copy text value
			  mbstowcs(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> textValue, screen -> screenObjects[i] -> textValue, screen -> screenObjects[i] -> textValueSize);
			}

			// Get drop down list
			if (screen -> screenObjects[i] -> listValuesSet)
			{
				userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> comboBoxValuesCount = screen -> screenObjects[i] -> listValuesSet -> valuesCount;

				// Copy list values
				for(int j = 0; j < userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> comboBoxValuesCount; j++)
					mbstowcs(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> comboBoxValues[j], screen -> screenObjects[i] -> listValuesSet -> listValues[j], STR_VALUE_LEN);

				// Set first value as default
				if(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> comboBoxValuesCount > 0)
					mbstowcs(userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] -> windowObjects[*objCounter] -> strValue, screen -> screenObjects[i] -> listValuesSet -> listValues[0], STR_VALUE_LEN);
			}

			(*objCounter)++;
		}

		userScreenContainer -> subWindowCount++;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			char msg[128];
			sprintf(msg, "WinCPScreenBuilder : AddSubWindow. Sub windows count: %d", userScreenContainer -> subWindowCount);
			WriteToLog(msg);
			WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
		#endif

		return TRUE;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : Error of AddSubWindow using!");
			WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
		#endif

		return FALSE;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : AddSubWindow
   
   Parameters:
			Input : 
				subWindow - pointer to sub window
			Output:
				userScreenContainer - pointer to user
									  screen container
   
   Return : Success flag
	
	Description : Create and add sub window to list

*****************************************************************/
BOOL WinCPScreenBuilder :: AddSubWindow(PSUB_WINDOW subWindow, PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : AddSubWindow. Start");
	#endif

	if (!subWindow)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSubWindow. Wrong input data!");
			WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
		#endif

		return FALSE;
	}

	if (userScreenContainer)
	{
		userScreenContainer -> subWindows[userScreenContainer -> subWindowCount] = subWindow;
		userScreenContainer -> subWindowCount++;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
		#endif

		return TRUE;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSubWindow. User screen container is empty!");
			WriteToLog("WinCPScreenBuilder : AddSubWindow. Done");
		#endif

		return FALSE;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : CreateScreenContainer
   
   Return : pointer to user screen container
	
   Description : Creates user screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER  WinCPScreenBuilder :: CreateScreenContainer(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateScreenContainer. Start");
	#endif
	
	// Allocate memory for user screen container
	PUSER_SCREEN_CONTAINER userScreenContainer = (PUSER_SCREEN_CONTAINER)malloc(sizeof(USER_SCREEN_CONTAINER));

	// Validate allocation result
	if (userScreenContainer) 
	{
		userScreenContainer -> screenObjectsCount = 0;
		userScreenContainer -> subWindowCount = 0;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateScreenContainer. Success!");
			WriteToLog("WinCPScreenBuilder : CreateScreenContainer. Done");
		#endif

		return userScreenContainer;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateScreenContainer. Error of memory allocation!");
			WriteToLog("WinCPScreenBuilder : CreateScreenContainer. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : AddTileImage

   Parameters:
			Output:
				userScreenContainer - pointer to user
									  screen container
   Return : success flag
	
   Description : Add tile image to main screen

*****************************************************************/
BOOL WinCPScreenBuilder :: AddTileImage(PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : AddTileImage. Start");
	#endif

	// Validate container
	if (userScreenContainer)
	{
		// Set descriptor values
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = -1;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_IMAGE;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
		mbstowcs(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, "Logo", NAME_LEN);
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;

		// Allocate memory for label
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
		
		// Validate allocation result
		if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : AddTileImage. Error label memory allocation!");
				WriteToLog("WinCPScreenBuilder : AddTileImage. Done");
			#endif

			return FALSE;
		}
		
		wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, L"Logo");

		// Set field state
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

		// Set field interactive state
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
		
		userScreenContainer -> screenObjectsCount++;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddTileImage. Done");
		#endif

		return TRUE;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : Error AddTileImage using!");
			WriteToLog("WinCPScreenBuilder : AddTileImage. Done");
		#endif

		return FALSE;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : AddSubmitButton

   Parameters:
			Output:
				userScreenContainer - pointer to user
									  screen container
   
   Return : success flag
	
   Description : Add submit button to main screen

*****************************************************************/
BOOL WinCPScreenBuilder :: AddSubmitButton(PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : AddSubmitButton. Start");
	#endif
	
	// Validate container
	if (userScreenContainer)
	{
		// Set descriptor values
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] = (PMAIN_SCREEN_OBJECT_DESCRIPTOR)malloc(sizeof(MAIN_SCREEN_OBJECT_DESCRIPTOR));

		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectID = -1;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID = SOT_BUTTON;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> order = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> questionID = -1;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> rightAnswerID = -1;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> chbChecked = FALSE;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxIndex = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> comboBoxValuesCount = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValue = NULL;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValue = NULL;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> imgValueSize = 0;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> textValueSize = 0;
		mbstowcs(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectName, "SubmitButton", NAME_LEN);
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.cpft = GetFieldType(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.dwFieldID = userScreenContainer -> screenObjectsCount;
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = NULL;
		
		// Allocate memory for label
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel = (LPWSTR)malloc(NAME_LEN*2);;
		
		// Validate allocation result
		if (!userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : AddSubmitButton. Error label memory allocation!");
				WriteToLog("WinCPScreenBuilder : AddSubmitButton. Done");
			#endif

			return FALSE;
		}
		
		wcscpy(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldDescriptor.pszLabel, L"OK");
		
		// Set field state
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldState = GetFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);

		// Set field interactive state
		userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> fieldInteractiveState = GetInteractiveFieldState(userScreenContainer -> screenObjects[userScreenContainer -> screenObjectsCount] -> objectTypeID);
		
		userScreenContainer -> screenObjectsCount++;
		
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : AddSubmitButton. Done");
		#endif

		return TRUE;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : Error AddSubmitButton using!");
			WriteToLog("WinCPScreenBuilder : AddSubmitButton. Done");
		#endif

		return FALSE;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : GetFieldType
      	
	Parameters :
			Input : 
				paramType - content parameter type

	Return : Windows credential provider field type

	Description :  Get windows credential provider field type

*****************************************************************/
CREDENTIAL_PROVIDER_FIELD_TYPE WinCPScreenBuilder :: GetFieldType(int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : GetFieldType");
	#endif

	switch(paramType)
	{
		case SOT_IMAGE							: return CPFT_TILE_IMAGE;
		case SOT_LARGE_TEXT						: return CPFT_LARGE_TEXT;
		case SOT_SMALL_TEXT						: return CPFT_SMALL_TEXT;
		case SOT_BIG_TEXT_BLOCK					: return CPFT_SMALL_TEXT;
		case SOT_TEXT_BOX						: return CPFT_EDIT_TEXT;
		case SOT_PASSWORD_BOX					: return CPFT_PASSWORD_TEXT;
		case SOT_BUTTON							: return CPFT_SUBMIT_BUTTON;
		case SOT_CHECKBOX						: return CPFT_CHECKBOX;
		case SOT_COMBOBOX						: return CPFT_COMBOBOX;
		case SOT_COMMAND_LINK					: return CPFT_COMMAND_LINK;
		case SOT_DATE_TIME_TEXT					: return CPFT_LARGE_TEXT;
		case SOT_DOMAIN_NAME_BOX				: return CPFT_COMBOBOX;
		case SOT_USER_NAME_BOX					: return CPFT_EDIT_TEXT;
		case SOT_EDUCATION_LABEL				: return CPFT_SMALL_TEXT;
		case SOT_EDU_ANSWER_BOX					: return CPFT_COMBOBOX;
		case SOT_EDU_QUESTION_TEXT				: return CPFT_SMALL_TEXT;
		case SOT_EDU_LESSON_TEXT				: return CPFT_SMALL_TEXT;
		case SOT_EDU_LESSON_IMAGE				: return CPFT_TILE_IMAGE;
		case SOT_LEGAL_DISCLAIMER_COMBOBOX		: return CPFT_COMBOBOX;
		case SOT_LEGAL_DISCLAIMER_IMAGE			: return CPFT_TILE_IMAGE;
		case SOT_LEGAL_DISCLAIMER_TEXT			: return CPFT_SMALL_TEXT;
		case SOT_LEGAL_DISCLAIMER_LABEL			: return CPFT_SMALL_TEXT;
		case SOT_SIMPLE_NOTICE_TEXT				: return CPFT_SMALL_TEXT;
		case SOT_WARNING_NOTICE_TEXT			: return CPFT_SMALL_TEXT;
		case SOT_PASSWORD_RESET_BUTTON			: return CPFT_COMMAND_LINK;

		default 								: return CPFT_INVALID;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : GetFieldState
      	
	Parameters :
			Input : 
				paramType - content parameter type

	Return : Windows credential provider field state

	Description :  Get windows credential provider field state

*****************************************************************/
CREDENTIAL_PROVIDER_FIELD_STATE WinCPScreenBuilder :: GetFieldState(int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : GetFieldState");
	#endif

	switch(paramType)
	{
		case SOT_IMAGE							: 
		case SOT_EDU_LESSON_IMAGE				: 
		case SOT_LEGAL_DISCLAIMER_IMAGE			: return CPFS_DISPLAY_IN_BOTH;

		case SOT_LARGE_TEXT						: 
		case SOT_SMALL_TEXT						: 
		case SOT_BIG_TEXT_BLOCK					: 
		case SOT_TEXT_BOX						: 
		case SOT_PASSWORD_BOX					: 
		case SOT_BUTTON							: 
		case SOT_CHECKBOX						: 
		case SOT_COMBOBOX						: 
		case SOT_COMMAND_LINK					: 
		case SOT_DATE_TIME_TEXT					: 
		case SOT_DOMAIN_NAME_BOX				: 
		case SOT_USER_NAME_BOX					: 
		case SOT_EDUCATION_LABEL				: 
		case SOT_EDU_QUESTION_TEXT				: 
		case SOT_EDU_ANSWER_BOX					: 
		case SOT_EDU_LESSON_TEXT				: 
		case SOT_SIMPLE_NOTICE_TEXT				: 
		case SOT_WARNING_NOTICE_TEXT			: 
		case SOT_LEGAL_DISCLAIMER_COMBOBOX		: 
		case SOT_LEGAL_DISCLAIMER_TEXT			: 
		case SOT_LEGAL_DISCLAIMER_LABEL			:
		case SOT_PASSWORD_RESET_BUTTON			: return CPFS_DISPLAY_IN_SELECTED_TILE;

		default				 					: return CPFS_HIDDEN;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : GetInteractiveFieldState
      	
	Parameters :
			Input : 
				paramType - content parameter type

	Return : Windows credential provider field 
			 interactive state

	Description :  Get windows credential 
				   provider field interactive state

*****************************************************************/
CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE WinCPScreenBuilder :: GetInteractiveFieldState(int paramType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : GetInteractiveFieldState");
	#endif

	switch(paramType)
	{
		case SOT_USER_NAME_BOX					: return CPFIS_FOCUSED;

		case SOT_IMAGE							: 
		case SOT_LARGE_TEXT						: 
		case SOT_SMALL_TEXT						: 
		case SOT_BIG_TEXT_BLOCK					: 
		case SOT_TEXT_BOX						: 
		case SOT_BUTTON							: 
		case SOT_CHECKBOX						: 
		case SOT_COMBOBOX						: 
		case SOT_COMMAND_LINK					: 
		case SOT_DATE_TIME_TEXT					: 
		case SOT_DOMAIN_NAME_BOX				: 
		case SOT_PASSWORD_BOX					: 
		case SOT_EDUCATION_LABEL				: 
		case SOT_EDU_ANSWER_BOX					: 
		case SOT_EDU_QUESTION_TEXT				: 
		case SOT_EDU_LESSON_TEXT				: 
		case SOT_EDU_LESSON_IMAGE				: 
		case SOT_SIMPLE_NOTICE_TEXT				: 
		case SOT_WARNING_NOTICE_TEXT			: 
		case SOT_LEGAL_DISCLAIMER_COMBOBOX		: 
		case SOT_LEGAL_DISCLAIMER_IMAGE			: 
		case SOT_LEGAL_DISCLAIMER_TEXT			: 
		case SOT_LEGAL_DISCLAIMER_LABEL			: 
		case SOT_PASSWORD_RESET_BUTTON			: return CPFIS_NONE;

		default 								: return CPFIS_NONE;
	}
}

/****************************************************************

   Class : WinCPScreenBuilde

   Method : SetFieldValues
      	
	Parameters :
			Input : 
				mainScreenObject - pointer to main screen object
				contentObject - pointer to content screen object

	Description :  Set user parameter field value

*****************************************************************/
void WinCPScreenBuilder :: SetFieldValues(PMAIN_SCREEN_OBJECT_DESCRIPTOR mainScreenObject, PSCREEN_OBJECT contentObject)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : SetFieldParamValue");
	#endif

	switch(contentObject -> objTypeId)
	{
		case SOT_DATE_TIME_TEXT		: 
			{
				// Get current data and time
				time_t seconds = time(NULL);
				tm * timeinfo = localtime(&seconds);
				mainScreenObject -> timeinfo = (tm *)malloc(sizeof(tm));
				memcpy(mainScreenObject -> timeinfo, timeinfo, sizeof(tm));
				wcsftime(mainScreenObject -> fieldDescriptor.pszLabel, STR_VALUE_LEN, L"%A, %m/%d/%y, %H:%M:%S"/*L"%H:%M:%S on %A, %B %d"*/, mainScreenObject -> timeinfo);
				wcsftime(mainScreenObject -> strValue, STR_VALUE_LEN, L"%A, %m/%d/%y, %H:%M:%S"/*L"%H:%M:%S on %A, %B %d"*/, mainScreenObject -> timeinfo);
				break;
			}

		case SOT_LARGE_TEXT				: 
		case SOT_SMALL_TEXT				: 
		case SOT_CHECKBOX				: 
		case SOT_COMMAND_LINK			: 
		case SOT_EDUCATION_LABEL		: 
		case SOT_LEGAL_DISCLAIMER_LABEL :
		case SOT_PASSWORD_RESET_BUTTON	:
			{
				// Set values of label and srtValue
				mbstowcs(mainScreenObject -> fieldDescriptor.pszLabel, contentObject -> objCaption, NAME_LEN);
				mbstowcs(mainScreenObject -> strValue, contentObject -> strValue, NAME_LEN);
				break;
			}

		case SOT_IMAGE				:
		case SOT_EDU_LESSON_IMAGE	:
		case SOT_LEGAL_DISCLAIMER_IMAGE	:
			{
				// Get image value
				if (mainScreenObject -> imgValue)
					free(mainScreenObject -> imgValue);

				if (mainScreenObject -> imgValueSize > 0)
				{
					mainScreenObject -> imgValue = malloc(mainScreenObject -> imgValueSize);
				
					if ((mainScreenObject -> imgValue) && (contentObject -> imgValue))
						memcpy(mainScreenObject -> imgValue, contentObject -> imgValue, mainScreenObject -> imgValueSize);
				}
				else
					mainScreenObject -> imgValue = NULL;
				
				mbstowcs(mainScreenObject -> fieldDescriptor.pszLabel, "Picture", NAME_LEN);
				break;
			}

		case SOT_BIG_TEXT_BLOCK			:
		case SOT_EDU_QUESTION_TEXT		:
		case SOT_EDU_LESSON_TEXT		:
		case SOT_LEGAL_DISCLAIMER_TEXT	:
		case SOT_SIMPLE_NOTICE_TEXT		: 
		case SOT_WARNING_NOTICE_TEXT	: 
			{
				// Get big text value
				if (contentObject -> textValueSize > 0)
				{
					if (mainScreenObject -> textValue)
						free(mainScreenObject -> textValue);

					if (mainScreenObject -> textValueSize > 0)
					{
						mainScreenObject -> textValue = (WCHAR *)malloc(mainScreenObject -> textValueSize);
				
						if ((mainScreenObject -> textValue) && (contentObject -> textValue))
							mbstowcs(mainScreenObject -> textValue, contentObject -> textValue, contentObject -> textValueSize);
					}
					else
						mainScreenObject -> textValue = NULL;

					mbstowcs(mainScreenObject -> fieldDescriptor.pszLabel, "Text", NAME_LEN);
				}

				break;
			}

		case SOT_PASSWORD_BOX	: 
			{
				if (strcmp(contentObject -> objCaption, "") == 0)
					wcscpy(mainScreenObject -> fieldDescriptor.pszLabel, L"User password");
				else
					mbstowcs(mainScreenObject -> fieldDescriptor.pszLabel, contentObject -> objCaption, NAME_LEN);

				wcscpy(mainScreenObject -> strValue, L"");
				break;
			}

		case SOT_USER_NAME_BOX	: 
			{
				if (strcmp(contentObject -> objCaption, "") == 0)
					wcscpy(mainScreenObject -> fieldDescriptor.pszLabel, L"User name");
				else
					mbstowcs(mainScreenObject -> fieldDescriptor.pszLabel, contentObject -> objCaption, NAME_LEN);

				wcscpy(mainScreenObject -> strValue, L"");
				break;
			}

		default 				: 
			{
				// Default actions
				mbstowcs(mainScreenObject -> fieldDescriptor.pszLabel, contentObject -> objCaption, NAME_LEN);
				wcscpy(mainScreenObject -> strValue, L"");
				break;
			}
	}
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : GenerateSymbolBoxes
   
   Parameters:
			Input:
				symbolBoxesType - type of symbol box password

   Return : Pointer to symbol matrixes list
	
   Description :  Generate symbol boxes list

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST WinCPScreenBuilder :: GenerateSymbolBoxes(int symbolBoxesType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : GenerateSymbolBoxes. Start");
	#endif

	// Create symbol boxes manager instance
	SymbolBoxes * symbolBoxes = new SymbolBoxes(0, logWriter);

	// Preapre list of all symbols
	char symbols [] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
		               'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
					   '#', '$', '%', '*', '~', '+', '-', '(', ')', '{', '}', '[', ']', '//', '<', '=', '>', '^', ';', ':', '|', '?', '!', '@', '\\'};

	// Create symbol matrixes list
	PUTF8_STRINGS_MATRIX_LIST pMatrixes = symbolBoxes -> GenerateSymbolBoxes(symbols, sizeof(symbols), symbolBoxesType);
	
	// Remove symbol boxes manager instance
	delete symbolBoxes;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : GenerateSymbolBoxes. Done");
	#endif

	return pMatrixes;
}


/****************************************************************

   Class : WinCPScreenBuilder

   Method : CreateSymbolBoxPasswordWindow

   Parameters:
			Input:
				imgSize - images size
				symbolBoxesType - type of symbol box password
				pMatrixes - pointer to symbol matrixes list

   Return : pointer to subwindow instance
	
   Description :  Create symbol boxes password window

*****************************************************************/
PSUB_WINDOW WinCPScreenBuilder :: CreateSymbolBoxPasswordWindow(int imgSize, int symbolBoxesType, PUTF8_STRINGS_MATRIX_LIST pMatrixes)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Start");
	#endif

	if(!pMatrixes)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Wrong input parameters");
			WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Done");
		#endif

		return NULL;
	}

	// Create symbol boxes manager instance
	SymbolBoxes * symbolBoxes = new SymbolBoxes(imgSize, logWriter);

	// Draw images
	symbolBoxes -> DrawSymbolBoxes(pMatrixes);
	
	PSUB_WINDOW pSubWindow = (PSUB_WINDOW)malloc(sizeof(SUB_WINDOW));

	if (!pSubWindow)
	{
		// Remove symbol boxes manager instance
		delete symbolBoxes;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Can not create subwindow instance!");
			WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Done");
		#endif

		return NULL;
	}

	// Sub window parameters
	pSubWindow -> windowID = -1;
	pSubWindow -> windowTypeId = SOT_SYMBOL_BOXES_PWD_SCREEN;
	wcscpy(pSubWindow -> windowName, L"Symbol boxes password");
	wcscpy(pSubWindow -> caption, L"Symbol boxes password");
	pSubWindow -> color = 0x0;
	pSubWindow -> hWnd = NULL;
	pSubWindow -> heightPix = 0;
	pSubWindow -> widthPix = 0;
	pSubWindow -> locationX = 0;
	pSubWindow -> locationY = 0;
	pSubWindow -> widthPers = 0;
	pSubWindow -> heightPers = 0;
	pSubWindow -> locationXPers = 0;
	pSubWindow -> locationYPers = 0;

	int osVer = GetOSVersion();
	
	// Symbol boxes password window width
	#define PWD_ONE_SYM_BOX_WND_WIDTH		81
	#define PWD_TWO_SYM_BOX_WND_WIDTH		60

	// Symbol boxes password window width
	#define PWD_ONE_SYM_BOX_WND_HEIGHT		17
	#define PWD_TWO_SYM_BOX_WND_HEIGHT		23


	if ((osVer == OS_WIN_7_X32) || 
		(osVer == OS_WIN_7_X64))
	{
		// Win 7 params
		if (symbolBoxesType == ONE_SYMBOL_BOX_PWD)
		{
			pSubWindow -> widthPix = (screenWidth * PWD_ONE_SYM_BOX_WND_WIDTH) / 100;
			pSubWindow -> heightPix = (pSubWindow -> widthPix * PWD_ONE_SYM_BOX_WND_HEIGHT) / 100;
		}
		else
		if (symbolBoxesType == TWO_SYMBOL_BOX_PWD)
		{
			pSubWindow -> widthPix = (screenWidth * PWD_TWO_SYM_BOX_WND_WIDTH) / 100;
			pSubWindow -> heightPix = (pSubWindow -> widthPix * PWD_TWO_SYM_BOX_WND_HEIGHT) / 100;
		}

		pSubWindow -> locationX = (screenWidth - pSubWindow -> widthPix) / 2;
		pSubWindow -> locationY = screenHeight - pSubWindow -> heightPix - (screenHeight - pSubWindow -> heightPix * 2) / 100;
	}

	if ((osVer == OS_WIN_8_X32) || 
		(osVer == OS_WIN_8_X64) || 
		(osVer == OS_WIN_10_X32) || 
		(osVer == OS_WIN_10_X64) || 
		(osVer == OS_UNKNOWN))
	{
		// Win 8 params
		if (symbolBoxesType == ONE_SYMBOL_BOX_PWD)
		{
			pSubWindow -> widthPix = (screenWidth * PWD_ONE_SYM_BOX_WND_WIDTH) / 100;
			pSubWindow -> heightPix = (pSubWindow -> widthPix * PWD_ONE_SYM_BOX_WND_HEIGHT) / 100;
		}
		else
		if (symbolBoxesType == TWO_SYMBOL_BOX_PWD)
		{
			pSubWindow -> widthPix = (screenWidth * PWD_TWO_SYM_BOX_WND_WIDTH) / 100;
			pSubWindow -> heightPix = (pSubWindow -> widthPix * PWD_TWO_SYM_BOX_WND_HEIGHT) / 100;
		}

		pSubWindow -> locationX = (screenWidth - pSubWindow -> widthPix) / 2;
		pSubWindow -> locationY = (screenHeight - pSubWindow -> heightPix * 4) / 100;
	}

	// Symbol box position

	// Location X
	#define ONE_SYM_BOX_LOCATION_X			0.2
	#define TWO_SYM_BOX_LOCATION_X			4

	// Location Y
	#define ONE_SYM_BOX_LOCATION_Y			5
	#define TWO_SYM_BOX_LOCATION_Y			4

	
	// Symbol box size
	#define ONE_SYM_BOX_SIZE				10
	#define TWO_SYM_BOX_SIZE				15


	// Create sub window objects
	int locX = 0;
	int locY = 0;
	int boxSize = 0;
	
	switch(symbolBoxesType)
	{
		case ONE_SYMBOL_BOX_PWD: 
			{
				locX = (pSubWindow -> widthPix * ONE_SYM_BOX_LOCATION_X)/100;
				locY = ONE_SYM_BOX_LOCATION_Y;
				boxSize = ONE_SYM_BOX_SIZE;
				break;
			}

		case TWO_SYMBOL_BOX_PWD: 
			{
				locX = (pSubWindow -> widthPix * TWO_SYM_BOX_LOCATION_X)/100;
				locY = TWO_SYM_BOX_LOCATION_Y;
				boxSize = TWO_SYM_BOX_SIZE;
				break;
			}
	}


	pSubWindow -> windowObjectsCount = 0;

	// Create symbol boxes
	char fileName[STR_VALUE_LEN] = "";
	for(int i = 0; i < pMatrixes -> size; i++)
	{
		try
		{
			symbolBoxes -> GetSymbolBoxFileName(i + 1, fileName);

			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] = (PWINDOW_OBJECT_DESCRIPTOR)malloc(sizeof(WINDOW_OBJECT_DESCRIPTOR));
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> backgroundColor = 0xFFFFFF;
			wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> caption,L"Symbol Box");
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> chbChecked = FALSE;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> comboBoxIndex = -1;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> comboBoxValuesCount = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> fontSize = 12;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hBitmap = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hFont = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hWnd = NULL;

			int imgSize = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> imgValue = LoadBMPImageValue(fileName, &imgSize);
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> imgValueSize = imgSize;
			DeleteFileA(fileName);

			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectID = -1;
			wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectName, L"Symbol Box");
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectTypeId = SOT_IMAGE;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> questionID = -1;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> rightAnswerID = -1;
			wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> strValue, L"");
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textColor = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textValue = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textValueSize = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> timeinfo = NULL;
			
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPix =  (pSubWindow -> widthPix * boxSize)/100;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> heightPix = pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPix;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationX = locX;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationY = (pSubWindow -> heightPix * locY)/100;

			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> heightPers = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPers = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationXPers = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationYPers = 0;

			switch(symbolBoxesType)
			{		
				case ONE_SYMBOL_BOX_PWD: 
				{
					locX += (pSubWindow -> widthPix * ONE_SYM_BOX_LOCATION_X*0.3)/100 + pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPix;
					break;
				}

				case TWO_SYMBOL_BOX_PWD: 
				{
					locX += (pSubWindow -> widthPix * TWO_SYM_BOX_LOCATION_X)/100 + pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPix;
					break;
				}
			}
						

			pSubWindow -> windowObjectsCount++;

		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Can't create symbol box object!");
			#endif
		}
	}
			
	// Create buttons
	int buttonsCount = 8;

	switch(symbolBoxesType)
	{
		case ONE_SYMBOL_BOX_PWD: 
			{
				buttonsCount = 8;
				locX = 8;
				break;
			}

		case TWO_SYMBOL_BOX_PWD: 
			{
				buttonsCount = 8;
				locX = 8;
				break;
			}
	}
		
	for(int i = 0; i < buttonsCount; i++)
	{
		try
		{
			// Get string coords
			int sX = 0, sY = 0;
			switch(i)
			{
				case 0: sX = 0;
						sY = 0;
						break;

				case 1: sX = 0;
						sY = 1;
						break;

				case 2: sX = 0;
						sY = 2;
						break;

				case 3: sX = 1;
						sY = 0;
						break;

				case 4: sX = 1;
						sY = 2;
						break;

				case 5: sX = 2;
						sY = 0;
						break;

				case 6: sX = 2;
						sY = 1;
						break;

				case 7: sX = 2;
						sY = 2;
						break;
			}

			char tmpStr[STR_VALUE_LEN];
			int tmpStrLen = 0;
			
			// Get string bytes
			symbolBoxes -> WriteUTF8CharsToByteSequence(pMatrixes -> matrixes[0] -> strings[sX][sY], tmpStr, &tmpStrLen);
			tmpStr[tmpStrLen] = 0;
			WCHAR wTmpStr[STR_VALUE_LEN];
			mbstowcs(wTmpStr, tmpStr, STR_VALUE_LEN);


			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] = (PWINDOW_OBJECT_DESCRIPTOR)malloc(sizeof(WINDOW_OBJECT_DESCRIPTOR));
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> backgroundColor = 0xFFFFFF;
			
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> caption[0] = wTmpStr[0];
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> caption[1] = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> strValue[0] = wTmpStr[0];
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> strValue[1] = 0;
			
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> chbChecked = FALSE;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> comboBoxIndex = -1;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> comboBoxValuesCount = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> fontSize = 12;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hBitmap = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hFont = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hWnd = NULL;

			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> imgValue = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> imgValueSize = 0;

			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectID = i;
			wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectName, L"Symbol Button");
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectTypeId = SOT_BUTTON;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> questionID = -1;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> rightAnswerID = -1;
			
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textColor = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textValue = NULL;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textValueSize = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> timeinfo = NULL;
			
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> heightPix = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPix = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationX = 0;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationY = 0;

			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> heightPers = 22;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPers = 6;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationXPers = locX;
			pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationYPers = 74;

			locX += 3 + pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPers;

			pSubWindow -> windowObjectsCount++;

		}
		catch(...)
		{
			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Can't create symbol button!");
			#endif
		}
	}

	// Create backspace button
	try
	{
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] = (PWINDOW_OBJECT_DESCRIPTOR)malloc(sizeof(WINDOW_OBJECT_DESCRIPTOR));
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> backgroundColor = 0xFFFFFF;
			
		wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> caption, L"Back");
		wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> strValue, L"Back");
			
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> chbChecked = FALSE;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> comboBoxIndex = -1;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> comboBoxValuesCount = 0;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> fontSize = 12;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hBitmap = NULL;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hFont = NULL;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> hWnd = NULL;

		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> imgValue = NULL;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> imgValueSize = 0;

		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectID = 8;
		wcscpy(pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectName, L"Backspace Button");
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> objectTypeId = SOT_BUTTON;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> questionID = -1;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> rightAnswerID = -1;
			
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textColor = 0;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textValue = NULL;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> textValueSize = 0;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> timeinfo = NULL;
			
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> heightPix = 0;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPix = 0;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationX = 0;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationY = 0;

		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> heightPers = 22;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPers = 12;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationXPers = locX;
		pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> locationYPers = 74;

		locX += 3 + pSubWindow -> windowObjects[pSubWindow -> windowObjectsCount] -> widthPers;

		pSubWindow -> windowObjectsCount++;

	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Can't create backspace button!");
		#endif
	}
	
	delete symbolBoxes;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateSymbolBoxPasswordWindow. Done");
	#endif

	return pSubWindow;
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : LoadBMPImageValue

   Parameters:
			Input:
				fileName - file name

			Output:
				imgSize - size of BMP image

   Return : Buffer with BMP file caontent
	
   Description :  Load BMP file

*****************************************************************/
char * WinCPScreenBuilder :: LoadBMPImageValue(char * fileName, int * imgSize)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Start");
	#endif

	if ((!fileName) || (!imgSize))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Wrong input data!");
			WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Start");
		#endif

		return NULL;
	}
	
	 FILE* f;

	// Open file
    if((f = fopen(fileName, "rb")) == NULL)
	{
       #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Can't read image file! File does not exist!");
			WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Done");
		#endif

		*imgSize = -1;
		return NULL;
    }
    
    // Get file size
    fseek(f, 0L, SEEK_END);
    int size = ftell(f); 
    fseek(f, 0L, SEEK_SET); 
    
	*imgSize = size;

    // Prepare buffer
    char * buf = (char *)malloc(size);

	if (!buf)
	{
		fclose(f);

       #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Memory allocation error!");
			WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Done");
		#endif

		*imgSize = -1;
		return NULL;
	}

    // Read file
    fread(buf, 1, size, f);
 
    // Close file
    fclose(f);

    #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. BMP file reading success!");
		WriteToLog("WinCPScreenBuilder : LoadBMPImageValue. Done");
	#endif

	return buf;
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : GetPwdSymbolBoxImageSize

   Return : Symbol box image size
	
   Description :  Calculate symbol box image size

*****************************************************************/
int WinCPScreenBuilder :: GetPwdSymbolBoxImageSize(int symbolBoxesType)
{
	int width = 0;
	int size = 0;

	switch(symbolBoxesType)
	{
		case ONE_SYMBOL_BOX_PWD: 
			{
				width = PWD_ONE_SYM_BOX_WND_WIDTH;
				size = ONE_SYM_BOX_SIZE;
				break;
			}

		case TWO_SYMBOL_BOX_PWD: 
			{
				width = PWD_TWO_SYM_BOX_WND_WIDTH;
				size = TWO_SYM_BOX_SIZE;
				break;
			}
	}

	return (((screenWidth * width) / 100) * size) / 100;
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : ClearScreenContainer

   Parameters:
			Input:
				userScreenContainer - pointer to user screen container

   Return : if container is cleared then returns NULL
	
	Description :  Clear of user screen container

*****************************************************************/
PUSER_SCREEN_CONTAINER WinCPScreenBuilder :: ClearScreenContainer(PUSER_SCREEN_CONTAINER userScreenContainer)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : ClearScreenContainer");
	#endif

	// Validate container
	if (userScreenContainer)
	{
		// Free main screen objects
		for(int i = 0; i < userScreenContainer -> screenObjectsCount; i++)
		{
			if(userScreenContainer -> screenObjects[i])
			{
				// Free label
				if (userScreenContainer -> screenObjects[i] -> fieldDescriptor.pszLabel)
					free(userScreenContainer -> screenObjects[i] -> fieldDescriptor.pszLabel);

				// Free image
				if (userScreenContainer -> screenObjects[i] -> imgValue)
					free(userScreenContainer -> screenObjects[i] -> imgValue);

				// Free big text
				if (userScreenContainer -> screenObjects[i] -> textValue)
					free(userScreenContainer -> screenObjects[i] -> textValue);

				if (userScreenContainer -> screenObjects[i] -> timeinfo)
					free(userScreenContainer -> screenObjects[i] -> timeinfo);

			
				// Free object
				free(userScreenContainer -> screenObjects[i]);
			}
		}

		// Free sub windows
		for(int i = 0; i < userScreenContainer -> subWindowCount; i++)
		{
			if (userScreenContainer -> subWindows[i])
			{
				// Free sub window objects
				for(int j = 0; j < userScreenContainer -> subWindows[i] -> windowObjectsCount; j++)
				{
					if (userScreenContainer -> subWindows[i] -> windowObjects[j])
					{
						// Free iamge
						if (userScreenContainer -> subWindows[i] -> windowObjects[j] -> imgValue)
							free(userScreenContainer -> subWindows[i] -> windowObjects[j] -> imgValue);

						// Free big text
						if (userScreenContainer -> subWindows[i] -> windowObjects[j] -> textValue)
							free(userScreenContainer -> subWindows[i] -> windowObjects[j] -> textValue);

						if (userScreenContainer -> subWindows[i] -> windowObjects[j]  -> timeinfo)
							free(userScreenContainer -> subWindows[i] -> windowObjects[j]  -> timeinfo);

						// Free object
						free(userScreenContainer -> subWindows[i] -> windowObjects[j]);
					}
				}

				// Free sub window
				free(userScreenContainer -> subWindows[i]);
			}
		}

		// Free container
		free(userScreenContainer);
		
		userScreenContainer = NULL;
	}
	
	return userScreenContainer;
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : CreateSymbolBoxes

   Return : Pointer to symbol matrixes list
	
   Description :  Create symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST WinCPScreenBuilder :: CreateSymbolBoxes(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateSymbolBoxes. Start");
	#endif

	SymbolBoxes * symbolBoxes = new SymbolBoxes(0, logWriter);
	
	PUTF8_STRINGS_MATRIX_LIST pMatrixes = symbolBoxes -> CreateUTF8MatrixList();

	delete symbolBoxes;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : CreateSymbolBoxes. Done");
	#endif

	return pMatrixes;
}

/****************************************************************

   Class : WinCPScreenBuilder

   Method : RemoveSymbolBoxes

   Parameters:
			Input:
				symbolMatrixesList - pointer to symbol matrixes list

   Return : Pointer to symbol matrixes list
	
   Description :  Remove symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST WinCPScreenBuilder :: RemoveSymbolBoxes(PUTF8_STRINGS_MATRIX_LIST symbolMatrixesList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : RemoveSymbolBoxes. Start");
	#endif

	SymbolBoxes * symbolBoxes = new SymbolBoxes(0, logWriter);
	
	symbolMatrixesList = symbolBoxes -> RemoveUTF8MatrixList(symbolMatrixesList);

	delete symbolBoxes;
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("WinCPScreenBuilder : RemoveSymbolBoxes. Done");
	#endif

	return symbolMatrixesList;
}