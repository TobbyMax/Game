#include "../header/Game.h"
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

using namespace std;
#define CLIENT_PORT 55001
#define SERVER_PORT 55002

int main()
{
    sf::UdpSocket socket;
    socket.bind(CLIENT_PORT);

    // Send a message to 10.5.0.2 on port 55002
    std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
    socket.send(message.c_str(), message.size() + 1, "172.17.54.153", SERVER_PORT);

    // Receive an answer (most likely from 10.5.0.2, but could be anyone else)
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(buffer, sizeof(buffer), received, sender, port);
    if (received > 0) {
        std::cout << sender.toString() << " said: " << buffer << std::endl;
    }

    Game game;
    while (!game.isGameOver()) {
        game.update();
        game.draw();
    }
    game.closeWindow();
    return 0;
}
