#include <iostream>
#include "Units.h"


//===========[Universal]==========//
void BasicAttack(Units *from, Units *too){
        too->HP -= from->Attack - (too->Defence * 0.25);
}
//================================//


//==========[Healer]=========//
void Heal(Units *from, Units *too){ //heal works but magickAttack is not set
    if(too->HP > too->MaxMP){
        too->HP = too->MaxHP;
    }else if(!too->Dead){
        too->HP = too->HP + (from->MagicAttack * 1.5);
        from->Emnity += 5;
    }
}

void Revive(Units *from, Units *too) {
    if(too->Dead){
        too->Dead = false;
        too->HP = too->MaxHP * 0.25;
        from->Emnity += 50;
    }
}
//==========================//

//==========[Tank]==========//
void EnmityUp(Units *from) {
    from->Emnity += 40;
}

void IronSkin(Units *from) {
    from->Defence += from->HP * 0.05;
}
//==========================//

//===========[Mage]===========//
void Fireball(Units *from, Units *too){
    too->HP -= (from->MagicAttack + 10) - too->MagicDefence;
    from->Emnity += 2;
}

void EXPLOSION(Units *from, Units *too){
    if (too->HP * 0.5 > 50) {
        too->HP -= 50;
    } else {
        too->HP -= too->HP * 0.5;
    }
    from->Emnity += 20;
}
//============================//


//===========[ranger]===========//
void DodgeUp(Units *from) {
    from->Evade += 1;
}

void Sharpshot(Units *from, Units *too){
    too->HP =- from->Attack * 2 - from->Defence;
    from->Emnity += 2;
}
//==============================//

//===========[fighter]===========//
void Slash(Units *from, Units *too){
    too->HP -= from->Attack + 10 - too->Defence;
    from->Emnity += 2;
}

void Crosslash(Units *from, Units *too){
    too->HP -= (from->Attack * 1.50) + 10;
    from->Emnity += 4;
}
//===============================//


bool AttackHandling(Units *from, Units *too, std::string AttackType) {

    if (from->tag == "Ally") { //if the player attacks
            if (too->tag == "Ally") {
                if (from->Class == "Healer") { //check if the units class is healer
                    if (AttackType == "One") { //healer skill
                        if (from->MP > 20) {
                            Heal(from, too);
                            from->MP -= 20;
                            return true;
                        }
                        return false;
                    }
                    if (AttackType == "Two") { //healer skill
                        if (from->MP > from->MaxMP / 2) {
                            Revive(from, too);
                            from->MP -= from->MaxMP / 2;
                            return true;
                        }
                        return false;
                    }
                } else {
                    return false;
                }
            } else {
                if (!too->Dead) {
                    if (AttackType == "Basic") { //universal skill
                        BasicAttack(from, too);
                        if (from->MP < from->MaxMP)
                            from->MP += 2 + (from->MaxMP * 0.05);
                        if (from->MP > from->MaxMP)
                            from->MP = from->MaxMP;
                        return true;

                    } else if (from->Class == "Mage") { //check if mage
                        if (AttackType == "One") { // mage skill
                            if (from->MP >= 20) {
                                Fireball(from, too);
                                from->MP -= 20;
                                return true;
                            }
                            return false;
                        }
                        if (AttackType == "Two") {// mage skill
                            if (from->MP >= from->MaxMP / 2) {
                                EXPLOSION(from, too);
                                from->MP -= from->MaxMP / 2;
                                return true;
                            }
                            return false;
                        }

                    } else if (from->Class == "Ranger") {// check if ranger
                        if (AttackType == "One") { // ranger skill
                            if (from->MP >= 30) {
                                DodgeUp(from);
                                from->MP -= 30;
                                return true;
                            }
                            return false;
                        }
                        if (AttackType == "Two") { // ranger skill
                            if (from->MP >= 30) {
                                Sharpshot(from, too);
                                from->MP -= 30;
                                return true;
                            }
                            return false;
                        }
                    }
                    else if (from->Class == "Tank") {// check if tank
                        if (AttackType == "One") { // tank skill
                            if (from->MP >= 20) {
                                EnmityUp(from);
                                from->MP -= 20;
                                return true;
                            }
                            return false;
                        }
                        if (AttackType == "Two") { // tank skill
                            if (from->MP >= 20) {
                                IronSkin(from);
                                from->MP -= 20;
                                return true;
                            }
                            return false;
                        }
                    }
                    else if (from->Class == "Fighter") { // check if fighter
                        if (AttackType == "One") {    // fighter skill
                            if (from->MP >= 15) {
                                Slash(from, too);
                                from->MP -= 15;
                                return true;
                            }
                            return false;
                        }
                        if (AttackType == "Two") { // fighteer skill
                            if (from->MP >= 20) {
                                Crosslash(from, too);
                                from->MP -= 20;
                                return true;
                            }
                            return false;
                        }

                    }
                } else {
                    too->HP = 0;
                    return false;
                }
            }
        } else if (from->tag == "Enemy" || from->tag == "Boss") { // if the Enemy Attacks
            if (!too->Dead) {
                if (AttackType == "Basic") { //universal skill
                    BasicAttack(from, too);
                    return true;
                }
            }

        } else { // if nothing happened return false
            return false;
        }
}