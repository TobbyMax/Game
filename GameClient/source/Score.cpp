#include "../header/Score.h"

Score::Score(String orientaton) {
    if (!this->font.loadFromFile("arial.ttf")) {
        // error...
    }

    this->points = 0;

    this->text.setFont(font);
    this->text.setCharacterSize(24);
    this->text.setString(std::to_string(points));
    this->text.setFillColor(Color(Color::Black));

    this->orientation = orientaton;
    if (this->orientation == "left") {
        this->text.setPosition(75.f, 20.f);
    } else {
        this->text.setPosition(700.f, 20.f);
    }
}

void Score::update() {
    this->text.setString(std::to_string(points));
}

void Score::plusOne() {
    (this->points)++;
    update();
}

void Score::minusOne() {
    (this->points)--;
    update();
}

int Score::getPoints() {
    return this->points;
}

void Score::setPoints(int playerPoints) {
    this->points = playerPoints;
}
