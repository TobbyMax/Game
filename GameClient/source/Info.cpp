#include "../header/Info.h"

Info::Info() {
    if (!this->font.loadFromFile("arial.ttf")) {
        // error...
    }

    this->condition.setFont(font);
    this->condition.setCharacterSize(24);
    this->condition.setFillColor(Color(Color::Black));

    this->possibleConditions[0] = "Pong!\nPress any key to start";
    this->possibleConditions[1] = "Paused";
    this->possibleConditions[2] = "Game over!\nPlayer 1 won";
    this->possibleConditions[3] = "Game over!\nPlayer 2 won";
    this->possibleConditions[4] = "\nPress Enter to start again";
    this->possibleConditions[5] = "Waiting for connection...";
}

Text Info::getInfo() {
    return condition;
}

void Info::setPauseText() {
    condition.setPosition(355, 250);
    condition.setString(possibleConditions[1]);
}

void Info::setStartText() {
    condition.setPosition(300, 250);
    condition.setString(possibleConditions[0]);
}

void Info::setPlayerWonText(int position) {
    condition.setPosition(275, 250);
    if (position == 0) {
        condition.setString(possibleConditions[2]);
    } else {
        condition.setString(possibleConditions[3]);
    }
    condition.setString(condition.getString() + possibleConditions[4]);
}

void Info::setNoConnectionText() {
    condition.setPosition(250, 250);
    condition.setString(possibleConditions[5]);
}
