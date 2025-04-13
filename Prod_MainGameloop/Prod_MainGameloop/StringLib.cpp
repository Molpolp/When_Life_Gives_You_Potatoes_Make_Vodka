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

	void MyString::newStr(char* charArr)
	{
		delete[] storedString;

		storedString = charArr;

		for (int index = 0; index < nextSubStrIndex - 1; index++)
		{
			delete[] subStrsToCleanup[index];
		}

		nextSubStrIndex = 0;

		setStrLen();
	}

	void MyString::getNewStr(const char inputPrompt[MAX_STR_LENGTH])
	{
		char* inputCharArr = VI::verifyCharArrInput(inputPrompt, MAX_STR_LENGTH);

		setStrLen(inputCharArr);

		newStr(inputCharArr);
	}

	void MyString::append(const char charToAppend)
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