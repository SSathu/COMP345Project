//
// Created by ismai on 11/8/2023.
//

#ifndef A1_335_P5_COMMANDPROCESSING_H
#define A1_335_P5_COMMANDPROCESSING_H

#include <string>
#include <vector>

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

    bool validate(std::string command);

    // Getters
    std::vector<Command*>* getCommandsList();
    Command * getCommand();

    friend std::ostream& operator<<(std::ostream& os, const CommandProcessor& processor);
};

class FileLineReader {
private:
    std::vector <std::string*>* lines;
public:
    FileLineReader();
    FileLineReader(const FileLineReader& other);
    ~FileLineReader();

    void readLineFromFile();

    // Getter
    std::vector<std::string*>* getLines();
};


// This is an adapter class between a FileLineReader and a CommandProcessor
class FileCommandProcessorAdapter : public CommandProcessor {
private:
    FileLineReader* fileLineReader;
public:
    FileCommandProcessorAdapter();
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter& other);
    ~FileCommandProcessorAdapter();

    std::string readCommand();
    Command* passCommand();


    // Getters
    FileLineReader* getFileLineReader();
};



#endif //A1_335_P5_COMMANDPROCESSING_H