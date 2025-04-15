// StringLib.h

#ifndef STRING_LIB
#define STRING_LIB

#include <stdexcept>
#include "VerifyInput.h"


namespace ST
{
	const int MAX_STR_LENGTH = 4096;

	struct MyString
	{
		MyString();		// Constructor
		~MyString();	// Destructor

		int length();
		char* asStr();
		void newStr(char*);
		void getNewStr(const char[MAX_STR_LENGTH]);
		void append(char charToAppend);
		void insert(char charsToInsert[MAX_STR_LENGTH], int numberOfCharsToInsert, int indexToInsertChars);

	private:
		char* storedString,
			* subStrsToCleanup[100] = { {nullptr} }; // Used to cleanup substrings that were dynamically allocated for outside use

		int strLen,
			nextSubStrIndex = 0;

		bool isStrValidLen(char arrToCheck[MAX_STR_LENGTH], int lengthToValidate);
		void setStrLen();
		void setStrLen(char*);
	};
}

#endif