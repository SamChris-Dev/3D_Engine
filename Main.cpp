#include "Engine.h"

int main(int argc, char** argv) {
    Engine game;
    game.Init(argc, argv, 800, 600, "Labs 07-09 Complete");
    game.Run();
    return 0;
}