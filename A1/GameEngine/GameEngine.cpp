#include <iostream>
#include "GameEngine.h"

// Constructor that initializes all transistions and currentState to Start
GameEngine::GameEngine() : currentState(new State(State::start)) {
    // Initialize stateTransitions
    stateTransitions = new std::map<State, std::map<std::string, State>>();
    (*stateTransitions)[State::start]["loadmap"] = State::map_loaded;
    (*stateTransitions)[State::map_loaded]["loadmap"] = State::map_loaded;
    (*stateTransitions)[State::map_loaded]["validatemap"] = State::map_validated;
    (*stateTransitions)[State::map_validated]["addplayer"] = State::players_added;
    (*stateTransitions)[State::players_added]["addplayer"] = State::players_added;
    (*stateTransitions)[State::players_added]["assigncountries"] = State::assign_reinforcement;
    (*stateTransitions)[State::assign_reinforcement]["issueorder"] = State::issue_orders;
    (*stateTransitions)[State::issue_orders]["issueorder"] = State::issue_orders;
    (*stateTransitions)[State::issue_orders]["endissueorders"] = State::execute_orders;
    (*stateTransitions)[State::execute_orders]["endexecorders"] = State::assign_reinforcement;
    (*stateTransitions)[State::execute_orders]["execorder"] = State::execute_orders;
    (*stateTransitions)[State::execute_orders]["win"] = State::win;
    (*stateTransitions)[State::win]["end"] = State::end;
    (*stateTransitions)[State::win]["play"] = State::start;
}

// Copy constructor
GameEngine::GameEngine(const GameEngine& other) {
    currentState = other.currentState;
    stateTransitions = other.stateTransitions;
}

// Assignment operator
GameEngine& GameEngine::operator=(const GameEngine& other) {
    // Checks if the two objects are equal, no need for further operations
    if (this == &other) {
        return *this;
    }
    // Assigning variables
    currentState = other.currentState;
    stateTransitions = other.stateTransitions;
    return *this;
}

// Triggers the transition
void GameEngine::transitionTo(State* state) {
    currentState = state;
    std::cout << "State transitioned to: " << stateToString(*state) << std::endl;
}

// ToString method for States
std::string GameEngine::stateToString(State state) {
    return stateStrings[static_cast<int>(state)];
}

// Getter for currentState
State* GameEngine::getCurrentState() {
    return currentState;
}

// Validates the input if it corresponds to a state's edge, then triggers the transition
void GameEngine::processInput(const std::string& input) {
    if ((*stateTransitions)[*currentState].find(input) != (*stateTransitions)[*currentState].end()) {
        transitionTo(&(*stateTransitions)[*currentState][input]);
    } else {
        std::cout << "No transitions found given: " << input << std::endl;
    }
}

// Stream insertion operator, returning the game's state
std::ostream &operator<<(std::ostream &os, const GameEngine &engine) {
    os << "Game's current state: " << GameEngine::stateToString(*engine.currentState);
    return os;
}

//Startup Phase
void GameEngine::startupPhase(std::string loadmapOrAddplayer, std::string playernameOrFilename) {
    //If the command is loadmap
    if (loadmapOrAddplayer == "loadmap"){
        MapLoader mapDriver = MapLoader();
        gameEngineMap = new Map();
        bool loaded = mapDriver.createMapFromFile(playernameOrFilename, gameEngineMap);
        if (loaded) {
            cout << "Successful creation of a map from " << playernameOrFilename << endl;
            processInput("loadmap");
        }
        else {
            cout << "Unsuccessful creation of a map from " << playernameOrFilename << endl;
        }
    }

    //Else, the command must be addplayer
    else {
        Player* tempPlayer = new Player();
        tempPlayer->setName(playernameOrFilename);
        players.push_back(tempPlayer);
        cout << "New list of players:" << endl;
        for (int i = 0; i < players.size(); ++i) {
            cout << " - " << players[i]->getName() << endl;
        }
        processInput("addplayer");
    }
}
void GameEngine::startupPhase(std::string validateOrGamestart) {
    //If the command is validatemap
    if (validateOrGamestart == "validatemap") {
        //Simply reuse the code from MapDriver
        if (gameEngineMap->validate()) {
            cout << "Map is valid!" << endl;
            processInput("validatemap");
        }
        else {
            cout << "Map is invalid!" << endl;
        }
    }

    //Else, the command must be gamestart
    else {
        // 1) distribute all territories to all players
        for (int i = 0; i < gameEngineMap->territories->size() - (gameEngineMap->territories->size() % players.size()); ++i) {
            players[(i / (gameEngineMap->territories->size() / players.size()))]->territory->push_back(gameEngineMap->territories->at(i));
        }
        for (int i = 0; i < (gameEngineMap->territories->size() % players.size()); ++i) {
            players[i]->territory->push_back(gameEngineMap->territories->at((gameEngineMap->territories->size() - (gameEngineMap->territories->size() % players.size())) + i));
        }
        processInput("assigncountries");
        cout << endl;

        // 2) randomly determine order of players
        cout << "New order of player turns:" << endl;
        std::random_shuffle(players.begin(), players.end());
        for (int i = 0; i < players.size(); ++i) {
            cout << " - " << players[i]->getName() << endl;
        }
        cout << endl;

        // 3) give 50 armies to each as reinforcements
        for (int i = 0; i < players.size(); ++i) {
            players[i]->reinforcementArmies = 50;
        }

        // 4) have each player draw() 2 cards
        cout << "Instantiating deck..." << endl;
        Card* card5 = new Card(5);
        Card* card2 = new Card(2);
        Card* card1 = new Card(1);
        Card* card3 = new Card(3);
        Card* card4 = new Card(4);
        Card* card05 = new Card(5);
        Card* card02 = new Card(2);
        Card* card01 = new Card(1);
        Card* card03 = new Card(3);
        Card* card04 = new Card(4);
        Card* card003 = new Card(3);
        Card* card004 = new Card(4);

        Deck* deck = new Deck();

        deck->insertCard(card1);
        deck->insertCard(card2);
        deck->insertCard(card3);
        deck->insertCard(card4);
        deck->insertCard(card5);
        deck->insertCard(card01);
        deck->insertCard(card02);
        deck->insertCard(card03);
        deck->insertCard(card04);
        deck->insertCard(card05);
        deck->insertCard(card003);
        deck->insertCard(card004);
        cout << "Deck complete! Cards in deck:" << endl;
        cout << *deck;
        cout << endl;

        for (int i = 0; i < players.size(); ++i) {
            cout << "Player " << i + 1 << " drawing..." << endl;
            players[i]->hand = new Hand();
            deck->draw(players[i]->hand);
            deck->draw(players[i]->hand);
            cout << "Cards in " << players[i]->getName() << "'s Hand: \n" ;
            cout << *players[i]->hand;
        }
        cout << endl;

        // 5) switch game state to "Play"
        cout << "Now in play phase!" << endl;
    }
}

