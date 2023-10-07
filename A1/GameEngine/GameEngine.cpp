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

