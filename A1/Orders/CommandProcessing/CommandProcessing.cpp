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
    return new string("Command effect does: " + *effect);
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