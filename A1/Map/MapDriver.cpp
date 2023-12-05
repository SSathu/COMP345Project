//Written by Kiran Freund, ID: 40195543
//
#include "MapDriver.h"
#include "Map.h"
#include <iostream>

using namespace std;

/*int main() {
    MapDriver::testLoadMaps();
    return 0;
}*/

void MapDriver::testLoadMaps() {
	MapLoader mapDriver = MapLoader();

	string mapFile1 = "../MapFiles/Texas.map";
	string mapFile2 = "../MapFiles/Roman_Empire.map";

	Map* mapTest1 = new Map();
#pragma region Test1
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
    mapTest1->territories->clear();
    delete mapTest1;
#pragma endregion

    Map* mapTest2 = new Map();
#pragma region Test2
    bool test2 = mapDriver.createMapFromFile(mapFile2, mapTest2);
    if (test2) {
        cout << "Successful creation of a map from " << mapFile2 << endl;
    }
    else {
        cout << "Unsuccessful creation of a map from " << mapFile2 << endl;
    }
    if (mapTest2->validate()) {
        cout << "Map from " << mapFile2 << " is valid!" << endl;
    }
    else {
        cout << "Map from " << mapFile2 << " is invalid!" << endl;
    }
    mapTest2->territories->clear();
    delete mapTest2;
#pragma endregion
}
