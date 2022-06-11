#include "../header/Game.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    Game game;

    game.connectToServer();
    while (!game.isGameOver()) {
        game.update();
        game.draw();
    }
    game.closeWindow();
    return 0;
}
