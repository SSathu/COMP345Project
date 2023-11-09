// Name: Quang Kien Bui
// ID: 40204011

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "../Map/Map.h"
#include "../Cards/Cards.h"
using namespace std;


class PlayerOrder {
public:
	// Constructor
	PlayerOrder(string playerOrder);
	// Get order method
	string getOrder();

private:
	// store order
	string playerOrder;
};

class Territory;
class Player {
public:
	// Constuctors and Destructor
	Player();
	Player(string name, std::vector<Territory*>* territory, vector<string> card, vector<PlayerOrder*> orderList);
	Player(Player &player);
	~Player();

	// assignment operator
	Player& operator = (Player& player);
	// stream insertion operator
	friend ostream& operator << (ostream& os, Player& player);
	// Show a list of territories to be defended
	void toDefend();
	// Show a list of territories to be attacked
	void toAttack();
	// Put orders in a list
	void issueOrder(string order);
	
	string getName();
        void setName(string newName);
        Hand* hand;
        int reinforcementArmies;
public:
	// Store name of a player
	string name;
	// Store territories
	std::vector<Territory*>* territory;
	// Store cards
	vector<string> card;
	// Store a list of orders
	vector<PlayerOrder*> orderList;
	static Player* NeutralPlayer;
	std::vector<Player*>* negotiating;
};


#endif
