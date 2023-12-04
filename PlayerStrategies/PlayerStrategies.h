#pragma once
#include <vector>

using std::vector;
class Player;
class Territory;

class PlayerStrategy {
public:
	Player* p;
	bool* neutral = new bool(false);
	~PlayerStrategy() { delete neutral; neutral = nullptr; }
	void setPlayer(Player* player) { this->p = player; };
	virtual void issueOrder() = 0;
	virtual vector<Territory*>* toAttack() = 0;
	virtual vector<Territory*>* toDefend() = 0;
};

class NeutralPlayerStrategy : public PlayerStrategy {

public:
		NeutralPlayerStrategy() { *neutral = true; }
		void issueOrder();
		vector<Territory*>* toAttack();
		vector<Territory*>* toDefend();
};

class CheaterPlayerStrategy :public  PlayerStrategy {
public:

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class HumanPlayerStrategy :public  PlayerStrategy {
public:

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class AggressivePlayerStrategy :public  PlayerStrategy {
public:

	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};

class BenevolentPlayerStrategy :public  PlayerStrategy {
public:
	void issueOrder();
	vector<Territory*>* toAttack();
	vector<Territory*>* toDefend();
};