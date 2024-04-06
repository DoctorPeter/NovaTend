/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : ScreenDataDef.h

   Description :  this module defines structure of
				  windows authentication screen objects

*****************************************************************/

#include <Windows.h>
#include <ContentDataDef.h>
#include <time.h>
#include <credentialprovider.h>

#ifndef SCREEN_DATA_DEF_H
#define SCREEN_DATA_DEF_H

// Structure of descriptor of main screen object
typedef struct mainScreenObjectDescriptor
{
	// Object unique number
	int objectID;
	
	// Type of object
	int objectTypeID;

	// Object order
	int order;

	// ID of right answer (for SOT_QUESTION_TEXT)
	int rightAnswerID;
	
	// ID of question (for SOT_QUESTION_TEXT)
	int questionID;

	// Object name
	WCHAR objectName[NAME_LEN];
	
	// Object string value
	WCHAR strValue[STR_VALUE_LEN];

	// Object text value size
	int textValueSize;

	// Object text value
	WCHAR * textValue;

	// Object image value size
	int imgValueSize;

	// Object image value
	void * imgValue;
	
	// Index of combobox selected item
	DWORD comboBoxIndex;

	// Checkbox flag
	BOOL chbChecked;

	// Time for time label
	tm * timeinfo;

	// Windows credential provider field descriptor
	CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR fieldDescriptor;

	// Windows credential provider field state
	CREDENTIAL_PROVIDER_FIELD_STATE fieldState;

	// Windows credential provider field interactive state
	CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE fieldInteractiveState;

	// Combobox items count
	int comboBoxValuesCount;

	// Comobobox values
	WCHAR comboBoxValues[LIST_VALUES_SET_MAX_SIZE][STR_VALUE_LEN];

} MAIN_SCREEN_OBJECT_DESCRIPTOR, *PMAIN_SCREEN_OBJECT_DESCRIPTOR;


// Structure of window object
typedef struct windowObjectDescriptor
{
	// Window object unique number
	int objectID;

	// Window object name
	WCHAR objectName[NAME_LEN];

	// Window object type ID
	int objectTypeId;

	// Window object caption
	WCHAR caption[NAME_LEN];

	// Window object position X
	int locationX;

	// Window object position Y
	int locationY;

	// Window object position X in percents
	int locationXPers;

	// Window object position Y in percents
	int locationYPers;

	// Window object width in pixels
	int widthPix;
	
	// Window object height in pixels
	int heightPix;

	// Window object width in percents
	int widthPers;
	
	// Window object height in percents
	int heightPers;

	// Font size
	int fontSize;

	// Color of text
	unsigned int textColor;

	// Color of background
	unsigned int backgroundColor;

	// ID of right answer (for SOT_EDU_QUESTION_TEXT)
	int rightAnswerID;
	
	// ID of question (for SOT_EDU_QUESTION_TEXT)
	int questionID;

	// Object string value
	WCHAR strValue[STR_VALUE_LEN];

	// Object text value size
	int textValueSize;

	// Object text value
	WCHAR * textValue;

	// Object image value size
	int imgValueSize;

	// Object image value
	void * imgValue;
	
	// Index of combobox selected item
	DWORD comboBoxIndex;

	// Checkbox flag
	BOOL chbChecked;

	// Combobox items count
	int comboBoxValuesCount;

	// Comobobox values
	WCHAR comboBoxValues[LIST_VALUES_SET_MAX_SIZE][STR_VALUE_LEN];

	// Time for time label
	tm * timeinfo;

	// Window handle
	HWND hWnd;

	// Bitmap handle
	HBITMAP hBitmap;

	// Foant handle
	HFONT	hFont;

} WINDOW_OBJECT_DESCRIPTOR, *PWINDOW_OBJECT_DESCRIPTOR;

// Structure of sub window
typedef struct subWindow
{
	// Window unique number
	int windowID;

	// Window name
	WCHAR windowName[NAME_LEN];

	// Window type ID
	int windowTypeId;

	// Window caption
	WCHAR caption[NAME_LEN];

	// Window position X
	int locationX;

	// Window position Y
	int locationY;

	// Window position X in percents
	int locationXPers;

	// Window position Y in percents
	int locationYPers;

	// Window width in pixels
	int widthPix;
	
	// Window height in pixels
	int heightPix;

	// Window width in percents
	int widthPers;
	
	// Window height in percents
	int heightPers;

	// Color of window
	unsigned int color;

	// Window objects count
	int windowObjectsCount;

	// Window objects list
	PWINDOW_OBJECT_DESCRIPTOR windowObjects[MAX_SCR_OBJ_COUNT];

	// Window handle
	HWND hWnd;

} SUB_WINDOW, *PSUB_WINDOW;

// Structure of user screen container
typedef struct userScreenContainer
{
	// Main screen objects count
	int screenObjectsCount;
	
	// List of main screen objects
	PMAIN_SCREEN_OBJECT_DESCRIPTOR screenObjects[MAX_SCR_OBJ_COUNT];

	// Sub windows count
	int subWindowCount;

	// List of sub windows
	PSUB_WINDOW subWindows[MAX_SCR_OBJ_COUNT];

}USER_SCREEN_CONTAINER, *PUSER_SCREEN_CONTAINER;

#endif