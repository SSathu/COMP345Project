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
		orderList = new vector<Order*>;
		hand = new Hand();
		deck = new Deck();
		reinforcementPool = 0;
	}

	// Parameterized constructor
    Player::Player(string name, std::vector<Territory*>* territory, std::vector<Card*>* card, vector<Order*>* orderList)
    {
    // TODO: Check if the constructor is correctly implemented
        this->name = name;
        this->territory = territory;
        this->hand = new Hand();
        this->orderList = orderList;
        this->deck = new Deck();
        this->reinforcementPool = 0;
    }
	// Parameterized constructor including playerStrategy
	Player::Player(std::string name, std::vector<Territory *> *territory, std::vector<Card *> *card,
                   vector<Order *> *orderList, PlayerStrategy *playerStrategy) {
    // TODO: Check if the constructor is correctly implemented
        this->name = name;
        this->territory = territory;
        this->hand = new Hand();
        this->orderList = orderList;
        this->deck = new Deck();
        this->reinforcementPool = 0;
        this->ps = playerStrategy;
        ps->setPlayer(this);
    }
	// Copy constructor
	Player::Player(Player& player) {

		name = player.name;
		territory = player.territory;
		hand = player.hand;
		deck = player.deck;
		orderList = player.orderList;
	}
	
	// Destructor
	Player::~Player() {
		name.clear();
		territory->clear();
		hand->~Hand();
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
			hand = player.hand;

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
		if (!orderList->empty()) {
			Order* topOrder = orderList->front();
			orderList->front()->execute();
			// Clean up the executed order
			delete orderList->front();
			orderList->erase(orderList->begin());
		}
	}
