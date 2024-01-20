#ifndef RISPIRIT_SAVE_H
#define RISPIRIT_SAVE_H


#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../AudioHandler.h"
#include "../Battlestate/Units.h"

class Save{
public:
    Save()= default;
    void Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *currentstate, AudioHandler& audio);
    bool update = false;

    void setCharacterCreation(std::string name, int Head, int Uniform, int Skin){
        this->name = name;
        this->Head = Head;
        this->Uniform = Uniform;
        this->Skin = Skin;
    }

    void setposition(sf::Vector2f pos){
        x = pos.x; y = pos.y;
    }

    void setLevelState(std::string currentMap) {
        this->levelState = currentMap;
    }

    void setUnits(std::vector<Units> unitlist){
        allylist = unitlist;
    }


private:
    void loadSave(tgui::Gui& gui, std::string& curentstate, AudioHandler& audio);
    void WriteToFile();
    void ResetSave();
    void getname();

    float x;
    float y;

    std::string focusSave = "";

    std::string name;
    std::string levelState;
    //position

    //stats
    float lvl = -1;
    float exp = -1;
    //sprite
    int Head = -1;
    int Uniform = -1;
    int Skin = -1;

    std::vector<Units> allylist;

    std::string Save1txt = "Save1";
    std::string Save2txt = "Save2";
    std::string Save3txt = "Save3";
    std::string Save4txt = "Save4";

};

#endif //RISPIRIT_SAVE_H
