#include "../header/Game.h"

Game::Game() {
    this->windowWidth = 800.f;
    this->windowHeight = 600.f;
    this->title = "Game 1";
    this->frameLimit = 60.f;

    this->window.create(VideoMode(windowWidth, windowHeight), title);
    this->window.setFramerateLimit(frameLimit);
    this->window.setVerticalSyncEnabled(true);

    resetGame();
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::update() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            this->gameOver = true;
        }
        if (event.type == Event::KeyPressed) {
            if (isJustStarted) {
                this->isJustStarted = false;  // press any button and start a game
            }
            if (isJustEnded) {
                if (event.key.code == Keyboard::Enter) {
                    resetGame();
                    return;
                }
            }

            if (event.key.code == Keyboard::Escape) {
                isPaused = !isPaused;
            }
            if (event.key.code == Keyboard::Tilde) {
                rightScore->minusOne();
            }
        }
    }

    if (!gameOver) {
        if (!isPaused && !isJustStarted) {
            leftPaddle->update();
            rightPaddle->update();
            ball->update(*leftPaddle, *rightPaddle, *leftScore, *rightScore);
            leftScore->update();
            rightScore->update();
            checkTheEnd(*leftScore, *rightScore);
        }
    }
}

void Game::draw() {
    if (!gameOver) {
        window.clear(Color(255, 255, 204));

        if (isJustStarted) {
            window.draw(startInfo.getInfo());
        } else if (isJustEnded) {
            window.draw(endInfo.getInfo());
        } else {
            if (isPaused) {
                window.draw(pauseInfo.getInfo());
            }
            window.draw(rightPaddle->paddle);
            window.draw(leftPaddle->paddle);
            window.draw(ball->ball);
            window.draw(leftScore->text);
            window.draw(rightScore->text);
        }

        window.display();
    }
}

void Game::closeWindow() {
    window.close();
}

void Game::checkTheEnd(Score leftScore, Score rightScore) {
    if (leftScore.getPoints() == pointsToEnd && !isJustEnded) {
        endInfo.setPlayerWonText(0);
        isJustEnded = true;
    }
    if (rightScore.getPoints() == pointsToEnd && !isJustEnded) {
        endInfo.setPlayerWonText(1);
        isJustEnded = true;
    }
}

void Game::resetGame() {
    this->gameOver = false;
    this->isPaused = false;
    this->isJustStarted = true;
    this->isJustEnded = false;

    this->ball = new Ball();
    this->leftPaddle = new Paddle("left", 0);
    this->rightPaddle = new Paddle("right", 800 - 35);

    this->leftScore = new Score("left");
    this->rightScore = new Score("right");

    this->pauseInfo.setPauseText();
    this->startInfo.setStartText();

    this->pointsToEnd = 3;
}
