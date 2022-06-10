#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Paddle.h"
#include "Ball.h"
#include "Score.h"
#include "Info.h"
#include <SFML/Graphics.hpp>
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
public:
    Game();
    bool isGameOver();
    void update();
    void draw();
    void closeWindow();
    void checkTheEnd(Score leftScore, Score rightScore);
    void resetGame();
};

#endif //GAME_GAME_H
