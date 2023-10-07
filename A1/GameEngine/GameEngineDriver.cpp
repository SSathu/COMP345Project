#include <iostream>
#include "GameEngine.h"

void testGameStates() {
    // Instance of GameEngine
    GameEngine gameEngine;
    // Variable holding the user's input, expecting a transition
    std::string input;
    // Loop asking the user to prompt a transition until they exit the program
    while (true) {
        // Checks if the game is ended
        if(*gameEngine.getCurrentState() == State::end){
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


