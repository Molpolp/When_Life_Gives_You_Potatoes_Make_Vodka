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

	std::string outputString;

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

	unsigned int createSeed(const std::string& userInput)
	{
		// Just picked a random prime number
		unsigned int seed = 907;

		for (char character : userInput)
		{
			seed = seed + character;
		}
		return seed;
	}

	std::string createGamestate(unsigned int seed, int height, int width)
	{
		int totalBoolsRequired = height * width,
			currentSeedValue
			;

		short remainder = totalBoolsRequired % 6;

		srand(seed);

		for (int index = 0; index < (totalBoolsRequired / 6); index++)
		{
			currentSeedValue = rand() % 64;

			outputString.push_back(B64::base64ValToChar[currentSeedValue]);
		}

		if (0 < remainder)
		{
			// Break character
			outputString.push_back('!');

			// This is the number of bits remaining to be read
			outputString.push_back(B64::base64ValToChar[remainder]);

			currentSeedValue = rand() % 64;

			outputString.push_back(B64::base64ValToChar[currentSeedValue]);

			lengthOfGamestateString = totalBoolsRequired / 6 + 3;
		}

		else
			lengthOfGamestateString = totalBoolsRequired / 6;

		// convert lengthOfGamestateString to base 64

		return outputString;
	}

	void initializeMapBools(const std::string& userInput, int height, int width, std::vector<std::vector<int>>& gameMap)
	{
		int currentCol = 0,
			currentRow = 0;

		unsigned int seed = createSeed(userInput);

		int* mapPtr = &gameMap[currentRow].front();

		std::string encodedString = createGamestate(seed, height, width);

		char* charPtr = &encodedString.front();

		for (;charPtr < &encodedString.back(); charPtr++)
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
					}

					mapPtr = &gameMap[currentRow].front();
				}
			}
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

	void generateGameMap(std::string userInputForSeed, int userInputHeight, int userInputWidth, std::vector<std::vector<int>>& mapToInitialize)
	{
		// std::vector<std::vector<int>> gameMap(userInputHeight, std::vector<int>(userInputWidth, 0));

		initializeMapBools(userInputForSeed, userInputHeight, userInputWidth, mapToInitialize);

		displayMap(mapToInitialize);
	}

	void userContinueIterations(unsigned short& numberOfIterations)
	{
		numberOfIterations = VII::verifyUserInput("Please input the number of times you want to iterate (0 to terminate the simulation): ", 0, 4000);
	}

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