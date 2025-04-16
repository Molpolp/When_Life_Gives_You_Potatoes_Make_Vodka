/***************************************
Gregory Tuosto
Date Completed: April 14, 2025
Description: Data struct for storing map values
Version: 1.0
***************************************/

#include "MapDataStruct.h"

namespace MD
{
	MapData::MapData(ST::MyString *gamestateString)
	{
		ptrGamestateStr = gamestateString;

		mapHeight = mapWidth = 0;

		initWithSeed = false;
	}

	// Provides direction for map init based on user input.
	void MapData::initMapData()
	{
		initWithSeed = NO_SEED;
		
		static char userSeedInput[500];
		
		std::cout << "Please input some string for a seed (Any input is valid): ";

		std::cin.getline(userSeedInput, 500);

		ptrGamestateStr->newStr(userSeedInput);

		mapHeight = VI::verifyIntInput("Please input an int value for the map's height [5, 75]: ", 5, 75);
		mapWidth = VI::verifyIntInput("Please input an int value for the map's width [5, 75]: ", 5, 75);

		std::cout << std::endl << std::endl;
	}
	inputSeedValid MapData::initMapData(userChoice USER_HAS_SEED)
	{
		initWithSeed = USER_HAS_SEED;

		ptrGamestateStr->newStr(getSeedInput());

		if (validDecodedSeedInput()) return inputSeedValid::VALID_INPUT;

		else return inputSeedValid::INVALID_SEED_INPUT;
	}

	// Verifies the seed input by the user is vaild.
	bool MapData::validDecodedSeedInput()
	{
		bool validEncodedGamestate = true;

		char* copyEncodedArr = ptrGamestateStr->asStr();

		int checksumTotal = (B64::base64CharToVal[copyEncodedArr[4]] * 64) + (B64::base64CharToVal[copyEncodedArr[5]]),
			totalLength = 0, index = 0;

		while (copyEncodedArr[index] != '\0')
		{
			totalLength++;

			index++;
		}

		if (totalLength == checksumTotal)
		{
			mapHeight = (B64::base64CharToVal[copyEncodedArr[0]]) + (B64::base64CharToVal[copyEncodedArr[1]]);
			
			mapWidth = (B64::base64CharToVal[copyEncodedArr[2]]) + (B64::base64CharToVal[copyEncodedArr[3]]);

			char* newGamestateStr = new char[totalLength - 5];

			// Skipping the first 6 height (YY), width (XX), checksum (ZZ)
			int oldStrIndex = 6,
				newStrIndex = 0;

			do
			{
				newGamestateStr[newStrIndex] = copyEncodedArr[oldStrIndex];

				newStrIndex++;

			} while (copyEncodedArr[oldStrIndex++] != '\0');

			ptrGamestateStr->newStr(newGamestateStr);
		}

		else
		{
			validEncodedGamestate = false;
		}

		return validEncodedGamestate;
	}

	// Gets seed input (encodedString) from user.
	char* MapData::getSeedInput()
	{
		static bool invalidUserInput;
		char* arrayPtr = new char[512];

		invalidUserInput = true;

		while (invalidUserInput)
		{
			std::cout << "Please input your encoded map data: ";
			std::cin.getline(arrayPtr, 500);

			if (std::cin.fail())
			{
				std::cin.clear();

				std::cin.ignore(1000, '\n');

				std::cout << "Invalid input, please only enter strings less than "
					<< 500 << " characters long." << std::endl << std::endl;
			}
			else if (arrayPtr[0] == '\0')
			{
				std::cout << "Invalid input, please enter a valid map seed." << std::endl << std::endl;
			}

			else invalidUserInput = false;
		}
		return arrayPtr;
	}
}