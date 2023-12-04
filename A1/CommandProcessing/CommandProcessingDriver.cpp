#include "CommandProcessing.h"

using namespace std;


void testCommandProcessor() {
    auto* gameEngine = new GameEngine();
    gameEngine->startupPhase();

    delete gameEngine;
}

/*int main() {
    testCommandProcessor();
}*/