#ifndef PROJECT_TEST_ATTACKS_H
#define PROJECT_TEST_ATTACKS_H

#include <iostream>
class Units;


bool AttackHandling(Units *from, Units *too, std::string AttackType);


//===========[Universal]==========//
void BasicAttack(Units *from, Units *too);
//================================//

//==========[Healer]=========//
void Heal(Units *from, Units *too);
void Revive(Units *too);
//==========================//

//==========[Tank]==========//
void EnmityUp(Units *from);
void IronSkin(Units *from);
//==========================//

//===========[Mage]===========//
void Fireball(Units *from, Units *too);
void EXPLOSION(Units *from, Units *too);
//============================//

//===========[ranger]===========//
void DodgeUp(Units *from);
void Sharpshot(Units *from, Units *too);
//==============================//

//===========[fighter]===========//
void Slash(Units *from, Units *too);
void Crosslash(Units *from, Units *too);
//===============================//

#endif //PROJECT_TEST_ATTACKS_H
