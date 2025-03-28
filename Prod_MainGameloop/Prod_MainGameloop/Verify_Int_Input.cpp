/***************************************
Gregory Tuosto
Verification library for integer input
Date Completed: March 19, 2025
Description: This library ensures the user enters an integer as input.
Version: 1.0
***************************************/

#include "Verify_Int_Input.h"

namespace VII
{
	// Used in loop for verifying integers for an input list
	int verifyUserInput(int inputItteration)
	{
		static float toBeValidatedUserInput;
		static int intUserInput;
		static bool invalidUserInput;

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cout << "Input " << inputItteration + 1 << ": ";
			std::cin >> toBeValidatedUserInput;

			intUserInput = static_cast<int>(toBeValidatedUserInput);

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');

				std::cout << "Please refrain from entering non integer values.\n";
			}

			else if (toBeValidatedUserInput != intUserInput)
			{
				std::cout << "Please do not enter floats.\n";
			}

			else
			{
				invalidUserInput = false;
			}
		}

		return intUserInput;
	}

	// Used to verify integer input with variable prompt, no range restrictions
	int verifyUserInput(std::string inputPrompt)
	{
		static float toBeValidatedUserInput;
		static int intUserInput;
		static bool invalidUserInput;

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cout << inputPrompt;
			std::cin >> toBeValidatedUserInput;

			intUserInput = static_cast<int>(toBeValidatedUserInput);

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');

				std::cout << "Please refrain from entering non integer values.\n";
			}

			else if (toBeValidatedUserInput != intUserInput)
			{
				std::cout << "Please do not enter floats.\n";
			}

			else
			{
				invalidUserInput = false;
			}
		}

		return intUserInput;
	}

	// Used to verify integer input with variable prompt, with range restrictions
	int verifyUserInput(std::string inputPrompt, int minValue, int maxValue)
	{
		static float toBeValidatedUserInput;
		static int intUserInput;
		static bool invalidUserInput;

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cout << inputPrompt;
			std::cin >> toBeValidatedUserInput;

			intUserInput = static_cast<int>(toBeValidatedUserInput);

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');

				std::cout << "Please refrain from entering non integer values.\n";
			}

			else if (toBeValidatedUserInput != intUserInput)
			{
				std::cout << "Please do not enter floats.\n";
			}

			else if (intUserInput < minValue || maxValue < intUserInput)
			{
				if (intUserInput < minValue)
				{
					std::cout << "Please input a value greater than \"" << minValue - 1 << "\"" << std::endl;
				}

				else if (maxValue < intUserInput)
				{
					std::cout << "Please input a value less than \"" << maxValue + 1 << "\"" << std::endl;
				}

				else
				{
					std::cout << "IDK how this happened... error in Varify_Int_Input library in prompted function with range restrictions.\n";
				}
			}

			else
			{
				invalidUserInput = false;
			}
		}

		return intUserInput;
	}
}