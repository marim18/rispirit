#ifndef RISPIRIT_OVERWORLD_H
#define RISPIRIT_OVERWORLD_H

#include <SFML/Graphics.hpp>
#include "textbox.h"

typedef std::map<std::string,sf::Vector2f> nextMapTemp; //Defining first layer of map

//Program does not accept sf::RectangleShape in typedef, so was made into separate maps
//typedef std::map<sf::RectangleShape,int> tempmap;

class overworld {
public:
    //Define functions meant to run in main
    overworld();
    void runOverworld(sf::RenderWindow *window,std::string *currentPhase);

    std::string currentMapName; //Create variable for use in battle
    std::string enemyType;
    sf::RectangleShape protagonist;
    sf::RectangleShape protagonist_2;
    sf::RectangleShape protagonist_3;
    sf::Vector2f protagPos;
    void loadMap(std::string);

private:
    //Define class functions
    int collision(std::map<int,sf::RectangleShape>,sf::RectangleShape,std::map<int,int>,std::string *currentState);
    int objectCollision(std::map<int,sf::RectangleShape>,sf::RectangleShape,std::map<int,int>,std::string *currentState);

    //Define class variables
    int REChance;
    int RECounter = 0;
    std::vector<sf::Texture> tileTextures;
    std::vector<sf::Texture> objectTextures;
    int moveSpeed;
    std::map<int,sf::RectangleShape> currentMap;
    std::map<int,int> mapColor;
    std::map<int,sf::RectangleShape> currentObjectMap;
    std::map<int,int> objectMapColor;
    std::map<int,std::string> NPCMap; //Name of NPC
    std::map<int,bool> NPCType; // Boss or friend
    std::map<int,int> exitNr;
    std::map<int,nextMapTemp> nextMap;
    textbox textbox;
    int activeNPCnr;
    int hairDifferenceY = 20;
    int hairDifferenceX = 5;
    int uniformDifference = 18;




};





#endif //RISPIRIT_OVERWORLD_H
