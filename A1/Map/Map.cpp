//Written by Kiran Freund, ID: 40195543

#include <algorithm>
#include "Map.h"

using namespace std;

//Territory Constructors
Territory::Territory(string name, string cont, int x, int y) {
	playerOwner = &name;
	continent = &cont;
	int xx = x;
	xCoord = &xx;
	int yy = y;
	yCoord = &yy;
	bool visit = false;
	neighbors = new vector<Territory*>;
}
Territory::Territory(Territory* copy) {
	playerOwner = new std::string(copy->getName());
	continent = new std::string(copy->getContinent());
	int xx = copy->getXCoord();
	xCoord = &xx;
	int yy = copy->getYCoord();
	yCoord = &yy;
	bool visit = false;
	neighbors = copy->neighbors;
}

//Territory get and set methods
int Territory::getXCoord() const {
	return *xCoord;
}
int Territory::getYCoord() const {
	return *yCoord;
}
void Territory::setXCoord(int* newX) {
	delete xCoord;
	xCoord = newX;
}
void Territory::setYCoord(int* newY) {
	delete yCoord;
	yCoord = newY;
}
string Territory::getPlayer() const {
	return *playerOwner;
}
void Territory::setPlayer(string* newName) {
	delete playerOwner;
	playerOwner = newName;
}
string Territory::getName() const {
	return *territoryName;
}
string Territory::getContinent() const {
	return *continent;
}

//stream insertion operator for Territory
void Territory::streamInsertion() {
	cout << "Territory name: " << *territoryName << "; Position: " << *xCoord << ", " << *yCoord
		<< "; Continent " << *continent << ". Owned by: " << *playerOwner << ", with " << *numArmies 
		<< " armies." << endl;
}

//connect 2 territories
void Territory::addNeighbor(Territory* neighbor) {
	neighbors->push_back(neighbor);
}

void Territory::deleteVariables() {
	//deallocates all variables to not have memory leaks or dangling pointers
	delete playerOwner;
	playerOwner = nullptr;
	delete territoryName;
	territoryName = nullptr;
	delete continent;
	continent = nullptr;
	delete xCoord;
	xCoord = nullptr;
	delete yCoord;
	yCoord = nullptr;
	delete numArmies;
	numArmies = nullptr;
	delete neighbors;
	neighbors = nullptr;
}

//Map constructors
Map::Map() {
	territories = new vector<Territory*>;
}
Map::Map(Map* copy) {
	territories = copy->territories;
}

//stream insertion operator for Map
void Map::streamInsertion() {
	cout << "Territories: [" << endl;
	for (Territory* var : *territories)
	{
		var->streamInsertion();
	}
	cout << "]" << endl;
}

//Map validate()
bool Map::validate() {
	//Check #1, making sure all territories are connected
	if (!isConnected())
		return false;

	//Check #2, making sure all continents are connected
	map<string, Map> continentGraphs;
	// Sort the original graph and sort nodes into new graphs.
	for (Territory* node : *territories) {
		// Check if a graph for this continent already exists.
		if (continentGraphs.find(node->getContinent()) == continentGraphs.end()) {
			// Create a new graph for this continent.
			continentGraphs[node->getContinent()] = Map();
		}

		// Add the node to the corresponding graph.
		continentGraphs[node->getContinent()].territories->push_back(node);
	}
	for (auto& var : continentGraphs)
	{
		Map& map = var.second;
		if (!map.isConnected())
			return false;
	}

	//Check #3, making sure all territories are part of only 1 continent
	for (Territory* var : *territories)
	{
		if (var->getContinent().empty())
			return false;
	}
	return true;
}
bool Map::isConnected() {
	if (territories->empty()) {
		return true;
	}

	stack<Territory*> stack;
	stack.push((*territories)[0]);

	while (!stack.empty()) {
		Territory* node = stack.top();
		stack.pop();

		if (!node->visited) {
			*node->visited = true;
			for (Territory* neighbor : *node->neighbors) {
				stack.push(neighbor);
			}
		}
	}

	for (Territory* node : *territories) {
		if (!node->visited) {
			return false;
		}
	}
	return true;
}


//MapLoader creating a map from a filename
bool MapLoader::createMapFromFile(string& fileName, Map* map2make) {
	ifstream inputFileStream;
	inputFileStream.open(fileName);

	//Reject if file couldnt open
	if (!inputFileStream.is_open()) {
		cout << "Error: Could not open file." << endl;
		return false; // Return an error code
	}
	//If the first line of the file isnt "[Map]", reject file
	string nextLine;
	if (!getline(inputFileStream, nextLine) || nextLine != "[Map]") {
		inputFileStream.close();
		return false;
	}

	//Skip all other lines until we reach "[Continents]"
	//If this line isn't reached, reject file
	while (nextLine != "[Continents]") {
		if (!getline(inputFileStream, nextLine)) {
			inputFileStream.close();
			return false;
		}
	}

	//Read Continents until we reach an empty line (or i guess the "[Territories]" line)
	//link all continents to a map<string, int>, with continent name being identifier and territory amount being data
	//we'll use these to verify validity of map later
	map<string, int> continents;
	while (nextLine != "[Territories]") {
		if (!getline(inputFileStream, nextLine)) {
			//if no "[Territories]" line, reject file
			inputFileStream.close();
			return false;
		}
		try { //successfully indexed continent 
			int index = nextLine.find("=");
			continents.insert(make_pair(nextLine.substr(0, index), stoi(nextLine.substr(index))));
		}
		catch (const std::exception& e) {
			inputFileStream.close();
			return false;
		}
	}

	//reach "[Territories]" line, and begin loop until end of file
	//if no territories in map, reject
	//be creating another map that temporarily stores all the Territories by their names
	Map outputMap = new Map();
	map<string, Territory*> tempTerritorylist;
	vector<vector<string>> neighborList;
	while (!inputFileStream.eof()) {
		//First pass: assign territories their name, x coord, y coord, and continent name
		//skip over empty lines, those don't matter
		if (getline(inputFileStream, nextLine) && !nextLine.empty()) {
			try {
				//remove spaces
				nextLine.erase(std::remove_if(nextLine.begin(), nextLine.end(), ::isspace), nextLine.end());

				//split string by commas
				vector<string> nextLineElements;
				size_t start = 0, end;

				while ((end = nextLine.find(',', start)) != string::npos) {
					nextLineElements.push_back(nextLine.substr(start, end - start));
					start = end + 1;
				}
				nextLineElements.push_back(nextLine.substr(start));

				//create a territory from the initial elements, and add it to the map list
				Territory* newTerritory = new Territory(nextLineElements[0], nextLineElements[3], stoi(nextLineElements[1]), stoi(nextLineElements[2]));
				outputMap.territories->push_back(newTerritory);
				tempTerritorylist.insert(make_pair(newTerritory->getName(), newTerritory));

				//If continent number is now negative, or continent cannot be found, reject file
				continents[nextLineElements[3]] -= 1;
				if (continents[nextLineElements[3]] < 0) {
					inputFileStream.close();
					return false;
				}

				//add the remaining list, which should be the neighbors, to the neighbor list to be saved
				nextLineElements.erase(nextLineElements.begin(), nextLineElements.begin() + 4);
				neighborList.push_back(nextLineElements);
			}
			catch (const std::exception& e) {
				inputFileStream.close();
				return false;
			}
		}
	}

	//Second pass: assign territories their neighbors
	//if a territory has no neighbors, reject file (not fully connected)
	if (outputMap.territories->size() == neighborList.size() && outputMap.territories->size() > 0) {
		for (int i = 0; i < neighborList.size(); i++) {
			if (neighborList[i].size() > 0) {
				for (const string& neighbor : neighborList[i]) {
					outputMap.territories->at(i)->addNeighbor(tempTerritorylist[neighbor]);
				}
			}
			else {
				inputFileStream.close();
				return false;
			}
		}
	}
	else {
		inputFileStream.close();
		return false;
	}

	//if we haven't returned false yet, return the map.
	inputFileStream.close();
	map2make = new Map(outputMap);
	return true;
}
