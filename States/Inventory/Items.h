#ifndef TEMPPROJECT_ITEMS_H
#define TEMPPROJECT_ITEMS_H

#include <iostream>
#include <string>
#include <vector>
class item{

public:
    /* int buyPrice;
    int sellPrice;
    int weight;*/
    std::string name;
};
class Potion: public item{
public:
    int amount;
    std::string type;//Types are: health, mana(stamina)
    int numberOfPotions;//The idea is to number the potions, in order for them to only take up one inventory space per potion
};
class equip: public item{
public:
    std::string equippedBy; //Will say if it is equipped by somebody, string will be "NONE" if nobody is using it, and if nobody is using it, you can equip it
};
class armour: public equip{
public:
    int standardProtection;//Just two sets of protection, for normal damage, and magic damage
    int magicProtection;
};
class weapon: public item{
public:
    int standardDamage;//Two sets of damage, can be changed later
    int magicDamage;
};
//Storing all types separately, because the items will be stored
class listOfStuff{
public:
    std::vector<Potion> listOfPotions;//All Potions will be stored here
    std::vector<weapon> listOfWeapons;//Weapons stored here
    std::vector<armour> listOfArmour;//Armour stored here
};

#endif //TEMPPROJECT_ITEMS_H
