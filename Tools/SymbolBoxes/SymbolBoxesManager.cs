/// <summary>
///   Solution : NovaTend
///   Project : SymbolBoxes.dll
///   Module : SymbolBoxesManager.cs
///   Description :  implements the methods of class SymbolBoxesManager
/// </summary>
/// 

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
//using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;

using SystemData.ComplexDataType;
using SystemData.ComplexDataType.List;

namespace SymbolBoxes
{
       /// <summary>
    /// Symbol matrixes list manager. Designed for symbol 
    /// boxes passwords support
    /// </summary>
    public class SymbolBoxesManager
    {

        #region Constants

        // Symbol boxes types

        // One symbol box (3 x 3)
        public const int ONE_SYMBOL_BOX = 3;

        // Two symbol box (3 x 3)
        public const int TWO_SYMBOL_BOX = 2;

        #endregion
        
        #region Data structures creation

        /// <summary>
        /// Create matrix of UTF8 strings
        /// </summary>
        /// <returns>UTF-8 symbols strings matrix</returns>
        public UTF8_STRINGS_MATRIX CreateUTF8Matrix()
        {
            return new UTF8_STRINGS_MATRIX();
        }

        /// <summary>
        /// Create matrix of UTF8 strings
        /// </summary>
        /// <returns>UTF-8 symbols strings matrix</returns>
        public UTF8_STRINGS_MATRIX CreateUTF8Matrix(int size)
        {
            UTF8_STRINGS_MATRIX matrix = new UTF8_STRINGS_MATRIX();
            for (int i = 0; i < size; i++)
            {
                UTF8_STRING_LIST stringList = new UTF8_STRING_LIST();
                for (int j = 0; j < size; j++)
                    stringList.Add(new UTF8_STRING());

                matrix.Add(stringList);
            }

            return matrix;
        }

        /// <summary>
        /// Create UTF8 string
        /// </summary>
        /// <returns>UTF-8 symbols string</returns>
        public UTF8_STRING CreateUTF8String()
        {
            return new UTF8_STRING();
        }

        /// <summary>
        /// Create UTF8 string
        /// </summary>
        /// <returns>UTF-8 symbols string</returns>
        public UTF8_STRING CreateUTF8String(int length)
        {
            UTF8_STRING _string = new UTF8_STRING();
            for (int i = 0; i < length; i++)
                _string.Add(new UTF8_CHAR());

            return _string;
        }

        /// <summary>
        /// Create UTF8 char
        /// </summary>
        /// <returns>UTF-8 char</returns>
        public UTF8_CHAR CreateUTF8Char()
        {
            UTF8_CHAR _char = new UTF8_CHAR();
            _char.bytesCount = 0;
            return _char;
        }

        /// <summary>
        /// Create UTF8 char
        /// </summary>
        /// <returns>UTF-8 char</returns>
        public UTF8_CHAR CreateUTF8Char(int bytesCount)
        {
            UTF8_CHAR _char = new UTF8_CHAR();
            _char.bytesCount = bytesCount;
            _char.bytes = new byte[bytesCount];

            return _char;
        }

        /// <summary>
        /// Create zero char
        /// </summary>
        /// <returns>UTF-8 char</returns>
        public UTF8_CHAR CreateZeroChar()
        {
            UTF8_CHAR _char = new UTF8_CHAR();
            _char.bytesCount = 1;
            _char.bytes = new byte[_char.bytesCount];
            _char.bytes[0] = 0;

            return _char;
        }

        #endregion

        #region Char list

        /// <summary>
        /// Read UTF8 chars to UTF8 string structure from byte sequence
        /// </summary>
        /// <param name="seq">byte sequence</param>
        /// <returns>UTF8 string</returns>
        public UTF8_STRING ReadUTF8CharsFromByteSequence(byte[] seq)
        {
            UTF8_STRING charList = CreateUTF8String();
            
            if (seq != null)
            {
                int byteCounter = 0;

                while (byteCounter < seq.Length)
                {
                    // Is a single-byte code?
                    if ((seq[byteCounter] & 0x80) == 0x00)
                    {
                        // Create new UTF8 char
                        charList.Add(CreateUTF8Char(1));

                        // Copy data
                        Array.Copy(seq, byteCounter, charList[charList.Count - 1].bytes, 0, 1);
                        
                        byteCounter++;

                        continue;
                    }

                    // Is a two-byte code?
                    if ((seq[byteCounter] & 0xE0) == 0xC0)
                    {
                        if (seq.Length - byteCounter >= 2)
                        {
                            // Create new UTF8 char
                            charList.Add(CreateUTF8Char(2));

                            // Copy data
                            Array.Copy(seq, byteCounter, charList[charList.Count - 1].bytes, 0, 2);

                            byteCounter += 2;

                            continue;

                        }
                        else byteCounter = seq.Length;

                        continue;
                    }

                    // Is a three-byte code?
                    if ((seq[byteCounter] & 0xF0) == 0xE0)
                    {
                        if (seq.Length - byteCounter >= 3)
                        {
                            // Create new UTF8 char
                            charList.Add(CreateUTF8Char(3));

                            // Copy data
                            Array.Copy(seq, byteCounter, charList[charList.Count - 1].bytes, 0, 3);

                            byteCounter += 3;

                            continue;
                        }
                        else byteCounter = seq.Length;

                        continue;
                    }

                    // Is a four-byte code?
                    if ((seq[byteCounter] & 0xF8) == 0xF0)
                    {
                        if (seq.Length - byteCounter >= 4)
                        {
                            // Create new UTF8 char
                            charList.Add(CreateUTF8Char(4));

                            // Copy data
                            Array.Copy(seq, byteCounter, charList[charList.Count - 1].bytes, 0, 4);

                            byteCounter += 4;

                            continue;
                        }
                        else byteCounter = seq.Length;

                        continue;
                    }

                    // Is a five-byte code?
                    if ((seq[byteCounter] & 0xFC) == 0xF8)
                    {
                        if (seq.Length - byteCounter >= 5)
                        {
                            // Create new UTF8 char
                            charList.Add(CreateUTF8Char(5));

                            // Copy data
                            Array.Copy(seq, byteCounter, charList[charList.Count - 1].bytes, 0, 5);

                            byteCounter += 5;
                        }
                        else byteCounter = seq.Length;

                        continue;
                    }

                    // Is a six-byte code?
                    if ((seq[byteCounter] & 0xFE) == 0xFC)
                    {
                        if (seq.Length - byteCounter >= 6)
                        {
                            // Create new UTF8 char
                            charList.Add(CreateUTF8Char(6));

                            // Copy data
                            Array.Copy(seq, byteCounter, charList[charList.Count - 1].bytes, 0, 6);

                            byteCounter += 6;
                        }
                        else byteCounter = seq.Length;

                        continue;
                    }

                    byteCounter = seq.Length;
                }
            }
            return charList;
        }

        /// <summary>
        /// Calculate size of UTF8 string in bytes
        /// </summary>
        /// <param name="_string">UTF8 string</param>
        /// <returns>size in bytes</returns>
        public int GetBytesCount(UTF8_STRING _string)
        {
            int size = 0;

            // Calculate size
            foreach (UTF8_CHAR _char in _string)
                size += _char.bytesCount;

            return size;
        }

        /// <summary>
        /// Write UTF8 chars of UTF8 string to byte sequence
        /// </summary>
        /// <param name="_string">UTF8 string</param>
        /// <returns>byte sequence</returns>
        public byte[] WriteUTF8CharsToByteSequence(UTF8_STRING _string)
        {
            byte [] seq = new byte[GetBytesCount(_string)];

            int tmpIndex = 0;

            foreach (UTF8_CHAR _char in _string)
            {
                Array.Copy(_char.bytes, 0, seq, tmpIndex, _char.bytesCount);
                tmpIndex += _char.bytesCount;
            }

            return seq;
        }

        /// <summary>
        /// Find char in string
        /// </summary>
        /// <param name="charList">UTF8 string</param>
        /// <param name="uChar">UTF8 char</param>
        /// <returns>TRUE - if success</returns>
        public bool UTF8CharPresentInString(UTF8_STRING charList, UTF8_CHAR uChar)
        {
            bool present = false;

            foreach (UTF8_CHAR _char in charList)
            {
                if ((_char.bytesCount == uChar.bytesCount) && (_char.bytes.SequenceEqual(uChar.bytes)))
                {
                    present = true;
                    break;
                }
            }

            return present;
        }

        /// <summary>
        /// Copy UTF8 char
        /// </summary>
        /// <param name="dest">destination char</param>
        /// <param name="src">source char</param>
        public void CopyUTF8Char(ref UTF8_CHAR dest, UTF8_CHAR src)
        {
            dest.bytesCount = src.bytesCount;
            dest.bytes = new byte[dest.bytesCount];
            Array.Copy(src.bytes, dest.bytes, src.bytesCount);
        }

        /// <summary>
        /// Get random UTF8 chars list from some UTF8 chars list
        /// </summary>
        /// <param name="charList">base UTF8 char list</param>
        /// <param name="symbolsCount">count of random chars</param>
        /// <returns>UTF8 char list</returns>
        public UTF8_STRING GetRandomCharList(UTF8_STRING charList, int symbolsCount)
        {
            // Create result list
            UTF8_STRING resCharList = CreateUTF8String();

            Random rand = new Random();

            for (int i = 0; i < symbolsCount; i++)
            {
                int rndInd = -1;
                int rndCounter = 0;

                do
                {
                    // Get random index
                    rndInd = rand.Next(0, charList.Count);
                    rndCounter++;
                } while ((UTF8CharPresentInString(resCharList, charList[rndInd])) && (rndCounter < 0xFFFFF));

                if (rndCounter < 0xFFFFF)
                {
                    // Create new char
                    resCharList.Add(charList[rndInd]);
                }
            }

            return resCharList;
        }

        /// <summary>
        /// Get random UTF8 chars list from byte sequence
        /// </summary>
        /// <param name="seq">byte sequence</param>
        /// <param name="symbolsCount">count of random chars</param>
        /// <returns>UTF8 char list</returns>
        public UTF8_STRING GetRandomCharList(byte[] seq, int symbolsCount)
        {
            // Get random values
            return GetRandomCharList(ReadUTF8CharsFromByteSequence(seq), symbolsCount);
        }

        /// <summary>
        /// Randomly sort UTF8 char list
        /// </summary>
        /// <param name="_string">UTF8 char list</param>
        public void RandomSortUTF8String(UTF8_STRING _string)
        {
            Random rand = new Random();

            int swapCount = rand.Next(20);

            for(int  i = 0; i < swapCount; i++)
		    {
			    int firstInd  = rand.Next(_string.Count);
			    int secondInd = rand.Next(_string.Count);

                UTF8_CHAR tmpChar = _string[firstInd];
                _string[firstInd] = _string[secondInd];
                _string[secondInd] = tmpChar;
    	    }
        }


        /// <summary>
        /// Ratate UTF8 char list right
        /// </summary>
        /// <param name="_string">UTF8 char list</param>
        /// <param name="steps">steps count</param>
        public void RotateUTF8StringRight(UTF8_STRING _string, int steps)
        {
            for(int k = 0; k < steps; k++)
		    {
                UTF8_CHAR tmpChar = _string[_string.Count - 1];
                for (int i = _string.Count - 1; i > 0; i--)
                    _string[i] = _string[i - 1];
                _string[0] = tmpChar;
		    }
        }

        #endregion

        #region Symbol boxes


        /// <summary>
        /// Generate symbol boxes list
        /// </summary>
        /// <param name="charList">source UTF8 char list</param>
        /// <returns>symbol boxes list</returns>
        private UTF8_STRINGS_MATRIX_LIST GenerateOneSymbolsSymbolBoxesList(UTF8_STRING charList)
        {
            // Check input data
            if ((charList == null) || (charList.Count != 8))
                return null;

            UTF8_STRINGS_MATRIX_LIST matrixList = new UTF8_STRINGS_MATRIX_LIST();

            byte[] digBytes = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
            UTF8_STRING digits = ReadUTF8CharsFromByteSequence(digBytes);

            // Randomly sort all lists
            RandomSortUTF8String(digits);
            RandomSortUTF8String(charList);

            for (int i = 0; i < 10; i++)
            {
                matrixList.Add(CreateUTF8Matrix(3));

                // Central item with digits
                matrixList[i][1][1].Add(digits[i]);
                matrixList[i][1][1].Add(CreateZeroChar());

                int currentRowInd = 0;
                int currentColInd = 0;

                // Fill other items
                for (int j = 0; j < 8; j++)
                {
                    // Prepare items
                    switch (j)
                    {
                        case 0:
                            {
                                currentRowInd = 0;
                                currentColInd = 0;
                                break;
                            }

                        case 1:
                            {
                                currentRowInd = 0;
                                currentColInd = 1;
                                break;
                            }

                        case 2:
                            {
                                currentRowInd = 0;
                                currentColInd = 2;
                                break;
                            }

                        case 3:
                            {
                                currentRowInd = 1;
                                currentColInd = 2;
                                break;
                            }

                        case 4:
                            {
                                currentRowInd = 2;
                                currentColInd = 2;
                                break;
                            }

                        case 5:
                            {
                                currentRowInd = 2;
                                currentColInd = 1;
                                break;
                            }

                        case 6:
                            {
                                currentRowInd = 2;
                                currentColInd = 0;
                                break;
                            }

                        case 7:
                            {
                                currentRowInd = 1;
                                currentColInd = 0;
                                break;
                            }
                    }



                    matrixList[i][currentRowInd][currentColInd].Add(charList[j]);
                    matrixList[i][currentRowInd][currentColInd].Add(CreateZeroChar());
                }

                RotateUTF8StringRight(charList, 1);
            }

            return matrixList;
        }



        /// <summary>
        /// Generate symbol boxes list
        /// </summary>
        /// <param name="charList">source UTF8 char list</param>
        /// <returns>symbol boxes list</returns>
        private UTF8_STRINGS_MATRIX_LIST GenerateTwoSymbolsSymbolBoxesList(UTF8_STRING charList)
        {
            // Check input data
            if ((charList == null) || (charList.Count != 8))
                return null;

            UTF8_STRINGS_MATRIX_LIST matrixList = new UTF8_STRINGS_MATRIX_LIST();

            byte[] digBytes = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
            UTF8_STRING digits = ReadUTF8CharsFromByteSequence(digBytes);

            // Randomly sort all lists
            RandomSortUTF8String(digits);
            RandomSortUTF8String(charList);

            for (int i = 0; i < 5; i++)
            {
                matrixList.Add(CreateUTF8Matrix(3));

                // Central item with digits
                matrixList[i][1][1].Add(digits[i * 2]);
                matrixList[i][1][1].Add(digits[i * 2 + 1]);
                matrixList[i][1][1].Add(CreateZeroChar());

                int currentRowInd1 = 0;
                int currentColInd1 = 0;

                int currentRowInd2 = 0;
                int currentColInd2 = 0;
                
                // Fill other items
                for (int j = 0; j < 4; j++)
                {
                    // Prepare mirror items
                    switch (j)
                    {
                        case 0:
                            {
                                currentRowInd1 = 0;
                                currentColInd1 = 0;

                                currentRowInd2 = 2;
                                currentColInd2 = 2;
                                break;
                            }

                        case 1:
                            {
                                currentRowInd1 = 0;
                                currentColInd1 = 1;

                                currentRowInd2 = 2;
                                currentColInd2 = 1;
                                break;
                            }

                        case 2:
                            {
                                currentRowInd1 = 0;
                                currentColInd1 = 2;

                                currentRowInd2 = 2;
                                currentColInd2 = 0;
                                break;
                            }

                        case 3:
                            {
                                currentRowInd1 = 1;
                                currentColInd1 = 2;

                                currentRowInd2 = 1;
                                currentColInd2 = 0;
                                break;
                            }
                    }

                    matrixList[i][currentRowInd1][currentColInd1].Add(charList[j * 2]);
                    matrixList[i][currentRowInd1][currentColInd1].Add(charList[j * 2 + 1]);
                    matrixList[i][currentRowInd1][currentColInd1].Add(CreateZeroChar());

                    matrixList[i][currentRowInd2][currentColInd2].Add(charList[j * 2 + 1]);
                    matrixList[i][currentRowInd2][currentColInd2].Add(charList[j * 2]);
                    matrixList[i][currentRowInd2][currentColInd2].Add(CreateZeroChar());
                }

                // Rotate char list
                RotateUTF8StringRight(charList, 2);

                UTF8_CHAR tmpChar = charList[0];
                charList[0] = charList[1];
                charList[1] = tmpChar;
            }

            return matrixList;
        }


        /// <summary>
        /// Generate symbol boxes list from byte sequence
        /// </summary>
        /// <param name="charList">UTF8 char list</param>
        /// <param name="symbolBoxesType">Symbol boxes type</param>
        /// <returns>UTF8 symbol boxes list</returns>
        public UTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxes(UTF8_STRING charList, int symbolBoxesType)
        {
            switch (symbolBoxesType)
            {
                case ONE_SYMBOL_BOX: return GenerateOneSymbolsSymbolBoxesList(charList);
                case TWO_SYMBOL_BOX: return GenerateTwoSymbolsSymbolBoxesList(charList);
                default: return null;
            }
        }


        /// <summary>
        /// Generate symbol boxes list from byte sequence
        /// </summary>
        /// <param name="seq">byte sequence</param>
        /// <param name="symbolBoxesType">Symbol boxes type</param>
        /// <returns>UTF8 symbol boxes list</returns>
        public UTF8_STRINGS_MATRIX_LIST GenerateSymbolBoxes(byte[] seq, int symbolBoxesType)
        {
            switch (symbolBoxesType)
            {
                case ONE_SYMBOL_BOX: return GenerateSymbolBoxes(GetRandomCharList(seq, 8), symbolBoxesType);
                case TWO_SYMBOL_BOX: return GenerateSymbolBoxes(GetRandomCharList(seq, 8), symbolBoxesType);
                default: return null;
            }
        }

        /// <summary>
        /// Draw symbol box to graphical file
        /// </summary>
        /// <param name="matrix">UTF8 symbols matrix</param>
        /// <param name="fileName">file  name</param>
        /// <returns>TRUE - if success</returns>
        public bool DrawSymbolBox(UTF8_STRINGS_MATRIX matrix, int imageSize, string fileName)
        {
            if ((matrix == null) || (matrix.Count != 3))
                return false;

            Bitmap bmp = new Bitmap(imageSize, imageSize);
            Graphics graphics = Graphics.FromImage(bmp);

            // Draw green rectangle
            SolidBrush greenBrush = new SolidBrush(Color.Green);
            graphics.FillRectangle(greenBrush, new Rectangle(0, 0, imageSize, imageSize));
            greenBrush.Dispose();

            int borderWidth = (imageSize * 2) / 100;

            // Draw white rectangle
            SolidBrush whiteBrush = new SolidBrush(Color.White);
            graphics.FillRectangle(whiteBrush, new Rectangle(borderWidth, borderWidth, imageSize - 2 * borderWidth, imageSize - 2 * borderWidth));
            whiteBrush.Dispose();

            int itemSize = imageSize / 3;
            int itemShift = itemSize / 5;

            Pen greenPen;
            greenPen = new Pen(Color.Green);
            greenPen.Width = (imageSize * 3) / 100;

            // Small rectangle
            graphics.DrawRectangle(greenPen, new Rectangle(itemSize - itemShift, itemSize - itemShift, itemSize + 2 * itemShift, itemSize + 2 * itemShift));

            greenPen.Dispose();

            Font drawFont;
            SolidBrush drawBrush = new System.Drawing.SolidBrush(Color.Black);

            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    // Set font size
                    if ((i == 1) && (j == 1))
                    {
                        drawFont = new Font("Arial", (float)(itemSize * 0.7));
                    }
                    else
                    {
                        if (matrix[i][j].Count == 2)
                            drawFont = new Font("Arial", (float)(itemSize * 0.4));
                        else
                            drawFont = new Font("Arial", (float)(itemSize * 0.29));
                    }

                    //  Get string value
                    byte[] stringBytes = WriteUTF8CharsToByteSequence(matrix[i][j]);
                    string outputString = Encoding.UTF8.GetString(stringBytes);

                    // Calculate text coords
                    SizeF size = graphics.MeasureString(outputString, drawFont);
                    int x = (imageSize / 2) - ((int)size.Width / 2) + (j - 1) * (itemSize + itemSize / 8);
                    int y = (imageSize / 2) - ((int)size.Height / 2) + (i - 1) * (itemSize + itemSize / 8);

                    // Draw string
                    graphics.DrawString(outputString, drawFont, drawBrush, x, y);

                    drawFont.Dispose();
                }
            }

            drawBrush.Dispose();

            graphics.Dispose();
            bmp.Save(fileName, ImageFormat.Bmp);
            bmp.Dispose();

            return true;
        }

        /// <summary>
        /// Draw symbol boxes list to graphical files
        /// </summary>
        /// <param name="matrixList">symbol boxes list</param>
        /// <returns>TRUE - if success</returns>
        public bool DrawSymbolBoxes(UTF8_STRINGS_MATRIX_LIST matrixList, int imageSize)
        {
            bool result = true;

            // Draw all matrixes
            for (int i = 0; i < matrixList.Count; i++)
                result = result && DrawSymbolBox(matrixList[i], imageSize, "pwdSymBox" + (i + 1).ToString() + ".bmp");

            return result;
        }

        /// <summary>
        /// Generate and draw list of symbol boxes
        /// </summary>
        /// <param name="charList">list of input chars</param>
        /// <returns>TRUE - if success</returns>
        public bool GenerateAndDrawSymbolBoxes(UTF8_STRING charList, int symbolBoxesType, int imageSize)
        {
            return DrawSymbolBoxes(GenerateSymbolBoxes(charList, symbolBoxesType), imageSize);
        }


        /// <summary>
        /// Generate and draw list of symbol boxes
        /// </summary>
        /// <param name="seq">byte sequence</param>
        /// <returns>TRUE - if success</returns>
        public bool GenerateAndDrawSymbolBoxes(byte[] seq, int symbolBoxesType, int imageSize)
        {
            return DrawSymbolBoxes(GenerateSymbolBoxes(seq, symbolBoxesType), imageSize);
        }

        #endregion
    }

}
