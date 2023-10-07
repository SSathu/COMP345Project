#include "Orders.h"


//Empty Constr
Order::Order() {}
DeployOrder::DeployOrder() {}
AdvanceOrder::AdvanceOrder() {}
BombOrder::BombOrder() {}
BlockadeOrder::BlockadeOrder() {}
AirliftOrder::AirliftOrder() {}
NegotiateOrder::NegotiateOrder() {}

//Order
bool Order::validate() { return false; } //to implement A2?
void Order::execute() {} //to implement A2?



OrdersList::OrdersList() {}

//OrderList FUnctions
void OrdersList::addOrder(Order* orderToAdd) {
    orderList.push_back(orderToAdd);
}

void OrdersList::removeOrder(int orderIndex) {
    if (orderIndex >= 0 && orderIndex < orderList.size()) {
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