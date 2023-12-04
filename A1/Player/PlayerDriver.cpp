

#include "Player.h"
#include <iostream>
#include "../Map/Map.h"

void testPlayers() {
    // Create variables to store name, territories, cards and orders
    vector<Territory*>* territory = {};
    vector<Territory*>* territory2 = {};
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

int main(){
testPlayers();
return 0;
}
