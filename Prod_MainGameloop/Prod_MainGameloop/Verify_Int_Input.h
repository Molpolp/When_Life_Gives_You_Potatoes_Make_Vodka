// Verify_Int_Input.h

// Include guard
#ifndef VERIFICATION_INT_INPUT_H
#define VERIFICATION_INT_INPUT_H

#include <iostream>
#include <vector>
#include <string>

// VII stands for "Verify Integer Input"
namespace VII
{
	int verifyUserInput(int inputItteration);

	int verifyUserInput(std::string inputPrompt);

	int verifyUserInput(std::string inputPrompt, int minValue, int maxValue);
}

#endif