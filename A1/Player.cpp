#include "Player.h"
#include <iostream>

// Constructor
PlayerOrder::PlayerOrder(string playerOrder) {
	this->playerOrder = playerOrder;
}

// Get the order information
string PlayerOrder::getOrder() {
	return playerOrder;
}

// Default constructor
	Player::Player(){
		name = "";
		territory = {};
		card = {};
		orderList = {};
	}

	// Parameterized constructor
	Player::Player(string  name, vector<string>territory, vector<string>card, vector<PlayerOrder*> orderList) {
		this->name = name;
		this->territory = territory;
		this->card = card;
		this->orderList = orderList;
	}
	// Copy constructor
	Player::Player(Player& player) {
		name = player.name;
		territory = player.territory;
		card = player.card;
		orderList = player.orderList;

	}
	
	// Destructor
	Player::~Player() {
		name.clear();
		territory.clear();
		card.clear();
	for (PlayerOrder* order : orderList) {
				delete order;
		}
	orderList.clear();
	}

	// assignment operator
	Player& Player::operator = (Player& player) {
		if (this != &player) {
			name = player.name;
			territory = player.territory;
			card = player.card;

			for (PlayerOrder* order : orderList) {
				delete order;
			}
			orderList.clear();

			for (PlayerOrder* order : player.orderList) {
				orderList.push_back(new PlayerOrder(*order));
			}
		}
		return *this;
	}

	// print out the information of a player
	ostream& operator << (ostream& os, Player& player) {
		os << "Name: " << player.name << endl;
		os << "Territories: " << endl;
		for (string& s1 : player.territory) {
			os << "-" << s1 << endl;
		}
		os << endl;
		os << "Cards: " << endl;
		for (string& s2 : player.card) {
			os << "-" << s2 << endl;
		}
		os << endl;
		os << "List of orders: " << endl;
		for (PlayerOrder* order : player.orderList) {
			os << "-" << order->getOrder() << endl;
		}
		return os;
	}

	// The method shows a list of territories to be defended
	void Player::toDefend() {
		cout << "Territories to be defended: " << endl;
		for (string& s : territory) {
				cout << s << endl;
		}
		cout << endl;

	}

	// the method shows a list of territories to be attacked
	void Player::toAttack() {
		cout << "Territories to be attacked: " << endl;
		for (string& s : territory) {
				cout << s << endl;
	
		}
		cout << endl;

	}

	// The method puts the orders into a list of orders
	void Player::issueOrder(string order) {
		PlayerOrder* playerOrder = new PlayerOrder(order);
		orderList.push_back(playerOrder);
	}


