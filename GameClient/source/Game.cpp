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
//    Event event;
    while(!gameOver) {
//        int key = -1;
//        Packet outbox;
//        while (window.pollEvent(event)) {
//            std::cout << event.type << std::endl;
//            if (event.type == Event::Closed) {
//                this->gameOver = true;
//                key = 0;
//                outbox << key;
//                socket.send(outbox, SERVER_IP, SERVER_PORT);
//                return;
//            }
//            if (event.type == Event::KeyPressed) {
//                if (isJustEnded) {
//                    if (event.key.code == Keyboard::Enter) {
//                        resetGame();
//                        key = 1;
//                        outbox << key;
//                        socket.send(outbox, SERVER_IP, SERVER_PORT);
//                        return;
//                    }
//                }
//                if (event.key.code == Keyboard::Escape) {
//                    // isPaused = !isPaused;
//                    key = 2;
//                    outbox << key;
//                    socket.send(outbox, SERVER_IP, SERVER_PORT);
//                }
//                /*
//                 * if (event.key.code == Keyboard::Tilde) {
//                    rightScore->minusOne();
//                }
//                 */
//                if (Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
//                    key = 3;
//                    outbox << key;
//                    socket.send(outbox, SERVER_IP, SERVER_PORT);
//                } else if (Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
//                    key = 4;
//                    outbox << key;
//                    socket.send(outbox, SERVER_IP, SERVER_PORT);
//                }
//                if (isJustStarted) {
//                    //this->isJustStarted = false;  // press any button and start a game
//                    key = 5;
//                    outbox << key;
//                    socket.send(outbox, SERVER_IP, SERVER_PORT);
//                }
//            }
//        }

        Packet packet;
        sf::IpAddress sender;
        unsigned short port;
        float xl = leftPaddle->paddle.getPosition().x, yl = leftPaddle->paddle.getPosition().y;
        float xr = rightPaddle->paddle.getPosition().x, yr =rightPaddle->paddle.getPosition().y;
        float xBall = ball->ball.getPosition().x, yBall = ball->ball.getPosition().y;
        int leftPoints = leftScore->getPoints(), rightPoints = rightScore->getPoints();
        socket.receive(packet, sender, port);

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
        std::cout << "\nLeft paddle:" << xl << " " << yl << std::endl;
        std::cout << "Right paddle:" << xr << " " << yr << std::endl;
        std::cout << "Ball:" << xBall << " " << yBall << std::endl;
        std::cout << "Score:" << leftPoints << " " << rightPoints << std::endl;
        std::cout << "gameOver: " << gameOver << std::endl;
        std::cout << "isPaused: " << isPaused << std::endl;
        std::cout << "isJustStarted: " << isJustStarted << std::endl;
        std::cout << "isJustEnded: " << isJustEnded << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(13));
    }
    /*if (!gameOver) {
        if (!isPaused && !isJustStarted) {
            leftPaddle->update();
            rightPaddle->update();
            ball->update(*leftPaddle, *rightPaddle, *leftScore, *rightScore);
            leftScore->update();
            rightScore->update();
            checkTheEnd(*leftScore, *rightScore);
        }
    }*/
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

void Game::connectToServer() {
    // CHANGE LATER
    std::string message = "Hi, I am " + sf::IpAddress::getLocalAddress().toString();
    socket.send(message.c_str(), message.size() + 1,SERVER_IP, SERVER_PORT);
    socket.setBlocking(false);
}

void Game::startGame() {
    std::thread updateThread(&Game::update, this);

    while (!this->isGameOver()) {
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
        std::cout << event.type << std::endl;
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
                // isPaused = !isPaused;
                key = 2;
                outbox << key;
                socket.send(outbox, SERVER_IP, SERVER_PORT);
            }
            /*
             * if (event.key.code == Keyboard::Tilde) {
                rightScore->minusOne();
            }
             */
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
                //this->isJustStarted = false;  // press any button and start a game
                key = 5;
                outbox << key;
                socket.send(outbox, SERVER_IP, SERVER_PORT);
            }
        }
    }
}

