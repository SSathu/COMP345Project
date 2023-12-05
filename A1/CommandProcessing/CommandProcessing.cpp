#include <iostream>
#include "../Utils/GameUtils.h"
#include "CommandProcessing.h"

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
    cout << "Enter command:";
    string command;
    getline(cin, command);
    return command;
}

string* CommandProcessor::stringToLog()
{
    return new string("Added new command: " + *commands->back()->getCommand());
}

Command* CommandProcessor::saveCommand(string* command, string* effect) {
    auto* newCommand = new Command(command, effect);
    commands->push_back(newCommand);
    Notify(this);
    return newCommand;
}

Command* CommandProcessor::getCommand(GameEngine& gameEngine) {
    while(true) {
        string commandString = this->readCommand();

        string effect;
        Command* newCommand = saveCommand(new string(commandString), new string(effect));

        // Tokenize the string to handle commands with multiple arguments
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

bool CommandProcessor::validateTournamentCommand(vector<std::string> &tournamentTokens) {
    // This command lets the user choose the parameters of the tournament, i.e.: M = 1 to 5 different maps, P = 2 to 4
    //different computer players strategies, G = 1 to 5 games to be played on each map, and D = 10 to 50 maximum
    //number of turns for each game.


    // tournament command is of template:
    // tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>

    int index = 2;

    // Check number of maps is between 1 and 5
    int mapCount = 0;
    while(tournamentTokens.at(index) != "-P") {
        mapCount++;
        index++;
    }
    if(mapCount < 1 || mapCount > 5){
        cout << "Invalid number of maps (1-5)" << endl;
        return false;
    }

    // Skip -P
    index++;

    // Check number of player strategy is between 2 and 4
    int strategyCount = 0;
    while(tournamentTokens.at(index) != "-G") {
        strategyCount++;
        index++;
    }
    if(strategyCount < 2 || strategyCount > 4) {
        cout << "Invalid number of player strategies (2-4)" << endl;
        return false;
    }

    // Skip -G
    index++;

    // Check number of games is between 1 and 5
    int gameCount = stoi(tournamentTokens.at(index));

    if(gameCount < 1 || gameCount > 5) {
        cout << "Invalid number of games (1-5)" << endl;
        return false;
    }
    // Skip -D
    index++;
    index++;

    // Check number of turns is between 10 and 50
    int turnCount = stoi(tournamentTokens.at(index));
    if(turnCount < 10 || turnCount > 50){
        cout << "Invalid number of turns (10-50)" << endl;
        return false;
    }

    return true;
}

// COMMAND CLASS //
// Constructors and destructors
Command::Command() {
    this->command = new string("No Command");
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

string* Command::stringToLog()
{
    return new string(*effect);
}

// Methods
Command* Command::saveEffect(string* effect) {
    this->effect = effect;
    Notify(this);
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

    // Check if the file is successfully opened
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << ". Please try again." << endl << endl << endl;
        return;
    }

    // Read file line by line and save each line in a vector
    string line;
    while (getline(file, line)) {
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
    vector<string*>* lines = fileLineReader->getLines();

    // Check if lines is not empty and currentLine is within bounds
    if (lines != nullptr && !lines->empty() && currentLine < lines->size()) {
        string line = *(lines->at(currentLine));
        currentLine++;
        return line;
    } else {
        cout << "No more lines to read." << endl;
        return "";
    }
}

// Getters
FileLineReader* FileCommandProcessorAdapter::getFileLineReader() {
    return fileLineReader;
}

// Overloaded operators
ostream& operator<<(ostream& os, const Command& command) {
    os << "{Command: " << *(command.command);
    os << ", Effect: " << *(command.effect) << "}";
    return os;
}

ostream& operator<<(ostream& os, const CommandProcessor& processor) {
    os << "Commands: " << endl;
    for(Command* command : *processor.commands) {
        os << " - " << *command << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const FileLineReader& reader) {
    os << "FileLineReader's Lines: " << endl;
    for(string* line : *reader.lines) {
        os << *line << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const FileCommandProcessorAdapter& adapter) {
    os << "FileCommandProcessorAdapter: " << endl;
    os << *adapter.fileLineReader;
    return os;
}