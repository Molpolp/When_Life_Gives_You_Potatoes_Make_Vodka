/***************************************
Gregory Tuosto
Date Completed: March 15, 2025
Description: CreateMap library used for initializing the game map
Version: 1.0
***************************************/

#include "CreateMap.h"

namespace CM
{
	// Used in createGamestate to keep track of the string's length and will be used for the checksum
	int lengthOfGamestateString;

	char* outputString[];

	/*
	Example input string for a map using base 64 (A-Z)(a-z)(0-9)(+)(/)
	(YY)(XX)(ZZZ)(FFFFFFFFF...FF!F)
	(!RF) is included if 0 < (width * height) % 6
		R is the remainder count
		F is the base 64 char containing the remainder values
	(YY) is the encoded height of the map
	(XX) is the encoded width of the map
	(ZZZ) is a checksum for the length of the string and is the total length of the string
	*/

	unsigned int createSeed(char* userInput)
	{
		// Just picked a random prime number
		unsigned int seed = 907;

		while (*userInput != '\0')
		{
			seed = seed + *userInput;

			userInput++;
		}
		return seed;
	}

	ST::MyString* createGamestate(ST::MyString *gamestateString,unsigned int seed, int height, int width)
	{
		int totalBoolsRequired = height * width,
			currentSeedValue;

		short remainder = totalBoolsRequired % 6;

		srand(seed);

		int index = 0;
		for (index = 0; index < (totalBoolsRequired / 6); index++)
		{
			currentSeedValue = rand() % 64;

			gamestateString->append(B64::base64ValToChar[currentSeedValue]);
		}

		if (0 < remainder)
		{
			// Break character
			gamestateString->append('!');

			// This is the number of bits remaining to be read
			gamestateString->append(B64::base64ValToChar[remainder]);

			currentSeedValue = rand() % 64;

			gamestateString->append(B64::base64ValToChar[currentSeedValue]);

			lengthOfGamestateString = totalBoolsRequired / 6 + 3;
		}

		else
			lengthOfGamestateString = totalBoolsRequired / 6;

		return gamestateString;
	}

	ST::MyString convertMapToBase64Str(int height, std::vector<std::vector<int>>& gameMap)
	{
		int currentCol = 0,
			currentRow = 0,
			runningTotalToDecode= 0;

		bool encodingMap = true;

		int* mapPtr = &gameMap[currentRow].front();

		char* stringToBeEncoded[ST::MAX_STR_LENGTH] = {};

		ST::MyString encodedString;
		
		while (encodingMap)
		{
			for (int index = 0; ++index < 5;)
			{
				if (&gameMap[currentRow].back() < mapPtr)
				{
					if (currentRow == height - 1)
					{
						encodingMap = false;

						encodedString.append('!');

						break;
					}

					currentRow++;

					mapPtr = &gameMap[currentRow].front();
				}

				runningTotalToDecode += (*mapPtr == 1 ? std::pow(2, index) : 0);

				mapPtr++;
			}

			encodedString.append(B64::base64ValToChar[runningTotalToDecode]);

			runningTotalToDecode = 0;
		}

		return encodedString;
	}

	void convertBase64StrToMap(ST::MyString *gamestateString, int height, int width, std::vector<std::vector<int>>& gameMap)
	{
		int currentCol = 0,
			currentRow = 0;

		unsigned int seed = createSeed(gamestateString->asStr());

		int* mapPtr = &gameMap[currentRow].front();

		gamestateString = createGamestate(gamestateString, seed, height, width);

		char* charPtr = gamestateString->asStr();

		while ((currentRow < height) && (currentRow < width))
		{
			// Break character if less than 6 map values remain to be set
			if (*charPtr == '!')
			{
				// do something
				charPtr++;

				// Should be a value in [1, 5]
				int remainder = B64::base64CharToVal[*charPtr];

				for (int index = 0; index < remainder; index++)
				{
					mapPtr++;

					std::bitset<6> bits(B64::base64CharToVal[*charPtr]);

					*mapPtr = bits[index];
				}
				// next value will be the number of remaining map locations
				// value after will be the final char in the string and will be the encoded remainder bools

				break;
			}

			// Gets the current character's binary representation from base 64
			std::bitset<6> bits(B64::base64CharToVal[*charPtr]);

			for (int index = 0; index < 6; index++)
			{

				if (mapPtr < &gameMap[currentRow].back())
				{
					*mapPtr = bits[index];

					mapPtr++;

					currentCol++;
				}

				else
				{
					*mapPtr = bits[index];

					if (currentCol == width - 1)
					{
						currentRow++;

						currentCol = 0;

						if (currentRow == height) break;
					}

					mapPtr = &gameMap[currentRow].front();
				}
			}

			// End of loop, iterate character pointer
			charPtr++;
		}
	}

	void displayMap(std::vector<std::vector<int>>& gameMap)
	{
		for (const auto& currentRow : gameMap)
		{
			for (int currentCell : currentRow)
			{
				std::cout << (currentCell ? "X" : "-")
					<< " "
					;
			}

			std::cout << std::endl;
		}
	}

	void generateGameMap(ST::MyString *gamestateString, int userInputHeight,
		int userInputWidth, std::vector<std::vector<int>>& mapToInitialize)
	{
		convertBase64StrToMap(gamestateString, userInputHeight, userInputWidth, mapToInitialize);

		displayMap(mapToInitialize);
	}

	void userContinueIterations(unsigned short& numberOfIterations)
	{
		numberOfIterations = VI::verifyIntInput("Please input the number of times you want to"
			" iterate (0 to terminate the simulation) : ", 0, 4000);
	}

	// testing function
	void printValuesFromMaps(char character, int number, int range)
	{
		for (int itteration = number; itteration <= number + range; itteration++)
		{
			std::cout << B64::base64ValToChar[itteration]
				<< " --> "
				<< B64::base64ValToChar[character]
				<< std::endl << std::endl
				;
			character++;
		}
	}
}