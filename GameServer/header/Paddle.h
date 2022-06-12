#ifndef GAME_PADDLE_H
#define GAME_PADDLE_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Paddle {
private:
    Vector2<float> velocity;
    float acceleration;
    float drag;
    float velocityMax;
    float velocityMin;
    String orientation;
    Color green;
public:
    RectangleShape paddle;
    float xSize;
    float ySize;

    Paddle(const String& orientation, float xPosition);
    void initPhysics();
    void move(const float dir_x, const float dir_y);
    void updatePhysics();
    void update(int key);
    void updateMovement(int key);
    Vector2<float> getVelocity();
};

#endif //GAME_PADDLE_H
