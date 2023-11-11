#include "Cards/Cards.h"
#include "Map/Map.h"
#include "Map/MapDriver.h"
#include "Orders/Orders.h"
#include "Player/Player.h"
#include "GameEngine/GameEngine.h"
#include <iostream>


void testPlayers() {
    // Create variables to store name, territories, cards and orders
    vector<string> territory = { "West Europe", "South Europe"};
    vector<string> territory2 = { "Great Britain", "North Europe" };
    vector<string> card = { "Order Priority", "Order Priority" };
    vector<PlayerOrder*> orderList = {};

    string name = "Anderson";
    string name2 = "Brian";

    // Create players
    Player player(name, territory, card, orderList);
    Player player2(name2, territory2, card, orderList);

    // Check if the program perform the implemented functions
    cout << "Test functions of first player: " << endl;
    // Display territories to be attacked and defended
    player.toDefend();
    player.toAttack();

    // Issue the orders
    player.issueOrder("Advance");
    player.issueOrder("Advance");

    cout << endl;
    cout << "Information of first player: " << endl;
    cout << player;


    cout << endl;
    cout << "Test functions of second player: " << endl;
    player2.toAttack();
    player2.toDefend();
    player2.issueOrder("Attack");
    player2.issueOrder("Advance");
    cout << endl;
    cout << "Information of second player: " << endl;
    cout << player2;
}
void testGameStates() {
    // Instance of GameEngine
    GameEngine gameEngine;
    // Variable holding the user's input, expecting a transition
    std::string input;
    // Loop asking the user to prompt a transition until they exit the program
    while (true) {
        // Checks if the game is ended
        if(*gameEngine.getCurrentState() == State::END){
            std::cout << "Thank you for playing!" << std::endl;
            break;
        }
        // Prompting the user
        std::cout << std::endl << gameEngine << std::endl;
        std::cout << "Enter a transition or type \"exit\" to terminate" << std::endl;
        std::cin >> input;

        // Exits the program if the user enters 'exit'
        if(input == "exit") break;

        // Calls game logic to handle the input and trigger a transition if it is valid
        gameEngine.processInput(input);
    }
}
void MapDriver::testLoadMaps() {
    MapLoader mapDriver = MapLoader();

    string mapFile1 = "/Map/MapFiles/Texas.map";
    string mapFile2 = "/Map/MapFiles/Roman Empire.map";

    Map* mapTest1 = new Map();
#pragma region Test1
    bool test1 = mapDriver.createMapFromFile(mapFile1, mapTest1);
    if (test1) {
        cout << "Successful creation of a map from " << mapFile1 << endl;
    }
    else {
        cout << "Unsuccessful creation of a map from " << mapFile1 << endl;
    }
    if (mapTest1->validate()) {
        cout << "Map from " << mapFile1 << " is valid!" << endl;
    }
    else {
        cout << "Map from " << mapFile1 << " is invalid!" << endl;
    }
    mapTest1->territories->clear();
    delete mapTest1;
#pragma endregion

    Map* mapTest2 = new Map();
#pragma region Test2
    bool test2 = mapDriver.createMapFromFile(mapFile2, mapTest2);
    if (test2) {
        cout << "Successful creation of a map from " << mapFile2 << endl;
    }
    else {
        cout << "Unsuccessful creation of a map from " << mapFile2 << endl;
    }
    if (mapTest2->validate()) {
        cout << "Map from " << mapFile2 << " is valid!" << endl;
    }
    else {
        cout << "Map from " << mapFile2 << " is invalid!" << endl;
    }
    mapTest2->territories->clear();
    delete mapTest2;
#pragma endregion
}
void testCards()
{
    Card* card5 = new Card(5);
    Card* card2 = new Card(2);
    Card* card1 = new Card(1);
    Card* card3 = new Card(3);
    Card* card4 = new Card(4);
    Card* card0 = new Card(1);

    Deck* deck = new Deck();
    Hand* hand = new Hand();

    deck->insertCard(card1);
    deck->insertCard(card2);
    deck->insertCard(card3);
    deck->insertCard(card4);
    deck->insertCard(card5);
    deck->insertCard(card0);
    cout << "Cards in Deck: \n";
    cout << *deck;
    cout << "Cards in Hand: \n";
    cout << *hand;


    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);



    cout << "Cards in Deck: \n";
    cout << *deck;
    cout << "Cards in Hand: \n" ;
    cout << *hand;

    hand->play(card1, deck);
    hand->play(card2, deck);
    hand->play(card3, deck);
    hand->play(card4, deck);
    hand->play(card5, deck);
    hand->play(card0, deck);

    cout << "Cards in Deck: \n";
    cout << *deck;
    cout << "Cards in Hand: \n";
    cout << *hand << "\n";
}
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

int main() {
//    testCards();
//    testGameStates();
//    MapDriver::testLoadMaps();
//    testOrdersLists();
//    testPlayers();
    return 0;
}
