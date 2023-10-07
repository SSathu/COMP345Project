#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

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
    DeployOrder();
    DeployOrder(string* name);
    DeployOrder(const DeployOrder &obj);
    bool validate();
    void execute();
    void copy(DeployOrder &obj);
    
};
class AdvanceOrder : public Order
{
public:
    AdvanceOrder();
    AdvanceOrder(string* name);
    AdvanceOrder(const AdvanceOrder &obj);
    bool validate();
    void execute();
    void copy(AdvanceOrder &obj);
};
class BombOrder : public Order
{
public:
    BombOrder();
    BombOrder(string* name);
    BombOrder(const BombOrder &obj);
    bool validate();
    void execute();
    void copy(BombOrder &obj);
};
class BlockadeOrder : public Order
{
public:
    BlockadeOrder();
    BlockadeOrder(string* name);
    BlockadeOrder(const BlockadeOrder &obj);
    bool validate();
    void execute();
    void copy(BlockadeOrder &obj);
};
class AirliftOrder : public Order
{
public:
    AirliftOrder();
    AirliftOrder(string* name);
    AirliftOrder(const AirliftOrder &obj);
    bool validate();
    void execute();
    void copy(AirliftOrder &obj);
};
class NegotiateOrder : public Order
{
public:
    NegotiateOrder();
    NegotiateOrder(string* name);
    NegotiateOrder(const NegotiateOrder &obj);
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
