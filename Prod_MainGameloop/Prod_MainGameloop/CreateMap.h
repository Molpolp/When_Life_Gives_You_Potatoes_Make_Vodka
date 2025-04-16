// CreateMap.h

#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "VerifyInput.h"
#include "StringLib.h"
#include "MapDataStruct.h"
#include <iostream>
#include <bitset>
#include <cstdlib>
#include <vector>

// base64Map[character] = int		// This is our dictionary for character to int
// base64Chars[int] = character		// This is our array for int to character
// B64::initializeBase64Maps();		// Call this to initialize the maps
// The library uses namespace B64
#include "Base64Map.h"

namespace CM
{
    unsigned int createSeed(const char* userInput);

    void writeEncodedDimensions(ST::MyString* encodedString, int height, int width);

    void convertMapToBase64Str(ST::MyString *encodedString,int height, int width, std::vector<std::vector<int>>& gameMap);

    void createGamestate(ST::MyString *gamestateString, unsigned int seed, int height, int width);

    void convertBase64StrToMap(MD::MapData *mapData, std::vector<std::vector<int>>& gameMap);

    void displayMap(std::vector<std::vector<int>>& gameMap);

    void generateGameMap(MD::MapData *mapData, std::vector<std::vector<int>>& mapToInitialize);

    void userContinueIterations(unsigned short& numberOfIterations);
}

#endif