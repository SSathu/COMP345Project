#include "Orders.h"
#include <iostream>
#include <string>
using namespace std;

Order::Order(){this->Name = new string("NoName");}  
Order::Order(string* name){this->Name = name;} 
Order::Order(const Order &obj){this->Name = new string(*(obj.Name));}
bool Order::validate(){ return false; }
void Order::execute() {}
void Order::copy(Order &obj){this->Name = new string(*(obj.Name));}
string Order::getName() const{
    return *Name;
}
void Order::streamInsertion() {
	cout << "Order name: "<< this->getName() << endl;
}

DeployOrder::DeployOrder(){this->Name = new string("NoName");}
DeployOrder::DeployOrder(string* name){this->Name = name;}
DeployOrder::DeployOrder(const DeployOrder &obj){this->Name = obj.Name;}
bool DeployOrder::validate(){ return false; }
void DeployOrder::execute() {}
void DeployOrder::copy(DeployOrder &obj){this->Name = obj.Name;}


AdvanceOrder::AdvanceOrder(){this->Name = new string("NoName");}
AdvanceOrder::AdvanceOrder(string* name){this->Name = name;}
AdvanceOrder::AdvanceOrder(const AdvanceOrder &obj){this->Name = obj.Name;}
bool AdvanceOrder::validate(){ return false; }
void AdvanceOrder::execute() {}
void AdvanceOrder::copy(AdvanceOrder &obj){this->Name = obj.Name;}


BombOrder::BombOrder(){this->Name = new string("NoName");}
BombOrder::BombOrder(string* name){this->Name = name;}
BombOrder::BombOrder(const BombOrder &obj){this->Name = obj.Name;}
bool BombOrder::validate(){ return false; }
void BombOrder::execute() {}
void BombOrder::copy(BombOrder &obj){this->Name = obj.Name;}


BlockadeOrder::BlockadeOrder(){this->Name = new string("NoName");}
BlockadeOrder::BlockadeOrder(string* name){this->Name = name;}
BlockadeOrder::BlockadeOrder(const BlockadeOrder &obj){this->Name = obj.Name;}
bool BlockadeOrder::validate(){ return false; }
void BlockadeOrder::execute() {}
void BlockadeOrder::copy(BlockadeOrder &obj){this->Name = obj.Name;}


AirliftOrder::AirliftOrder(){this->Name = new string("NoName");}
AirliftOrder::AirliftOrder(string* name){this->Name = name;}
AirliftOrder::AirliftOrder(const AirliftOrder &obj){this->Name = obj.Name;}
bool AirliftOrder::validate(){ return false; }
void AirliftOrder::execute() {}
void AirliftOrder::copy(AirliftOrder &obj){this->Name = obj.Name;}


NegotiateOrder::NegotiateOrder(){this->Name = new string("NoName");}
NegotiateOrder::NegotiateOrder(string* name){this->Name = name;}
NegotiateOrder::NegotiateOrder(const NegotiateOrder &obj){this->Name = obj.Name;}
bool NegotiateOrder::validate(){ return false; }
void NegotiateOrder::execute() {}
void NegotiateOrder::copy(NegotiateOrder &obj){this->Name = obj.Name;}



OrdersList::OrdersList(){}
OrdersList::OrdersList(const OrdersList &obj){this->orderList = obj.orderList;}

void OrdersList::copy(OrdersList &obj){this->orderList = obj.orderList;}

void OrdersList::addOrder(Order* orderToAdd){
	orderList.push_back(orderToAdd);
}

void OrdersList::removeOrder(int orderIndex){
	if(orderIndex >= 0 && orderIndex < orderList.size()){
		orderList.erase(orderList.begin() + orderIndex);
	}
}

void OrdersList::moveOrder(int startPos, int endPos) {
    if (startPos >= 0 && startPos < orderList.size() && endPos >= 0 && endPos < orderList.size() && startPos != endPos) {
        Order* temp = orderList[startPos];
        orderList.erase(orderList.begin() + startPos);
        orderList.insert(orderList.begin() + endPos, temp);
    }
}