/***************************************
Gregory Tuosto
Date Completed: March 20, 2025
Description: This library ensures valid input given specifications.
Version: 1.0
***************************************/

#include "VerifyInput.h"

namespace VI
{
	// Used in loop for verifying integers for an input list
	int verifyIntInput(int inputItteration)
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
	int verifyIntInput(std::string inputPrompt)
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
	int verifyIntInput(std::string inputPrompt, int minValue, int maxValue)
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

		// Fix for dangling newline char
		if (std::cin.peek() == 10)
			std::cin.ignore(1);

		return intUserInput;
	}

	// Used to verify numeric input with variable prompt, with range restrictions
	float verifyFloatInput(std::string inputPrompt, float minValue, float maxValue)
	{
		static float userInput;
		static bool invalidUserInput;

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cout << inputPrompt;
			std::cin >> userInput;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');

				std::cout << "Please refrain from entering non numarical values.\n";
			}

			else if (userInput < minValue || maxValue < userInput)
			{
				if (userInput < minValue)
				{
					std::cout << "Please input a value greater than or equal to \"" << minValue << "\"" << std::endl;
				}

				else if (maxValue < userInput)
				{
					std::cout << "Please input a value less than or equal to \"" << maxValue << "\"" << std::endl;
				}

				else
				{
					std::cout << "IDK how this happened... error in \"Verify_Input\" library, in prompted float function with range restrictions.\n";
				}
			}
			else
			{
				invalidUserInput = false;
			}
		}
		return userInput;
	}

	// LettersOnly to be implimented
	// Fix bools, they don't like being passed in tbh
	char verifyCharInput(std::string inputPrompt, bool returnLower = true)
	{
		static bool invalidUserInput;
		static char userInput;

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cin.get(userInput);

			if (std::cin.fail())
			{
				std::cin.clear();

				std::cin.ignore(1000, '\n');

				std::cout << "Invalid input, something entered caused cin.get to fail." << std::endl;
			}

			else if (tolower(userInput) < 'a' || 'z' < tolower(userInput))
			{
				std::cin.clear();

				std::cin.ignore(1000, '\n');

				std::cout << "Invalid input, characters only please." << std::endl;
			}

			else
			{
				invalidUserInput = false;
			}
		}

		if (returnLower)
			return tolower(userInput);

		else
			return toupper(userInput);
	}

	// Used to create a string aka character array
	char* verifyCharArrInput(std::string inputPrompt, const short arraySize)
	{
		static bool invalidUserInput;
		char* arrayPtr = new char[arraySize + 1];

		invalidUserInput = true;

		// If arraySize is 0 we just return the pointer
		if (!arraySize) return arrayPtr;

		while (invalidUserInput)
		{
			startLoop:

			std::cout << inputPrompt;
			std::cin.getline(arrayPtr, arraySize);

			if (std::cin.fail())
			{
				std::cin.clear();

				std::cin.ignore(1000, '\n');

				std::cout << "Invalid input, please only enter strings less than " << arraySize << " characters long." << std::endl;

				goto startLoop;
			}

			for (int index = 0; index < arraySize; index++)
			{
				if (arrayPtr[index] == '\0')
				{
					invalidUserInput = false;

					break;
				}

				if ((arrayPtr[index] != ' ') && (tolower(arrayPtr[index]) < 'a' || 'z' < tolower(arrayPtr[index])))
				{
					std::cin.clear();

					std::cin.ignore(1000, '\n');

					std::cout << "Invalid input, characters only please." << std::endl;

					break;
				}
			}
		}
		return arrayPtr;
	}

	// Assuming letters only currently for simplicity
	std::string verifyStringInput(std::string inputPrompt)
	{
		static bool invalidUserInput;
		static std::string userInput;

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cout << inputPrompt;

			std::getline(std::cin, userInput);

			for (int index = 0; index < userInput.size(); index++)
			{
				if ((static_cast<int>(userInput[index]) != ' ') && (tolower(userInput[index]) < 'a') || 'z' < tolower(userInput[index]))
				{
					// Invalid input, non character ASCII value detected

					std::cout << "Invalid input, please refrain from using special characters or numbers."
						<< std::endl;

					userInput.clear();

					invalidUserInput = true;

					break;
				}

				else
				{
					invalidUserInput = false;
				}
			}
		}

		return userInput;
	}
}