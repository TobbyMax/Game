#include "../header/Ball.h"
#include <iostream>

Ball::Ball() {
    this->radius = 25.f;
    this->red = Color(255, 153, 0);
    this->acceleration = 0.0025f;
    this->isOutOfZone = false;

    ball.setRadius(radius);
    ball.setFillColor(red);
    returnToTheStart();
}
void Ball::updatePhysics() {
    velocity += Vector2<float>(acceleration * ((velocity.x < 0) ? -1.f : 1.f),0);
    ball.move(velocity);
}
void Ball::updateMovement(Paddle &left, Paddle &right, Score &leftScore, Score &rightScore) {
    // Change the direction by touching upper and lower boundaries (maybe change color?...)
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= (600 - 2 * radius)) {
        velocity.y *= -1;
    }

    // Change the direction after the contact between ball and left/right paddle
    if (ball.getPosition().x <= left.xSize) {
        if ((ball.getPosition().y + radius >= left.paddle.getPosition().y - 20)
            && (ball.getPosition().y + radius <= left.paddle.getPosition().y + left.ySize + 20) && !isOutOfZone) {
            velocity.x *= -1;
            velocity.y += (left.getVelocity().y) / 10;  // ricochet effect :D
        } else {
            rightScore.plusOne();
            returnToTheStart();
        }
    }
    if (ball.getPosition().x >= 800 - right.xSize - 2 * radius) {
        if ((ball.getPosition().y + radius >= right.paddle.getPosition().y - 20)
            && (ball.getPosition().y + radius <= right.paddle.getPosition().y + left.ySize + 20) && !isOutOfZone) {
            velocity.x *= -1;
            velocity.y += (right.getVelocity().y) / 10;  // ricochet effect :D
        } else {
            leftScore.plusOne();
            returnToTheStart();
        }
    }
}
void Ball::update(Paddle &left, Paddle &right, Score &leftScore, Score &rightScore) {
    updateMovement(left, right, leftScore, rightScore);
    updatePhysics();
}

void Ball::returnToTheStart() {
    srand(time(NULL));

    ball.setPosition(400 - radius, 300 - radius);

    // rand() % 2 - a random number between 0 and 1
    // if 0 -> positive direction, if 1 -> negative direction
    velocity = Vector2<float>(2.5f * (float)((rand() % 2) ? 1 : -1),
                              2.5f * (float)((rand() % 2) ? 1 : -1));
}
