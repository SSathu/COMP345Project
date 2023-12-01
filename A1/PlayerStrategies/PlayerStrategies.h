#pragma once
#include "../Player/Player.h"



class PlayerStrategy {
public:
	Player* p;
	PlayerStrategy(Player* player) { this->p = player; };
	PlayerStrategy() {};
	virtual void issueOrder() = 0;
	virtual vector<Territory*>* toAttack() = 0;
	virtual vector<Territory*>* toDefend() = 0;
};

class NeutralPlayerStrategy : PlayerStrategy {

public:
		NeutralPlayerStrategy(Player* player) { this->p = player; };
		void issueOrder();
		vector<Territory*>* toAttack();
		vector<Territory*>* toDefend();
};

class CheaterPlayerStrategy : PlayerStrategy {
public:
	CheaterPlayerStrategy(Player* player) { this->p = player; };

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class HumanPlayerStrategy : PlayerStrategy {
public:
	HumanPlayerStrategy(Player* player) { this->p = player; };

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class AggressivePlayerStrategy : PlayerStrategy {
public:
	AggressivePlayerStrategy(Player* player);

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class BenevolentPlayerStrategy : PlayerStrategy {
public:
	BenevolentPlayerStrategy(Player* player);
	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};