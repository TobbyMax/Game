#include "../header/Game.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    IpAddress ip = IpAddress::getLocalAddress();
    cout << ip.toString() << endl;

    Game game;
    game.waitForConnection();
    while (!game.isGameOver()) {
        game.update();
        // game.draw();
    }
    // game.closeWindow();
    return 0;
}
