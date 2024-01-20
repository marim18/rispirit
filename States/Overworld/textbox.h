#ifndef RISPIRIT_TEXTBOX_H
#define RISPIRIT_TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <jsoncpp/json/json.h>


class textbox {
public:
    textbox();
    void createBox(int x, int y, std::string npc);
    void buttonPromt(int x, int y, std::string key);
    void updateBox();
    bool activeButton = false;
    bool activeDialog = false;
    sf::RectangleShape promptBox;
    sf::Text text;
    sf::RectangleShape dialogBox;
    sf::Font font;
private:
    std::vector<sf::Texture> promptTextures;
    std::vector<sf::Texture> dialogBoxTexture;
    int dialogStep = 1;
    Json::Value root;
    std::string NPCdialog;

};


#endif //RISPIRIT_TEXTBOX_H
