#ifndef RISPIRIT_PAUSE_H
#define RISPIRIT_PAUSE_H


#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../AudioHandler.h"

class Pause{
public:
    Pause()= default;
    void Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *PrevState, std::string *currentstate, AudioHandler& audio);
    void loadPause(tgui::Gui& gui, std::string& PrevState, std::string& curentstate, AudioHandler& audio);
    bool update = false;
    sf::Color AlphaBlack = sf::Color(0, 0, 0, 15);
};

#endif //RISPIRIT_PAUSE_H
