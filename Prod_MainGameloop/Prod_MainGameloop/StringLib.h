// StringLib.h

#ifndef STRING_LIB
#define STRING_LIB

#include "VerifyInput.h"


namespace ST
{
	const int MAX_STR_LENGTH = 500;

	struct MyString
	{
		MyString();		// Constructor
		~MyString();	// Destructor

		int length();
		char* asStr();
		void newStr(char*);
		void getNewStr(const char[MAX_STR_LENGTH]);
		void append(const char charToAppend);

	private:
		char* storedString,
			* subStrsToCleanup[100] = { {nullptr} }; // Used to cleanup substrings that were dynamically allocated for outside use

		int strLen,
			nextSubStrIndex = 0;

		void setStrLen();
		void setStrLen(char*);
	};
}

#endif