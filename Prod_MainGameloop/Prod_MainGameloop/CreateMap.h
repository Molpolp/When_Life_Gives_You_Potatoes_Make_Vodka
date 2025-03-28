// CreateMap.h

// include guard
#ifndef CREATEMAP_H
#define CREATEMAP_H

#include "Verify_Int_Input.h"
#include <iostream>
#include <string>
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

    extern std::string outputString;

    unsigned int createSeed(const std::string& userInput);

    std::string createGamestate(unsigned int seed, int height, int width);

    void initializeMapBools(const std::string& userInput, int height, int width,
        std::vector<std::vector<int>>& gameMap);

    void displayMap(std::vector<std::vector<int>>& gameMap);

    void generateGameMap(std::string userInputForSeed, int userInputHeight, int userInputWidth,
        std::vector<std::vector<int>>& mapToInitialize);

    void userContinueIterations(unsigned short& numberOfIterations);

    void printValuesFromMaps(char character, int number, int range);
}

#endif