// Name: Quang Kien Bui
// ID: 40204011

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
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

class Player {
public:
	// Constuctors and Destructor
	Player();
	Player(string name, vector<string> territory, vector<string> card, vector<PlayerOrder*> orderList);
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
	
	
private:
	// Store name of a player
	string name;
	// Store territories
	vector<string> territory;
	// Store cards
	vector<string> card;
	// Store a list of orders
	vector<PlayerOrder*> orderList;
};


#endif
