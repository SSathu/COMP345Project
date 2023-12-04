#pragma once

#include <iostream>
#include <vector>
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../PlayerStrategies/PlayerStrategies.h"
using namespace std;


class PlayerOrder {
public:
	// Constructor
	PlayerOrder(string playerOrder);
	PlayerOrder(Card playerOrderCard);
	// Get order method
	string getOrder();
	void execute();
private:
	// store order
	string playerOrder;
	Card playerOrderCard;
};

class Territory;
class Player {
public:
	// Constuctors and Destructor
	Player();
	Player(string name, std::vector<Territory*>* territory, std::vector<Card*>* card, vector<Order*>* orderList);
	Player(string name, std::vector<Territory*>* territory, std::vector<Card*>* card, vector<Order*>* orderList, PlayerStrategy* playerStrategy);

	Player(Player &player);

	~Player();
	PlayerStrategy* ps;

	// assignment operator
	Player& operator = (Player& player);
	// stream insertion operator
	friend ostream& operator << (ostream& os, Player& player);
	// Show a list of territories to be defended
	vector<Territory*>* toDefend();
	// Show a list of territories to be attacked
	vector<Territory*>* toAttack();
	// Put orders in a list
	void issueOrder();

	void setStrategy(PlayerStrategy* strategy);
	
	string getName();
        void setName(string newName);
        Hand* hand;
		Deck* deck;
		void setDeck(Deck* d);
		void setReinforcementPool(int reinforcementPool);

		int getReinforcementPool();

		void executeTopOrder();
		
public:
	// Store name of a player
	string name;
	// Store territories
	std::vector<Territory*>* territory;
	// Store cards
	// Store a list of orders
	vector<Order*>* orderList;
	static Player* NeutralPlayer;
	std::vector<Player*>* negotiating;
	int reinforcementPool;
};

