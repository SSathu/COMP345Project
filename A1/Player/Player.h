
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
	void execute();
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
	void issueOrder();
	
	string getName();
        void setName(string newName);
        Hand* hand;
		void setReinforcementPool(int reinforcementPool);

		int getReinforcementPool();

		void executeTopOrder();
		
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
	int reinforcementPool;
};


#endif
