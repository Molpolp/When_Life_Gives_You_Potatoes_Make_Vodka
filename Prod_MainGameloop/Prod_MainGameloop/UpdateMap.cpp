/***************************************
Gregory Tuosto
Date Completed: March 15, 2025
Description: UpdateMap library used to iterate the game map
Version: 1.0
***************************************/

#include "UpdateMap.h"

namespace UM
{
	static const int ALIVE_CELL = 1,
		DEAD_CELL = 0
		;

	// Counts the number of alive neighbors a cell has.
	int getTotalNeighbors(int boardHeight, int boardWidth, char& cellDeadOrAlive, int& yOfCellToCheck, int& xOfCellToCheck,
		std::vector<std::vector<char>>& mapToParse)
	{
		int totalNeighbors = 0,
			lowerBoundY = -1,
			upperBoundY = 1,
			lowerBoundX = -1,
			upperBoundX = 1
			;

		if (yOfCellToCheck == 0)
		{
			lowerBoundY = 0;
		}

		else if (yOfCellToCheck == boardHeight - 1)
		{
			upperBoundY = 0;
		}

		if (xOfCellToCheck == 0)
		{
			lowerBoundX = 0;
		}

		else if (xOfCellToCheck == boardWidth - 1)
		{
			upperBoundX = 0;
		}

		for (int yOffset = lowerBoundY; yOffset <= upperBoundY; yOffset++)
		{
			for (int xOffset = lowerBoundX; xOffset <= upperBoundX; xOffset++)
			{
				int yOfNeighborToCheck = yOfCellToCheck + yOffset;
				int xOfNeighborToCheck = xOfCellToCheck + xOffset;

				if (mapToParse[yOfNeighborToCheck][xOfNeighborToCheck] == ALIVE_CELL)
					totalNeighbors++;
			}
		}

		// Because it counts the cell itself in the evaluation
		if (cellDeadOrAlive == ALIVE_CELL)
		{
			totalNeighbors--;
		}

		return totalNeighbors;
	}

	// Parses the cell who's coordinates were passed as an argument.
	int valueToSetNewCell(int& currentY, int& currentX, int& height, int& width,
		std::vector<std::vector<char>>& mapToParse)
	{
		int totalNeighbors = 0;

		totalNeighbors = getTotalNeighbors(height + 1, width + 1, mapToParse[currentY][currentX],
			currentY, currentX, mapToParse);

		// Cell is dead regardless of initial state
		if (totalNeighbors < 2 || 3 < totalNeighbors)
			return DEAD_CELL;

		// Cell state remains the same
		else if (totalNeighbors == 2)
			return mapToParse[currentY][currentX];

		// Cell is set to alive
		else if (totalNeighbors == 3)
			return ALIVE_CELL;

		// Error case
		return 0;

	}

	// Updates outputMap with the parsed cells from mapToParse.
	void updateMap(int& maxHeight, int& maxWidth, std::vector<std::vector<char>>& mapToParse,
		std::vector<std::vector<char>>& outputMap)
	{

		for (int currentY = 0; currentY <= maxHeight; currentY++)
		{
			for (int currentX = 0; currentX <= maxWidth; currentX++)
			{
				outputMap[currentY][currentX] = valueToSetNewCell(currentY, currentX,
					maxHeight, maxWidth, mapToParse);
			}
		}
	}

	// Sleeps in between map iterations.
	void clearScreen(bool sleepYes)
	{
		#ifdef _WIN32
			if (sleepYes) Sleep(1000);
			system("cls");

		#else
			if (sleepYes) usleep(1000000);
			system("clear");

		#endif
	}

	// Init display of gameMap.
	void displayMap(std::vector<std::vector<char>>& gameMap)
	{
		ST::MyString* mapToPrint;

		mapToPrint = new ST::MyString[gameMap.size()];

		int currentY = 0;

		for (const auto& currentRow : gameMap)
		{
			mapToPrint[currentY].append('\n');

			for (int currentCell : currentRow)
			{
				mapToPrint[currentY].append(currentCell ? 'X' : '-');
				mapToPrint[currentY].append(' ');
			}

			currentY++;
		}

		for (int index = 0; index < gameMap.size(); index++)
		{
			std::cout << mapToPrint[index].asStr();
		}

		std::cout << std::endl << std::endl;
	}

	// Used to iterate the given map state and display it.
	void iterateMap(int mapHeightIndexing, int mapWidthIndexing, int& generationItteration,
		std::vector<std::vector<char>>& map0, std::vector<std::vector<char>>& map1)
	{
		clearScreen(true);

		if (generationItteration % 2 == 0)
		{
			UM::updateMap(mapHeightIndexing, mapWidthIndexing, map0, map1);

			std::cout << std::endl;

			UM::displayMap(map1);
		}

		else
		{
			UM::updateMap(mapHeightIndexing, mapWidthIndexing, map1, map0);

			std::cout << std::endl;

			UM::displayMap(map0);
		}
	}

	// Used in our simulation loop to request a number of generations to iterate through.
	void userContinueIterations(unsigned short& numberOfIterations)
	{
		numberOfIterations = VI::verifyIntInput("Please input the number of times you want to"
			" iterate (0 to terminate the simulation): ", 0, 4000);
	}
}