/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : SymbolBox.h

   Description :  this module defines interface of
				  class SymbolBoxes

*****************************************************************/

#include "ScreenDataDef.h"
#include <LogWriter.h>

#ifndef SBOX_H
#define SBOX_H

/****************************************************************

   Class : SymbolBoxes

   Description : Responsible for generation of a list of symbol boxes
				 which is used for graphical-symbol passwords

*****************************************************************/
class SymbolBoxes
{
	private:

		// Image size
		int imageSize;

		// Log writer instance
		LogWriter * logWriter;

		// Write message to log-file
		int WriteToLog(char * message);

		// Random number generator in the range [min_val, max_val]
		int RangeRand(int min_val, int max_val);

		// Random sort UTF8 string
		PUTF8_STRING RandomSortUTF8String(PUTF8_STRING string);

		// Rotate right UTF8 string
		PUTF8_STRING RotateUTF8StringRight(PUTF8_STRING string, int steps);


	public:
		
		// Constructor
		SymbolBoxes(int imageSize, LogWriter * logWriter);

		// Destructor
		~SymbolBoxes(void);


		// Create list of symbol boxes
		PUTF8_STRINGS_MATRIX_LIST CreateUTF8MatrixList(void);

		// Remove list of symbol boxes
		PUTF8_STRINGS_MATRIX_LIST RemoveUTF8MatrixList(PUTF8_STRINGS_MATRIX_LIST matrixList);


		// Create symbol matrix
		PUTF8_STRINGS_MATRIX CreateUTF8Matrix(void);
		
		// Remove symbol matrix
		PUTF8_STRINGS_MATRIX RemoveUTF8Matrix(PUTF8_STRINGS_MATRIX matrix);


		// Create UTF8 chars list
		PUTF8_STRING CreateUTF8String(void);

		// Remove UTF8 chars list
		PUTF8_STRING RemoveUTF8String(PUTF8_STRING string);


		// Create UTF8 char structure
		PUTF8_CHAR CreateUTF8Char(void);

		// Remove UTF8 char structure
		PUTF8_CHAR RemoveUTF8Char(PUTF8_CHAR uChar);


		// Read UTF8 chars list from byte sequence
		PUTF8_STRING ReadUTF8CharsFromByteSequence(char * seq, int size);

		// Write UTF8 chars list from byte sequence
		char * WriteUTF8CharsToByteSequence(PUTF8_STRING string, char * seq, int * size);

		// Get size of UTF8 string in bytes
		int GetBytesCount(PUTF8_STRING string);

		// Get random UTF8 chars list from byte sequence
		PUTF8_STRING GetRandomCharList(char * seq, int size, int symbolsCount);
		
		// Get random UTF8 chars list from some UTF8 chars list
		PUTF8_STRING GetRandomCharList(PUTF8_STRING charList, int symbolsCount);

		// Find char in list
		bool UTF8CharPresentInString(PUTF8_STRING charList, PUTF8_CHAR uChar);

		// Generate list of symbol boxes (one symbol per cell)
		PUTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxesOneSymbol(PUTF8_STRING charList);

		// Generate list of symbol boxes (two symbols per cell)
		PUTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxesTwoSymbols(PUTF8_STRING charList);

		// Generate list of symbol boxes
		PUTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxes(PUTF8_STRING charList, int symbolBoxesType);

		// Generate list of symbol boxes
		PUTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxes(char * seq, int size, int symbolBoxesType);

		// Generate and draw list of symbol boxes
		bool GenerateAndDrawSymbolBoxes(PUTF8_STRING charList, int symbolBoxesType);

		// Generate and draw list of symbol boxes
		bool GenerateAndDrawSymbolBoxes(char * seq, int size, int symbolBoxesType);

		// Draw symbol boxes
		bool DrawSymbolBoxes(PUTF8_STRINGS_MATRIX_LIST matrixList);

		// Draw symbol box
		bool DrawSymbolBox(PUTF8_STRINGS_MATRIX matrix, char * fileName);

		// Get symbol box file name
		char * GetSymbolBoxFileName(int index, char * fileName);

};

#endif