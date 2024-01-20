#include <SFML/Graphics/RectangleShape.hpp>
#include "Units.h"

Units::Units(sf::Vector2f PosVec, std::string texPath, int spritepos, std::string Name, int level, float currentExp, float ExpNextLvL, float HP, float MP, float Atc, float Def, float mac, float mdf, float acc, float evd, float Enmity, std::string tag, std::string Class, int i){
    PosVector = PosVec;
    image.loadFromFile(texPath);
    texture.loadFromImage(image, {(32 * spritepos),0,32,32});
    skinpath = texPath;
    this->Name = Name;

    this->level = level;
    this->currentExp = currentExp;
    this->ExpNextLvL = ExpNextLvL;


    this->HP = HP;    MaxHP = HP;
    this->MP = MP;    MaxMP = MP;
    Attack = Atc;   Defence = Def;
    MagicAttack = mac;  MagicDefence = mdf;
    Accuracy = acc; Evade = evd;
    Emnity = Enmity;

    this->tag = tag;
    this->Class = Class;
    index = i;
}


void Units::tick(){
    if(HP <= 0)
        Dead = true;
}
void Units::render(){

    if (!Dead){

        if(Protagonist){
            shape = sf::RectangleShape(sf::Vector2f((32 * scale),(32 * scale)));
            shape1 = sf::RectangleShape(sf::Vector2f((32 * scale),(32 * scale)));
            shape2 = sf::RectangleShape(sf::Vector2f((32 * scale),(32 * scale)));

            shape.setPosition(PosVector);
            shape1.setPosition(PosVector.x, PosVector.y + 26);
            shape2.setPosition(PosVector.x, PosVector.y - 23);


        }else{
            shape = sf::RectangleShape(vec);
            shape.setTexture(&texture);
            shape.setPosition(PosVector);
        }

    }/*else{
        shape.setFillColor(sf::Color::White);
        if(tag == "Ally"){
            shape.setRotation(270);
        }else{
            shape.setRotation(90);
        }
    }
*/

}

void Units::SetSize(float height, float width){
    vec = sf::Vector2f(height, width);
}

