#include <iostream>
#include <sstream>
#include "CommandProcessing.h"
#include "../Utils/GameUtils.h"

using namespace std;

// COMMANDPROCESSOR CLASS //
// Constructors and destructors
CommandProcessor::CommandProcessor() {
    this->commands = new vector<Command*>();
}

CommandProcessor::CommandProcessor(const CommandProcessor& other) {
    this->commands = other.commands;
}

CommandProcessor::~CommandProcessor() {
    delete commands;
}

// Methods
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

Command* CommandProcessor::getCommand(GameEngine& gameEngine) {
    while(true) {
        string commandString = readCommand();
        string effect;
        Command* newCommand = saveCommand(new string(commandString), new string(effect));

        // Tokenize the string to handle multiple arguments commands
        std::vector<std::string> commandTokens = splitString(commandString);

        if(validate(commandTokens.at(0), gameEngine)) return newCommand;
        else {
            cout << "Invalid command. \"" << commandString << "\" Please try again." << endl;
            newCommand->saveEffect(new string("Invalid CommandProcessing \"" + commandString  +"\""));
        }
    }
}

bool CommandProcessor::validate(const string& commandString, GameEngine& gameEngine) {
    return gameEngine.validateInput(commandString);
}

// COMMAND CLASS //
// Constructors and destructors
Command::Command() {
    this->command = new string("No CommandProcessing");
    this->effect = new string("No Effect");
}

Command::Command(string* command, string* effect) {
    this->command = command;
    this->effect = effect;
}

Command::Command(const Command& other) {
    this->command = other.command;
    this->effect = other.effect;
}

Command::~Command() {
    delete command;
    delete effect;
}

// Methods
Command* Command::saveEffect(string* effect) {
    this->effect = effect;
    return this;
}

// Getters
string* Command::getCommand() {
    return command;
}

string* Command::getEffect() {
    return effect;
}

// FILELINEREADER CLASS //

// Constructors and destructors
FileLineReader::FileLineReader() {
    this->lines = new vector<string*>();
}

FileLineReader::FileLineReader(const FileLineReader& other) {
    this->lines = other.lines;
}

FileLineReader::~FileLineReader() {
    delete lines;
}

// Methods
void FileLineReader::readLineFromFile(string& fileName) {
    // Retrieve file
    ifstream file("../Saves/" + fileName);
    // Read file line by line and save each line in a vector
    string line;
    while(getline(file, line)) {
        lines->push_back(new string(line));
        cout << line << endl;
    }
    file.close();
}

// Getters
vector<string*>* FileLineReader::getLines() {
    return lines;
}

// FILECOMMANDPROCESSORADAPTER CLASS //

// Initialize static variable
int FileCommandProcessorAdapter::currentLine = 0;

// Constructors and destructors
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    this->fileLineReader = new FileLineReader();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other) {
    this->fileLineReader = other.fileLineReader;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete fileLineReader;
}

// Methods
string FileCommandProcessorAdapter::readCommand() {
    string line = *(fileLineReader->getLines()->at(currentLine));
    currentLine++;
    return line;
}

// Getters
FileLineReader* FileCommandProcessorAdapter::getFileLineReader() {
    return fileLineReader;
}


