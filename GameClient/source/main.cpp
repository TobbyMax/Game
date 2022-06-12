#include "../header/Game.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    Game game;

    game.connectToServer();
    game.startGame();

    return 0;
}
