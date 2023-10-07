#include "Orders.h"
#include "Orders.cpp"
#include <iostream>
using namespace std;

void testOrdersLists() {
    OrdersList ordersList;
    Order namedOrder = Order(new string("NamedOrder"));
    DeployOrder deployOrder = DeployOrder(new string("DeployOrderName"));
    AdvanceOrder advanceOrder = AdvanceOrder(new string("AdvanceOrderName"));
    BombOrder bombOrder = BombOrder(new string("BombOrderName"));
    BlockadeOrder blockadeOrder = BlockadeOrder(new string("BlockadeOrderName"));
    AirliftOrder airliftOrder = AirliftOrder(new string("AirLiftOrderName"));
    NegotiateOrder negotiateOrder = NegotiateOrder(new string("NegotiateOrderName"));

    ordersList.addOrder(&namedOrder);
    ordersList.addOrder(&deployOrder);   
    ordersList.addOrder(&advanceOrder);
    ordersList.addOrder(&bombOrder);
    ordersList.addOrder(&blockadeOrder);
    ordersList.addOrder(&airliftOrder);
    ordersList.addOrder(&negotiateOrder);

    ordersList.removeOrder(1); 
    ordersList.moveOrder(2, 3); 

    for (Order* order : ordersList.orderList) {
        std::cout << order->getName() << std::endl;
    }

    cout << ordersList.orderList.size();

    ordersList.orderList.clear();
}



