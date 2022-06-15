#include "../header/Game.h"
#include <iostream>

Game::Game() {
    this->windowWidth = 800.f;
    this->windowHeight = 600.f;
    this->title = "Game 1";
    this->frameLimit = 60.f;

    this->window.create(VideoMode(windowWidth, windowHeight), title);
    this->window.setFramerateLimit(frameLimit);
    this->window.setVerticalSyncEnabled(true);

    socket.bind(CLIENT_PORT);
    socket.setBlocking(true);
    resetGame();
}

bool Game::isGameOver() {
    return gameOver;
}

void Game::update() {
    int noConnection = 0;
    while(!gameOver) {
        Packet packet;
        sf::IpAddress sender;
        unsigned short port = 0;
        float xl = leftPaddle->paddle.getPosition().x, yl = leftPaddle->paddle.getPosition().y;
        float xr = rightPaddle->paddle.getPosition().x, yr =rightPaddle->paddle.getPosition().y;
        float xBall = ball->ball.getPosition().x, yBall = ball->ball.getPosition().y;
        int leftPoints = leftScore->getPoints(), rightPoints = rightScore->getPoints();
        socket.receive(packet, sender, port);
        if (port != SERVER_PORT) {
            ++noConnection;
        } else {
            noConnection = 0;
            this->isConnected = true;
        }
        if (noConnection > 10) {
            this->isConnected = false;
        }

        packet >> xl >> yl;
        packet >> xr >> yr;
        packet >> xBall >> yBall;
        packet >> gameOver >> isPaused >> isJustStarted >> isJustEnded;
        packet >> leftPoints >> rightPoints;

        leftPaddle->paddle.setPosition(xl, yl);
        rightPaddle->paddle.setPosition(xr, yr);
        ball->ball.setPosition(xBall, yBall);

        leftScore->setPoints(leftPoints);
        rightScore->setPoints(rightPoints);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Game::draw() {
    if (!gameOver) {
        window.clear(Color(255, 255, 204));
        if (!isConnected) {
            window.draw(connectionInfo.getInfo());
        } else if (isJustStarted) {
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

void Game::checkTheEnd() {
    if (leftScore->getPoints() == pointsToEnd && rightScore->getPoints() < pointsToEnd && isJustEnded) {
        endInfo.setPlayerWonText(0);
    }
    if (rightScore->getPoints() == pointsToEnd && leftScore->getPoints() < pointsToEnd && isJustEnded) {
        endInfo.setPlayerWonText(1);
    }
}

void Game::resetGame() {
    this->gameOver = false;
    this->isPaused = false;
    this->isJustStarted = true;
    this->isJustEnded = false;
    this->isConnected = true;

    this->ball = new Ball();
    this->leftPaddle = new Paddle("left", 0);
    this->rightPaddle = new Paddle("right", 800 - 35);

    this->leftScore = new Score("left");
    this->rightScore = new Score("right");

    this->pauseInfo.setPauseText();
    this->startInfo.setStartText();
    this->connectionInfo.setNoConnectionText();

    this->pointsToEnd = 3;
}

void Game::connectToServer() {
    // CHANGE LATER
    std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
    socket.send(message.c_str(), message.size() + 1,SERVER_IP, SERVER_PORT);
    socket.setBlocking(false);
}

void Game::startGame() {
    std::thread updateThread(&Game::update, this);
    while (!this->isGameOver()) {
        this->checkTheEnd();
        this->eventPoll();
        this->draw();
    }
    this->closeWindow();
    updateThread.join();
}


void Game::eventPoll() {
    Event event;
    int key = -1;
    Packet outbox;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            this->gameOver = true;
            key = 0;
            outbox << key;
            socket.send(outbox, SERVER_IP, SERVER_PORT);
            return;
        }
        if (event.type == Event::KeyPressed) {
            if (isJustEnded) {
                if (event.key.code == Keyboard::Enter) {
                    resetGame();
                    key = 1;
                    outbox << key;
                    socket.send(outbox, SERVER_IP, SERVER_PORT);
                    return;
                }
            }
            if (event.key.code == Keyboard::Escape) {
                key = 2;
                outbox << key;
                socket.send(outbox, SERVER_IP, SERVER_PORT);
            }
            if (Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                key = 3;
                outbox << key;
                socket.send(outbox, SERVER_IP, SERVER_PORT);
            } else if (Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                key = 4;
                outbox << key;
                socket.send(outbox, SERVER_IP, SERVER_PORT);
            }
            if (isJustStarted) {
                key = 5;
                outbox << key;
                socket.send(outbox, SERVER_IP, SERVER_PORT);
            }
        }
    }
}

