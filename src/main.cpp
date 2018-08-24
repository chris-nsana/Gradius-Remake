#include "Game/Game.h"
#include <iostream>

int main()
{
    try{
      Game::Game Gradius;
      Gradius.start();
    }
    catch(std::exception& e){
      std::cout << "Fatal error occured causing the game to crash." << std::endl;
      std::cout << e.what() << std::endl;
    }
    return 0;
}
