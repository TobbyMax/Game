#include "../header/Game.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

using namespace std;
#define CLIENT_PORT 55001
#define SERVER_PORT 55002


int main()
{
    UdpSocket socket;
    socket.bind(SERVER_PORT);

    IpAddress ip = IpAddress::getLocalAddress();
    cout << ip.toString() << endl;

    map<IpAddress, unsigned short> computerID;
    while (computerID.size() < 2) {
        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        socket.receive(buffer, sizeof(buffer), received, sender, port);
        if (received > 0) {
            computerID[sender] = computerID.size();
            cout << sender.toString() << " said: " << buffer << std::endl;
        }
    }

    Game game;
    while (!game.isGameOver()) {
        game.update();
        game.draw();
    }
    game.closeWindow();
    return 0;
}
