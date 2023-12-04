#include "Orders.h"
#include <iostream>
#include <string>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"
#include <algorithm>
using namespace std;

// Implementations for Order class
Order::Order(){this->Name = new string("NoName"), this->OrderType = new string("Order");}  // Allocate memory for Name
Order::Order(string* name){this->Name = name, this->OrderType = new string("Order");}  // Change parameter to string pointer
Order::Order(const Order &obj){this->Name = new string(*(obj.Name)), this->OrderType = new string("Order");;}  // Allocate memory for Name
bool Order::validate(){ return false; }
void Order::execute() {
    Notify(this);
}
void Order::copy(Order &obj){this->Name = new string(*(obj.Name)), this->OrderType = new string("Order");;}  // Allocate memory for Name
string Order::getName() const{
    return *Name;
}


void Order::switchNeutralPlayer(Player* p)
{
    if ((p) &&*p->ps->neutral == true)
    {
        *p->ps->neutral = false;
        p->ps = new AggressivePlayerStrategy();
    }
}

string* Order::stringToLog()
{
    return new string("Executed order type: " + *OrderType);
}

void Order::streamInsertion() {
	cout << "Order name: "<< this->getName() << endl;
}

// Implementations for DeployOrder
DeployOrder::DeployOrder(){this->Name = new string("NoName"), this->OrderType = new string("DeployOrder");}
DeployOrder::DeployOrder(string* name){this->Name = name, this->OrderType = new string("DeployOrder");}
DeployOrder::DeployOrder(const DeployOrder &obj){this->Name = obj.Name, this->OrderType = new string("DeployOrder");}
DeployOrder::~DeployOrder(){}
DeployOrder::DeployOrder(Player* issuingPlayer, int numOfArmies, Territory* location) :Order(), issuingPlayer(issuingPlayer), numberOfArmies(numberOfArmies), area(area){ this->OrderType = new string("DeployOrder");}


bool DeployOrder::validate(){
       if(std::find(issuingPlayer->territory->begin(), issuingPlayer->territory->end(), area) != issuingPlayer->territory->end()){
            return true;
        }
        return false;  
 }

void DeployOrder::execute() {
    
    if(this->validate()){
        Order::execute();
        this->area->numArmies += numberOfArmies;
    }
}

void DeployOrder::copy(DeployOrder &obj){this->Name = obj.Name;}


// Implementations for AdvanceOrder
AdvanceOrder::AdvanceOrder(){this->Name = new string("NoName");}
AdvanceOrder::AdvanceOrder(string* name){this->Name = name, this->OrderType = new string("AdvanceOrder");}
AdvanceOrder::AdvanceOrder(const AdvanceOrder &obj){this->Name = obj.Name, this->OrderType = new string("AdvanceOrder");}
AdvanceOrder::AdvanceOrder(Player* issuingPlayer, Territory* start, Territory* destination, int numberOfArmies) : Order(), isAttacking(false), issuingPlayer(issuingPlayer), start(start), destination(destination), numberOfArmies(numberOfArmies){this->OrderType = new string("AdvanceOrder");}


bool AdvanceOrder::validate(){ 
    // source terr != issuing players terr
    if(std::find(issuingPlayer->territory->begin(), issuingPlayer->territory->end(), start) == issuingPlayer->territory->end()) return false;
    // territories not adjacent
    else if(std::find(start->neighbors->begin(),start->neighbors->end(),destination) == start->neighbors->end()) return false;
    // target player is negociating with issuing player
    else if(destination->playerOwner != issuingPlayer 
    && std::find(issuingPlayer->negotiating->begin(),issuingPlayer->negotiating->end(), destination->playerOwner) != issuingPlayer->negotiating->end()){
        return false;
    }
        return true;
}

void AdvanceOrder::execute() { 
    Order::execute();

    switchNeutralPlayer(destination->playerOwner);

    if (cheater)
    {
        Player* p = this->issuingPlayer;
        Territory* attacking = this->destination;

        if (!attacking->playerOwner == NULL)
        {
            Player* playerBeingAttacked = attacking->playerOwner;
            auto it = std::find(playerBeingAttacked->territory->begin(), playerBeingAttacked->territory->end(), attacking);

            if (it != playerBeingAttacked->territory->end())
            {
                playerBeingAttacked->territory->erase(it);
            }
        }
        p->territory->push_back(attacking);
        std::cout << "Cheater captured territory " << attacking->getName();
        return;
    }

    // both territories from issuing player
    if(start->playerOwner == issuingPlayer && destination ->playerOwner == issuingPlayer){
        destination->numArmies += numberOfArmies;
        start->numArmies -= numberOfArmies;
    }
    // different players
    if(destination->playerOwner != issuingPlayer){

        srand(static_cast<unsigned>(time(0))); //rand generator
        int remainingAttackers = *(start->numArmies);
        int remainingDefenders = *(destination->numArmies);

    while(remainingAttackers > 0 && remainingDefenders > 0 ){

            if(rand() % 100 < 70){
                remainingAttackers--;
            }
        
            if(rand() % 100 < 60){
                remainingDefenders--;
            }
        
    }
    
    // Attackers Won
    if(remainingAttackers > 0){
        cout << "Attack successful! " << issuingPlayer->name << " has captured " << destination->getName() << endl;
        destination->playerOwner->reinforcementPool -= *(destination->numArmies);
        *(destination->numArmies) = remainingAttackers;
        destination->setPlayer(issuingPlayer);
        
        int randCardNumb = std::rand()%5;
        Card newCard(randCardNumb);
        issuingPlayer->hand->handCards->push_back(&newCard);
    }else{
        cout << "Attack failed! " << destination->getName() << " won against Attackers:  " << issuingPlayer->name  << endl;
    }

        
    }
}
void AdvanceOrder::copy(AdvanceOrder &obj){this->Name = obj.Name, this->OrderType = new string("AdvanceOrder");}



// Implementations for BombOrder
BombOrder::BombOrder(){this->Name = new string("NoName"), this->OrderType = new string("BombOrder");}
BombOrder::BombOrder(string* name){this->Name = name, this->OrderType = new string("BombOrder");}
BombOrder::BombOrder(const BombOrder &obj){this->Name = obj.Name, this->OrderType = new string("BombOrder");}
BombOrder::BombOrder(Player* issuingPlayer, Territory* attackedTerritory) : Order(), issuingPlayer(issuingPlayer), attackedTerritory(attackedTerritory){this->OrderType = new string("BombOrder");}

bool BombOrder::validate(){ 
    // issuing = attacked
    if(attackedTerritory->playerOwner = issuingPlayer){
            return false;
    }
    // target not adjacent to any owned by iussing
    for(Territory* terri : *(issuingPlayer->territory)){
            if(std::find(attackedTerritory->neighbors->begin(), attackedTerritory->neighbors->end(), terri) == attackedTerritory->neighbors->end()){
                return false;
            }
    }
    //issuing negociating with attacked
    if(std::find(issuingPlayer->negotiating->begin(),issuingPlayer->negotiating->end(), attackedTerritory->playerOwner) != issuingPlayer->negotiating->end()){
        return false;
    }
    return true;
}


void BombOrder::execute() {
    if(this->validate()){
        Order::execute();
        switchNeutralPlayer(this->attackedTerritory->playerOwner);
        if (attackedTerritory != nullptr && attackedTerritory->numArmies != nullptr) {
                *(attackedTerritory->numArmies) /= 2;
        }

    }

}
void BombOrder::copy(BombOrder &obj){this->Name = obj.Name, this->OrderType = new string("BombOrder");}


// Implementations for BlockadeOrder
BlockadeOrder::BlockadeOrder(){this->Name = new string("NoName"), this->OrderType = new string("BlockadeOrder");}
BlockadeOrder::BlockadeOrder(string* name){this->Name = name, this->OrderType = new string("BlockadeOrder");}
BlockadeOrder::BlockadeOrder(const BlockadeOrder &obj){this->Name = obj.Name, this->OrderType = new string("BlockadeOrder");}
BlockadeOrder::BlockadeOrder(Player* issuingPlayer, Territory* area) : Order(), issuingPlayer(issuingPlayer), area(area){this->OrderType = new string("BlockadeOrder");}

bool BlockadeOrder::validate(){ 
    
	if (area->playerOwner != issuingPlayer) {
		return false;
	}
        return true;
}
    
void BlockadeOrder::execute() {

    if(this->validate()){
        Order::execute();
        *(area->numArmies) *= 2;
        area->playerOwner = Player::NeutralPlayer;

        issuingPlayer->territory->erase(std::remove(issuingPlayer->territory->begin(), issuingPlayer->territory->end(), area), issuingPlayer->territory->end());
    }
}
void BlockadeOrder::copy(BlockadeOrder &obj){this->Name = obj.Name, this->OrderType = new string("BlockadeOrder");}


// Implementations for AirliftOrder
AirliftOrder::AirliftOrder(){this->Name = new string("NoName");}
AirliftOrder::AirliftOrder(string* name){this->Name = name, this->OrderType = new string("AirLiftOrder");}
AirliftOrder::AirliftOrder(const AirliftOrder &obj){this->Name = obj.Name, this->OrderType = new string("AirLiftOrder");}
AirliftOrder::AirliftOrder(Player* issuingPlayer, int numberOfArmies, Territory* start, Territory* destination) : Order(), issuingPlayer(issuingPlayer), numberOfArmies(numberOfArmies), start(start), destination(destination){this->OrderType = new string("AirLiftOrder");}

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
    Order::execute();

    destination->numArmies += numberOfArmies;
    start->numArmies -= numberOfArmies;
}
void AirliftOrder::copy(AirliftOrder &obj){this->Name = obj.Name, this->OrderType = new string("AirLiftOrder");}


// Implementations for NegotiateOrder
NegotiateOrder::NegotiateOrder(){this->Name = new string("NoName");}
NegotiateOrder::NegotiateOrder(string* name){this->Name = name, this->OrderType = new string("NegociateOrder");}
NegotiateOrder::NegotiateOrder(const NegotiateOrder &obj){this->Name = obj.Name, this->OrderType = new string("NegociateOrder");}
NegotiateOrder::NegotiateOrder(Player* issuingPlayer, Player* targetPlayer) : Order(), issuingPlayer(issuingPlayer), targetPlayer(targetPlayer){this->OrderType = new string("NegociateOrder");}

bool NegotiateOrder::validate(){ 
    
    if (issuingPlayer != targetPlayer) {
		 return true;
	}
    return false;
}


void NegotiateOrder::execute() {

    if(this->validate()){
        Order::execute();

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
    Notify(this);
}

string* OrdersList::stringToLog()
{
    return new string("Order Issued: " + orderList.back()->getName());
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