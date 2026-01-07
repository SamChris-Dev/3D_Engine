#include "Engine.h"


int main(int argc, char** argv) {
    Engine gameEngine;

    
    gameEngine.Init(argc, argv, 800, 600, "OpenGL Engine");

   
    gameEngine.Run();

    return 0;
}