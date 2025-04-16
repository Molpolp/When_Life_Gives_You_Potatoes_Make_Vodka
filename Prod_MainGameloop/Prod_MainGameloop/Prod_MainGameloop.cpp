/***************************************
Gregory Tuosto
Final Project
Date Completed: April 15, 2025
Description: This is a prototype for the backend of the project I'm working on for this class,
			 It's a representation of Conway's Game of Life
			 X is an alive cell
			 - is a dead cell
			 The program is not yet fully functional, but the core of it all is here,
			 and I figured it'd be good to get feedback on, especially if there is any of the core functionality I can improve.

			 The last thing I have to do to make the output seed for a user is to set the first 8 characters
			 to dimensions and a checksum, decoding functionality is already here.

			 Inputs are
			 Map seed: can be literally anything, no need to validate input as I simply want a random input from the user.
			 Map dimensions: limited to range [1, 75]
			 Continue iteration?: 1 to iterate map and 0 to exit the program
Version: 1.0
***************************************/

#include "CreateMap.h"
#include "UpdateMap.h"
#include "Base64Map.h"
#include "VerifyInput.h"
#include "StringLib.h"
#include "MapDataStruct.h"
#include <cstdlib>

void mainMenu(MD::MapData *mapData);

int main()
{
	B64::initializeBase64Maps();

	ST::MyString gamestateString;

	MD::MapData mapData(&gamestateString);

	START_OF_GAME:

	mainMenu(&mapData);

	// init game maps.
	std::vector<std::vector<int>> gameMap0(mapData.mapHeight, std::vector<int>(mapData.mapWidth, 0));
	std::vector<std::vector<int>> gameMap1(mapData.mapHeight, std::vector<int>(mapData.mapWidth, 0));

	// Initializes our game map with data and prints its first state.
	CM::generateGameMap(&mapData, gameMap0);

	unsigned short continueIterationsToDo = 0;
	CM::userContinueIterations(continueIterationsToDo);

	int mapHeightIndexing = mapData.mapHeight - 1,
		mapWidthIndexing = mapData.mapWidth - 1,
		generationItteration = 0
		;

	// Main simulation loop.
	while (continueIterationsToDo != 0)
	{
		for (unsigned short iteration = 0; iteration < continueIterationsToDo; iteration++)
		{
			UM::iterateMap(mapHeightIndexing, mapWidthIndexing, generationItteration, gameMap0, gameMap1);

			generationItteration++;
		}

		CM::userContinueIterations(continueIterationsToDo);

		generationItteration++;
	}

	int userChoiceToPrintSeed = VI::verifyIntInput(
		"Would you like the seed of this map printed to the console? (1 for yes, 0 for no): ", 0, 1);

	std::cout << std::endl;

	if (userChoiceToPrintSeed)
	{
		ST::MyString requestedSeed;
		
		CM::convertMapToBase64Str(&requestedSeed, mapData.mapHeight, mapData.mapWidth,
			(generationItteration % 2 ? gameMap1 : gameMap0));

		std::cout << requestedSeed.asStr();
	}

	std::cout << std::endl << std::endl;

	return 0;
}

void mainMenu(MD::MapData *mapData)
{
	std::cout << "\tConway's Game of Life!\n"
		<< "\t______________________\n\n"
		<< "(0) I do not have a seed and would like to generate a random gamemap.\n"
		<< "(1) I have a seed from a previous simulation I would like to use.\n"
		<< "(2) Terminate program.\n\n";

	int userInput = VI::verifyIntInput("Please enter your choice: ", 0, 2);

	switch (userInput)
	{
	case NO_SEED:
	{
		mapData->initMapData();

		break;
	}

	case USER_HAS_SEED:
	{
		if (mapData->initMapData(USER_HAS_SEED) == INVALID_SEED_INPUT)
		{
			std::cout << "Invalid seed input, please input a valid seed or initialize a random gamemap.\n\n";

			return mainMenu(mapData);
		}

		break;
	}

	case REQUESTED_EXIT:
	{
		std::exit(0);

		break;
	}

	default:
	{
		throw std::invalid_argument("Invalid input for menu somehow made it through input validation.\n\n");
	}
	}
}