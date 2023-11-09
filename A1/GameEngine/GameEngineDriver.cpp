#include <iostream>
#include "GameEngine.h"
#include "../Map/Map.h"
#include <string>
#include <vector>
#include <dirent.h>

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

void testStartupPhase(){
    // Instance of GameEngine
    GameEngine gameEngine;
    gameEngine.gameEngineMap = 0;

    //This part is just console UI
    std::string input;
    std::cout << "Welcome to the Startup Phase!" << std::endl;
    while (true) {
        cout << endl;
        std::cout << "Enter \"loadmap\", \"validatemap\", "
                     "\"addplayer\", or \"gamestart\" to run the commands."
                     " Enter \"exit\" if you want to quit out." << std::endl;
        std::cin >> input;
        if(input == "exit") break;

        //Reuse most of the functionality of the MapDriver, as this has already been done.
        else if (input == "loadmap"){
            std::cout << "Please select which map you would like to load:" << std::endl;
            std::string directory_path = "../Map/MapFiles";
            std::vector<std::string> files;

            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir(directory_path.c_str())) != NULL) {
                while ((ent = readdir(dir)) != NULL) {
                    if (ent->d_type == DT_REG) {
                        files.push_back(ent->d_name);
                    }
                }
                closedir(dir);
                for (int i = 0; i < files.size(); ++i) {
                    std::cout << "Enter " << i << " for \"" << files[i] << "\"" << std::endl;
                }
                std::cin >> input;

                //Load up the map
                string fileName = "../Map/MapFiles/" + files[std::stoi(input)];
                gameEngine.startupPhase("loadmap", fileName);
            }
            else {
                std::cout << "Unexpected Error in loading file directory." << std::endl;
            }
        }

        //Similarly here, I can reuse assignment 1's driver
        else if (input == "validatemap"){
            if (gameEngine.gameEngineMap == 0){
                std::cout << "The map hasn't been created yet!" << std::endl;
            }
            else {
                gameEngine.startupPhase("validatemap");
            }
        }


        else if (input == "addplayer"){
            if (gameEngine.players.size() == 6){
                std::cout << "Max players achieved already!" << std::endl;
            }
            else {
                std::cout << "Enter the name of the new player:" << std::endl;
                std::cin >> input;
                gameEngine.startupPhase("addplayer", input);
            }
        }


        else if (input == "gamestart"){
            if (gameEngine.gameEngineMap == 0){
                std::cout << "The map hasn't been created yet!" << std::endl;
            }
            else if (gameEngine.players.size() < 2){
                std::cout << "Not enough players have been assigned yet!" << std::endl;
            }
            else {
                gameEngine.startupPhase("gamestart");
            }
        }

        //simply quit out if the input was not recognized
        else{
            std::cout << "Unrecognized input detected. Please try again." << std::endl;
        }
    }
}

int main(){
testGameStates();
return 0;
}

