//
// Created by Eier on 08.11.2019.
//

#ifndef DEPRESSION_EXTRAS_H
#define DEPRESSION_EXTRAS_H

#include <TGUI/Gui.hpp>
#include <SFML/Graphics.hpp>

#include "../AudioHandler.h"

class Extras{
public:
    Extras()= default;
    void Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *currentstate, AudioHandler& audio);
    void loadExtras(tgui::Gui& gui, std::string& curentstate, AudioHandler& audio);
    bool update = false;

    std::string text = "shobilobi";
};

#endif //DEPRESSION_EXTRAS_H
