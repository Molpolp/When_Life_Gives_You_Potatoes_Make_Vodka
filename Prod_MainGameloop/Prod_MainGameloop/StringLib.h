// StringLib.h

#ifndef STRING_LIB
#define STRING_LIB

#include <iostream>
#include <stdexcept>
#include "VerifyInput.h"

enum strLibraryLengthLimits
{
	MAX_STR_LENGTH = 1024
};

namespace ST
{
	struct MyString
	{
		MyString();		// Constructor
		~MyString();	// Destructor

		const int length();
		char* asStr();
		void newStr(char*);
		void getNewStr(const char[MAX_STR_LENGTH]);
		void append(char charToAppend);
		void insert(char charsToInsert[MAX_STR_LENGTH], int numberOfCharsToInsert, int indexToInsertChars);

	private:
		char* storedString,
			// Used to cleanup substrings that were dynamically allocated for outside use
			* subStrsToCleanup[100] = { {nullptr} };

		int strLen,
			nextSubStrIndex = 0;

		bool isStrValidLen(char arrToCheck[MAX_STR_LENGTH], int lengthToValidate);
		void setStrLen();
		void setStrLen(char*);
	};
}

#endif