/****************************************************************

   Solution : NovaTend

   Project : z-screenbuild-01.dll

   Module : SymbolBox.cpp

   Description :  this module implements methods of
				  class SymbolBoxes

*****************************************************************/

#include "stdafx.h"
#include "SymbolBox.h"

#include "cairo\cairo.h"
#include <ShlObj.h>

/****************************************************************

   Class : SymbolBoxes

   Method : Constructor

   Parameters :
			Input : 
				imageSize - image size
				logWriter - pointer to LogWriter instance

*****************************************************************/
SymbolBoxes :: SymbolBoxes(int imageSize, LogWriter * logWriter)
{
	this -> logWriter = logWriter;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : constructor");
	#endif
	
	int sizeCorrect = imageSize % 10;
	this -> imageSize = imageSize - sizeCorrect;
	
	
	/*if (imageSize % 10 == 5)
		this -> imageSize = imageSize - 1;
	else
		this -> imageSize = imageSize;*/
	

	srand((unsigned int)time(NULL));
}

/****************************************************************

   Class : SymbolBoxes

   Method : Destructor

*****************************************************************/
SymbolBoxes :: ~SymbolBoxes(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : destructor");
	#endif
}

/****************************************************************

   Class : SymbolBoxes

   Method : CreateUTF8MatrixList
   
   Return : pointer to symbol matrix list

   Description : Create list of symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SymbolBoxes :: CreateUTF8MatrixList(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8MatrixList. Start");
	#endif

	PUTF8_STRINGS_MATRIX_LIST matrixList = (PUTF8_STRINGS_MATRIX_LIST)malloc(sizeof(UTF8_STRINGS_MATRIX_LIST));

	if (!matrixList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : CreateUTF8MatrixList. Can't create symbol matrixes list!");
			WriteToLog("SymbolBoxes : CreateUTF8MatrixList. Done");
		#endif

		return NULL;
	}

	matrixList -> size = 0;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8MatrixList. Symbol matrixes list created successfully!");
		WriteToLog("SymbolBoxes : CreateUTF8MatrixList. Done");
	#endif

	return matrixList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : RemoveUTF8MatrixList
   
   Parameters:
			Input:
				matrixList - pointer to symbol matrix list

   Return : pointer to symbol matrix list

   Description : Remove list of symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SymbolBoxes :: RemoveUTF8MatrixList(PUTF8_STRINGS_MATRIX_LIST matrixList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RemoveUTF8MatrixList. Start");
	#endif

	if (matrixList)
	{
		// Remove all matrixes
		for(int i = 0; i < matrixList -> size; i++)
			matrixList -> matrixes[i] = RemoveUTF8Matrix(matrixList -> matrixes[i]);
		
		// Set list size to zero
		matrixList -> size = 0;

		// Remove list structure
		free(matrixList);

		matrixList = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RemoveUTF8MatrixList. Symbol matrixes list deleted successfully!");
			WriteToLog("SymbolBoxes : RemoveUTF8MatrixList. Done");
		#endif

		return matrixList;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RemoveUTF8MatrixList. Symbol matixes list is empty!");
			WriteToLog("SymbolBoxes : RemoveUTF8MatrixList. Done");
		#endif

		return matrixList;
	}
}

/****************************************************************

   Class : SymbolBoxes

   Method : CreateUTF8Matrix
   
   Return : pointer to symbol matrix

   Description : Create symbol box

*****************************************************************/
PUTF8_STRINGS_MATRIX SymbolBoxes :: CreateUTF8Matrix(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8Matrix. Start");
	#endif

	PUTF8_STRINGS_MATRIX matrix = (PUTF8_STRINGS_MATRIX)malloc(sizeof(UTF8_STRINGS_MATRIX));

	if (!matrix)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : CreateUTF8Matrix. Can't create symbol matrix!");
			WriteToLog("SymbolBoxes : CreateUTF8Matrix. Done");
		#endif

		return NULL;
	}

	matrix -> size = 0;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8Matrix. Symbol matrix created successfully!");
		WriteToLog("SymbolBoxes : CreateUTF8Matrix. Done");
	#endif

	return matrix;
}

/****************************************************************

   Class : SymbolBoxes

   Method : RemoveUTF8Matrix
   
   Parameters:
			Input:
				matrix - pointer to symbol matrix

   Return : pointer to symbol matrix

   Description : Remove symbol box

*****************************************************************/
PUTF8_STRINGS_MATRIX SymbolBoxes :: RemoveUTF8Matrix(PUTF8_STRINGS_MATRIX matrix)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RemoveUTF8Matrix. Start");
	#endif

	if (matrix)
	{
		// Remove matrix
		for(int i = 0; i < matrix -> size; i++)
			for(int j = 0; j < matrix -> size; j++)
				matrix -> strings[i][j] = RemoveUTF8String(matrix -> strings[i][j]);
		
		// Set size to zero
		matrix -> size = 0;

		// Remove matrix structure
		free(matrix);

		matrix = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RemoveUTF8Matrix. Symbol matrix deleted successfully!");
			WriteToLog("SymbolBoxes : RemoveUTF8Matrix. Done");
		#endif

		return matrix;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RemoveUTF8Matrix. Symbol matix is empty!");
			WriteToLog("SymbolBoxes : RemoveUTF8Matrix. Done");
		#endif

		return matrix;
	}
}

/****************************************************************

   Class : SymbolBoxes

   Method : CreateUTF8String
   
   Return : pointer to UTF8 chars list

   Description : Create UTF8 chars list

*****************************************************************/
PUTF8_STRING SymbolBoxes :: CreateUTF8String(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8String. Start");
	#endif

	PUTF8_STRING string = (PUTF8_STRING)malloc(sizeof(UTF8_STRING));

	if (!string)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : CreateUTF8String. Can't create symbol string!");
			WriteToLog("SymbolBoxes : CreateUTF8String. Done");
		#endif

		return NULL;
	}

	string -> length = 0;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8String. Symbol string created successfully!");
		WriteToLog("SymbolBoxes : CreateUTF8String. Done");
	#endif

	return string;
}

/****************************************************************

   Class : SymbolBoxes

   Method : RemoveUTF8String
   
   Parameters:
			Input:
				string - pointer to UTF8 chars list

   Return : pointer to UTF8 chars list

   Description : Remove UTF8 chars list

*****************************************************************/
PUTF8_STRING SymbolBoxes :: RemoveUTF8String(PUTF8_STRING string)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RemoveUTF8String. Start");
	#endif

	if (string)
	{
		// Remove all chars
		for(int i = 0; i < string -> length; i++)
			string -> chars[i] = RemoveUTF8Char(string -> chars[i]);
		
		// Set list size to zero
		string -> length = 0;

		// Remove list structure
		free(string);

		string = NULL;

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RemoveUTF8String. UTF8 chars list deleted successfully!");
			WriteToLog("SymbolBoxes : RemoveUTF8String. Done");
		#endif

		return string;
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RemoveUTF8String. UTF8 chars list is empty!");
			WriteToLog("SymbolBoxes : RemoveUTF8String. Done");
		#endif

		return string;
	}
}

/****************************************************************

   Class : SymbolBoxes

   Method : CreateUTF8Char
   
   Return : pointer to UTF8 char

   Description : Create UTF8 char

*****************************************************************/
PUTF8_CHAR SymbolBoxes :: CreateUTF8Char(void)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8Char. Start");
	#endif

	PUTF8_CHAR uChar = (PUTF8_CHAR)malloc(sizeof(UTF8_CHAR));

	if (!uChar)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : CreateUTF8Char. Can't create symbol!");
			WriteToLog("SymbolBoxes : CreateUTF8Char. Done");
		#endif

		return NULL;
	}

	uChar -> bytesCount = 0;

	for(int i = 0; i < UTF8_CODE_MAX_LENGTH; i++)
		uChar -> bytes[i] = 0;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : CreateUTF8Char. Symbol created successfully!");
		WriteToLog("SymbolBoxes : CreateUTF8Char. Done");
	#endif

	return uChar;
}

/****************************************************************

   Class : SymbolBoxes

   Method : RemoveUTF8Char
   
   Parameters:
			Input:
				uChar - pointer to UTF8 char

   Return : pointer to UTF8 char

   Description : Remove UTF8 char

*****************************************************************/
PUTF8_CHAR SymbolBoxes :: RemoveUTF8Char(PUTF8_CHAR uChar)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RemoveUTF8Char. Start");
	#endif

	// Set size to zero
	uChar -> bytesCount = 0;

	// Remove UTF8 char structure
	free(uChar);

	uChar = NULL;

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RemoveUTF8Char. Done");
	#endif

	return uChar;
}

/****************************************************************

   Class : SymbolBoxes

   Method : ReadCharsFromByteSequence
   
   Parameters:
			Input:
				seq - byte sequence
				size - length of byte sequence

   Return : pointer to UTF8 char list

   Description : Read UTF8 chars list from byte sequence

*****************************************************************/
PUTF8_STRING SymbolBoxes :: ReadUTF8CharsFromByteSequence(char * seq, int size)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Start");
	#endif

	// Check input data
	if ((seq == NULL) || (size <= 0))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Wrong input data!");
			WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Done");
		#endif

		return NULL;
	}
	
	// Create UTF8 char list
	PUTF8_STRING charList = CreateUTF8String();

	// Check list
	if (!charList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Can't create UTF8 chars string!");
			WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Done");
		#endif

		return NULL;
	}

	unsigned short byteCounter = 0;
	
	try
	{
		while(byteCounter < size)
		{
			// Is a single-byte code?
			if ((seq[byteCounter] & 0x80) == 0x00)
			{
				// Create new UTF8 char
				charList -> chars[charList -> length] = CreateUTF8Char();

				// Check creation result
				if (charList -> chars[charList -> length])
				{
					// Copy data
					charList -> chars[charList -> length] -> bytesCount = 1;
					memcpy(charList -> chars[charList -> length] -> bytes, seq + byteCounter, 1); 
					charList -> length++;
				}

				byteCounter++;
			
				continue;
			}
	 
			// Is a two-byte code?
			if ((seq[byteCounter] & 0xE0) == 0xC0)
			{
				if (size - byteCounter >= 2)
				{
					// Create new UTF8 char
					charList -> chars[charList -> length] = CreateUTF8Char();

					// Check creation result
					if (charList -> chars[charList -> length])
					{
						// Copy data
						charList -> chars[charList -> length] -> bytesCount = 2;
						memcpy(charList -> chars[charList -> length] -> bytes, seq + byteCounter, 2); 
						charList -> length++;
					}

					byteCounter += 2;

				}
				else byteCounter = size;
				
				continue;
			}
	
			// Is a three-byte code?
			if ((seq[byteCounter] & 0xF0) == 0xE0)
			{
				if (size - byteCounter >= 3)
				{
					// Create new UTF8 char
					charList -> chars[charList -> length] = CreateUTF8Char();

					// Check creation result
					if (charList -> chars[charList -> length])
					{
						// Copy data
						charList -> chars[charList -> length] -> bytesCount = 3;
						memcpy(charList -> chars[charList -> length] -> bytes, seq + byteCounter, 3); 
						charList -> length++;
					}

					byteCounter += 3;
				}
				else byteCounter = size;

				continue;
			}

			// Is a four-byte code?
			if ((seq[byteCounter] & 0xF8) == 0xF0)
			{
				if (size - byteCounter >= 4)
				{
					// Create new UTF8 char
					charList -> chars[charList -> length] = CreateUTF8Char();

					// Check creation result
					if (charList -> chars[charList -> length])
					{
						// Copy data
						charList -> chars[charList -> length] -> bytesCount = 4;
						memcpy(charList -> chars[charList -> length] -> bytes, seq + byteCounter, 4); 
						charList -> length++;
					}

					byteCounter += 4;
				}
				else byteCounter = size;

				continue;
			}

			// Is a five-byte code?
			if ((seq[byteCounter] & 0xFC) == 0xF8)
			{
				 if (size - byteCounter >= 5)
				{
					// Create new UTF8 char
					charList -> chars[charList -> length] = CreateUTF8Char();

					// Check creation result
					if (charList -> chars[charList -> length])
					{
						// Copy data
						charList -> chars[charList -> length] -> bytesCount = 5;
						memcpy(charList -> chars[charList -> length] -> bytes, seq + byteCounter, 5); 
						charList -> length++;
					}

					byteCounter += 5;
				}
				else byteCounter = size;

				continue;
			}

			// Is a six-byte code?
			if ((seq[byteCounter] & 0xFE) == 0xFC)
			{
				if (size - byteCounter >= 6)
				{
					// Create new UTF8 char
					charList -> chars[charList -> length] = CreateUTF8Char();

					// Check creation result
					if (charList -> chars[charList -> length])
					{
						// Copy data
						charList -> chars[charList -> length] -> bytesCount = 6;
						memcpy(charList -> chars[charList -> length] -> bytes, seq + byteCounter, 6); 
						charList -> length++;
					}

					byteCounter += 6;
				}
				else byteCounter = size;

				continue;
			}
    
			byteCounter = size;
		}
  }
  catch(...)
  {
	  
	  // Exception processing

	  charList = RemoveUTF8String(charList);

	  #if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Can't read byte sequence!");
		WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Done");
	  #endif

	  return charList;
  }

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Byte sequence successfully read!");
		WriteToLog("SymbolBoxes : ReadCharsFromByteSequence. Done");
	#endif

	return charList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : WriteUTF8CharsToByteSequence
   
   Parameters:
			Input:
				string - UTF8 char list

			Output:
				seq - byte sequence
				size - length of byte sequence

   Return : pointer to byte sequence

   Description : Write UTF8 chars list from byte sequence

*****************************************************************/
char * SymbolBoxes :: WriteUTF8CharsToByteSequence(PUTF8_STRING string, char * seq, int * size)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : WriteUTF8CharsToByteSequence. Start");
	#endif

	// Check input data
	if ((string == NULL) || (seq == NULL) || (size == NULL))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : WriteUTF8CharsToByteSequence. Wrong input data!");
			WriteToLog("SymbolBoxes : WriteUTF8CharsToByteSequence. Done");
		#endif

		return NULL;
	}

	try
	{
		char * pTmp = seq;
		*size = 0;

		// Copy data
		for(int i = 0; i < string -> length; i++)
		{
			memcpy(pTmp, string -> chars[i] -> bytes, string -> chars[i] -> bytesCount);
			pTmp += string -> chars[i] -> bytesCount;
			*size += string -> chars[i] -> bytesCount;
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : WriteUTF8CharsToByteSequence. Error of data processing!");
			WriteToLog("SymbolBoxes : WriteUTF8CharsToByteSequence. Done");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : WriteUTF8CharsToByteSequence. Done");
	#endif

	return seq;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GetBytesCount
   
   Parameters:
			Input:
				string - UTF8 char list

   Return : size of UTF8 string in bytes

   Description : Get size of UTF8 string in bytes

*****************************************************************/
int SymbolBoxes :: GetBytesCount(PUTF8_STRING string)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetBytesCount. Start");
	#endif

	// Check input data
	if (string == NULL)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetBytesCount. Wrong input data!");
			WriteToLog("SymbolBoxes : GetBytesCount. Done");
		#endif

		return 0;
	}

	int size = 0;

	try
	{
		// Calculate size
		for(int i = 0; i < string -> length; i++)
			size += string -> chars[i] -> bytesCount;
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetBytesCount. Error of data processing!");
			WriteToLog("SymbolBoxes : GetBytesCount. Done");
		#endif

		return 0;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetBytesCount. Done");
	#endif

	return size;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GetRandomCharList
   
   Parameters:
			Input:
				seq - byte sequence
				size - length of byte sequence
				symbolsCount - count of random symbols

   Return : pointer to UTF8 char list

   Description : Get random UTF8 chars list from byte sequence

*****************************************************************/
PUTF8_STRING SymbolBoxes :: GetRandomCharList(char * seq, int size, int symbolsCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetRandomCharList. Start");
	#endif
	
	// Read chars from byte sequence
	PUTF8_STRING srcCharList = ReadUTF8CharsFromByteSequence(seq, size);

	// Check char list
	if (srcCharList)
	{
		// Get random values
		PUTF8_STRING resCharList = GetRandomCharList(srcCharList, symbolsCount);

		// Check result
		if (resCharList)
		{
			// Remove first list
			srcCharList = RemoveUTF8String(srcCharList);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("SymbolBoxes : GetRandomCharList. Result char list created successfully!");
				WriteToLog("SymbolBoxes : GetRandomCharList. Done");
			#endif

			return resCharList;
		}
		else
		{
			// Remove first list
			srcCharList = RemoveUTF8String(srcCharList);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("SymbolBoxes : GetRandomCharList. Can't get result char list!");
				WriteToLog("SymbolBoxes : GetRandomCharList. Done");
			#endif

			return NULL;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetRandomCharList. Can't get source char list!");
			WriteToLog("SymbolBoxes : GetRandomCharList. Done");
		#endif

		return NULL;
	}
}

/****************************************************************

   Class : SymbolBoxes

   Method : GetRandomCharList
   
   Parameters:
			Input:
				charList - UTF8 char list
				symbolsCount - count of random symbols

   Return : pointer to UTF8 char list

   Description : Get random UTF8 chars list from some UTF8 chars list

*****************************************************************/
PUTF8_STRING SymbolBoxes :: GetRandomCharList(PUTF8_STRING charList, int symbolsCount)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetRandomCharList. Start");
	#endif
	
	if (!charList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetRandomCharList. Wrong input data!");
			WriteToLog("SymbolBoxes : GetRandomCharList. Done");
		#endif

		return NULL;
	}

	// Create result list
	PUTF8_STRING resCharList = CreateUTF8String();

	// Check list
	if (resCharList)
	{
		try
		{
			for(int i = 0; i < symbolsCount; i++)
			{
				int rndInd = -1;
				int rndCounter = 0;

				do
				{
					// Get random index
					rndInd = RangeRand(0, charList -> length - 1);
					rndCounter++;

				}while((UTF8CharPresentInString(resCharList, charList -> chars[rndInd])) && (rndCounter < 0xFFFFF));

				if (rndCounter < 0xFFFFF)
				{
					// Create new char
					resCharList -> chars[resCharList -> length] = CreateUTF8Char();

					// Copy data
					memcpy(resCharList -> chars[resCharList -> length], charList -> chars[rndInd], sizeof(UTF8_CHAR));

					resCharList -> length++;
				}
			}
		}
		catch(...)
		{
			resCharList = RemoveUTF8String(resCharList);

			#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
				WriteToLog("SymbolBoxes : GetRandomCharList. Data processing error!");
				WriteToLog("SymbolBoxes : GetRandomCharList. Done");
			#endif

			return resCharList;
		}
	}
	else
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetRandomCharList. Can't create result char list!");
			WriteToLog("SymbolBoxes : GetRandomCharList. Done");
		#endif

		return NULL;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetRandomCharList. Done");
	#endif

	return resCharList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GenerateSymbolBoxesOneSymbol

   Parameters :
			Input : 
				charList - list of input chars

	Return : pointer to UTF8 symbols matrixes list

	Description : Generate list of symbol boxes (one symbol per cell)

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SymbolBoxes :: GenerateSymbolBoxesOneSymbol(PUTF8_STRING charList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Start");
	#endif

	// Check input data
	if ((charList == NULL) || (charList -> length != 8))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Wrong input data!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Done");
		#endif

		return NULL;
	}

	// Preapre list of digits
	char * digBytes = "0123456789";

	PUTF8_STRING digits = ReadUTF8CharsFromByteSequence(digBytes, 10);

	if (!digits)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Can't create didgits list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Done");
		#endif

		return NULL;
	}

	// Randomly sort all lists
	RandomSortUTF8String(digits);
	RandomSortUTF8String(charList);

	// Create matrixes list
	PUTF8_STRINGS_MATRIX_LIST matrixList = CreateUTF8MatrixList();

	// Check result
	if (!matrixList)
	{
		digits = RemoveUTF8String(digits);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Can't create matrix list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesOneSymbol. Done");
		#endif

		return NULL;
	}

	try
	{
		// Preapare list of 10 matrixes
		matrixList -> size = 10;

		for (int i = 0; i < matrixList -> size; i++)
		{
			// Create UTF8 symbols matrix
			matrixList -> matrixes[i] = CreateUTF8Matrix();
			PUTF8_STRINGS_MATRIX matrix = matrixList -> matrixes[i];

			// Check matrix
			if (matrix)
			{
				// Square matrix 3x3
				matrix -> size = 3;
				matrix -> strings[1][1] = CreateUTF8String();

				// Central item with digits
				PUTF8_STRING centerStr = matrix -> strings[1][1];

				centerStr -> length = 2;
				for(int k = 0; k < centerStr -> length; k++)
					centerStr -> chars[k] = CreateUTF8Char();

				memcpy(centerStr -> chars[0], digits -> chars[i], sizeof(UTF8_CHAR));
				centerStr -> chars[1] -> bytesCount = 1;

				// Fill other items
				for(int j = 0; j < 8; j++)
				{
					PUTF8_STRING currentStr = NULL;
					
					// Prepare mirror items
					switch(j)
					{
						case 0 : {
									matrix -> strings[0][0] = CreateUTF8String();
									currentStr = matrix -> strings[0][0];
									break;
								 }

						case 1 : {
									matrix -> strings[0][1] = CreateUTF8String();
									currentStr = matrix -> strings[0][1];
									break;
								 }

						case 2 : {
									matrix -> strings[0][2] = CreateUTF8String();
									currentStr = matrix -> strings[0][2];
									break;
								 }

						case 3 : {
									matrix -> strings[1][2] = CreateUTF8String();
									currentStr = matrix -> strings[1][2];
									break;
								 }

						case 4 : {
									matrix -> strings[2][2] = CreateUTF8String();
									currentStr = matrix -> strings[2][2];
									break;
								 }

						case 5 : {
									matrix -> strings[2][1] = CreateUTF8String();
									currentStr = matrix -> strings[2][1];
									break;
								 }

						case 6 : {
									matrix -> strings[2][0] = CreateUTF8String();
									currentStr = matrix -> strings[2][0];
									break;
								 }

						case 7 : {
									matrix -> strings[1][0] = CreateUTF8String();
									currentStr = matrix -> strings[1][0];
									break;
								 }
					}

					// Fill item
					currentStr -> length = 2;
					for(int k = 0; k < currentStr -> length; k++)
						currentStr -> chars[k] = CreateUTF8Char();
					
					memcpy(currentStr -> chars[0], charList -> chars[j], sizeof(UTF8_CHAR));
					currentStr -> chars[1] -> bytesCount = 1;
				}
			}

			// Rotate char list
			RotateUTF8StringRight(charList, 1);
		}
	
	}
	catch(...)
	{
		// Error processing
		matrixList = RemoveUTF8MatrixList(matrixList);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Can't fill matrix list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Data processing error!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
		#endif

		return matrixList;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Matrix list successfully created!");
		WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
	#endif

	return matrixList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GenerateSymbolBoxesTwoSymbols

   Parameters :
			Input : 
				charList - list of input chars

	Return : pointer to UTF8 symbols matrixes list

	Description : Generate list of symbol boxes (two symbols per cell)

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SymbolBoxes :: GenerateSymbolBoxesTwoSymbols(PUTF8_STRING charList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Start");
	#endif

	// Check input data
	if ((charList == NULL) || (charList -> length != 8))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Wrong input data!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
		#endif

		return NULL;
	}

	// Preapre list of digits
	char * digBytes = "0123456789";

	PUTF8_STRING digits = ReadUTF8CharsFromByteSequence(digBytes, 10);

	if (!digits)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Can't create didgits list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
		#endif

		return NULL;
	}

	// Randomly sort all lists
	RandomSortUTF8String(digits);
	RandomSortUTF8String(charList);

	// Create matrixes list
	PUTF8_STRINGS_MATRIX_LIST matrixList = CreateUTF8MatrixList();

	// Check result
	if (!matrixList)
	{
		digits = RemoveUTF8String(digits);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Can't create matrix list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
		#endif

		return NULL;
	}
	
	try
	{
		// Preapare list of 5 matrixes
		matrixList -> size = 5;

		for (int i = 0; i < matrixList -> size; i++)
		{
			// Create UTF8 symbols matrix
			matrixList -> matrixes[i] = CreateUTF8Matrix();
			PUTF8_STRINGS_MATRIX matrix = matrixList -> matrixes[i];

			// Check matrix
			if (matrix)
			{
				// Square matrix 3x3
				matrix -> size = 3;
				matrix -> strings[1][1] = CreateUTF8String();

				// Central item with digits
				PUTF8_STRING centerStr = matrix -> strings[1][1];

				centerStr -> length = 3;
				for(int k = 0; k < centerStr -> length; k++)
					centerStr -> chars[k] = CreateUTF8Char();

				memcpy(centerStr -> chars[0], digits -> chars[i*2], sizeof(UTF8_CHAR));
				memcpy(centerStr -> chars[1], digits -> chars[i*2 + 1], sizeof(UTF8_CHAR));
				centerStr -> chars[2] -> bytesCount = 1;

				// Fill other items
				for(int j = 0; j < 4; j++)
				{
					PUTF8_STRING currentStr1 = NULL;
					PUTF8_STRING currentStr2 = NULL;

					// Prepare mirror items
					switch(j)
					{
						case 0 : {
									matrix -> strings[0][0] = CreateUTF8String();
									currentStr1 = matrix -> strings[0][0];
									matrix -> strings[2][2] = CreateUTF8String();
									currentStr2 = matrix -> strings[2][2];
									break;
								 }

						case 1 : {
									matrix -> strings[0][1] = CreateUTF8String();
									currentStr1 = matrix -> strings[0][1];
									matrix -> strings[2][1] = CreateUTF8String();
									currentStr2 = matrix -> strings[2][1];
									break;
								 }

						case 2 : {
									matrix -> strings[0][2] = CreateUTF8String();
									currentStr1 = matrix -> strings[0][2];
									matrix -> strings[2][0] = CreateUTF8String();
									currentStr2 = matrix -> strings[2][0];
									break;
								 }

						case 3 : {
									matrix -> strings[1][2] = CreateUTF8String();
									currentStr1 = matrix -> strings[1][2];
									matrix -> strings[1][0] = CreateUTF8String();
									currentStr2 = matrix -> strings[1][0];
									break;
								 }

					}

					// Fill mirror items
					currentStr1 -> length = 3;
					currentStr2 -> length = 3;
					for(int k = 0; k < currentStr1 -> length; k++)
					{
						currentStr1 -> chars[k] = CreateUTF8Char();
						currentStr2 -> chars[k] = CreateUTF8Char();
					}

					//First symbols pair
					memcpy(currentStr1 -> chars[0], charList -> chars[j*2], sizeof(UTF8_CHAR));
					memcpy(currentStr1 -> chars[1], charList -> chars[j*2 + 1], sizeof(UTF8_CHAR));
					currentStr1 -> chars[2] -> bytesCount = 1;

					//Second symbols pair (mirror)
					memcpy(currentStr2 -> chars[0], charList -> chars[j*2 + 1], sizeof(UTF8_CHAR));
					memcpy(currentStr2 -> chars[1], charList -> chars[j*2], sizeof(UTF8_CHAR));
					currentStr2 -> chars[2] -> bytesCount = 1;

				}
			}

			// Rotate char list
			RotateUTF8StringRight(charList, 2);

			UTF8_CHAR tmpChar;

			memcpy(&tmpChar, charList -> chars[0], sizeof(UTF8_CHAR));
			memcpy(charList -> chars[0], charList -> chars[1], sizeof(UTF8_CHAR));
			memcpy(charList -> chars[1], &tmpChar, sizeof(UTF8_CHAR));
		}
	
	}
	catch(...)
	{
		// Error processing
		matrixList = RemoveUTF8MatrixList(matrixList);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Can't fill matrix list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Data processing error!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
		#endif

		return matrixList;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Matrix list successfully created!");
		WriteToLog("SymbolBoxes : GenerateSymbolBoxesTwoSymbols. Done");
	#endif

	return matrixList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GenerateSymbolBoxes

   Parameters :
			Input : 
				charList - list of input chars
				symbolBoxesType - type of symbol boxes

	Return : pointer to UTF8 symbols matrixes list

	Description : Generate list of symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SymbolBoxes :: GenerateSymbolBoxes(PUTF8_STRING charList, int symbolBoxesType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Start");
	#endif

	PUTF8_STRINGS_MATRIX_LIST matrixList = NULL;
	
	switch (symbolBoxesType)
	{
		case ONE_SYMBOL_BOX_PWD :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Symbol boxes type = ONE SYMBOL BOX");
				#endif

				matrixList = GenerateSymbolBoxesOneSymbol(charList);
				break;
			}

		case TWO_SYMBOL_BOX_PWD :
			{
				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Symbol boxes type = TWO SYMBOLS BOX");
				#endif

				matrixList = GenerateSymbolBoxesTwoSymbols(charList);
				break;
			}
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Start");
	#endif

	return matrixList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GenerateSymbolBoxes

   Parameters :
			Input : 
				seq - byte sequence
				size - length of byte sequence
				symbolBoxesType - type of symbol boxes

	Return : pointer to UTF8 symbols matrixes list

	Description : Generate list of symbol boxes

*****************************************************************/
PUTF8_STRINGS_MATRIX_LIST SymbolBoxes :: GenerateSymbolBoxes(char * seq, int size, int symbolBoxesType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Start");
	#endif

	// Check input data
	if ((seq == NULL) || (size == 0))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Wrong input data!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Done");
		#endif

		return NULL;
	}
	
	PUTF8_STRING charList = NULL;

	/*switch (symbolBoxesType)
	{
		case ONE_SYMBOL_BOX_PWD:
		{
			charList = GetRandomCharList(seq, size, 4);
			break;
		}

		case TWO_SYMBOL_BOX_PWD:
		{
			charList = GetRandomCharList(seq, size, 8);
			break;
		}
	}*/

	charList = GetRandomCharList(seq, size, 8);

	if (!charList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Can't get random char list!");
			WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Done");
		#endif

		return NULL;
	}

	PUTF8_STRINGS_MATRIX_LIST matrixList = GenerateSymbolBoxes(charList, symbolBoxesType);

	charList = RemoveUTF8String(charList);

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateSymbolBoxes. Done");
	#endif

	return matrixList;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GenerateAndDrawSymbolBoxes

   Parameters :
			Input : 
				charList - list of input chars
				symbolBoxesType - type of symbol boxes

	Return : TRUE - if success

	Description : Generate and draw list of symbol boxes

*****************************************************************/
bool SymbolBoxes :: GenerateAndDrawSymbolBoxes(PUTF8_STRING charList, int symbolBoxesType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateAndDrawSymbolBoxes. Start");
	#endif
	
	PUTF8_STRINGS_MATRIX_LIST matrixList = GenerateSymbolBoxes(charList, symbolBoxesType);
	bool result = DrawSymbolBoxes(matrixList);
	matrixList = RemoveUTF8MatrixList(matrixList);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateAndDrawSymbolBoxes. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GenerateAndDrawSymbolBoxes

   Parameters :
			Input : 
				seq - byte sequence
				size - length of byte sequence
				symbolBoxesType - type of symbol boxes

	Return : TRUE - if success

	Description : Generate and draw list of symbol boxes

*****************************************************************/
bool SymbolBoxes ::  GenerateAndDrawSymbolBoxes(char * seq, int size, int symbolBoxesType)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateAndDrawSymbolBoxes. Start");
	#endif
	
	PUTF8_STRINGS_MATRIX_LIST matrixList = GenerateSymbolBoxes(seq, size, symbolBoxesType);
	bool result = DrawSymbolBoxes(matrixList);
	matrixList = RemoveUTF8MatrixList(matrixList);
	
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GenerateAndDrawSymbolBoxes. Done");
	#endif

	return result;
}

/****************************************************************

   Function : save_as_BMP

   Parameters :
			Input : 
				surface - cairo surface
				fileName = fileName;

   Description : Helper function. Save cairo surface to BMP file

*****************************************************************/
void cairo_save_as_bmp(cairo_surface_t *surface, char * fileName)
{
	if ((!surface) || (!fileName)) return;

	int w = cairo_image_surface_get_width(surface);
	int h = cairo_image_surface_get_height(surface);
	int s = cairo_image_surface_get_stride(surface);

	cairo_surface_flush (surface);
	unsigned char * img = cairo_image_surface_get_data(surface);

	unsigned char file[14] = { 'B','M', // magic
							   0,0,0,0, // size in bytes
							   0,0, // app data
							   0,0, // app data
							   40+14,0,0,0 // start of data offset
							 };

	unsigned char info[40] = { 40,0,0,0, // info hd size
							   0,0,0,0, // width
							   0,0,0,0, // heigth
							   1,0, // number color planes
							   24,0, // bits per pixel
							   0,0,0,0, // compression is none
							   0,0,0,0, // image bits size
							   0x13,0x0B,0,0, // horz resoluition in pixel / m
							   0x13,0x0B,0,0, // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
							   0,0,0,0, // #colors in pallete
							   0,0,0,0, // #important colors
							 };


	int padSize  = (4 - w % 4) % 4;
	int sizeData = w*h*3 + h*padSize;
	int sizeAll  = sizeData + sizeof(file) + sizeof(info);

	file[ 2] = (unsigned char)( sizeAll    );
	file[ 3] = (unsigned char)( sizeAll >> 8);
	file[ 4] = (unsigned char)( sizeAll >> 16);
	file[ 5] = (unsigned char)( sizeAll >> 24);

	info[ 4] = (unsigned char)( w   );
	info[ 5] = (unsigned char)( w >> 8);
	info[ 6] = (unsigned char)( w >> 16);
	info[ 7] = (unsigned char)( w >> 24);

	info[ 8] = (unsigned char)( h    );
	info[ 9] = (unsigned char)( h >> 8);
	info[10] = (unsigned char)( h >> 16);
	info[11] = (unsigned char)( h >> 24);

	info[24] = (unsigned char)( sizeData    );
	info[25] = (unsigned char)( sizeData >> 8);
	info[26] = (unsigned char)( sizeData >> 16);
	info[27] = (unsigned char)( sizeData >> 24);


	unsigned char pad[3] = {0,0,0};
		
	FILE * f;
	f = fopen(fileName, "wb");

	if (f)
	{
		fwrite(file, 1, sizeof(file), f);
		fwrite(info, 1, sizeof(info), f);

		for (int i = 0; i < h; i++)
		{
			unsigned char * pTmp = img + (h - (i + 1))*s;

			for (int j = 0; j < w; j++)
			{
				fwrite(pTmp, 1, 3, f);
				pTmp += 4;
			}

			fwrite(pad, 1, padSize, f);
		}

		fclose(f);
	}
}

/****************************************************************

   Class : SymbolBoxes

   Method : DrawSymbolBoxes

   Parameters :
			Input : 
				matrixList - symbol boxes list
	
   Return : TRUE - if success

   Description : Draw symbol boxes list

*****************************************************************/
bool SymbolBoxes :: DrawSymbolBoxes(PUTF8_STRINGS_MATRIX_LIST matrixList)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : DrawSymbolBoxes. Start");
	#endif

	// Check input data
	if (!matrixList)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : DrawSymbolBoxes. Wrong input data!");
			WriteToLog("SymbolBoxes : DrawSymbolBoxes. Done");
		#endif

		return false;
	}

	bool result = true;
	char fileName[STR_VALUE_LEN] = "";

	// Draw all matrixes
	for(int i = 0; i < matrixList -> size; i++)
	{
		GetSymbolBoxFileName(i + 1, fileName);
		result = DrawSymbolBox(matrixList -> matrixes[i], fileName) && result;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		if(result)
		{
			WriteToLog("SymbolBoxes : DrawSymbolBoxes. All success!");
		}
		else
		{
			WriteToLog("SymbolBoxes : DrawSymbolBoxes. Fail!");
		}
	#endif

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : DrawSymbolBoxes. Done");
	#endif

	return result;
}

/****************************************************************

   Class : SymbolBoxes

   Method : GetSymbolBoxFileName

   Parameters :
			Input : 
				index - symbol box index
				fileName - file name
	
   Return : symbol box file name

   Description : Get symbol box file name

*****************************************************************/
char * SymbolBoxes :: GetSymbolBoxFileName(int index, char * fileName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetSymbolBoxFileName. Start");
	#endif

	// Check file name
	if (!fileName)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetSymbolBoxFileName. Wrong input data");
			WriteToLog("SymbolBoxes : GetSymbolBoxFileName. Done");
		#endif

		return NULL;
	}
	
	//WINDOWS ONLY!!!
	LPWSTR wszPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramData, KF_FLAG_CREATE, NULL, &wszPath)))
	{
		wcstombs(fileName, wszPath, STR_VALUE_LEN);
		CoTaskMemFree(wszPath);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : GetSymbolBoxFileName. Special path retrieved!");
		#endif

		strcat(fileName, "\\");
	}

	strcat(fileName, "pwdSymBox");

	char number[16];
	itoa(index, number, 10);
	strcat(fileName, number);

	strcat(fileName, "%d.bmp");

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : GetSymbolBoxFileName. Done");
	#endif

	return fileName;
}

/****************************************************************

   Class : SymbolBoxes

   Method : DrawSymbolBox

   Parameters :
			Input : 
				matrix - symbol box
				fileName - file name
	
   Return : TRUE - if success

   Description : Draw symbol box

*****************************************************************/
bool SymbolBoxes :: DrawSymbolBox(PUTF8_STRINGS_MATRIX matrix, char * fileName)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : DrawSymbolBox. Start");
	#endif

	// Check input data
	if ((!matrix) || (matrix -> size != 3))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : DrawSymbolBox. Wrong input data!");
			WriteToLog("SymbolBoxes : DrawSymbolBox. Done");
		#endif

		return false;
	}

	// Create surface
	cairo_surface_t * surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, imageSize, imageSize);

	if (!surface)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : DrawSymbolBox. Can't create cairo surface!");
			WriteToLog("SymbolBoxes : DrawSymbolBox. Done");
		#endif

		return false;
	}

	cairo_t * cr = cairo_create(surface);
	
	if (!cr)
	{
		cairo_surface_destroy (surface);

		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : DrawSymbolBox. Can't create cairo context!");
			WriteToLog("SymbolBoxes : DrawSymbolBox. Done");
		#endif

		return false;
	}

	try
	{
		// Draw white rectangle
		cairo_rectangle(cr, 0.0, 0.0, imageSize, imageSize);
		cairo_set_source_rgb(cr, 1, 1, 1);
		cairo_fill(cr);

		// Draw big green rectangle
		cairo_set_line_width (cr, imageSize * 0.02);
		cairo_set_source_rgb(cr, 0.22, 0.52, 0.17);
		cairo_rectangle(cr, 0.0, 0.0, imageSize, imageSize);
	
		int itemSize = imageSize / 3;
		int itemShift = itemSize / 5;

		// Draw small green rectangle
		cairo_rectangle(cr, itemSize - itemShift, itemSize - itemShift, itemSize + 2*itemShift, itemSize + 2*itemShift);

		cairo_stroke_preserve(cr);
	
		// Set font settings
		cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
		cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);

		for(int i = 0; i < matrix -> size; i++)
		{
			for(int j = 0; j < matrix -> size; j++)
			{
				// Set font size
				if ((i == 1) && (j == 1))
				{
					//cairo_set_font_size (cr, itemSize / 3 + itemSize / 4 + 0.5*(itemSize / 3 + itemSize / 4));
					cairo_set_font_size (cr, itemSize);
				}
				else
				{
					//cairo_set_font_size (cr, itemSize / 3  + 0.5*(itemSize / 3));
					if (matrix -> strings[i][j] -> length == 2)
						cairo_set_font_size (cr, itemSize * 0.55);
					else
						cairo_set_font_size (cr, itemSize * 0.4);
						
				}

				char buffer[STR_VALUE_LEN] = "";
				int bufferSize = 0;

				// Calculate text coords
				cairo_text_extents_t extents;
				cairo_text_extents (cr, WriteUTF8CharsToByteSequence(matrix -> strings[i][j], buffer, &bufferSize), &extents);
				int x = (imageSize / 2) - (extents.width/2 + extents.x_bearing) + (j - 1) * (itemSize + itemSize/8);
				int y = (imageSize / 2) - (extents.height/2 + extents.y_bearing) + (i - 1) * (itemSize + itemSize/8);
			
				// Put text to image
				cairo_move_to (cr, x, y);
				cairo_show_text (cr, buffer);
			}
		}
	
		cairo_destroy (cr);

		// Save image
		cairo_save_as_bmp(surface, fileName);

		// Destroy cairo surface
		cairo_surface_destroy (surface);
	}
	catch(...)
	{
		cairo_destroy (cr);
		cairo_surface_destroy (surface);

		// Error processing
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : DrawSymbolBox. Error of image creation!");
			WriteToLog("SymbolBoxes : DrawSymbolBox. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : DrawSymbolBox. Done");
	#endif

	return true;
}


/****************************************************************

   Class : SymbolBoxes

   Method : RangeRand

   Parameters :
			Input : 
				min_val - lower bound of the range
				max_val - higher bound of the range

	Return : Random value in the range [min_val, max_val]

	Description : Random number generator in the range [min_val, max_val]

*****************************************************************/
int SymbolBoxes :: RangeRand(int min_val, int max_val)
{
	return min_val + (max_val - min_val) * rand() / RAND_MAX;
}

/****************************************************************

   Class : SymbolBoxes

   Method : RandomSortUTF8String

   Parameters :
			Input : 
				string - pointer to UTF8 string

   Return : pointer to UTF8 string

   Description : Random sort UTF8 string

*****************************************************************/
PUTF8_STRING SymbolBoxes :: RandomSortUTF8String(PUTF8_STRING string)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RandomSortUTF8String. Start");
	#endif

	if (!string)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RandomSortUTF8String. Wrong input data!");
			WriteToLog("SymbolBoxes : RandomSortUTF8String. Done");
		#endif
		
		return NULL;
	}

	UTF8_CHAR tmpChar;

	try
	{
		int swapCount = (string -> length)*((rand() % 10) + 1);

		for(int  i = 0; i < swapCount; i++)
		{
			int firstInd  = rand()  % (string -> length);
			int secondInd = rand() % (string -> length);
		
			memcpy(&tmpChar, string -> chars[firstInd], sizeof(UTF8_CHAR));
			memcpy(string -> chars[firstInd], string -> chars[secondInd], sizeof(UTF8_CHAR));
			memcpy(string -> chars[secondInd], &tmpChar, sizeof(UTF8_CHAR));
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RandomSortUTF8String. Sort error!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RandomSortUTF8String. Done");
	#endif

	return string;
}

/****************************************************************

   Class : SymbolBoxes

   Method : RotateUTF8StringRight

   Parameters :
			Input : 
				string - pointer to UTF8 string

   Return : pointer to UTF8 string

   Description : Rotate right UTF8 string

*****************************************************************/
PUTF8_STRING SymbolBoxes :: RotateUTF8StringRight(PUTF8_STRING string, int steps)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RotateUTF8StringRight. Start");
	#endif
	
	if (!string)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RotateUTF8StringRight. Wrong input data!");
			WriteToLog("SymbolBoxes : RotateUTF8StringRight. Done");
		#endif
		
		return NULL;
	}

	try
	{
		for(int k = 0; k < steps; k++)
		{
			UTF8_CHAR tmpChar;
			memcpy(&tmpChar, string -> chars[string -> length - 1], sizeof(UTF8_CHAR));

			for(int i = string -> length - 1; i > 0; i--)
				memcpy(string -> chars[i], string -> chars[i - 1], sizeof(UTF8_CHAR));

			memcpy(string -> chars[0], &tmpChar, sizeof(UTF8_CHAR));
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : RotateUTF8StringRight. Rotate error!");
		#endif
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : RotateUTF8StringRight. Start");
	#endif

	return string;
}


/****************************************************************

   Class : SymbolBoxes

   Method : RangeRand

   Parameters :
			Input : 
				charList - char list
				uChar - UTF8 char

	Return : TRUE - if char present in list

	Description : Find char in list

*****************************************************************/
bool SymbolBoxes :: UTF8CharPresentInString(PUTF8_STRING charList, PUTF8_CHAR uChar)
{
	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : UTF8CharPresetInString. Start");
	#endif

	bool present = false;

	if ((!charList) || (!uChar))
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : UTF8CharPresetInString. Wrong input data!");
			WriteToLog("SymbolBoxes : UTF8CharPresetInString. Done");
		#endif

		return present;
	}

	try
	{
		for(int i = 0; i < charList -> length; i++)
		{
			if (memcmp(charList -> chars[i], uChar, sizeof(UTF8_CHAR)) == 0)
			{
				present = true;

				#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
					WriteToLog("SymbolBoxes : UTF8CharPresetInString. Char present in list!");
				#endif

				break;
			}
		}
	}
	catch(...)
	{
		#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
			WriteToLog("SymbolBoxes : UTF8CharPresetInString. Data processing error!");
			WriteToLog("SymbolBoxes : UTF8CharPresetInString. Done");
		#endif

		return false;
	}

	#if defined(_DEBUG_LOG_ALL) || defined(_DEBUG_LOG_SCREEN_BUILDER)
		WriteToLog("SymbolBoxes : UTF8CharPresetInString. Done");
	#endif

	return present;
}


/****************************************************************

   Class : SymbolBoxes

   Method : WriteToLog

   Parameters :
			Input : 
				message - message for writting into log-file

	Return : error code

	Description : Write message to log-file

*****************************************************************/
int SymbolBoxes :: WriteToLog(char * message)
{
	if (logWriter)
		return logWriter -> WriteToLog(message);
	else
		return LOG_FILE_OPEN_ERROR;
}

