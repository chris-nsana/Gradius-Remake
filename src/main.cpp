#include "Game/Game.h"
#include <iostream>

int main()
{
    Game Gradius;
    Gradius.init();
    Gradius.run();
    std::cout << "Game Ended Cleanly" << std::endl;
    return 0;
}
