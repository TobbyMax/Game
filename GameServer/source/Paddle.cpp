#include "../header/Paddle.h"

Paddle::Paddle(const String& orientation, float xPosition) {
    this->xSize = 35;
    this->ySize = 100;
    this->orientation = orientation;
    this->green = Color(100, 250, 50);

    paddle.setSize(Vector2<float>(xSize, ySize));
    paddle.setFillColor(green);
    paddle.setPosition(xPosition, 250);

    initPhysics();
}
void Paddle::initPhysics() {
    velocityMax = 10.f;
    velocityMin = 1.f;
    acceleration = 1.25f;
    drag = 0.95f;
}
void Paddle::move(const float dir_x, const float dir_y) {
    // Acceleration
    velocity.x += dir_x * acceleration;
    velocity.y += dir_y * acceleration;

    // Limit velocity
    if (std::abs(velocity.x) > velocityMax) {
        velocity.x = velocityMax * ((velocity.x < 0.f) ? -1.0f : 1.0f);
    }
    if (std::abs(velocity.y) > velocityMax) {
        velocity.y = velocityMax * ((velocity.y < 0.f) ? -1.0f : 1.0f);
    }
}
void Paddle::updatePhysics() {
    // Deceleration
    velocity *= drag;

    // Limit deceleration
    if (std::abs(velocity.x) < velocityMin) {
        velocity.x = 0.f;
    }
    if (std::abs(velocity.y) < velocityMin) {
        velocity.y = 0.f;
    }

    // Set the boundaries for paddles
    if (paddle.getPosition().y < 0) {
        paddle.setPosition(paddle.getPosition().x, 0);
        velocity.y = 0;
    }
    if (paddle.getPosition().y > 600 - ySize) {
        paddle.setPosition(paddle.getPosition().x, 600 - ySize);
        velocity.y = 0;
    }

    paddle.move(velocity);
}
void Paddle::update(int key) {
    updateMovement(key);
    updatePhysics();
}
void Paddle::updateMovement(int key) {
    if (key == 3) {
        move(0, -1);
    } else if (key == 4) {
        move(0, 1);
    }
}

Vector2<float> Paddle::getVelocity() {
    return this->velocity;
}
