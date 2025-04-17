// CreateMap.h

#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "VerifyInput.h"
#include "StringLib.h"
#include "MapDataStruct.h"
#include "UpdateMap.h"
#include <iostream>
#include <bitset>
#include <cstdlib>
#include <vector>

// base64Map[character] = int		// This is our dictionary for character to int
// base64Chars[int] = character		// This is our array for int to character
#include "Base64Map.h"

namespace CM
{
    unsigned int createSeed(const char* userInput);

    void writeEncodedDimensions(MD::MapData* mapData);

    void convertMapToBase64Str(MD::MapData* mapData, std::vector<std::vector<char>>& gameMap);

    void createGamestate(MD::MapData* mapData, unsigned int seed);

    void convertBase64StrToMap(MD::MapData *mapData, std::vector<std::vector<char>>& gameMap);

    void generateGameMap(MD::MapData *mapData, std::vector<std::vector<char>>& mapToInitialize);
}

#endif