#ifndef DEPRESSION_LOAD_H
#define DEPRESSION_LOAD_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../AudioHandler.h"

class Load{
public:
    Load(std::string *currentstate){
        this->currentstate = currentstate;
    }

    void Run(tgui::Gui *gui, sf::RenderWindow *window, AudioHandler& audio);

    bool update = false;
    std::string focusSave;

    std::string name;
    std::string levelState = "Map_Layout_Intro";

    std::string fromsave = "Default";
    //position
    sf::Vector2f protvec = sf::Vector2f(500, 1300);

    //sprite
    int Head = 0;
    int Uniform = 0;
    int Skin = 0;

    sf::RectangleShape* pro;
    sf::RectangleShape* pro_2;
    sf::RectangleShape* pro_3;

    std::vector<sf::Texture> protText;

private:
    void loadLoad(tgui::Gui& gui, AudioHandler& audio);
    void ReadFile(std::string focus);
    void getname();
    sf::Texture mainTexture(int option);

    std::string *currentstate;

    std::string Save1txt = "Save1";
    std::string Save2txt = "Save2";
    std::string Save3txt = "Save3";
    std::string Save4txt = "Save4";

};


#endif //DEPRESSION_LOAD_H
