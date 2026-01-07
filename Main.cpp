#include "Engine.h"

int main(int argc, char** argv) {
    Engine game;
    game.Init(argc, argv, 800, 600, "3D_Game engine");
    game.Run();
    return 0;
}