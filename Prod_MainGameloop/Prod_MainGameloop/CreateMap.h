// CreateMap.h

// include guard
#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "VerifyInput.h"
#include "StringLib.h"
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
    extern int lengthOfGamestateString;

    extern char* outputString[];

    unsigned int createSeed(const char* userInput);

    ST::MyString* createGamestate(ST::MyString *gamestateString, unsigned int seed, int height, int width);

    ST::MyString convertMapToBase64Str(int height, std::vector<std::vector<int>>& gameMap);

    void convertBase64StrToMap(ST::MyString *gamestateString, int height, int width,
        std::vector<std::vector<int>>& gameMap);

    void displayMap(std::vector<std::vector<int>>& gameMap);

    void generateGameMap(ST::MyString *gamestateString, int userInputHeight, int userInputWidth,
        std::vector<std::vector<int>>& mapToInitialize);

    void userContinueIterations(unsigned short& numberOfIterations);

    void printValuesFromMaps(char character, int number, int range);
}

#endif