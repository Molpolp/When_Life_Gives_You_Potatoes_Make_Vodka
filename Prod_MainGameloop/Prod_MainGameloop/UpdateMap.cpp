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

	// Counts the number of alive neighbors a cell has
	int getTotalNeighbors(int boardHeight, int boardWidth, int& cellDeadOrAlive, int& yOfCellToCheck, int& xOfCellToCheck,
		std::vector<std::vector<int>>& mapToParse)
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

	// Finds the future state of the current cell being evaluated
	int valueToSetNewCell(int& currentY, int& currentX, int& height, int& width,
		std::vector<std::vector<int>>& mapToParse)
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

	// Updates the second input array based on the cells from the first
	void updateMap(int& maxHeight, int& maxWidth, std::vector<std::vector<int>>& mapToParse,
		std::vector<std::vector<int>>& outputMap)
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

	// Used to print out the current array
	void printMap(int& maxHeight, int& maxWidth, std::vector<std::vector<int>>& gameMap)
	{
		ST::MyString* mapToPrint[75] = { {nullptr} };

		for (int currentY = 0; currentY <= maxHeight; currentY++)
		{
			mapToPrint[currentY]->append('\n');

			for (int currentX = 0; currentX <= maxWidth; currentX++)
			{
				mapToPrint[currentY]->append(gameMap[currentY][currentX]);
				mapToPrint[currentY]->append(' ');
			}
		}

		for (int index = 0; index < maxHeight; index++)
		{
			std::cout << mapToPrint[index]->asStr();
		}

		/*
		for (int currentY = 0; currentY <= maxHeight; currentY++)
		{
			std::cout << "\n";

			for (int currentX = 0; currentX <= maxWidth; currentX++)
			{
				std::cout << gameMap[currentY][currentX] << " ";
			}
		}
		*/
	}

	void clearScreen()
	{
		if (SLEEP_AVAIL == "TRUE") Sleep(1000);
		system(CLEAR);
	}

	// Used to iterate the given map state and display it
	void iterateMap(int mapHeightIndexing, int mapWidthIndexing, int& generationItteration,
		std::vector<std::vector<int>>& map0, std::vector<std::vector<int>>& map1)
	{
		clearScreen();

		if (generationItteration % 2 == 0)
		{
			UM::updateMap(mapHeightIndexing, mapWidthIndexing, map0, map1);

			std::cout << std::endl;

			CM::displayMap(map1);
		}

		else
		{
			UM::updateMap(mapHeightIndexing, mapWidthIndexing, map1, map0);

			std::cout << std::endl;

			CM::displayMap(map0);
		}
	}
}