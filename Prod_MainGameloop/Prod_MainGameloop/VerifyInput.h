// VerifyInput.h

// Include guard
#ifndef VERIFY_INPUT_H
#define VERIFY_INPUT_H


#include <iostream>
#include <vector>
#include "StringLib.h"
#include "Base64Map.h"


// VI stands for Verify Input
namespace VI
{
	int verifyIntInput(int inputItteration);

	int verifyIntInput(const char inputPrompt[]);

	int verifyIntInput(const char inputPrompt[], int minValue, int maxValue);

	float verifyFloatInput(const char inputPrompt[], float minValue, float maxValue);

	char verifyCharInput(const char inputPrompt[], bool returnLower);

	char* verifyCharArrInput(const char inputPrompt[], const short arraySize);
}

#endif