//imports
#include <iostream>
#include "../GameEngine/GameEngine.h"
#include <string>
#include "../Utils/GameUtils.h"
#include <random>

void testTournament();



void testTournament2() {
    GameEngine gameEngine;

    gameEngine.startupPhase();
}

//void testTournament() {
//    // Instance of GameEngine
//    GameEngine gameEngine;
//    gameEngine.gameEngineMap = 0;
//    int mapCount;
//    int playerStrategyCount;
//    int gameCount;
//    int turnCount;
//
//    //Get all the inputs
//    string input = "";
//    vector<string> players;
//    while (true) {
//        std::cout
//                << "Please type \"tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>\" to begin:"
//                << std::endl;
//        std::getline(std::cin, input);
//        //split input
//        std::istringstream iss(input);
//        std::string token;
//        std::vector<std::string> tokens;
//
//        while (std::getline(iss, token, '-')) {
//            tokens.push_back(token);
//        }
//
//        //manage the int inputs
//        mapCount = stoi(tokens[1].substr(2, 1));
//
//        gameCount = stoi(tokens[3].substr(2, 1));
//        turnCount = stoi(tokens[4].substr(2));
//
//        //manage the players
//        string playersInput = tokens[2].substr(2, tokens[2].length() - 3);
//        vector<string> tempPlayers;
//        std::istringstream iss2(playersInput);
//        while (std::getline(iss2, token, ',')) {
//            tempPlayers.push_back(token);
//            cout << token << endl;
//        }
//        players = tempPlayers;
//        playerStrategyCount = players.size();
//
//        if (mapCount < 1 || playerStrategyCount < 2 || gameCount < 1 || turnCount < 10
//        || mapCount > 5 || playerStrategyCount > 4 || gameCount > 5 || turnCount > 50)
//            continue;
//        else
//            break;
//    }
//    /*
//     * Turn all inputs into commands (aka add players into system)
//     */
//    vector<string> gameResults(gameCount * mapCount);
//
//    //List of maps
//    vector<string> maps = {"Texas.map",
//                           "Roman Empire.map",
//                           "Texas - 2.map",
//                           "Roman Empire - 2.map",
//                           "Texas - 3.map"};
//
//    //Simulate the games
//    for (int i = 0; i < mapCount; ++i) { //each map is a row
//        //load the map at index i in the ../Map/MapFiles folder
//        gameEngine.loadMap(maps[i]);
//        gameEngine.validateMap();
//
//        for (int j = 0; j < gameCount; ++j) {
//
//            //add all the players using commandProcessing
//            for (int i = 0; i < playerStrategyCount; ++i) {
//                string* playerName = new string("Player" + to_string(i + 1) + "(" + players[i] + ")");
//                gameEngine.addPlayer(playerName);
//            }
//
//
//
//            gameEngine.mainGameLoop(&gameEngine, turnCount);
//
//            /*
//             * TODO: you need to implement some way to catalog the result of the game into gameResults[]
//             *
//             */
//
//            //somehow reset game progress so you can begin again
//            gameEngine.players->clear();
//            gameEngine.processInput("replay");
//        }
//    }
//
//    //Output
//    cout << endl;
//    cout << "Tournament Mode:" << endl;
//    //print the list of maps based on the amount of maps
//    cout << "M: ";
//    for (int i = 0; i < mapCount; ++i) {
//        cout << maps[i] << ", ";
//    }
//    cout << endl;
//    //print the list of player strategies used
//    cout << "P: ";
//    for (int i = 0; i < playerStrategyCount; ++i) {
//        cout << players[i] << ", ";
//    }
//    cout << endl;
//    //print the other 2
//    cout << "G: " << gameCount << endl;
//    cout << "D: " << turnCount << endl;
//
//    //print out the table of victories
//    cout << "|          |";
//    for (int i = 1; i <= gameCount; ++i) {
//        cout << "Game " + to_string(i) + "    |";
//    }
//    for (int i = 0; i < mapCount; ++i) {
//        cout << endl;
//        cout << "------------";
//        for (int j = 0; j < gameCount; ++j) {
//            cout << "-----------";
//        }
//        cout << endl;
//        cout << "|Map " + to_string(i) + "     |";
//        for (int j = 0; j < gameCount; ++j) {
//            cout << gameResults[j + gameCount * i] + "|";
//        }
//    }
//}

int main(){
    testTournament2();
    return 0;
}