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
#define SERVER_IP "172.17.54.172"

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

    Paddle *leftPaddle;
    Paddle *rightPaddle;

    Ball *ball;

    Score *leftScore;
    Score *rightScore;

    Info pauseInfo;
    Info startInfo;
    Info endInfo;

    int pointsToEnd;

    sf::UdpSocket socket;
public:
    Game();
    bool isGameOver();
    void update();
    void draw();
    void closeWindow();
    void checkTheEnd(Score leftScore, Score rightScore);
    void resetGame();

    void connectToServer();
    void startGame();
    void eventPoll();
};

#endif //GAME_GAME_H
