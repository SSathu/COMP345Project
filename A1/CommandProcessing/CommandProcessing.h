#pragma once

#include <string>
#include <vector>
#include "../GameEngine/GameEngine.h"
#include "../LogObserver/LoggingObserver.h"


class GameEngine;

class Command : public Subject, ILoggable {
private:
    std::string* command;
    std::string* effect;
public:
    Command();
    Command(std::string* command, std::string* effect);
    Command(const Command& other);
    ~Command();

    Command* saveEffect(std::string* effect);

    friend std::ostream& operator<<(std::ostream& os, const Command& command);

    string* stringToLog();

    // Getters
    std::string* getCommand();
    std::string* getEffect();
};

class CommandProcessor : public Subject, ILoggable {
private:
    std::vector<Command*>* commands;
protected:
    virtual std::string readCommand();
    Command* saveCommand(std::string* command, std::string* effect);
public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor& other);
    ~CommandProcessor();
    string* stringToLog();

    static bool validate(const std::string& command, GameEngine& gameEngine);
    bool validateTournamentCommand(vector<string>& tournamentTokens);
    // Getters
    std::vector<Command*>* getCommandsList();
    Command * getCommand(GameEngine& gameEngine);

    friend std::ostream& operator<<(std::ostream& os, const CommandProcessor& processor);
};

class FileLineReader {
private:
    std::vector <std::string*>* lines;
public:
    FileLineReader();
    FileLineReader(const FileLineReader& other);
    ~FileLineReader();

    void readLineFromFile(std::string& fileName);
    friend std::ostream& operator<<(std::ostream& os, const FileLineReader& reader);

    // Getter
    std::vector<std::string*>* getLines();
};

// This is an adapter class between a FileLineReader and a CommandProcessor
class FileCommandProcessorAdapter : public CommandProcessor {
private:
    FileLineReader* fileLineReader;
    static int currentLine;
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
    ~FileCommandProcessorAdapter();

    std::string readCommand() override;

    friend std::ostream& operator<<(std::ostream& os, const FileCommandProcessorAdapter& adapter);

    // Getters
    FileLineReader* getFileLineReader();
};
