// Comp345Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "mapdriver.h"
#include "Map.h"
#include <iostream>

using namespace std;

void MapDriver::testLoadMaps() {
	MapLoader mapDriver = MapLoader();

	string mapFile1 = "../MapFiles/Texas";
	string mapFile2 = "../MapFiles/Skyland";
	string mapFile3 = "../MapFiles/Roman_Empire";

	Map* mapTest1;
	bool test1 = mapDriver.createMapFromFile(mapFile1, mapTest1);
	if (test1) {
		cout << "Successful creation of a map from " << mapFile1 << endl;
	}
	else {
		cout << "Unsuccessful creation of a map from " << mapFile1 << endl;
	}
	if (mapTest1->validate()) {
		cout << "Map from " << mapFile1 << " is valid!" << endl;
	}
	else {
		cout << "Map from " << mapFile1 << " is invalid!" << endl;
	}
}
