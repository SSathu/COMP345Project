#pragma once
#include "../Player/Player.h"



class PlayerStrategy {
public:
	Player* p;
	void setPlayer(Player* player) { this->p = player; };
	virtual void issueOrder() = 0;
	virtual vector<Territory*>* toAttack() = 0;
	virtual vector<Territory*>* toDefend() = 0;
};

class NeutralPlayerStrategy : PlayerStrategy {

public:
		void issueOrder();
		vector<Territory*>* toAttack();
		vector<Territory*>* toDefend();
};

class CheaterPlayerStrategy : PlayerStrategy {
public:

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class HumanPlayerStrategy : PlayerStrategy {
public:

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class AggressivePlayerStrategy : PlayerStrategy {
public:

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class BenevolentPlayerStrategy : PlayerStrategy {
public:
	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};