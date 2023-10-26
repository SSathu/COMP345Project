//Written by Kiran Freund, ID: 40195543
#pragma once
#include <vector>
#include <string>
#include <iterator>
#include <stack>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;


class Territory
{
	private:
		string* playerOwner;
		string* territoryName;
		string* continent;
		int* xCoord;
		int* yCoord;
	public:
		Territory(string name, string cont, int x, int y);
		Territory(Territory* copy);

		std::vector<Territory*>* neighbors;
		int* numArmies;
		bool* visited;

		int getXCoord() const;
		int getYCoord() const;
		void setXCoord(int* newX);
		void setYCoord(int* newY);
		std::string getPlayer() const;
		void setPlayer(string* newName);
		std::string getName() const;
		std::string getContinent() const;
		void addNeighbor(Territory* neighbor);
		void streamInsertion();
        ~Territory();
};

class Map
{
public:
    Map();
    Map(const Map& copy);
    vector<Territory*>* territories;
    bool validate();
    bool isConnected();
    void streamInsertion();
};

class MapLoader
{
public:
    bool createMapFromFile(string& fileName, Map* map2make);
};


