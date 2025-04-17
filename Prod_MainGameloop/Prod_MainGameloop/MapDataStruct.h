// MapDataStruct.h

#ifndef MAP_DATA_STRUCT_H
#define MAP_DATA_STRUCT_H

#include "StringLib.h"
#include "Base64Map.h"

enum userChoice
{
	NO_SEED = 0,
	USER_HAS_SEED = 1,
	REQUESTED_EXIT = 2
};

enum inputSeedValid
{
	INVALID_SEED_INPUT = 0,
	VALID_INPUT = 1
};

namespace MD
{
	struct MapData
	{
		MapData(ST::MyString* gamestateString);
		void initMapData();
		inputSeedValid initMapData(userChoice USER_HAS_SEED);

		int mapHeight,
			mapWidth;

		bool initWithSeed;

		ST::MyString* ptrGamestateStr;
		ST::MyString* seedToPrintStr;

	private:
		bool validDecodedSeedInput();
		char* getSeedInput();
	};
}

#endif