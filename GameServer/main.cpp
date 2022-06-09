#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace sf;

int main()
{
    // ----- The server ----- add
// Create a listener to wait for incoming connections on port 55001
    sf::TcpListener listener;
    listener.listen(2000);
// Wait for a connection
    sf::TcpSocket socket;
    listener.accept(socket);
    std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
// Receive a message from the client
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "The client said: " << buffer << std::endl;
// Send an answer
    std::string message = "Welcome, client";
    socket.send(message.c_str(), message.size() + 1);
    return 0;
}
