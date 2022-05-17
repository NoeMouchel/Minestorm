
#include <raylib.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include <ctime>
#include "../include/game.h"


int main(int argc, char* argv[])
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    srand((unsigned int)time(NULL));
    Game MineStorm;
    MineStorm.gameLoop();


    return 0;
}