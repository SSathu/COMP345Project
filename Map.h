#pragma once
#include <vector>
#include <string>
#include <iterator>
#include <stack>
#include <map>
#include <iostream>
#include <fstream>
class Map
{
	public:
		Map();
		Map(Map* copy);
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

		vector<Territory*>* neighbors;
		int* numArmies;
		bool* visited;

		int getXCoord() const;
		int getYCoord() const;
		void setXCoord(int* newX);
		void setYCoord(int* newY);
		string getPlayer() const;
		void setPlayer(string* newName);
		string getName() const;
		string getContinent() const;
		void addNeighbor(Territory* neighbor);
		void deleteVariables();
		void streamInsertion();
};

