#ifndef GAME_INFO_H
#define GAME_INFO_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Info {
private:
    Font font;
    Text condition;
    std::string possibleConditions[6];
public:
    Info();
    Text getInfo();
    void setPauseText();
    void setStartText();
    void setPlayerWonText(int position);  // 0 - left player, 1 - right player
    void setNoConnectionText();
};


#endif //GAME_INFO_H
