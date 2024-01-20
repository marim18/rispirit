//
// Created by Eier on 08.11.2019.
//

#ifndef DEPRESSION_CHARACTERCREATION_H
#define DEPRESSION_CHARACTERCREATION_H

#include "../AudioHandler.h"

class CharacterCreation{
public:
    CharacterCreation()= default;
    void Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *currentstate, AudioHandler& audio);//the part of the game loop
    void loadCC(tgui::Gui& gui, std::string& curentstate, AudioHandler& audio);


    std::string getName(){return name;}
    void setName(std::string name){this->name = name;}

    int getHeadIndex(){return Head;}
    int getUniformIndex(){return Uniform;}
    int getSkinIndex(){return Skin;}

    void setHeadIndex(int i){Head = i;}
    void setUniformIndex(int i){Uniform = i;}
    void setSkinIndex(int i){Skin = i;}

    sf::Texture mainTexture(int option);

    bool update = false;

    sf::RectangleShape* pro;
    sf::RectangleShape* pro_2;
    sf::RectangleShape* pro_3;

    bool reset();
private:
    int Head = 0;
    int Uniform = 0;
    int Skin = 0;

    std::string name;
    std::vector<sf::Texture> protText;
};

#endif //DEPRESSION_CHARACTERCREATION_H
