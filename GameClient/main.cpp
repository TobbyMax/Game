#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
    // ----- The client -----
    // Create a socket and connect it to local ip on port 55001
    IpAddress ip = IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    socket.connect(ip, 2000);
    // Send a message to the connected host
    std::string message = "Hi, I am a client";
    socket.send(message.c_str(), message.size() + 1);
    // Receive an answer from the server
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "The server said: " << buffer << std::endl;
}
