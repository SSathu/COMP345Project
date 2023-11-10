
#include "Player.h"
#include <iostream>
#include "../Map/Map.h"

// Constructor
PlayerOrder::PlayerOrder(string playerOrder) {
	this->playerOrder = playerOrder;
}

// Get the order information
string PlayerOrder::getOrder() {
	return playerOrder;
}

void PlayerOrder::execute() {
	// Update game state based on the order
	cout << "Executing order: " << playerOrder;
}

// Default constructor
	Player::Player(){
		name = "";
		territory = new vector<Territory*>;
		card = {};
		orderList = {};
		reinforcementPool = 0;
	}

	// Parameterized constructor
	Player::Player(string  name, std::vector<Territory*>* territory, vector<string>card, vector<PlayerOrder*> orderList) {
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
		territory->clear();
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
		for (Territory* s1 : *(player.territory)) {
			os << "-" << s1->getName() << endl;
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
		for (Territory* s : *territory) {
				cout << s->getName() << endl;
		}
		cout << endl;

	}

	// the method shows a list of territories to be attacked
	void Player::toAttack() {
		cout << "Territories to be attacked: " << endl;
		for (Territory* s : *territory) {
				cout << s->getName() << endl;
	
		}
		cout << endl;

	}

	// The method puts the orders into a list of orders
	void Player::issueOrder() {
		// to defend
		toDefend();
		cout << "Issuing deploy orders:" << endl;
		for (Territory* t : *territory) {
			if (reinforcementPool > 0) {
				cout << "Deploying units to " << t->getName() << endl;
				orderList.push_back(new PlayerOrder("Deploy to " + t->getName()));
				reinforcementPool--;
			}
		}
		cout << endl; 
	
		// to attack
		if (reinforcementPool == 0) {
			toAttack();
			cout << "Issuing advance orders:" << endl;
			for (Territory* t : *territory) {

				if (reinforcementPool > 0) {
					cout << "Moving units to defend " << t->getName() << endl;
					orderList.push_back(new PlayerOrder("Defend " + t->getName()));
					reinforcementPool--;
				}
			}
			cout << endl;

			if (!card.empty()) {
				cout << "Using card: " << card.back() << endl;
				orderList.push_back(new PlayerOrder(card.back()));
				//  remove the used card from the hand
				card.pop_back(); 
			}
			cout << endl;

		}
	
	}

void Player::setName(std::string newName) {
        this->name = newName;
    }
    string Player::getName() {
        return name;
    }

	int Player::getReinforcementPool() {
		return reinforcementPool;
	}
	void Player::setReinforcementPool(int reinforcementPool) {
		this->reinforcementPool = reinforcementPool;
	}

	void Player::executeTopOrder() {
		if (orderList.empty()) {
			PlayerOrder* topOrder = orderList.front();
			topOrder->execute();

			// Clean up the executed order
			delete topOrder;
			orderList.erase(orderList.begin());
		}
	}
