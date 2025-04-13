/***************************************
Gregory Tuosto
Final Project
Date Completed: March 20, 2025
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
#include <cstdlib>


int main()
{
	B64::initializeBase64Maps();

	//std::string gamestateString;

	ST::MyString gamestateString;

	int userHeightInput,
		userWidthInput;

	char* userSeedInput = VI::verifyCharArrInput(
		{ "Please input some string for a seed (Any input is valid): " }, ST::MAX_STR_LENGTH);

	gamestateString.newStr(userSeedInput);

	userHeightInput = VI::verifyIntInput("Please input an int value for the map's height: ", 5, 75);
	userWidthInput = VI::verifyIntInput("Please input an int value for the map's width: ", 5, 75);

	std::cout << std::endl << std::endl;

	// init game maps
	std::vector<std::vector<int>> gameMap0(userHeightInput, std::vector<int>(userWidthInput, 0));
	std::vector<std::vector<int>> gameMap1(userHeightInput, std::vector<int>(userWidthInput, 0));

	// Generates our game map and prints it to the console
	CM::generateGameMap(&gamestateString, userHeightInput, userWidthInput, gameMap0);

	unsigned short continueIterationsToDo = 0;
	CM::userContinueIterations(continueIterationsToDo);

	int mapHeightIndexing = userHeightInput - 1,
		mapWidthIndexing = userWidthInput - 1,
		generationItteration = 0
		;

	// Loop for displaying the game map
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
		ST::MyString requestedSeed =
			CM::convertMapToBase64Str(userHeightInput, (generationItteration % 2 ? gameMap0 : gameMap1));

		std::cout << requestedSeed.asStr();
	}

	std::cout << std::endl << std::endl;

	// Not sure why return 0 isn't working to exit the program, this works tho.
	if (continueIterationsToDo == 0)
		std::exit(0);

	return 0;
}