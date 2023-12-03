#include "Player.h"
#include <iostream>

// Static variable initialization NeutralPlayer
Player* Player::NeutralPlayer = nullptr;

// Constructor
PlayerOrder::PlayerOrder(string playerOrder) {
	this->playerOrder = playerOrder;
}

PlayerOrder::PlayerOrder(Card playCard){
	this->playerOrderCard = playCard;
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
        negotiating = new vector<Player*>;
		card = {};
		orderList = {};
		reinforcementPool = 0;
	}

	// Parameterized constructor
	Player::Player(string  name, std::vector<Territory*>* territory, std::vector<Card*>* card, vector<Order*>* orderList) {
		this->name = name;
		this->territory = territory;
		this->card = card;
		this->orderList = orderList;
	}
	// Parameterized constructor including playerStrategy
	Player::Player(string name, std::vector<Territory*>* territory, std::vector<Card*>* card, vector<Order*>* orderList, PlayerStrategy* playerStrategy)
	{
		this->name = name;
		this->territory = territory;
		this->card = card;
		this->orderList = orderList;
		this->ps = playerStrategy;
		ps->setPlayer(this);
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
		card->clear();
	for (Order* order : *orderList) {
				delete order;
		}
	orderList->clear();
	}

	// assignment operator
	Player& Player::operator = (Player& player) {
		if (this != &player) {
			name = player.name;
			territory = player.territory;
			card = player.card;

			for (Order* order : *orderList) {
				delete order;
			}
			orderList->clear();

			for (Order* order : *player.orderList) {
				orderList->push_back(new Order(*order));
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
		for (Card* s2 : *(player.card)) {
			os << "-" << s2 << endl;
		}
		os << endl;
		os << "List of orders: " << endl;
		for (Order* order : *player.orderList) {
			os << "-" << order << endl;
		}
		return os;
	}

	// The method shows a list of territories to be defended
	vector<Territory*>* Player::toDefend() {
		return ps->toDefend();
	}

	// the method shows a list of territories to be attacked
		vector<Territory*>* Player::toAttack() {
			return ps->toAttack();

	}

	// The method puts the orders into a list of orders
	void Player::issueOrder() {
		ps->issueOrder();
	}

	void Player::setStrategy(PlayerStrategy* strategy)
	{
		this->ps = strategy;
		ps->setPlayer(this);
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
	void Player::setDeck(Deck* d)
	{
		this->deck = d;
	}
	void Player::setReinforcementPool(int reinforcementPool) {
		this->reinforcementPool = reinforcementPool;
	}

	void Player::executeTopOrder() {
		if (orderList->empty()) {
			Order* topOrder = orderList->front();
			topOrder->execute();

			// Clean up the executed order
			delete topOrder;
			orderList->erase(orderList->begin());
		}
	}
