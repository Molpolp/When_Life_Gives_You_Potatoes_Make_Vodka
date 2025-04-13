// VerifyInput.h

// Include guard
#ifndef VERIFY_INPUT_H
#define VERIFY_INPUT_H

#include <iostream>
#include <vector>
#include <string>

// VI stands for Verify Input
namespace VI
{
	int verifyIntInput(int inputItteration);

	int verifyIntInput(std::string inputPrompt);

	int verifyIntInput(std::string inputPrompt, int minValue, int maxValue);

	float verifyFloatInput(std::string inputPrompt, float minValue, float maxValue);

	char verifyCharInput(std::string inputPrompt, bool lettersOnly,
		bool choiceToReturnUpperOrLower, bool returnLower);

	char* verifyCharInput(std::string inputPrompt);

	std::string verifyStringInput(std::string inputPrompt);
}

#endif