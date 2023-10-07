#include "Player.h"
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