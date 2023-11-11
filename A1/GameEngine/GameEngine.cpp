#include <iostream>
#include <map>
#include <string>
#include "GameEngine.h"
#include "../Utils/GameUtils.h"
#include "../CommandProcessing/CommandProcessing.h"
using namespace std;

// Function to initialize the stateTransition map
void initializeStateTransition(std::map<State, std::map<std::string, State>>* stateTransitions){
    (*stateTransitions)[State::START]["loadmap"] = State::MAP_LOADED;
    (*stateTransitions)[State::MAP_LOADED]["loadmap"] = State::MAP_LOADED;
    (*stateTransitions)[State::MAP_LOADED]["validatemap"] = State::MAP_VALIDATED;
    (*stateTransitions)[State::MAP_VALIDATED]["addplayer"] = State::PLAYERS_ADDED;
    (*stateTransitions)[State::PLAYERS_ADDED]["addplayer"] = State::PLAYERS_ADDED;
    (*stateTransitions)[State::PLAYERS_ADDED]["gamestart"] = State::ASSIGN_REINFORCEMENTS;
    (*stateTransitions)[State::ASSIGN_REINFORCEMENTS]["issueorder"] = State::ISSUE_ORDERS;
    (*stateTransitions)[State::ISSUE_ORDERS]["issueorder"] = State::ISSUE_ORDERS;
    (*stateTransitions)[State::ISSUE_ORDERS]["endissueorders"] = State::EXECUTE_ORDERS;
    (*stateTransitions)[State::EXECUTE_ORDERS]["endexecorders"] = State::ASSIGN_REINFORCEMENTS;
    (*stateTransitions)[State::EXECUTE_ORDERS]["execorder"] = State::EXECUTE_ORDERS;
    (*stateTransitions)[State::EXECUTE_ORDERS]["WIN"] = State::WIN;
    (*stateTransitions)[State::WIN]["quit"] = State::END;
    (*stateTransitions)[State::WIN]["replay"] = State::START;
}


// Constructor that initializes all transistions and currentState to Start
GameEngine::GameEngine() : currentState(new State(State::START)) {
    // Initialize stateTransitions
    stateTransitions = new std::map<State, std::map<std::string, State>>();
    initializeStateTransition(stateTransitions);
}

GameEngine::GameEngine(State *initialState) : currentState(initialState){
    stateTransitions = new std::map<State, std::map<std::string, State>>();
    initializeStateTransition(stateTransitions);
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
    if (validateInput(input))
        transitionTo(&(*stateTransitions)[*currentState][input]);
    else {
        std::cout << "No transitions found given: " << input << std::endl;
    }
}

bool GameEngine::validateInput(const std::string &input) {
    return (*stateTransitions)[*currentState].find(input) != (*stateTransitions)[*currentState].end();
}

// Stream insertion operator, returning the game's state
std::ostream &operator<<(std::ostream &os, const GameEngine &engine) {
    os << "Game's current state: " << GameEngine::stateToString(*engine.currentState);
    return os;
}

void GameEngine::startupPhase() {
    cout << "Startup Phase" << endl << endl;

    cout << "write '-console' to read from console" << endl;
    cout << "write '-file <filename>' to read from file" << endl;

    string input;
    cout << "Enter command: ";
    getline(cin, input);

    // Tokenize input
    std::vector<std::string> inputTokens = splitString(input);
    std::string firstArgument = inputTokens.at(0);

    if(firstArgument == "-console"){
        commandProcessor = new CommandProcessor();

        // While the currentState is not ASSIGN_REINFORCEMENTS
        while(*currentState != State::ASSIGN_REINFORCEMENTS){
            Command* command = commandProcessor->getCommand(*this);

        }
    }
    else{

    }


}

string* GameEngine::executeCommand(Command* command) {
    vector<string> commandTokens = splitString(*command->getCommand());
    string* effect;

    return nullptr;
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

void GameEngine::reinforcementPhase() {
    // min reinforecement
    int min = 3;
    int reinforecement = 0;
    // calculate number of armies
    for (Player* player : players) {
        int totalOwned = player->territory->size();
        int tempt = totalOwned;
        reinforecement = max(min, totalOwned / 3);

        // calculate bonus
        while (tempt != 0) {
            reinforecement += 2;
            tempt--;
        }

        int currentReinforcementPool = player->getReinforcementPool();
        player->setReinforcementPool(currentReinforcementPool + reinforecement);

    }
}

void GameEngine::issueOrderPhase() {
    int index = 0;
    for(int i = 0; i < players.size(); ++i){

        Player* currentPlayer = players[index];


        if (!currentPlayer->orderList.empty()) {
            currentPlayer->issueOrder();
        }
        // Move to the next player in a round-robin fashion
        index = (index + 1) % players.size();
    }

}

bool GameEngine::executeOrdersPhase() {
    // Execute other orders in a round-robin fashion
    bool continueGame = true;
    while (continueGame) {

        for (Player* player : players) {

            if (!player->orderList.empty()) {
                player->executeTopOrder();
                continueGame = true;
            }
            else {
                continueGame = false;
            }
        }
    }

    // Check for player elimination and game termination
    vector<Player*>::iterator iterator = players.begin();
    while (iterator != players.end()) {
        if ((*iterator)->territory->size() == 0) {
            std::cout << "Player " << (*iterator)->getName() << " has been eliminated from the game." << std::endl;
            delete* iterator;
            iterator = players.erase(iterator);
        }

        else {
            ++iterator;
        }
    }
}

void GameEngine::mainGameLoop(GameEngine *game) {
    while (true) {
        if (game->players.size() > 1) {
            reinforcementPhase();
            issueOrderPhase();
            executeOrdersPhase();
        }
        else {
            break;
        }



    }
}