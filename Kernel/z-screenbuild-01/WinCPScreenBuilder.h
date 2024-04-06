/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : WinCPScreenBuilder.h

   Description :  this module defines interface of
				  class WinCPScreenBuilder

*****************************************************************/

#include "ScreenBuilder.h"
#include <credentialprovider.h>
#include <time.h>
#include "SymbolBox.h"
#include "ScreenDataDef.h"

#ifndef WINCPSCREENBUILDER_H
#define WINCPSCREENBUILDER_H

/****************************************************************

   Class : ScreenBuilder

   Description : class that inherited from SreenBuilder and
				 responsible for creation structure of 
				 user sing in screen for widows credential 
				 provider

				 This class is designed only for the 
				 Windows operating systems.

*****************************************************************/
class SCREENBUILDER_API WinCPScreenBuilder : public ScreenBuilder
{
	private:
						
		// Get user parameter field type
		CREDENTIAL_PROVIDER_FIELD_TYPE GetFieldType(int paramType);

		// Get user parameter field state
		CREDENTIAL_PROVIDER_FIELD_STATE GetFieldState(int paramType);

		// Get user parameter field interactive state
		CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE GetInteractiveFieldState(int paramType);
						
		// Create screen container
		PUSER_SCREEN_CONTAINER CreateScreenContainer(void);

		// Set user parameter field value
		void SetFieldValues(PMAIN_SCREEN_OBJECT_DESCRIPTOR mainScreenObject, PSCREEN_OBJECT contentObject);

		// Fill main screen
		BOOL FillMainScreen(PPRESET_CONTAINER content, PUSER_SCREEN_CONTAINER userScreenContainer);

		// Add tile image
		BOOL AddTileImage(PUSER_SCREEN_CONTAINER userScreenContainer);

		// Add submit button
		BOOL AddSubmitButton(PUSER_SCREEN_CONTAINER userScreenContainer);

		// Add sub window
		BOOL AddSubWindow(PUSER_SCREEN screen, PUSER_SCREEN_CONTAINER userScreenContainer);

		// Add sub window
		BOOL AddSubWindow(PSUB_WINDOW subWindow, PUSER_SCREEN_CONTAINER userScreenContainer);

		// Create symbol boxes password window
		PSUB_WINDOW CreateSymbolBoxPasswordWindow(int imgSize, int symbolBoxesType, PUTF8_STRINGS_MATRIX_LIST pMatrixes);

		// Load BMP file
		char * LoadBMPImageValue(char * fileName, int * imgSize);

		// Get password symbol box image size
		int GetPwdSymbolBoxImageSize(int symbolBoxesType);

	public:
		
		// Constructor
		WinCPScreenBuilder(unsigned long dllUserID, LogWriter * logWriter);

		// Destructor
		virtual ~WinCPScreenBuilder(void);

		// Create user screen container
		void * CreateUserScreen(PPRESET_CONTAINER content);

		// Clear user screen container
		PUSER_SCREEN_CONTAINER ClearScreenContainer(PUSER_SCREEN_CONTAINER userScreenContainer);
		
		// Create user screen container for local sign in
		PUSER_SCREEN_CONTAINER CreateLocalScreenContainer(void);
				
		// Create symbol boxes
		PUTF8_STRINGS_MATRIX_LIST CreateSymbolBoxes(void);

		// Remove symbol boxes
		PUTF8_STRINGS_MATRIX_LIST RemoveSymbolBoxes(PUTF8_STRINGS_MATRIX_LIST symbolMatrixesList);

		// Generate symbol boxes list
		PUTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxes(int symbolBoxesType);

		// Add symbol boxes password window
		bool AddSymbolBoxesPasswordWindow(PUTF8_STRINGS_MATRIX_LIST pMatrixes, int symbolBoxesType, PUSER_SCREEN_CONTAINER userScreenContainer);
};

#endif