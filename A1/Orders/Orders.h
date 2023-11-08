#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Territory;
class Player;


class Order
{
public:
    Order();
    Order(string* name);
    Order(const Order &obj);
    string* Name;
    bool validate();
    void execute();
    void copy(Order &obj);
	void streamInsertion();
    string getName() const;
    };

class DeployOrder : public Order
{
public:
    Player* issuingPlayer;
    Territory* area;
    int numberOfArmies;
    DeployOrder();
    DeployOrder(string* name);
    DeployOrder(const DeployOrder &obj);
    DeployOrder(Player* issuingPlayer, int numberOfArmies, Territory* area);
    virtual ~DeployOrder();
    bool validate();
    void execute();
    void copy(DeployOrder &obj);
    
};
class AdvanceOrder : public Order
{
public:
    Player* issuingPlayer;
    Territory* start;
    Territory* destination;
    int numberOfArmies;
    bool isAttacking;
    AdvanceOrder();
    AdvanceOrder(string* name);
    AdvanceOrder(const AdvanceOrder &obj);
    AdvanceOrder(Player* issuingPlayer, Territory* start, Territory* destination, int numberOfArmies);
    bool validate();
    void execute();
    void copy(AdvanceOrder &obj);
};
class BombOrder : public Order
{
public:
    Player* issuingPlayer;
    Territory* attackedTerritory;
    BombOrder();
    BombOrder(string* name);
    BombOrder(const BombOrder &obj);
    BombOrder(Player* issuingPlayer, Territory* attackedTerritory);
    bool validate();
    void execute();
    void copy(BombOrder &obj);
};
class BlockadeOrder : public Order
{
public:
    Player* issuingPlayer;
    Territory* area;
    BlockadeOrder();
    BlockadeOrder(string* name);
    BlockadeOrder(const BlockadeOrder &obj);
    BlockadeOrder(Player* issuingPlayer, Territory* area);
    bool validate();
    void execute();
    void copy(BlockadeOrder &obj);
};
class AirliftOrder : public Order
{
public:
    Player* issuingPlayer;
    int numberOfArmies;
    Territory* start;
    Territory* destination;
    AirliftOrder();
    AirliftOrder(string* name);
    AirliftOrder(const AirliftOrder &obj);
    AirliftOrder(Player* issuingPlayer, int numberOfArmies, Territory* start, Territory* destination);
    bool validate();
    void execute();
    void copy(AirliftOrder &obj);
};
class NegotiateOrder : public Order
{
public:
    Player* issuingPlayer;
    Player* targetPlayer;
    NegotiateOrder();
    NegotiateOrder(string* name);
    NegotiateOrder(const NegotiateOrder &obj);
    NegotiateOrder(Player* issuingPlayer, Player* targetPlayer);
    bool validate(); 
    void execute();
    void copy(NegotiateOrder &obj);
};

class OrdersList
{
public:
    OrdersList();
    OrdersList(const OrdersList &obj);
    vector<Order *> orderList;
    void addOrder(Order *orderToAdd);
    void removeOrder(int orderIndex);
    void moveOrder(int startPos, int endPos);
    void copy(OrdersList &obj);
};
