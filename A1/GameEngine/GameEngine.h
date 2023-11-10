#ifndef A1_335_P5_GAMEENGINE_H
#define A1_335_P5_GAMEENGINE_H


#include <map>
#include <string>
#include "../Map/Map.h"
#include "../Player/Player.h"

enum State {
    start,
    map_loaded,
    map_validated,
    players_added,
    assign_reinforcement,
    issue_orders,
    execute_orders,
    win,
    end,
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

class GameEngine {
    public:
        GameEngine(); // Constructor
        GameEngine(const GameEngine& other); // Copy constructor
        GameEngine& operator=(const GameEngine& other); // Assignment operator
        // Validates the input if it corresponds to a state's edge, then triggers the transition
        void processInput(const std::string& input);
        // Getter for currentState
        State* getCurrentState();
        static std::string stateToString(State state);
        friend std::ostream& operator<<(std::ostream& os, const GameEngine& engine); // Stream insertion operator

        void sartupPhase(std::string validateOrGamestart);
        void startupPhase(std::string loadmapOrAddplayer, std::string playernameOrFilename);

        void reinforcementPhase();
        Map* gameEngineMap;

        vector<Player*> players;
        void issueOrderPhase();
        bool executeOrdersPhase();
        void mainGameLoop(GameEngine* game);
    private:
        // Instance variable holding the game's current state
        State* currentState;
        // Represents the edges of a state
        std::map<State, std::map<std::string, State>>* stateTransitions;
        // Triggers the transition to 'state'
        void transitionTo(State* state);
};

#endif //A1_335_P5_GAMEENGINE_H
