#ifndef TEMPPROJECT_BATTLECONTROLLS_H
#define TEMPPROJECT_BATTLECONTROLLS_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <utility>
#include <queue>
#include "Attacks.h"
#include "../Inventory/Items.h"
#include "Units.h"

class BattleControlls{

public:
    BattleControlls(std::string* currentstate);
    listOfStuff listy;

    //========[Public Functions]=========//
    void drawAll(sf::RenderWindow& window, std::string& currentstate);
    void setEnemy(std::string Floor, std::string type);
    Units getUnitList(int i);
    void Potions(sf::RenderWindow& window, listOfStuff listy);
    void cPot(Potion &pot, Units &too);
    void Consume(tgui::ListBox::Ptr lista);
    void SetAlly(int hair, int body, int uniform, std::string name, std::string save);
    //===================================//

    //Public values//
    bool update = true;
    bool newBattle = true;
    bool CreateAlly = true;


    std::vector<Units> UnitList;
    //=============//

private:

    //=========[private varables]=============//
    int hair = 0;
    int uniform = 0;
    int skin = 0;
    std::string name;
    std::string save = "Defualt";

    float armour = 0;

    sf::Image image1;
    sf::Image image2;
    sf::Image image3;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Texture texture3;

    std::string* currentstate;
    tgui::Gui Bgui;
    sf::RectangleShape SelectedIndicator;
    sf::RectangleShape AttackerIndicator;
    bool Victory = false;
    bool Done = false;

    const sf::Time cooldownTime = sf::seconds (0.5f);
    sf::Clock elapsedCDTime;

    int battleMenu;//1 for no menu, 2 for attack menu, 3 for items.

    int amount = 4;
    std::string Floor = "Map_Layout_Floor_1";
    std::string type = "enemy";

    int TheAttacker = 0;
    int TheAttackee = 4;
    bool AllyTurn = true;

    int unit = 0;
    bool lvlUp = false;

    std::string WhoAttack;
    std::string WhomsTurn;
    std::string information;


    std::queue<int> queue;
    std::vector<int> checkqueue;

    std::string Attack1 = "";
    std::string Attack2 = "";
    std::string Attack3 = "";
    std::string Attack4 = "";
    std::string Message;
    //========================================//

    //========[Private Functions]=========//
    void Attack(std::string Attacktype, std::string Tag);
    void WinCondition();
    void VictoryScreen();
    void createEnemies();
    void createAlly();
    void run();

    //GUI
    void drawBottom(sf::RenderWindow& win);
    void healthPercent(sf::RenderWindow& win);
    void mainBButtons(sf::RenderWindow& win,int &i);
    void spesAtcBtns(sf::RenderWindow& win);
    //

    void checkQueue();
    void selectedUpdate();
    void setQueue();
    void NextInQueue();
    void reset();
    //====================================//
    };

#endif //TEMPPROJECT_BATTLECONTROLLS_H
