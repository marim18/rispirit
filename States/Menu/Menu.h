#ifndef DEPRESSION_MENU_H
#define DEPRESSION_MENU_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../AudioHandler.h"

class Menu{
public:
    Menu()= default;
    void Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *prevState, std::string *curentState, AudioHandler& audio);
    void loadMenu(tgui::Gui& gui, std::string& prevstate, std::string& curentstate, AudioHandler& audio);//initializing the gui
    bool update = false;
};

#endif //DEPRESSION_MENU_H
