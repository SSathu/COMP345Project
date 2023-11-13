#include "../Cards/Cards.h"
#include "../Map/Map.h"
#include "../Map/MapDriver.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include <iostream>


void testLoggingObserver()
{
    Command* c = new Command();
    CommandProcessor* cprocessor = new CommandProcessor();
    Order* order = new Order();
    AdvanceOrder* bo = new AdvanceOrder();
    OrdersList* orderList = new OrdersList();
    GameEngine* g = new GameEngine();

    LogObserver* log = new LogObserver();

    c->Attach(log);
    cprocessor->Attach(log);
    order->Attach(log);
    bo->Attach(log);
    orderList->Attach(log);
    g->Attach(log);

    c->saveEffect(new string("Does wicked things"));
    order->execute();
    orderList->addOrder(bo);
    g->processInput("loadmap");
    cprocessor->getCommand(*g);
}

int main()
{
    testLoggingObserver();

    return 0;
};