#ifndef PROJECT_TEST_UNITS_H
#define PROJECT_TEST_UNITS_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Attacks.h"



//#include <graphics.h>
 class Units{
//classes for movable units
 public:

    Units(sf::Vector2f PosVec, std::string texPath, int spritepos, std::string Name, int level, float currentExp, float ExpNextLvL, float HP, float MP, float Atc, float Def, float mac, float mdf, float acc, float evd, float Enmity, std::string tag, std::string Class, int i);

    void tick();
    void render();
    void SetSize(float height, float width);


    sf::Vector2f PosVector;
    sf::Texture texture;
    sf::Image image;
    sf::Color color;
    sf::RectangleShape shape; //dunno if this is right, needs to be different for everyone

    sf::RectangleShape shape1;
    sf::RectangleShape shape2;

    float scale = 3.3;
    sf::Vector2f vec = sf::Vector2f(32 * scale,32 * scale);

    bool Protagonist = false;

    bool Dead = false;

    int level;

    float currentExp;
    float ExpNextLvL;
    std::string Name = "";
    std::string skinpath;
    int spritepos = 0;
    float HP;

    float MaxHP;
    float MP;

    float MaxMP;

    float Attack;
    float Defence;
    float MagicAttack;

    float MagicDefence;
    float Accuracy;
    float Evade;
    float Emnity;

    std::string Class;
    std::string tag;
    int index;
};


#endif //PROJECT_TEST_UNITS_H
