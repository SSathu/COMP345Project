#include "CommandProcessing.h"
#include <iostream>
using namespace std;
#include <vector>


void testCommandProcessor() {
    auto* gameEngine = new GameEngine();
    gameEngine->startupPhase();

    delete gameEngine;
}

int main() {
    testCommandProcessor();
}