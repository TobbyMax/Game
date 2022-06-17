#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Paddle.h"
#include "Ball.h"
#include "Score.h"
#include "Info.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <thread>

#define CLIENT_PORT 55001
#define SERVER_PORT 55002
#define SERVER_IP "25.48.201.122"

using namespace sf;

class Game {
private:
    RenderWindow window;
    int windowWidth;
    int windowHeight;
    String title;
    int frameLimit;

    bool gameOver;
    bool isPaused;
    bool isJustStarted;
    bool isJustEnded;
    bool isConnected;

    Paddle *leftPaddle;
    Paddle *rightPaddle;

    Ball *ball;

    Score *leftScore;
    Score *rightScore;

    Info pauseInfo;
    Info startInfo;
    Info endInfo;
    Info connectionInfo;

    int pointsToEnd;

    sf::UdpSocket socket;
public:
    Game();
    bool isGameOver();
    void update();
    void draw();
    void closeWindow();
    void checkTheEnd();
    void resetGame();

    void connectToServer();
    void startGame();
    void eventPoll();
};

#endif //GAME_GAME_H
