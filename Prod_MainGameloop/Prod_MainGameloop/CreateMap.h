// CreateMap.h

#ifndef CREATEMAP_H
#define CREATEMAP_H

#include <vector>
#include <bitset>
#include "UpdateMap.h"
#include "MapDataStruct.h"
#include "StringLib.h"
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