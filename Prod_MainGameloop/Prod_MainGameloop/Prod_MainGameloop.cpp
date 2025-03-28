/***************************************
Gregory Tuosto
Exercise 07 Q5
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
#include "Verify_Int_Input.h"
#include <cstdlib>

//#include <Windows.h>
// Used to check over many iterations visually and manually

int main()
{
	B64::initializeBase64Maps();

	std::string userSeedInput,
		gamestateString
		;

	int userHeightInput,
		userWidthInput
		;

	std::cout << "Please input some string for a seed (Any input is valid): ";
	std::cin >> userSeedInput;
	std::cout << std::endl;

	// unsigned long seed = CM::createSeed(userSeedInput);

	userHeightInput = VII::verifyUserInput("Please input an int value for the map's height: ", 1, 75);

	userWidthInput = VII::verifyUserInput("Please input an int value for the map's width: ", 1, 75);

	std::cout << std::endl << std::endl;

	std::vector<std::vector<int>> mapPrototype0(userHeightInput, std::vector<int>(userWidthInput, 0));
	std::vector<std::vector<int>> mapPrototype1(userHeightInput, std::vector<int>(userWidthInput, 0));

	//gamestateString = CM::createGamestate(seed, userHeightInput, userWidthInput);
	//std::cout << gamestateString;

	// Generates our game map and prints it to the console
	CM::generateGameMap(userSeedInput, userHeightInput, userWidthInput, mapPrototype0);

	/*
	int menuChoice;

	std::cout << "MENU OPTIONS" << std::endl
		<< "_______________" << std::endl
		<< "1: Iterate once" << std::endl
		<< "2: Iterate \"n\" times" << std::endl
		<< "3: Print map seed to user" << std::endl
		<< "4: Exit program" << std::endl
		;
	std::cin >> menuChoice;

	switch (menuChoice)
	{
	case(1):
		{
			
			
			break;
		}
	
	case(2):
		{
			std::cout << "something 2";
			
			break;
		}

	case(3):
		{
			std::cout << "something 3";

			break;
		}

	case(4):
		{


			break;
		}

	default:
		{
			std::cout << "Invalid menu input";
		}
	}
	*/

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
			UM::iterateMap(mapHeightIndexing, mapWidthIndexing, generationItteration, mapPrototype0, mapPrototype1);
		}

		CM::userContinueIterations(continueIterationsToDo);

		generationItteration++;
	}

	// Not sure why return 0 isn't working to exit the program, this works tho.
	if (continueIterationsToDo == 0)
		std::exit(0);

	return 0;
}