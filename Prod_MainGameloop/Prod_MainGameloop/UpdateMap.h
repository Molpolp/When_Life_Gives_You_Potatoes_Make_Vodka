// UpdateMap.h

#ifndef UPDATEMAP_H
#define UPDATEMAP_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Base64Map.h"
#include "CreateMap.h"

#ifdef _WIN32
	#include <Windows.h>

#else
	#include <unistd.h>

#endif

namespace UM
{
	int getTotalNeighbors(int boardHeight, int boardWidth,
		char& cellDeadOrAlive, int& yOfCellToCheck, int& xOfCellToCheck,
		std::vector<std::vector<char>>& mapToParse);

	int valueToSetNewCell(int& currentY, int& currentX, int& height, int& width,
		std::vector<std::vector<char>>& mapToParse);

	void updateMap(int& maxHeight, int& maxWidth, std::vector<std::vector<char>>& mapToParse,
		std::vector<std::vector<char>>& outputMap);

	void clearScreen(bool sleepYes);

	void displayMap(std::vector<std::vector<char>>& gameMap);

	void iterateMap(int mapHeightIndexing, int mapWidthIndexing, int& generationItteration,
		std::vector<std::vector<char>>& map0, std::vector<std::vector<char>>& map1);

	void userContinueIterations(unsigned short& numberOfIterations);
}

#endif