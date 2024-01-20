#ifndef DEPRESSION_SETTINGS_H
#define DEPRESSION_SETTINGS_H

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

#include "../AudioHandler.h"

class Settings{
public:
    Settings(AudioHandler* audioHandler){
        this->audio = audioHandler;
    };

    void Run(tgui::Gui* gui, sf::RenderWindow *window, std::string *PrevState, std::string *currentstate);
    bool update = false;

    int selected = 1;

    bool VSync = true;
    std::string vynchstring = "on";

    float Mastervolume = 10.f;
    float Soundvolume = 10.f;
    float Musicvolume = 10.f;

    AudioHandler* audio;

private:
    void loadSettings(tgui::Gui& gui, std::string &PrevState, std::string& curentstate);
};


#endif //DEPRESSION_SETTINGS_H
