#include "../header/Game.h"
#include <iostream>
#include <thread>

Game::Game() {
    socket.bind(SERVER_PORT);
    socket.setBlocking(false);
    resetGame();
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::update() {
    int key = -1;
    Packet inbox;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(inbox, sender, port);
    inbox >> key;
    if (key != -1) {
        std::cout << key << std::endl;
        if (key == 0) {
            this->gameOver = true;
        } else if (key == 1) {
            if (isJustEnded) {
                resetGame();
                return;
            }
        } else if (key == 2) {
            isPaused = !isPaused;
        }
        if (isJustStarted) {
            this->isJustStarted = false;  // press any button and start a game
        }
    }

    unsigned position = computerID[sender];
    if (!gameOver) {
        if (!isPaused && !isJustStarted) {
            if (position == 0) {
                leftPaddle->update(key);
                rightPaddle->update(-1);
            } else if (position == 1) {
                leftPaddle->update(-1);
                rightPaddle->update(key);
            }
            // leftPaddle->update(*key);
            // rightPaddle->update(*key);
            ball->update(*leftPaddle, *rightPaddle, *leftScore, *rightScore);
            leftScore->update();
            rightScore->update();
            checkTheEnd(*leftScore, *rightScore);
        }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(4));
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

void Game::waitForConnection() {
    while (computerID.size() < 2) {
        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        this->socket.receive(buffer, sizeof(buffer), received, sender, port);
        if (received > 0) {
            computerID[sender] = computerID.size();
            std::cout << sender.toString() << " said: " << buffer << std::endl;
        }
    }
}

void Game::sendData() {
    while(!gameOver) {
        Packet packet;
        packet << leftPaddle->paddle.getPosition().x << leftPaddle->paddle.getPosition().y;
        packet << rightPaddle->paddle.getPosition().x << rightPaddle->paddle.getPosition().y;
        packet << ball->ball.getPosition().x << ball->ball.getPosition().y;
        packet << gameOver << isPaused << isJustStarted << isJustEnded;
        packet << leftScore->getPoints() << rightScore->getPoints();


        for (auto it = computerID.begin(); it != computerID.end(); ++it) {
            socket.send(packet, it->first, CLIENT_PORT);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(6));
    }
}

void Game::startGame() {
    std::thread sendThread(&Game::sendData, this);
    while (!this->isGameOver()) {
        this->update();
    }
    sendThread.join();
}


