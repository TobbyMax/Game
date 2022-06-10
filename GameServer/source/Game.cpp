#include "../header/Game.h"
#include <iostream>

Game::Game() {
    this->windowWidth = 800.f;
    this->windowHeight = 600.f;
    this->title = "Game";
    this->frameLimit = 60.f;

    // this->window.create(VideoMode(windowWidth, windowHeight), title);
    // this->window.setFramerateLimit(frameLimit);
    // this->window.setVerticalSyncEnabled(true);

    socket.bind(SERVER_PORT);
    socket.setBlocking(false);
    resetGame();
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::update() {
    // Event event;
    /* while (window.pollEvent(event)) {
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
    } */

    char key[1];
    key[0] = -1;
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    socket.receive(key, sizeof(key), received, sender, port);

    if (received > 0) {
        if (*key == 0) {
            this->gameOver = true;
        } else if (*key == 1) {
            if (isJustEnded) {
                resetGame();
                return;
            }
        } else if (*key == 2) {
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
                leftPaddle->update(*key);
                rightPaddle->update(-1);
            } else if (position == 1) {
                leftPaddle->update(-1);
                rightPaddle->update(*key);
            }
            leftPaddle->update(*key);
            rightPaddle->update(*key);
            ball->update(*leftPaddle, *rightPaddle, *leftScore, *rightScore);
            leftScore->update();
            rightScore->update();
            checkTheEnd(*leftScore, *rightScore);
        }
    }

    Packet packet;
    packet << leftPaddle->paddle.getPosition().x << leftPaddle->paddle.getPosition().y;
    packet << rightPaddle->paddle.getPosition().x << rightPaddle->paddle.getPosition().y;
    packet << ball->ball.getPosition().x << ball->ball.getPosition().y;
    packet << gameOver << isPaused << isJustStarted << isJustEnded;
    packet << leftScore->getPoints() << rightScore->getPoints();

    for (auto it = computerID.begin(); it != computerID.end(); it++) {
        socket.send(packet, it->first, CLIENT_PORT);
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

void Game::waitForConnection() {
    while (computerID.size() < 2) {
        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        socket.receive(buffer, sizeof(buffer), received, sender, port);
        if (received > 0) {
            computerID[sender] = computerID.size();
            std::cout << sender.toString() << " said: " << buffer << std::endl;
        }
    }
}