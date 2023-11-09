#include <iostream>
#include "CommandProcessing.h"
using namespace std;


// Constructors and destructors for CommandProcessor class
CommandProcessor::CommandProcessor() {
    // instantiate vector list of commands
    this->commands = new vector<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor& other) {
    this->commands = other.commands;
}

CommandProcessor::~CommandProcessor() {
    // delete vector list of commands
    delete commands;
}

// Methods for CommandProcessor class
vector <Command*>* CommandProcessor::getCommandsList() {
    return commands;
}

string CommandProcessor::readCommand() {
    cout << "Enter command: " << endl;
    string command;
    getline(cin, command);
    return command;
}

Command* CommandProcessor::saveCommand(string* command, string* effect) {
    Command* newCommand = new Command(command, effect);
    commands->push_back(newCommand);
    return newCommand;
}

Command* CommandProcessor::getCommand() {
    while(true) {
        string command = readCommand();
        string effect;
        Command* newCommand = saveCommand(new string(command), new string(effect));

        if(validate(command)) return newCommand;
        else {
            cout << "Invalid command. Please try again." << endl;
            newCommand->saveEffect(new string("Invalid move."));
        }
    }
}


