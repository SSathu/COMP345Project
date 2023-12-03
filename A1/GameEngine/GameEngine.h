#pragma once
#include <map>
#include <string>
#include "../CommandProcessing/CommandProcessing.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../LogObserver/LoggingObserver.h"

class CommandProcessor;
class Command;

enum State {
    START,
    MAP_LOADED,
    MAP_VALIDATED,
    PLAYERS_ADDED,
    ASSIGN_REINFORCEMENTS,
    ISSUE_ORDERS,
    EXECUTE_ORDERS,
    WIN,
    END,
};

//Array of strings used to convert State to String
static const std::string stateStrings[] = {
    "Start",
    "Map Loaded",
    "Map Validated",
    "Players Added",
    "Assign Reinforcement",
    "Issue Orders",
    "Execute Orders",
    "Win",
    "End"
};

class GameEngine : public Subject, ILoggable {
public:
    GameEngine(); // Constructor
    GameEngine(State* initialState); // Constructor
    GameEngine(const GameEngine& other); // Copy constructor
    GameEngine& operator=(const GameEngine& other); // Assignment operator
    // Process the input and triggers the transition
    void processInput(const std::string& input);
    // Validates the input if it corresponds to a state's edge
    bool validateInput(const std::string& input);
    // Getter for currentState
    State* getCurrentState();
    static std::string stateToString(State state);
    friend std::ostream& operator<<(std::ostream& os, const GameEngine& engine); // Stream insertion operator

    void startupPhase();

    Map* gameEngineMap;
    vector<Player*>* players;
    void reinforcementPhase();
    void issueOrderPhase();
    bool executeOrdersPhase();
    void mainGameLoop(GameEngine* game);
    void mainGameLoop(GameEngine* game, int turns);

    string* stringToLog();

private:
    CommandProcessor* commandProcessor;
    // Instance variable holding the game's current state
    State* currentState;
    // Represents the edges of a state
    std::map<State, std::map<std::string, State>>* stateTransitions;
    // Triggers the transition to 'state'
    void transitionTo(State* state);
    // Executes the command and returns its effect
    string* executeCommand(Command* command);

    // Methods in startup phase
    string* loadMap(string mapName);
    string* validateMap();
    string* addPlayer(string* playerName);
    string* gameStart();

};
