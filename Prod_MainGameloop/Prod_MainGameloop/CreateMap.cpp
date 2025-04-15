/***************************************
Gregory Tuosto
Date Completed: March 15, 2025
Description: CreateMap library used for initializing the game map
Version: 1.0
***************************************/

#include "CreateMap.h"

namespace CM
{
	/*
	Example input string for a map using base 64 (A-Z)(a-z)(0-9)(+)(/)
	(YY)(XX)(ZZ)(FFFFFFFFF...FF!F)
	(!RF) is included if 0 < (width * height) % 6
		R is the remainder count
		F is the base 64 char containing the remainder values
	(YY) is the encoded height of the map
	(XX) is the encoded width of the map
	(ZZ) is a checksum for the length of the string and is the total length of the string
		   is read left to right, firstLetter is (total / 64) second letter is (total - firstLetter * 64)
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

	void createAndWriteChecksum(ST::MyString *encodedString)
	{
		char* copyToCheck = encodedString->asStr(),
			checksumChars[3];

		// Counting the two characters from the checksum that will be added
		int totalLength = 2;

		while (*copyToCheck != '\0')
		{
			totalLength++;

			copyToCheck++;
		}

		if (totalLength > 63)
		{
			int multipleOf64 = totalLength / 64;

			checksumChars[0] = B64::base64ValToChar[multipleOf64];

			totalLength -= 64 * multipleOf64;

			checksumChars[1] = B64::base64ValToChar[totalLength];
		}

		else
		{
			checksumChars[0] = 'A';

			checksumChars[1] = B64::base64ValToChar[totalLength];
		}

		checksumChars[2] = '\0';

		encodedString->insert(checksumChars, 2, 4);
	}

	void writeEncodedDimensions(ST::MyString* encodedString, int height, int width)
	{
		int heightRemainder = 0,
			widthRemainder = 0;

		if (height > 63)
		{
			heightRemainder = height % 63;

			// 63 in base 64
			encodedString->append('/');

			encodedString->append(B64::base64ValToChar[heightRemainder]);
		}

		else
		{
			encodedString->append(B64::base64ValToChar[height]);

			// 0 in base 64
			encodedString->append('A');
		}

		if (width > 63)
		{
			widthRemainder = width % 63;

			// 63 in base 64
			encodedString->append('/');

			encodedString->append(B64::base64ValToChar[widthRemainder]);
		}

		else
		{
			encodedString->append(B64::base64ValToChar[width]);

			// 0 in base 64
			encodedString->append('A');
		}

	}

	void convertMapToBase64Str(ST::MyString* encodedString, int height, int width, std::vector<std::vector<int>>& gameMap)
	{
		int bitsRead = 0,
			maxBitsToRead = height * width,
			currentRow = 0,
			runningTotalToDecode = 0;

		writeEncodedDimensions(encodedString, height, width);

		bool encodingMap = true;

		int* mapPtr = &gameMap[currentRow].front();

		char* stringToBeEncoded[ST::MAX_STR_LENGTH] = {};

		while (encodingMap)
		{
			for (int index = 0; index < 6; index++)
			{

				if ((currentRow < height) && (& gameMap[currentRow].back() < mapPtr))
				{
					if (currentRow == height - 1)
					{
						encodingMap = false;

						encodedString->append('!');

						int remainder = (height * width) % 6;

						encodedString->append(B64::base64ValToChar[remainder]);

						break;
					}

					if (bitsRead == maxBitsToRead)
					{
						encodingMap = false;

						goto  terminatingLoop;
					}

					currentRow++;

					mapPtr = &gameMap[currentRow].front();
				}

				runningTotalToDecode += (*mapPtr == 1 ? std::pow(2, index) : 0);

				bitsRead++;

				if (encodingMap) mapPtr++;
			}
			
			terminatingLoop:

			if (runningTotalToDecode < 64)
				encodedString->append(B64::base64ValToChar[runningTotalToDecode]);

			else throw std::out_of_range("runningTotalToDecode in convertMapToBase64String out of range.");

			runningTotalToDecode = 0;
		}

		createAndWriteChecksum(encodedString);
	}

	void createGamestate(ST::MyString *gamestateString, unsigned int seed, int height, int width)
	{
		int totalBoolsRequired = height * width,
			currentSeedValue = 0,
			lengthOfGamestateString = 0;

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
	}

	void convertBase64StrToMap(MD::MapData *mapData, std::vector<std::vector<int>>& gameMap)
	{
		int currentCol = 0,
			currentRow = 0;

		int* mapPtr = &gameMap[currentRow].front();

		char* charPtr = mapData->ptrGamestateStr->asStr();

		while ((currentRow < mapData->mapHeight) && (currentRow < mapData->mapWidth))
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

					if (currentCol == mapData->mapWidth - 1)
					{
						currentRow++;

						currentCol = 0;

						if (currentRow == mapData->mapHeight) break;
					}

					mapPtr = &gameMap[currentRow].front();
				}
			}

			// End of loop, iterate character pointer
			charPtr++;
		}
	}

	// TODO make this print better
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

	void generateGameMap(MD::MapData *mapData, std::vector<std::vector<int>>& mapToInitialize)
	{

		switch (mapData->initWithSeed)
		{
		case NO_SEED:
		{
			unsigned int seed = createSeed(mapData->ptrGamestateStr->asStr());

			createGamestate(mapData->ptrGamestateStr, seed, mapData->mapHeight, mapData->mapWidth);

			convertBase64StrToMap(mapData, mapToInitialize);

			break;
		}

		case USER_HAS_SEED:
		{
			convertBase64StrToMap(mapData, mapToInitialize);

			break;
		}
		}

		displayMap(mapToInitialize);
	}

	void userContinueIterations(unsigned short& numberOfIterations)
	{
		numberOfIterations = VI::verifyIntInput("Please input the number of times you want to"
			" iterate (0 to terminate the simulation): ", 0, 4000);
	}

}