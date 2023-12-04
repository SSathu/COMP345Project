#include "Orders.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../Map/Map.h"
#include "../Player/Player.h"

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

void testOrderExecution() {
    // Create players
    Player* player1 = new Player();
    Player* player2 = new Player();
    player1->setName("Player 1");
    player2->setName("Player 2");

    Territory* territoryA = new Territory("A", "Africa", 1,2);
    Territory* territoryB = new Territory("B", "Europe", 1,5);

    player1->territory->push_back(territoryA);
    player2->territory->push_back(territoryB);

    // (1) Order Validation
    cout << "(1)Order Validation Test" << endl;
    cout << "-----------------------------" << endl;

    AdvanceOrder* validAdvanceOrder = new AdvanceOrder(player1, territoryA, territoryB, 3);
    if (validAdvanceOrder->validate()) {
        cout << "Valid Order: " << *validAdvanceOrder->Name << endl;
        validAdvanceOrder->execute();
    } else {
        cout << "Invalid Order: " << *validAdvanceOrder->Name << endl;
    }
    delete validAdvanceOrder;

    // (2) Territory ownership transfer
    cout << "\n (2)Territory Ownership Transfer Test" << endl;
    cout << "---------------------------------------" << endl;

    AdvanceOrder* conquestOrder = new AdvanceOrder(player1, territoryA, territoryB, 3);
    if (conquestOrder->validate()) {
        cout << "Valid Conquest Order: " << *conquestOrder->Name << endl;
        conquestOrder->execute();
    } else {
        cout << "Invalid Conquest Order: " << *conquestOrder->Name << endl;
    }
    delete conquestOrder;

    // (3) One card per turn for conquering a territory
    cout << "\n (3) Card Reward Test" << endl;
    cout << "---------------------------------------------" << endl;

    AdvanceOrder* conquestForCard = new AdvanceOrder(player1, territoryA, territoryB, 3);
    if (conquestForCard->validate()) {
        cout << "Valid Conquest Order for Card: " << *conquestForCard->Name << endl;
        // Execute the conquest order
        conquestForCard->execute();
        // Check if player1 received a card
        if ((player1->hand->handCards)->size() == 1) {
            cout << "Player 1 received a card." << endl;
        } else {
            cout << "Player 1 did not receive a card." << endl;
        }
    } else {
        cout << "Invalid Conquest Order for Card: " << *conquestForCard->Name << endl;
    }
    delete conquestForCard;

    // (4) Negotiate order test
    cout << "\n(4) Negotiate Order Test" << endl;
    cout << "---------------------------" << endl;

    NegotiateOrder* negotiateOrder = new NegotiateOrder(player1, player2);


    if (negotiateOrder->validate()) {

        negotiateOrder->execute();

        AdvanceOrder* invalidAttack = new AdvanceOrder(player1, territoryA, territoryB, 3);
        if (invalidAttack->validate()) {
            cout << "Invalid Attack Order after Negotiate: " << *invalidAttack->Name << endl;
        } else {
            cout << "Valid Attack Order Failed becayse by Negotiate." << endl;
        }
        delete invalidAttack;
    } else {
        cout << "Invalid Negotiate Order: " << *negotiateOrder->Name << endl;
    }
    delete negotiateOrder;

    // (5) Blockade order Test
    cout << "\n (5) Blockade Order" << endl;
    cout << "--------------------------" << endl;

    BlockadeOrder* blockadeOrder = new BlockadeOrder(player1, territoryA);
    if (blockadeOrder->validate()) {

        blockadeOrder->execute();

        cout << "Player 1 owns: " << player1->territory->size() << " territories" << endl;
        cout << "Neutral player owns: " << Player::NeutralPlayer->territory->size() << " territories" << endl;
    } else {
        cout << "Invalid Blockade Order: " << *blockadeOrder->Name << endl;
    }
}

int main() {
    testOrderExecution();
    return 0;
}
