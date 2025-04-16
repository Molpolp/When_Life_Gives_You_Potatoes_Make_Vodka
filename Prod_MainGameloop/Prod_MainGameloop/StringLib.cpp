/***************************************
Gregory Tuosto
Date Completed: April 12, 2025
Description: This library is my very own string library!
Version: 1.0
***************************************/

#include "StringLib.h"

namespace ST
{
	MyString::MyString()
	{
		storedString = new char[0];
		strLen = 0;
	}

	MyString::~MyString()	
	{
		delete[] storedString;

		for (int index = 0; index < nextSubStrIndex - 1; index++)
		{
			delete[] subStrsToCleanup[index];
		}
	}

	int MyString::length()
	{
		return strLen;
	}

	// Outputs a copy of storedStr.
	char* MyString::asStr()
	{
		char* strCopy = new char[strLen + 1];

		int index = 0;

		do
		{
			strCopy[index] = storedString[index];

		} while (index++ < strLen);

		subStrsToCleanup[nextSubStrIndex] = strCopy;

		nextSubStrIndex++;

		return strCopy;
	}

	// NOTE: If the passed in array is dynamically allocated we do NOT account for that here.
	void MyString::newStr(char* charArr)
	{
		delete[] storedString;

		// Get our new string length and update strLen with it
		setStrLen(charArr);

		storedString = new char[strLen + 1];

		int index = 0;

		do
		{
			storedString[index] = charArr[index];

		} while (index++ < strLen);

		for (int index = 0; index < nextSubStrIndex - 1; index++)
		{
			delete[] subStrsToCleanup[index];
		}

		nextSubStrIndex = 0;

		setStrLen();
	}

	// Requests and validates input for a new string.
	void MyString::getNewStr(const char inputPrompt[MAX_STR_LENGTH])
	{
		char* inputCharArr = VI::verifyCharArrInput(inputPrompt, MAX_STR_LENGTH);

		setStrLen(inputCharArr);

		newStr(inputCharArr);
	}

	// Appends a single character to the end of storedStr.
	void MyString::append(char charToAppend)
	{
		char* newArr = new char[strLen + 5];

		int index = 0;
		for (index = 0; index <= strLen; index++)
		{
			newArr[index] = storedString[index];
		}

		for (int index = 0; index < nextSubStrIndex - 1; index++)
		{
			delete[] subStrsToCleanup[index];
		}

		delete[] storedString;

		newArr[index - 1] = charToAppend;
		newArr[index] = '\0';

		storedString = newArr;

		strLen++;
	}

	// Inserts a string into storedStr.
	void MyString::insert(char charsToInsert[MAX_STR_LENGTH], int numberOfCharsToInsert, int indexToInsertChars)
	{
		bool validStrInput = isStrValidLen(charsToInsert, numberOfCharsToInsert);

		if (validStrInput)
		{
			int newStrIndex = 0,
				oldStrIndex = 0,
				newStrLen = strLen + numberOfCharsToInsert + 1,
				endIndex = indexToInsertChars + numberOfCharsToInsert - 1;

			// Buffer of +5 to prevent unexpected behavior
			char* newStr = new char[newStrLen + 5];

			while (newStrIndex < indexToInsertChars)
			{
				newStr[newStrIndex] = storedString[oldStrIndex];

				newStrIndex++;
				oldStrIndex++;
			}

			for (int insertIteration = 0; insertIteration < numberOfCharsToInsert; insertIteration++)
			{
				newStr[newStrIndex] = charsToInsert[insertIteration];

				newStrIndex++;
			}

			while (newStrIndex < newStrLen)
			{
				newStr[newStrIndex] = storedString[oldStrIndex];

				newStrIndex++;
				oldStrIndex++;
			}

			for (int index = 0; index < nextSubStrIndex - 1; index++)
			{
				delete[] subStrsToCleanup[index];
			}

			nextSubStrIndex = 0;

			delete[] storedString;

			storedString = newStr;

			setStrLen();
		}

		else
		{
			throw std::invalid_argument("Invalid str length given when attempting "
				"MyString::insert function(Input char array too long)");
		}

	}

	// Validates string passed as an arg in the insert() method.
	bool MyString::isStrValidLen(char arrToCheck[MAX_STR_LENGTH], int lengthToValidate)
	{
		bool validStrLen = false;

		int index = 0;

		for (index = 0; (arrToCheck[index] != '\0') && (index < MAX_STR_LENGTH); index++);

		if (index == lengthToValidate) validStrLen = true;

		return validStrLen;
	}

	// Private member functions for setting strLen.
	void MyString::setStrLen()
	{
		int curIndex = -1;

		do
		{
			curIndex++;

		} while (storedString[curIndex] != '\0');

		strLen = curIndex;
	}
	void MyString::setStrLen(char* strToUse)
	{
		int curIndex = -1;

		do
		{
			curIndex++;

		} while (strToUse[curIndex] != '\0');

		strLen = curIndex;
	}
}