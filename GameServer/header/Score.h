#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Score {
private:
    Font font;
    int points;
    String orientation;
public:
    Text text;
    Score(String orientation);
    void update();
    void plusOne();
    void minusOne();
    int getPoints();
};


#endif //GAME_SCORE_H
