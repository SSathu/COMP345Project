#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"
#include <algorithm>
using namespace std;

// Implementations for Order class
Order::Order(){this->Name = new string("NoName");}  // Allocate memory for Name
Order::Order(string* name){this->Name = name;}  // Change parameter to string pointer
Order::Order(const Order &obj){this->Name = new string(*(obj.Name));}  // Allocate memory for Name
bool Order::validate(){ return false; }
void Order::execute() {}
void Order::copy(Order &obj){this->Name = new string(*(obj.Name));}  // Allocate memory for Name
string Order::getName() const{
    return *Name;
}
void Order::streamInsertion() {
	cout << "Order name: "<< this->getName() << endl;
}

// Implementations for DeployOrder
DeployOrder::DeployOrder(){this->Name = new string("NoName");}
DeployOrder::DeployOrder(string* name){this->Name = name;}
DeployOrder::DeployOrder(const DeployOrder &obj){this->Name = obj.Name;}
DeployOrder::~DeployOrder(){}
DeployOrder::DeployOrder(Player* issuingPlayer, int numOfArmies, Territory* location) :Order(), issuingPlayer(issuingPlayer), numberOfArmies(numberOfArmies), area(area){					}


bool DeployOrder::validate(){
       if(std::find(issuingPlayer->territory->begin(), issuingPlayer->territory->end(), area) != issuingPlayer->territory->end()){
            return true;
        }
        return false;  
 }

void DeployOrder::execute() {
    if(this->validate()){
        this->area->numArmies += numberOfArmies;
    }
}

void DeployOrder::copy(DeployOrder &obj){this->Name = obj.Name;}


// Implementations for AdvanceOrder
AdvanceOrder::AdvanceOrder(){this->Name = new string("NoName");}
AdvanceOrder::AdvanceOrder(string* name){this->Name = name;}
AdvanceOrder::AdvanceOrder(const AdvanceOrder &obj){this->Name = obj.Name;}
AdvanceOrder::AdvanceOrder(Player* issuingPlayer, Territory* start, Territory* destination, int numberOfArmies) : Order(), isAttacking(false), issuingPlayer(issuingPlayer), start(start), destination(destination), numberOfArmies(numberOfArmies){}


bool AdvanceOrder::validate(){ 
    if(std::find(issuingPlayer->territory->begin(), issuingPlayer->territory->end(), start) == issuingPlayer->territory->end()){
            return false;
        }
    // TO FINISH    
    return false; }
void AdvanceOrder::execute() { // TO FINISH
}
void AdvanceOrder::copy(AdvanceOrder &obj){this->Name = obj.Name;}



// Implementations for BombOrder
BombOrder::BombOrder(){this->Name = new string("NoName");}
BombOrder::BombOrder(string* name){this->Name = name;}
BombOrder::BombOrder(const BombOrder &obj){this->Name = obj.Name;}
BombOrder::BombOrder(Player* issuingPlayer, Territory* attackedTerritory) : Order(), issuingPlayer(issuingPlayer), attackedTerritory(attackedTerritory){}

bool BombOrder::validate(){ 
    if(attackedTerritory->playerOwner = issuingPlayer){
            return false;
    }
    for(Territory* terri : *(issuingPlayer->territory)){
            if(std::find(attackedTerritory->neighbors->begin(), attackedTerritory->neighbors->end(), terri) == attackedTerritory->neighbors->end()){
                return false;
            }
    }
}


void BombOrder::execute() {

    if(this->validate()){
        if (attackedTerritory != nullptr && attackedTerritory->numArmies != nullptr) {
                *(attackedTerritory->numArmies) /= 2;
        }

    }

}
void BombOrder::copy(BombOrder &obj){this->Name = obj.Name;}


// Implementations for BlockadeOrder
BlockadeOrder::BlockadeOrder(){this->Name = new string("NoName");}
BlockadeOrder::BlockadeOrder(string* name){this->Name = name;}
BlockadeOrder::BlockadeOrder(const BlockadeOrder &obj){this->Name = obj.Name;}
BlockadeOrder::BlockadeOrder(Player* issuingPlayer, Territory* area) : Order(), issuingPlayer(issuingPlayer), area(area){}

bool BlockadeOrder::validate(){ 
    
	if (area->playerOwner != issuingPlayer) {
		return false;
	}
        return true;
}
    
void BlockadeOrder::execute() {

    if(this->validate()){
        *(area->numArmies) *= 2;
        area->playerOwner = Player::NeutralPlayer;
        issuingPlayer->territory->erase(std::remove(issuingPlayer->territory->begin(), issuingPlayer->territory->end(), *area), issuingPlayer->territory->end());
    }
}
void BlockadeOrder::copy(BlockadeOrder &obj){this->Name = obj.Name;}


// Implementations for AirliftOrder
AirliftOrder::AirliftOrder(){this->Name = new string("NoName");}
AirliftOrder::AirliftOrder(string* name){this->Name = name;}
AirliftOrder::AirliftOrder(const AirliftOrder &obj){this->Name = obj.Name;}
AirliftOrder::AirliftOrder(Player* issuingPlayer, int numberOfArmies, Territory* start, Territory* destination) : Order(), issuingPlayer(issuingPlayer), numberOfArmies(numberOfArmies), start(start), destination(destination){}

bool AirliftOrder::validate(){
        if(start->playerOwner == issuingPlayer && destination->playerOwner == issuingPlayer){
            if(numberOfArmies > *(start->numArmies)){
                return false;
            }else{
                return true;
            }
        }
    
     return false; 
     }
void AirliftOrder::execute() {
    
    destination->numArmies += numberOfArmies;
    start->numArmies -= numberOfArmies;
}
void AirliftOrder::copy(AirliftOrder &obj){this->Name = obj.Name;}


// Implementations for NegotiateOrder
NegotiateOrder::NegotiateOrder(){this->Name = new string("NoName");}
NegotiateOrder::NegotiateOrder(string* name){this->Name = name;}
NegotiateOrder::NegotiateOrder(const NegotiateOrder &obj){this->Name = obj.Name;}
NegotiateOrder::NegotiateOrder(Player* issuingPlayer, Player* targetPlayer) : Order(), issuingPlayer(issuingPlayer), targetPlayer(targetPlayer){}

bool NegotiateOrder::validate(){ 
    
    if (issuingPlayer != targetPlayer) {
		 return true;
	}
    return false;
}


void NegotiateOrder::execute() {

    if(this->validate()){
        issuingPlayer->negotiating->push_back(targetPlayer);
        targetPlayer->negotiating->push_back(issuingPlayer);
    }

}
void NegotiateOrder::copy(NegotiateOrder &obj){this->Name = obj.Name;}



OrdersList::OrdersList(){}
OrdersList::OrdersList(const OrdersList &obj){this->orderList = obj.orderList;}

void OrdersList::copy(OrdersList &obj){this->orderList = obj.orderList;}

//OrderList FUnctions
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