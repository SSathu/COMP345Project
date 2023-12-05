#include <iostream>
#include <map>
#include <string>
#include "GameEngine.h"
#include "../Utils/GameUtils.h"
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;

TournamentController::TournamentController(vector<string> maps, vector<std::string> playerStrategies, int gameCount,
                                           int turnCount, GameEngine *engine) {
    this->maps = maps;
    this->playerStrategies = playerStrategies;
    // Initialize results
    results.emplace_back();
    this->maxGameCount = gameCount;
    this->maxTurnCount = turnCount;
    this->engine = engine;
}

TournamentController::TournamentController(const TournamentController &th) {
    this->maps = th.maps;
    this->playerStrategies = th.playerStrategies;
    this->maxGameCount = th.maxGameCount;
    this->maxTurnCount = th.maxTurnCount;
    this->engine = th.engine;
    this->results = th.results;
}

TournamentController &TournamentController::operator=(const TournamentController &th) {
    if (this == &th) {
        return *this;
    }
    this->maps = th.maps;
    this->playerStrategies = th.playerStrategies;
    this->maxGameCount = th.maxGameCount;
    this->maxTurnCount = th.maxTurnCount;
    this->engine = th.engine;
    return *this;
}

TournamentController::~TournamentController() {
    delete engine;
}

// TournamentController methods
ostream &operator<<(ostream &out, const TournamentController &g) {
    out << "TournamentController: " << endl;
    // Print size of maps
    out << "Map Count: " << g.maps.size() << endl;

    out << "Player Strategies: " << endl;
    for (auto & playerStrategy : g.playerStrategies) {
        out << playerStrategy << endl;
    }

    out << "Game Count: " << g.maxGameCount << endl;
    out << "Turn Count: " << g.maxTurnCount << endl;
    return out;
}



bool TournamentController::canTurnBePlayed() {
    cout << "turn: " << engine->nbTurns << endl;
    if(engine->nbTurns < this->maxTurnCount){
        return true;
    }else{
        cout << "Max number of turns reached. Game: (" << this->gameIndex << ") finished in a draw." << endl;
        results[this->mapIndex].emplace_back("Draw");
        engine->transitionTo(new State(State::WIN));
        return false;
    }
}

void TournamentController::printResults() {
    std::ostringstream output;
    output << endl;

    output << "Tournament mode:" << endl;
    output << "M: ";
    // for loop through maps => M: <Map1>, <Map2>, <Map3> (remove last comma)
    for (size_t i = 0; i < maps.size(); ++i) {
        output << maps[i];
        if (i < maps.size() - 1) {
            output << ", ";
        }
    }
    output << endl << "P: ";
    // for loop through playerStrategies => P: <Player1>, <Player2>, <Player3> (remove last comma)
    for (size_t i = 0; i < playerStrategies.size(); ++i) {
        output << playerStrategies[i];
        if (i < playerStrategies.size() - 1) {
            output << ", ";
        }
    }

    output << endl << "G: " << maxGameCount << endl;
    output << "D: " << maxTurnCount << endl << endl << endl;

    output << "Results:" << endl;
    // rows and columns
    size_t numRows = maps.size() + 1;
    size_t numCols = static_cast<size_t>(maxGameCount) + 1;

    const int cellWidth = 10;

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (i == 0 && j == 0) {
                output << std::setw(cellWidth - 1) << " ";
            } else if (i == 0) {
                output << std::setw(cellWidth - 3) << "Game " << j;
            } else if (j == 0) {
                output << std::setw(cellWidth - 2) << "Map " << i;
            } else {
                output << std::setw(cellWidth - 2) << results[i - 1][j - 1];
            }

            // Print vertical divider except
            if (j < numCols - 1) {
                output << " | ";
            }
        }

        output << std::endl;

        // Print horizontal divider
        if (i < numRows - 1) {
            for (size_t j = 0; j < numCols; ++j) {
                output << std::string(cellWidth, '-') << "+";
            }
            output << std::endl;
        }
    }

    Command command = Command();
    auto* log = new LogObserver();
    command.Attach(log);
    command.saveEffect(new string(output.str()));

    // Print the table to the console
    std::cout << output.str();

}

void TournamentController::processCurrentState() {
    switch(*(engine->getCurrentState())){
        case State::START:
            loadMap(mapIndex);
            engine->validateMap();
            loadPlayers();
            engine->startGame();
            break;
        case State::WIN:
            if(engine->players->size() == 1){
                results[this->mapIndex].push_back(engine->players->at(0)->getName());
            }
            gameIndex++;
            if(gameIndex == maxGameCount){
                mapIndex++;
                gameIndex = 0;

                if(mapIndex == maps.size()){
                    cout << "Tournament finished!" << endl;
                    cout << "Printing results..." << endl;
                    printResults();

                    engine->tournamentController = nullptr;
                    delete this;
                    return;
                }
                results.emplace_back();
            }
            engine->transitionTo(new State(State::START));
            engine->resetGame();
            loadMap(mapIndex);
            engine->validateMap();
            loadPlayers();
            engine->startGame();
            break;
        default:
            break;
    }
}

void TournamentController::loadMap(int index) {
    cout << "Loading map file: " << maps[index] << " ..." << endl;
    engine->loadMap(maps[index]);
}

void TournamentController::loadPlayers() {
    cout << "Adding players..." << endl;
    for (auto& playerStrategy : playerStrategies) {
        if("Aggressive") {
            engine->addPlayer(new string(playerStrategy), new AggressivePlayerStrategy());
        }
        else if("Benevolent") {
            engine->addPlayer(new string(playerStrategy), new BenevolentPlayerStrategy());
        }
        else if("Neutral") {
            engine->addPlayer(new string(playerStrategy), new NeutralPlayerStrategy());
        }
        else if("Cheater") {
            engine->addPlayer(new string(playerStrategy), new CheaterPlayerStrategy());
        }
        else if("Human") {
            engine->addPlayer(new string(playerStrategy), new HumanPlayerStrategy());
        }
    }
}

// Function to initialize the stateTransition map
void initializeStateTransition(std::map<State, std::map<std::string, State>>* stateTransitions) {
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
    players = new vector<Player*>();
    nbTurns = 0;
    initializeStateTransition(stateTransitions);
}

GameEngine::GameEngine(State* initialState) : currentState(initialState) {
    stateTransitions = new std::map<State, std::map<std::string, State>>();
    players = new vector<Player*>();
    nbTurns = 0;
    initializeStateTransition(stateTransitions);
}

// Copy constructor
GameEngine::GameEngine(const GameEngine& other) {
    currentState = other.currentState;
    stateTransitions = other.stateTransitions;
    commandProcessor = other.commandProcessor;
    gameEngineMap = other.gameEngineMap;
    players = other.players;
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
    nbTurns = other.nbTurns;
    return *this;
}

// Triggers the transition
void GameEngine::transitionTo(State* state) {
    currentState = state;
    std::cout << "State transitioned to: " << stateToString(*state) << std::endl;
    Notify(this);
}

string* GameEngine::stringToLog()
{
    return new string("State transitioned to: " + stateToString(*currentState));
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

bool GameEngine::validateInput(const std::string& input) {
    return (*stateTransitions)[*currentState].find(input) != (*stateTransitions)[*currentState].end();
}

// Stream insertion operator, returning the game's state
std::ostream& operator<<(std::ostream& os, const GameEngine& engine) {
    os << "Game's current state: " << GameEngine::stateToString(*engine.currentState);
    return os;
}

// Startup Phase methods implementation
void GameEngine::startupPhase() {
    cout << "Startup Phase..." << endl << endl;

    cout << "write '-console' to read from console" << endl;
    cout << "write '-file <filename>' to read from file" << endl;
    cout << "write '-tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>' to start a tournament" << endl;

    string input;
    cout << "Enter command:";
    getline(cin, input);

    // Tokenize input
    std::vector<std::string> inputTokens = splitString(input);
    std::string firstArgument = inputTokens.at(0);

    if (firstArgument == "-console") {
        commandProcessor = new CommandProcessor();
        cout << "Chose to input commands via console..." << endl;
    }
    else if (firstArgument == "-file") {
        commandProcessor = new FileCommandProcessorAdapter();
        // Downcast commandProcessor to FileCommandProcessorAdapter to call readLineFromFile
        auto* fileCommandProcessor = dynamic_cast<FileCommandProcessorAdapter*>(commandProcessor);
        fileCommandProcessor->getFileLineReader()->readLineFromFile(inputTokens.at(1));
        if(fileCommandProcessor->getFileLineReader()->getLines()->empty()) startupPhase();
    }
    else if(firstArgument == "-tournament"){
        commandProcessor = new CommandProcessor();
        if(commandProcessor->validateTournamentCommand(inputTokens)){
            // Check if the tournament has been created successfully
            if(!createTournament(inputTokens))
                startupPhase();
            this->tournamentController->processCurrentState();
            return;
        }
        else{
            cout << "Invalid tournament command. Please try again." << endl;
            startupPhase();
        }
    }
    else {
        cout << "Invalid command. Please try again." << endl;
        startupPhase();
    }
    // While the currentState is not ASSIGN_REINFORCEMENTS
    while (*currentState != State::ASSIGN_REINFORCEMENTS) {
        Command* command = commandProcessor->getCommand(*this);
        string* effect = executeCommand(command);
        command->saveEffect(effect);
    }

    // Print all commands
    cout << endl << "Printing entered commands..." << endl;
    cout << *commandProcessor;

    // Switch to play phase
    startGame();
}

bool GameEngine::createTournament(vector<string> inputTokens) {
    int maxTokens = inputTokens.size();
    // Index = 1 since we have already processed -tournament and skip -M
    int index = 2;

    // tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>
    // -M <listofmapfiles>
    vector<string> mapFiles;
    MapLoader mapDriver = MapLoader();
    while (index < maxTokens && inputTokens.at(index) != "-P") {
        Map* map = new Map();
        bool isMapCreated = mapDriver.createMapFromFile(inputTokens.at(index), map);
        if(isMapCreated && map->validate()){
            mapFiles.push_back(inputTokens.at(index));
        }
        else{
            cout << "Map " << inputTokens.at(index) << " is invalid." << endl;
            return false;
        }
        index++;
    }

    // skip -P
    index++;

    // -P <listofplayerstrategies>
    vector<string> playerStrategies;
    while (index < maxTokens && inputTokens.at(index) != "-G") {
        playerStrategies.push_back(inputTokens.at(index));
        index++;
    }

    // skip -G
    index++;

    // -G <numberofgames>
    int gameCount = stoi(inputTokens.at(index));

    // skip -D
    index++;
    index++;

    int turnCount = stoi(inputTokens.at(index));

    auto* controller = new TournamentController(mapFiles, playerStrategies, gameCount, turnCount, this);
    this->tournamentController = controller;

    cout << *controller << endl;

    return true;

}

string* GameEngine::executeCommand(Command* command) {
    try {
        string* effect;
        vector<string> commandTokens = splitString(*command->getCommand());
        string firstArgument = commandTokens.at(0);

        if (firstArgument == "loadmap")
            effect = loadMap(commandTokens.at(1));
        else if (firstArgument == "validatemap")
            effect = validateMap();
        else if (firstArgument == "addplayer")
            effect = addPlayer(new string(commandTokens.at(1)));
        else if (firstArgument == "gamestart")
            effect = gameStart();
        else {
            // Handle unknown command
            effect = new string("Unknown command: " + *command->getCommand());
        }

        return effect;
    } catch (const std::out_of_range& e) {
        // Handle out-of-range exception (e.g., insufficient arguments)
        return new string("Caught Error: Command has insufficient arguments.");
    } catch (const std::exception& e) {
        // Handle other exceptions
        return new string("Caught Error: " + string(e.what()));
    }
}

string* GameEngine::loadMap(string mapName) {
    string* effect;
    MapLoader mapDriver = MapLoader();
    gameEngineMap = new Map();
    bool loaded = mapDriver.createMapFromFile(mapName, gameEngineMap);
    if (loaded) {
        cout << "Successful creation of a map from " << mapName << endl;
        effect = new string("Successful creation of a map from " + mapName);
        processInput("loadmap");
    }
    else {
        cout << "Unsuccessful creation of a map from " << mapName << endl;
        effect = new string("Unsuccessful creation of a map from " + mapName);
    }
    return effect;
}

string* GameEngine::addPlayer(std::string* playerName) {
    string* effect;
    cout << "Current Players: " << players->size() << endl;

    if (players->size() >= 6) {
        cout << "Limit players reached (Max: 6)." << endl;
        effect = new string("Failed. Exceeded the maximum number of players (Max: 6).");
        return effect;
    }

    // Create and add player
    auto* player = new Player();
    player->setName(*playerName);
    players->push_back(player);

    // Effect
    cout << "Player " << *playerName << " added." << endl << endl;
    effect = new string("Player " + *playerName + " added.");

    // Print players
    cout << "Current Players: " << endl;
    for (auto& p : *players) {
        cout << " - " << p->getName() << " " << endl;
    }
    cout << endl;

    processInput("addplayer");
    return effect;
}

string* GameEngine::addPlayer(std::string *playerName, PlayerStrategy *strategy) {
    string* effect;
    cout << "Current Players: " << players->size() << endl;

    if (players->size() >= 6) {
        cout << "Limit players reached (Max: 6)." << endl;
        effect = new string("Failed. Exceeded the maximum number of players (Max: 6).");
        return effect;
    }

    // Create and add player
    auto* player = new Player();
    player->setName(*playerName);
    player->setStrategy(strategy);
    players->push_back(player);

    // Effect
    cout << "Player " << *playerName << " added." << endl << endl;
    effect = new string("Player " + *playerName + " added.");

    // Print players
    cout << "Current Players: " << endl;
    for (auto& p : *players) {
        cout << " - " << p->getName() << " " << endl;
    }
    cout << endl;

    processInput("addplayer");
    return effect;
}

string* GameEngine::validateMap() {
    string* effect;
    if (gameEngineMap->validate()) {
        cout << "Map is valid!" << endl;
        effect = new string("Map has been validated.");
        processInput("validatemap");
    }
    else {
        cout << "Map is invalid!" << endl;
        effect = new string("Map is invalid!");
    }
    return effect;
}

string* GameEngine::gameStart() {
    // 1) distribute territories to players
    string* effect;
    if (players->size() < 2) {
        cout << "Not enough players to start the game (Min: 2)." << endl;
        effect = new string("Cannot start the game. Not enough players to start the game.");
        return effect;
    }
    for (int i = 0; i < gameEngineMap->territories->size() - (gameEngineMap->territories->size() % players->size()); ++i) {
        (*players)[(i / (gameEngineMap->territories->size() / players->size()))]->territory->push_back(gameEngineMap->territories->at(i));
    }
    for (int i = 0; i < (gameEngineMap->territories->size() % players->size()); ++i) {
        (*players)[i]->territory->push_back(gameEngineMap->territories->at((gameEngineMap->territories->size() - (gameEngineMap->territories->size() % players->size())) + i));
    }
    cout << endl;

    // 2) randomly determine order of players
    cout << "New order of player turns:" << endl;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();


    std::shuffle(players->begin(), players->end(), std::default_random_engine(seed));

    for (auto& player : *players) {
        cout << " - " << player->getName() << endl;
    }
    cout << endl;

    // 3) give 50 armies to each as reinforcements
    for (int i = 0; i < players->size(); ++i) {
        (*players)[i]->reinforcementPool = 50;
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

    for (int i = 0; i < players->size(); ++i) {
        (*players)[i]->deck = deck;
        cout << "Player " << i + 1 << " drawing..." << endl;
        (*players)[i]->hand = new Hand();
        deck->draw((*players)[i]->hand);
        deck->draw((*players)[i]->hand);
        cout << "Cards in " << (*players)[i]->getName() << "'s Hand: \n";
        cout << (*players)[i]->hand;
    }
    cout << endl;

    cout << "Game started!" << endl;
    effect = new string("Play phase started.");
    processInput("gamestart");

    return effect;
}

void GameEngine::startGame() {
    gameStart();
    cout << "Starting game..." << endl;
    cout << "Current State: " << stateToString(*currentState) << endl;
    mainGameLoop();
}

void GameEngine::resetGame() {
    // Clear map
    delete gameEngineMap;
    gameEngineMap = nullptr;

    // Clear players
    for (auto& player : *players) {
        delete player;
    }
    players->clear();

    // Reset turn counter
    nbTurns = 0;
}

void GameEngine::reinforcementPhase() {
    // min reinforecement
    int min = 3;
    int reinforecement = 0;
    // calculate number of armies
    for (Player* player : *players) {
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
    processInput("issueorder");
}

void GameEngine::issueOrderPhase() {
    int index = 0;
    for (int i = 0; i < players->size(); ++i) {

        Player* currentPlayer = (*players)[index];


        if (!currentPlayer->orderList->empty()) {
            currentPlayer->issueOrder();
        }
        // Move to the next player in a round-robin fashion
        index = (index + 1) % players->size();
    }
    processInput("endissueorders");
}

bool GameEngine::executeOrdersPhase() {
    // Execute other orders in a round-robin fashion
    bool continueGame = true;
    while (continueGame) {
        for (Player* player : *players) {
            if (!player->orderList->empty()) {
                player->executeTopOrder();
                continueGame = true;
            }
            else {
                continueGame = false;
            }
        }
    }

    // Check for player elimination and game termination
    auto iterator = players->begin();
    while (iterator != players->end()) {
        if ((*iterator)->territory->size() == 0) {
            std::cout << "Player " << (*iterator)->getName() << " has been eliminated from the game." << std::endl;
            delete* iterator;
            iterator = players->erase(iterator);
        }
        else ++iterator;
    }

    processInput("endexecorders");

    return true;
}

void GameEngine::mainGameLoop() {
    bool restart = false;
    while (currentState != new State(State::WIN)) {
        if (tournamentController && !tournamentController->canTurnBePlayed()){
            restart = true;
            break;
        }
        nbTurns++;
        switch(*currentState) {
            case State::ASSIGN_REINFORCEMENTS:
                reinforcementPhase();
                break;
            case State::ISSUE_ORDERS:
                issueOrderPhase();
                break;
            case State::EXECUTE_ORDERS:
                executeOrdersPhase();
                break;
            default:
                break;
        }
        checkForLosers();
        checkForWinner();
    }
    if(restart)
        this->tournamentController->processCurrentState();
}

void GameEngine::checkForLosers() {
    for (auto& player : *players) {
        if (player->territory->empty()) {
            cout << "Player " << player->getName() << " has been eliminated from the game." << endl;
            // Remove player from vector
            players->erase(std::remove(players->begin(), players->end(), player), players->end());
            delete player;
        }
    }
}

void GameEngine::checkForWinner() {
    if(players->size() != 1)
        return;

    Player* last = (*players)[0];

    // last player must own all territories
    if(last->territory->size() != gameEngineMap->territories->size())
        return;

    cout << "Player " << last->getName() << " has won the game!" << endl;
    this->transitionTo(new State(State::WIN));
}
