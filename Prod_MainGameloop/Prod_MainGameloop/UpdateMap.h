// UpdateMap.h

// include guard
#ifndef UPDATEMAP_H
#define UPDATEMAP_H

#include <iostream>
#include <vector>
#include "Base64Map.h"
#include "CreateMap.h"

namespace UM
{
	int getTotalNeighbors(int boardHeight, int boardWidth,
		int& cellDeadOrAlive, int& yOfCellToCheck, int& xOfCellToCheck,
		std::vector<std::vector<int>>& mapToParse);

	int valueToSetNewCell(int& currentY, int& currentX, int& height, int& width,
		std::vector<std::vector<int>>& mapToParse);

	void updateMap(int& maxHeight, int& maxWidth, std::vector<std::vector<int>>& mapToParse,
		std::vector<std::vector<int>>& outputMap);

	void printMap(int& maxHeight, int& maxWidth, std::vector<std::vector<int>>& gameMap);

	void iterateMap(int mapHeightIndexing, int mapWidthIndexing, int& generationItteration,
		std::vector<std::vector<int>>& map0, std::vector<std::vector<int>>& map1);
}

#endif