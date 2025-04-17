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
	(YY)(XX)(ZZ)(FFFFFFFFF...FF!RF)
	(!RF) is included if 0 < (width * height) % 6
		R is the remainder count
		F is the base 64 char containing the remainder values
	(YY) is the encoded height of the map
	(XX) is the encoded width of the map
	(ZZ) is a checksum for the length of the string and is the total length of the string
		   is read left to right, firstLetter is (total / 64) second letter is (total - firstLetter * 64)
		   if the total is less than 64 then (firstLetter = 0) and (secondLetter = total)
	*/

	// Creates a pseudo random seed based on the user's input.
	// Do note, it is deterministic.
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

	// Creates a checksum for our encoded string.
	// Though it is very simple and can easily be exploited it's still good to have just in case.
	void createAndWriteChecksum(ST::MyString *encodedString)
	{
		char* copyToCheck = encodedString->asStr(),
			checksumChars[3] = {};

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

	// Encodes map dimensions into the first 4 characters of the encoded string (YY) and (XX).
	void writeEncodedDimensions(MD::MapData* mapData)
	{
		int heightRemainder = 0,
			widthRemainder = 0;

		if (mapData->mapHeight > 63)
		{
			heightRemainder = mapData->mapHeight % 63;

			// 63 in base 64
			mapData->seedToPrintStr->append('/');

			mapData->seedToPrintStr->append(B64::base64ValToChar[heightRemainder]);
		}

		else
		{
			mapData->seedToPrintStr->append(B64::base64ValToChar[mapData->mapHeight]);

			// 0 in base 64
			mapData->seedToPrintStr->append('A');
		}

		if (mapData->mapWidth > 63)
		{
			widthRemainder = mapData->mapWidth % 63;

			// 63 in base 64
			mapData->seedToPrintStr->append('/');

			mapData->seedToPrintStr->append(B64::base64ValToChar[widthRemainder]);
		}

		else
		{
			mapData->seedToPrintStr->append(B64::base64ValToChar[mapData->mapWidth]);

			// 0 in base 64
			mapData->seedToPrintStr->append('A');
		}

	}

	// Converts our bitmap to a string in base 64.
	void convertMapToBase64Str(MD::MapData* mapData, std::vector<std::vector<char>>& gameMap)
	{
		int bitsRead = 0,
			maxBitsToRead = mapData->mapHeight * mapData->mapWidth,
			currentRow = 0,
			runningTotalToDecode = 0;

		writeEncodedDimensions(mapData);

		bool encodingMap = true;

		char* mapPtr = &gameMap[currentRow].front();

		char* stringToBeEncoded[ST::MAX_STR_LENGTH] = {};

		while (encodingMap)
		{
			for (int index = 0; index < 6; index++)
			{

				if ((currentRow < mapData->mapHeight) && (& gameMap[currentRow].back() < mapPtr))
				{
					if (currentRow == mapData->mapHeight - 1)
					{
						encodingMap = false;

						mapData->seedToPrintStr->append('!');

						int remainder = (mapData->mapHeight * mapData->mapWidth) % 6;

						mapData->seedToPrintStr->append(B64::base64ValToChar[remainder]);

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
				mapData->seedToPrintStr->append(B64::base64ValToChar[runningTotalToDecode]);

			else throw std::out_of_range("runningTotalToDecode in convertMapToBase64String out of range.");

			runningTotalToDecode = 0;
		}

		createAndWriteChecksum(mapData->seedToPrintStr);
	}

	// Init gamestate, this creates an encoded string representing our bitmap.
	// Is used as the gamestateString init when the user does not have a saved seed.
	void createGamestate(MD::MapData* mapData, unsigned int seed)
	{
		int totalBoolsNeeded = mapData->mapHeight * mapData->mapWidth,
			currentSeedValue = 0,
			lenGamestateStr = 0;

		short remainder = totalBoolsNeeded % 6;

		srand(seed);

		int index = 0;
		for (index = 0; index < (totalBoolsNeeded / 6); index++)
		{
			currentSeedValue = rand() % 64;

			mapData->ptrGamestateStr->append(B64::base64ValToChar[currentSeedValue]);
		}

		if (0 < remainder)
		{
			// Break character
			mapData->ptrGamestateStr->append('!');

			// This is the number of bits remaining to be read
			mapData->ptrGamestateStr->append(B64::base64ValToChar[remainder]);

			currentSeedValue = rand() % 64;

			mapData->ptrGamestateStr->append(B64::base64ValToChar[currentSeedValue]);

			lenGamestateStr = totalBoolsNeeded / 6 + 3;
		}

		else
			lenGamestateStr = totalBoolsNeeded / 6;
	}

	// Init for our first gameMap using an initialized gamestateString.
	void convertBase64StrToMap(MD::MapData *mapData, std::vector<std::vector<char>>& gameMap)
	{
		int currentCol = 0,
			currentRow = 0;

		char* mapPtr = &gameMap[currentRow].front();

		char* charPtr = mapData->ptrGamestateStr->asStr();

		while ((currentRow < mapData->mapHeight) && (currentRow < mapData->mapWidth))
		{
			// Break character if less than 6 map values remain to be set
			if (*charPtr == '!')
			{
				// next value will be the number of remaining map locations
				// value after will be the final char in the string and will be the encoded remainder bools
				charPtr++;

				// Will be a value in [1, 5]
				int remainder = B64::base64CharToVal[*charPtr];

				charPtr++;

				std::bitset<6> bits(B64::base64CharToVal[*charPtr]);

				for (int index = 0; index < remainder; index++)
				{
					*mapPtr = bits[index];

					mapPtr++;
				}

				break;
			}

			// Gets the current character's binary representation from base 64
			std::bitset<6> bits(B64::base64CharToVal[*charPtr]);

			for (int index = 0; index < 6; index++)
			{

				if (mapPtr < (&gameMap[currentRow].back()))
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

	// This is the lead init function for generating a gameMap.
	void generateGameMap(MD::MapData *mapData, std::vector<std::vector<char>>& mapToInitialize)
	{

		switch (mapData->initWithSeed)
		{
		case NO_SEED:
		{
			unsigned int seed = createSeed(mapData->ptrGamestateStr->asStr());

			createGamestate(mapData, seed);

			convertBase64StrToMap(mapData, mapToInitialize);

			break;
		}

		case USER_HAS_SEED:
		{
			convertBase64StrToMap(mapData, mapToInitialize);

			break;
		}
		}

		UM::displayMap(mapData, mapToInitialize);
	}
}