#ifndef A1_335_P5_COMMANDPROCESSING_H
#define A1_335_P5_COMMANDPROCESSING_H

#include <string>
#include <vector>
#include "../GameEngine/GameEngine.h"

class GameEngine;

class Command {
private:
    std::string* command;
    std::string* effect;
public:
    Command();
    Command(std::string* command, std::string* effect);
    Command(const Command& other);
    ~Command();

    Command* saveEffect(std::string* effect);

    // Getters
    std::string* getCommand();
    std::string* getEffect();
};

class CommandProcessor {
private:
    std::vector<Command*>* commands;
protected:
    virtual std::string readCommand();
    Command* saveCommand(std::string* command, std::string* effect);
public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor& other);
    ~CommandProcessor();

    static bool validate(const std::string& command, GameEngine& gameEngine);

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

    // Getters
    FileLineReader* getFileLineReader();
};



#endif //A1_335_P5_COMMANDPROCESSING_H
