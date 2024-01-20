#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <algorithm>
#include <TGUI/TGUI.hpp>
#include <jsoncpp/json/json.h>
#include <fstream>
#include "BattleControlls.h"
#include "Units.h"
#include "AI.h"
#include "../Inventory/Items.h"
#include <string>

BattleControlls::BattleControlls(std::string* currentstate) // inializing Battle controlls
{
    battleMenu = 1; //value of the menu and choices the player uses.
    this->currentstate = currentstate;

    Potion MinorH;
    MinorH.name = "Minor Healing";
    MinorH.type = "Health";
    MinorH.amount = 50;
    MinorH.numberOfPotions = 3;

    listy.listOfPotions.push_back(MinorH);
}

void BattleControlls::createAlly(){
    //creating Json root value
    Json::Value root;
    std::ifstream inputfilestream("States/Menu/Saves.json");
    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    bool parsingSuccsessful = Json::parseFromStream(readerBuilder, inputfilestream, &root, &errors);
    if(!parsingSuccsessful){
        std::cout << errors << std::endl;
    }
    //save = "Default";
    //end
    //==============================[Creates and pushes back protagonist and allies]==============================//
    for(int i = 0; i < 4; i++ ){
        UnitList.push_back(Units(sf::Vector2f(180 - (50 * i), 230 + (80 * i)),
                                 root[save]["Ally"][std::to_string(i)]["Sprite"].asString(),
                                 root[save]["Ally"][std::to_string(i)]["SpritePos"].asInt(),
                                 root[save]["Ally"][std::to_string(i)]["Name"].asString(),
                                 root[save]["Ally"][std::to_string(i)]["level"].asInt(),
                                 root[save]["Ally"][std::to_string(i)]["currentExp"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["ExpNextLvL"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["HP"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["MP"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["Attack"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["Defence"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["MagicAttack"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["MagicDefence"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["Accuracy"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["Evade"].asFloat(),
                                 root[save]["Ally"][std::to_string(i)]["Enmity"].asFloat(),
                                 "Ally",
                                 root[save]["Ally"][std::to_string(i)]["Class"].asString(),
                                 i));

        if(UnitList.at(i).Class == "Tank"){
            armour = UnitList.at(i).Defence;
        }
    }
    //===========================================================================================================//


    inputfilestream.close();
    UnitList.at(0).Name = name;
    UnitList.at(0).Protagonist = true;

}

void BattleControlls::SetAlly(int hair, int body, int uniform, std::string name, std::string save){
    this->hair = hair;  this->skin = body; this->uniform = uniform; this->name = name; this->save = save;
}

void BattleControlls::createEnemies(){ //function that takes in parameters and creating enemies, enemy type is decided by values.

    //=========[setup readable file]=================//
    Json::Value root;
    std::ifstream inputfilestream("States/Battlestate/Enemy.json");
    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    bool parsingSuccsessful = Json::parseFromStream(readerBuilder, inputfilestream, &root, &errors);
    if(!parsingSuccsessful){
        std::cout << errors << std::endl;
    }
    inputfilestream.close();





    //=====================[creation of enemiesby taking from .json file]====================//
    for(int i = 4; i < (4 + amount); i++ ){
        int j = (i-4);
        UnitList.push_back(Units(sf::Vector2f(680 - (50 * j), 460 - (80 * j)),
                                 root[Floor][type + std::to_string(j)]["Sprite"].asString(),
                                 root[Floor][type + std::to_string(j)]["SpritePos"].asInt(),
                                 root[Floor][type + std::to_string(j)]["Name"].asString(),
                                 root[Floor][type + std::to_string(j)]["level"].asInt(),
                                 root[Floor][type + std::to_string(j)]["currentExp"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["ExpNextLvL"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["HP"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["MP"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["Attack"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["Defence"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["MagicAttack"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["MagicDefence"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["Accuracy"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["Evade"].asFloat(),
                                 root[Floor][type + std::to_string(j)]["Enmity"].asFloat(),
                                 "Enemy",
                                 root[Floor]["enemy" + std::to_string(j)]["Class"].asString(),
                                 i));
        if(type == "boss"){
            UnitList.at(i).PosVector = sf::Vector2f(530 , 330);
            UnitList.at(i).SetSize(32*5,32*5);
        }
    }
}

void BattleControlls::drawBottom(sf::RenderWindow& win)
{//Wil optimize later
    float edge = 10;//Just defining the size of the edge to make it easier to edit
    Bgui.setTarget(win);

    //Angir størrelse på tegning av 3 objekter som knapper skal legges på
    sf::RectangleShape rectangle1(sf::Vector2f(240-edge, 200-edge));
    sf::RectangleShape rectangle2(sf::Vector2f(300-edge, 190-edge));
    sf::RectangleShape rectangle3(sf::Vector2f(250-edge, 200-edge));
    //Setter størrelsen på outlinen
    rectangle1.setOutlineThickness(edge);
    rectangle2.setOutlineThickness(edge);
    rectangle3.setOutlineThickness(edge);
    //Setter farge på outline og resten av objektet, begge grå, outline litt mørkere enn resten
    rectangle1.setOutlineColor(sf::Color(44, 44, 44));
    rectangle2.setOutlineColor(sf::Color(44, 44, 44));
    rectangle3.setOutlineColor(sf::Color(44, 44, 44));
    rectangle1.setFillColor(sf::Color(35, 35, 35));
    rectangle2.setFillColor(sf::Color(35, 35, 35));
    rectangle3.setFillColor(sf::Color(35, 35, 35));
    //Setting pos of the rectangles
    rectangle1.setPosition(10.f,600.f);
    rectangle2.setPosition(250.f,610.f);
    rectangle3.setPosition(550.f,600.f);//Health Will be displayed inside this one
    //Tegner objektene

    win.draw(rectangle1);
    win.draw(rectangle2);
    win.draw(rectangle3);
}
void BattleControlls::healthPercent(sf::RenderWindow& win)
{//Could be replaced by attack description

    tgui::Theme theme("Themes/Black.txt");// theme of health bars

    tgui::Theme theme2("Themes/Custom.txt");

    auto Panel = tgui::Panel::create(); // panel where health bar is drawn on
    Panel->setRenderer(theme.getRenderer("Panel"));
    Panel->setSize("30%","23,75%");
    Panel->setPosition("68,75%","75%");
        //========================================[Health bar for player and enemy]================================================//
        for (int i = 0; i < UnitList.size(); i++) {
            auto temp = tgui::ProgressBar::create();
            temp->setText(std::to_string((int)UnitList[i].HP));
            temp->setValue((int)UnitList[i].HP);
            temp->setSize(100, 15);
            temp->setPosition(10, 10);
            temp->setRenderer(theme2.getRenderer("ProgressBar"));
            temp->update(sf::milliseconds(1));
            if(i==0){
                temp->setPosition(10, 10);
                auto HealthBar0=temp;
                Panel->add(HealthBar0);
            }else if(i==1){
                temp->setPosition(10, 55);
                auto HealthBar1=temp;
                Panel->add(HealthBar1);
            }else if(i==2){
                temp->setPosition(10, 100);
                auto HealthBar2=temp;
                Panel->add(HealthBar2);
            }else if(i==3){
                temp->setPosition(10, 145);
                auto HealthBar3=temp;
                Panel->add(HealthBar3);
            }else if(i==4){
                temp->setPosition(130, 145);
                auto HealthBar4=temp;
                Panel->add(HealthBar4);
            }else if(i==5){
                temp->setPosition(130, 100);
                auto HealthBar5=temp;
                Panel->add(HealthBar5);
            }else if(i==6){
                temp->setPosition(130, 55);
                auto HealthBar6=temp;
                Panel->add(HealthBar6);
            }else if(i==7){
                temp->setPosition(130, 10);
                auto HealthBar7=temp;
                Panel->add(HealthBar7);
            }
        }
    //===============================================================================================================================//

    //========================================[MP bar for player and enemy]================================================//
        for(int i=0; i < UnitList.size();i++){
            auto temp = tgui::ProgressBar::create();
            temp->setText(std::to_string((int)UnitList[i].MP));
            temp->setValue((int)UnitList[i].MP);
            temp->setSize(100, 15);
            temp->setPosition(10, 10);
            temp->setRenderer(theme.getRenderer("ProgressBar"));
            temp->update(sf::milliseconds(1));
            if(i==0){
                temp->setPosition(10, 24);
                auto ManaBar0=temp;
                Panel->add(ManaBar0);
            }else if(i==1){
                temp->setPosition(10, 69);
                auto ManaBar1=temp;
                Panel->add(ManaBar1);
            }else if(i==2){
                temp->setPosition(10, 114);
                auto ManaBar2=temp;
                Panel->add(ManaBar2);
            }else if(i==3){
                temp->setPosition(10, 159);
                auto ManaBar3=temp;
                Panel->add(ManaBar3);
            }else if(i==4){
                temp->setPosition(130, 159);
                auto ManaBar4=temp;
                Panel->add(ManaBar4);
            }else if(i==5){
                temp->setPosition(130, 114);
                auto ManaBar5=temp;
                Panel->add(ManaBar5);
            }else if(i==6){
                temp->setPosition(130, 69);
                auto ManaBar6=temp;
                Panel->add(ManaBar6);
            }else if(i==7){
                temp->setPosition(130, 24);
                auto ManaBar7 = temp;
                Panel->add(ManaBar7);
            }
        }
    //===============================================================================================================================//


    //====[information about turns and attacks]====//

        auto InformationBox = tgui::ChatBox::create();
        InformationBox->setRenderer(theme2.getRenderer("ChatBox"));
        InformationBox->setTextSize(24);
        InformationBox->setTextColor(sf::Color(200, 200, 200));
        InformationBox->setLinesStartFromTop(true);
        InformationBox->addLine("" + WhoAttack);
        InformationBox->addLine("" + WhomsTurn);
        InformationBox->addLine("" + information);
        InformationBox->setPosition({"28%", "10%"});
        InformationBox->setSize("43,5%", "18,75%");
        Bgui.add(InformationBox);
        Bgui.add(Panel);

    //==============================================//

}
void BattleControlls::mainBButtons(sf::RenderWindow& win, int &i){//Will optimize later

    Bgui.setTarget(win);
    tgui::Theme theme("Themes/Black.txt");
    //Declaring buttons
    auto basicAtk = tgui::Button::create();
    auto SpesAtk = tgui::Button::create();
    auto Items = tgui::Button::create();
    auto Run = tgui::Button::create();
    //setting pos
    basicAtk->setPosition("3%","75,9%");
    SpesAtk->setPosition("3%","81,6%");
    Items->setPosition("3%","87%");
    Run->setPosition("3%","93,5%");
    //Setting size
    basicAtk->setSize("22%","5%");
    SpesAtk->setSize("22%","5%");
    Items->setSize("22%","5%");
    Run->setSize("22%","5%");
    //Setting text
    basicAtk->setText("Basic Attack");
    SpesAtk->setText("Special Attacks");//Wil open menu in the middle
    Items->setText("Items");//Wil open scrollable menu in middle
    Run->setText("Run");//Try to run from battle

    //setting text size
    basicAtk->setTextSize(20);
    SpesAtk->setTextSize(20);
    Items->setTextSize(20);
    Run->setTextSize(20);
    //Renders?
    basicAtk->setRenderer(theme.getRenderer("Button"));
    SpesAtk->setRenderer(theme.getRenderer("Button"));
    Items->setRenderer(theme.getRenderer("Button"));
    Run->setRenderer(theme.getRenderer("Button"));

    //Adding functions to buttons
    basicAtk->connect("Pressed",[&](){
        if(AllyTurn)
            Attack("Basic", "Ally");
        else
            information = "not your turn";
        update = true;
        battleMenu = 1;
    });

    SpesAtk->connect("Pressed",[&](){i = 2;update = true;});//Button doesnt do much, so no need to call a function
    Items->connect("Pressed",[&](){i = 3; update = true;});//Button doesnt do much, so no need to call a function
    Run->connect("Pressed",[&](){run();});
    //adding them to gui

    Bgui.add(basicAtk);
    Bgui.add(SpesAtk);
    Bgui.add(Items);
    Bgui.add(Run);

}
//void BattleControlls::spesAtcBtns(sf::RenderWindow& win, Units turn, Units select)
void BattleControlls::spesAtcBtns(sf::RenderWindow& win)
{//This function will add special buttons
    tgui::Theme theme("Themes/Black.txt");
    //Declaring buttons
    tgui::Button::Ptr Atk1 = tgui::Button::create();
    tgui::Button::Ptr Atk2 = tgui::Button::create();
    tgui::Button::Ptr Atk3 = tgui::Button::create();
    tgui::Button::Ptr Atk4 = tgui::Button::create();
    //setting pos
    Atk1->setPosition(260,640);
    Atk2->setPosition(260,700);
    Atk3->setPosition(410,640);
    Atk4->setPosition(410,700);
    //Setting size
    Atk1->setSize(120,30);
    Atk2->setSize(120,30);
    Atk3->setSize(120,30);
    Atk4->setSize(120,30);
    //Setting theme
    Atk1->setRenderer(theme.getRenderer("Button"));
    Atk2->setRenderer(theme.getRenderer("Button"));
    Atk3->setRenderer(theme.getRenderer("Button"));
    Atk4->setRenderer(theme.getRenderer("Button"));
    //Setting text
    Atk1->setText(Attack1);
    Atk2->setText(Attack2);
    Atk3->setText(Attack3);
    Atk4->setText(Attack4);
    //adding them to gui
    Bgui.add(Atk1);
    Bgui.add(Atk2);
    Bgui.add(Atk3);
    Bgui.add(Atk4);
    //printer
    Atk1->connect("Pressed",[&](){if(AllyTurn) Attack("One", "Ally"); update = true; battleMenu = 1;});
    Atk2->connect("Pressed",[&](){if(AllyTurn) Attack("Two", "Ally"); update = true; battleMenu = 1;});
    Atk3->connect("Pressed",[&](){if(AllyTurn) Attack("Three", "Ally"); update = true; battleMenu = 1;});
    Atk4->connect("Pressed",[&](){if(AllyTurn) Attack("Four", "Ally"); update = true; battleMenu = 1;});

}
void BattleControlls::run()
{
    float zoom = 1;
    int i=rand()%10;
    std::cout << i << std::endl;
    if(i>=0 && i<=2){
        //next turn
        std::cout << "Running failed" << std::endl;
        NextInQueue();
    }else{
        //Switch to overworld state
        *currentstate = "Overworld";
        std::cout << "You ran away, coward!" << std::endl;
        reset();
        *currentstate = "Overworld";
    }
}

void BattleControlls::VictoryScreen(){

    float expdrop = 0;


    if(Message != "Defeated"){

        for(auto &at : checkqueue){
            if(UnitList.at(at).tag == "Enemy"){
                expdrop += UnitList.at(at).ExpNextLvL;
            }
        }
    }


    auto Picture = tgui::Picture::create("Pictures/CharCreate/smalpanel.png");
    Picture->setSize("100%", "100%");

    auto Panel = tgui::Panel::create({250, 350});
    Panel->setPosition({"35%","10%"});
    auto Title = tgui::Label::create(Message);
    Title->setPosition(53,30);
    Title->setTextSize(34);

    auto Unit0  = tgui::Label::create(UnitList[0].Name + "'s XP from " + std::to_string(UnitList[0].level) + " to " + std::to_string(UnitList[0].level + 1) +"\n     " + std::to_string((int)UnitList[0].currentExp) + " --> " + std::to_string((int)(UnitList[0].currentExp + expdrop))); Unit0->setPosition(30,105);  Unit0->setTextSize(16);
    auto Unit1  = tgui::Label::create(UnitList[1].Name + "'s XP from " + std::to_string(UnitList[1].level) + " to " + std::to_string(UnitList[1].level + 1) + "\n     " + std::to_string((int)UnitList[1].currentExp) + " --> " + std::to_string((int)(UnitList[1].currentExp + expdrop)));     Unit1->setPosition(30,145);  Unit1->setTextSize(16);
    auto Unit2  = tgui::Label::create(UnitList[2].Name + "'s XP from " + std::to_string(UnitList[2].level) + " to " + std::to_string(UnitList[2].level + 1) + "\n     " + std::to_string((int)UnitList[2].currentExp) + " --> " + std::to_string((int)(UnitList[2].currentExp + expdrop)));     Unit2->setPosition(30,185);  Unit2->setTextSize(16);
    auto Unit3  = tgui::Label::create(UnitList[3].Name + "'s XP from " + std::to_string(UnitList[3].level) + " to " + std::to_string(UnitList[3].level + 1) + "\n     " + std::to_string((int)UnitList[3].currentExp) + " --> " + std::to_string((int)(UnitList[3].currentExp + expdrop)));     Unit3->setPosition(30,225);  Unit3->setTextSize(16);

    if(Message == "Victory!"){
        if(!Done){
            if(UnitList.at(0).currentExp >= UnitList.at(0).ExpNextLvL){
                for(int i = 0; i < 4 ; i++){
                    UnitList.at(i).level += 1;
                    UnitList.at(i).currentExp = 0;
                    UnitList.at(i).ExpNextLvL *= 0.05;

                    UnitList.at(i).MaxHP += 10;
                    UnitList.at(i).MaxMP += 10;

                    UnitList.at(i).Attack += 2;
                    UnitList.at(i).Defence += 2;
                    UnitList.at(i).MagicAttack += 2;
                    UnitList.at(i).MagicAttack += 2;
                    UnitList.at(i).Accuracy += 0;
                    UnitList.at(i).Evade += 0;
                }


                lvlUp = true;
                unit = 0;
                Done = true;
            } else{
                for(int i = 0; i < 4 ; i++){
                    UnitList.at(i).currentExp += expdrop;
                }
                unit = 3;
                Done = true;
                lvlUp = false;
            }
        }
    }else{
        if(!Done){
            unit = 3;
            lvlUp = false;
            Done = true;
        }
    }


    auto LEVELUP = tgui::Label::create("Level Up!");
    LEVELUP->setPosition(42,65);
    LEVELUP->setTextSize(26);

    auto Name  = tgui::Label::create(UnitList[unit].Name + " Just lvl up!");     Name->setPosition(30,105);  Name->setTextSize(16);
    auto Level  = tgui::Label::create("LVL        " + std::to_string((int)UnitList[unit].level) + " --> " + std::to_string((int)UnitList[unit].level + 1) );     Level->setPosition(30,125);  Level->setTextSize(16);
    auto MaxHP  = tgui::Label::create("MaxHP   " + std::to_string((int)UnitList[unit].MaxHP) + " + 10");     MaxHP->setPosition(30,145);  MaxHP->setTextSize(16);
    auto MaxMP  = tgui::Label::create("MaxMP   " + std::to_string((int)UnitList[unit].MaxMP) + " + 10");     MaxMP->setPosition(30,165);  MaxMP->setTextSize(16);
    auto ATC    = tgui::Label::create("ATC        " + std::to_string((int)UnitList[unit].Attack) + " + 2");        ATC->setPosition(30,185);    ATC->setTextSize(16);
    auto DEF    = tgui::Label::create("DEF        " + std::to_string((int)UnitList[unit].Defence) + " + 2");       DEF->setPosition(30,205);    DEF->setTextSize(16);
    auto MAT    = tgui::Label::create("MAT        " + std::to_string((int)UnitList[unit].MagicAttack) + " + 2");   MAT->setPosition(30,225);    MAT->setTextSize(16);
    auto MDF    = tgui::Label::create("MDF       " + std::to_string((int)UnitList[unit].MagicDefence) + " + 2");  MDF->setPosition(30,245);    MDF->setTextSize(16);
    auto ACC    = tgui::Label::create("ACC        " + std::to_string((int)UnitList[unit].Accuracy) + " + 0");      ACC->setPosition(30,265);    ACC->setTextSize(16);
    auto EVA    = tgui::Label::create("EVA        " + std::to_string((int)UnitList[unit].Evade) + " + 0");         EVA->setPosition(30,285);    EVA->setTextSize(16);

    Panel->add(Picture);
    Panel->add(Title);

    if(!lvlUp){
        Panel->add(Unit0);  Panel->add(Unit1);  Panel->add(Unit2);  Panel->add(Unit3);
    }else{

        Panel->add(LEVELUP);
        Panel->add(Name);   Panel->add(Level);
        Panel->add(MaxHP);  Panel->add(MaxMP);
        Panel->add(ATC);    Panel->add(DEF);
        Panel->add(MAT);    Panel->add(MDF);
        Panel->add(ACC);    Panel->add(EVA);
    }

    auto Next = tgui::Button::create("Next");
    Next->setTextSize(16);
    Next->setSize(50,25);
    Next->setPosition("54%","46%");

    Next->connect("Pressed",[=](){unit++; update = true;});

    Bgui.add(Panel);
    Bgui.add(Next);

    if(unit == 4){
        std::cout << "hello" <<std::endl;
        reset();
        *currentstate = "Overworld";
    }


};

void BattleControlls::Attack(std::string Attacktype, std::string tag)
{
    bool Done;
    information = "";

    if(tag == "Ally"){
        Done = AttackHandling(&UnitList[TheAttacker], &UnitList[TheAttackee], Attacktype);
        if(UnitList[TheAttackee].HP < 0){
            UnitList[TheAttackee].HP = 0;
        }
        if(UnitList[TheAttackee].MP < 0){
            UnitList[TheAttackee].MP = 0;
        }
    } else if (tag == "Enemy") {
        int Aichoice = AI100IQ(UnitList);
        Done = AttackHandling(&UnitList[TheAttacker], &UnitList[Aichoice], Attacktype);
        if(UnitList[Aichoice].HP < 0){
            UnitList[Aichoice].HP = 0;
        }
        if(UnitList[Aichoice].MP < 0){
            UnitList[Aichoice].MP = 0;
        }
    }
    if(Done){
        NextInQueue();
    } else {
        information = "Not Enough Mana";
    }
    update = true;
}

void BattleControlls::WinCondition() {

    int alive = amount;
    std::sort(checkqueue.begin(), checkqueue.end());
    for(auto &at : checkqueue){
        if(UnitList.at(at).tag == "Enemy"){
            if(UnitList.at(at).Dead){
                alive--;
            }
        }
    }

    checkQueue();

    if(UnitList[0].Dead && UnitList[1].Dead && UnitList[2].Dead && UnitList[3].Dead){
        Message = "Defeated";
        Victory = true;
        update = true;
    }else{
        if (alive == 0){
            Message = "Victory!";
            Victory = true;
            update = true;
        }
    }
}

void BattleControlls::checkQueue(){
    for(int i = 0; i < 4; i++){
        bool alive = true;
        std::queue<int> q = queue;
        while(!q.empty()){
            if(!UnitList[i].Dead){
                if(UnitList[i].index == q.front()){
                    alive = true;
                    break;
                }else if(UnitList[i].index != q.front()){
                    alive = false;
                }
            }
            q.pop();
        }
        if(!alive){
            queue.push(UnitList[i].index);
        }
    }
}

int random (int i) { return std::rand() % i;}

void printQueue(std::queue<int> q){
    while(!q.empty()){
        std::cout << std::to_string(q.front()) + " ";
        q.pop();
    }
    std::cout << std::endl;
}

void BattleControlls::setQueue(){
    std::srand(unsigned( std::time(0)));
    for (int i=0; i < UnitList.size(); ++i) checkqueue.push_back(i);
    std::random_shuffle(checkqueue.begin(), checkqueue.end());
    std::random_shuffle(checkqueue.begin(), checkqueue.end(), random);
    for (auto & it : checkqueue){
        queue.push(it);
    }
    TheAttacker = queue.front();
    NextInQueue();
}

//the function under checks if someone in the queue is dead, if they are their index is removed from the queue.
//this also checks who is at the front of the queue, then sends them back to the begining.
//this is done so that when the attack happens we just need to call queue.front() to see whos turn it is.

void BattleControlls::NextInQueue() {
    elapsedCDTime.restart();

    while(UnitList.at(queue.front()).Dead){
        queue.pop();
    }

    WhoAttack = UnitList.at(queue.front()).Name + "'s turn";
    TheAttacker = queue.front();
    if (UnitList[TheAttacker].tag == "Ally") {
        WhomsTurn = "Your turn";
        AllyTurn = true;
    } else {
        WhomsTurn = "Enemy turn";
        AllyTurn = false;
    }
    queue.push(queue.front());
    queue.pop();

    printQueue(queue);
    WinCondition();
    update = true;
}

void BattleControlls::selectedUpdate(){
    //who is selected by the player
    SelectedIndicator.setFillColor(sf::Color(0,255,255,100));
    SelectedIndicator.setPosition(UnitList[TheAttackee].shape.getPosition().x, UnitList[TheAttackee].shape.getPosition().y);
    SelectedIndicator.setSize(sf::Vector2f(UnitList[TheAttackee].shape.getSize().x, UnitList[TheAttackee].shape.getSize().y));
    //who is beeing attacked
    AttackerIndicator.setFillColor(sf::Color(255,0,255,100));
    AttackerIndicator.setPosition(UnitList[TheAttacker].shape.getPosition().x, UnitList[TheAttacker].shape.getPosition().y);
    AttackerIndicator.setSize(sf::Vector2f(UnitList[TheAttacker].shape.getSize().x, UnitList[TheAttacker].shape.getSize().y));

    if(UnitList[TheAttacker].Dead){
        NextInQueue();
    }

    if(UnitList[TheAttacker].Class == "Tank"){
        Attack1 = "Taunt 20MP";
        Attack2 = "Iron Skin 20MP";
        Attack3 = "None";
        Attack4 = "None";
    }else if(UnitList[TheAttacker].Class == "Mage"){
        Attack1 = "Fireball 20MP";
        Attack2 = "EXPLOSION 50%MP";
        Attack3 = "None";
        Attack4 = "None";
    }else if(UnitList[TheAttacker].Class == "Ranger"){
        Attack1 = "Dodge up 30MP";
        Attack2 = "SharpShoot 30MP";
        Attack3 = "None";
        Attack4 = "None";
    }else if(UnitList[TheAttacker].Class == "Fighter"){
        Attack1 = "Slash 15MP";
        Attack2 = "Cross Slash 20MP";
        Attack3 = "None";
        Attack4 = "None";
    }else if(UnitList[TheAttacker].Class == "Healer"){
        Attack1 = "Heal 20MP";
        Attack2 = "Revive 50%MP";
        Attack3 = "None";
        Attack4 = "None";
    }else if(UnitList[TheAttacker].Class == "None"){
        Attack1 = "None";
        Attack2 = "None";
        Attack3 = "None";
        Attack4 = "None";
    }

}

void BattleControlls::reset(){
    std::cout << "hello" << std::endl;

    newBattle = true;
    update = true;

    Victory = false;

    Done = false;
    lvlUp = false;
    unit = 0;

    battleMenu = 1;


    UnitList[0].HP = UnitList[0].MaxHP;   UnitList[0].MP = UnitList[0].MaxMP;   UnitList[0].Dead = false;
    UnitList[1].HP = UnitList[1].MaxHP;   UnitList[1].MP = UnitList[1].MaxMP;   UnitList[1].Dead = false;
    UnitList[2].HP = UnitList[2].MaxHP;   UnitList[2].MP = UnitList[2].MaxMP;   UnitList[2].Dead = false;
    UnitList[3].HP = UnitList[3].MaxHP;   UnitList[3].MP = UnitList[3].MaxMP;   UnitList[3].Dead = false;

    UnitList[1].Defence = armour;


    UnitList[0].Emnity = 0;
    UnitList[1].Emnity = 0;
    UnitList[2].Emnity = 0;
    UnitList[3].Emnity = 0;

    UnitList.erase(UnitList.begin() + 4, UnitList.end());


    while(!queue.empty()){
        queue.pop();
    }

    checkqueue.clear();


    Bgui.removeAllWidgets();

}

void BattleControlls::setEnemy(std::string Floor, std::string type){
    this->Floor = Floor; this->type = type;
    if(type == "enemy"){
        amount = 4;
    }else if(type == "boss"){
        amount = 1;
    }
}

Units BattleControlls::getUnitList(int i){
    return UnitList[i];
}

void BattleControlls::cPot(Potion &pot, Units &too) {
    if(AllyTurn && UnitList[TheAttackee].tag == "Ally") {
        if (pot.numberOfPotions > 0) {//Checks if you have potions
            std::cout << std::endl;
            std::cout << "The potion heals: ";
            std::cout << pot.amount << std::endl;
            if (!too.Dead) {
                too.HP = too.HP + (float) pot.amount;//Health is Increased by the amount in potion.
            }
            if (too.HP > too.MaxMP) {
                too.HP = too.MaxHP;//If Current health is over max healt, it is put down to max
            }
            pot.numberOfPotions--;
            std::cout << "Amount of potions left: ";
            std::cout << pot.numberOfPotions << std::endl;
            NextInQueue();
        } else {
            std::cout << "No potions left" << std::endl;
        }
        update = true;
        battleMenu = 1;
    }
}

void BattleControlls::Consume(tgui::ListBox::Ptr lista){
    int x=lista->getSelectedItemIndex();
    std::cout << std::to_string(x) + " hello i need jesus" << std::endl;
    cPot(listy.listOfPotions[x], UnitList[TheAttackee]);
}

void BattleControlls::Potions(sf::RenderWindow &window, listOfStuff listy) {

    auto child = tgui::ChildWindow::create();
    tgui::Theme theme("Themes/Black.txt");
    child->setRenderer(theme.getRenderer("ChildWindow"));
    child->setSize(290, 180);
    child->setPosition(250, 610);
    child->setTitle("Yer potions");

    tgui::ListBox::Ptr listBox1 = tgui::ListBox::create();
    listBox1->setSize(290, 100);
    listBox1->setPosition(0, 0);
    listBox1->setRenderer(theme.getRenderer("ListBox"));

    for (auto & listOfPotion : listy.listOfPotions) {
        std::string number = std::to_string(listOfPotion.numberOfPotions);
        std::string temp = listOfPotion.name + " : " + number;
        listBox1->addItem(temp);
    }



    auto btn = tgui::Button::create();
    btn->setPosition(40, 105);
    btn->setSize(100, 50);
    btn->setText("Consume Potion");
    btn->setRenderer(theme.getRenderer("Button"));
    btn->connect("Pressed",[=](){
        Consume(listBox1);
        update=true;
        battleMenu = 1;
    });//

    child->add(btn);
    child->add(listBox1);
    Bgui.add(child);
    if(battleMenu!=3){
        Bgui.remove(child);
    }
}


void BattleControlls::drawAll(sf::RenderWindow& window, std::string& currentstate) {

    sf::Event event;//Exit button

    float scale = 1;
    sf::Texture texture;
    sf::Sprite bgsprite;
    texture.loadFromFile("Pictures/Battleroom.png");
    bgsprite.setTexture(texture);
    bgsprite.setScale(scale, scale);

    if (newBattle) {
        listy.listOfPotions[0].numberOfPotions = 3;//Makes it so you start each new battle with 3 potions. Use the wisely
        if (CreateAlly) {
            createAlly();
            CreateAlly = false;
        }
        createEnemies();
        setQueue();
        newBattle = false;
    }

    window.clear();
    window.draw(bgsprite);

    selectedUpdate();


    if (update) {
        Bgui.removeAllWidgets();
        mainBButtons(window, battleMenu);//Handles which buttons is shown,2 for spec attacks, 3 for potions
        if (battleMenu == 2) {
            spesAtcBtns(window);
        } else if (battleMenu == 3) {
            Potions(window, listy);
        }
        healthPercent(window);
        if(Victory){
            VictoryScreen();
        }
        update = false;
    }

    if(!Victory){
        WinCondition();
    }


    sf::View view(sf::FloatRect(-375, -400, window.getSize().x, window.getSize().y));
    float zoom = 1;
    //Zoom in if higher resolution
    if(sf::VideoMode::getDesktopMode().width > 1920) {

        zoom = std::min(.5f, zoom + .1f);

        view.setSize(window.getDefaultView().getSize());
        view.zoom(zoom);
        window.setView(view);
    }
    else {
        view.move(375, 400); //Focus view on player
    }

    if (!AllyTurn) {
        if ((int) (elapsedCDTime.getElapsedTime() / cooldownTime) > 1) {
            elapsedCDTime.restart();
            if(!Victory){
                Attack("Basic", "Enemy");
            }
        }
    } else {
        window.draw(SelectedIndicator);
        window.draw(AttackerIndicator);
    }

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        Bgui.handleEvent(event);
    }

    window.setView(view);
    drawBottom(window);

    Bgui.draw();
    window.draw(SelectedIndicator);
    window.draw(AttackerIndicator);

    for (auto &chara : UnitList) {
        if (chara.shape.getGlobalBounds().contains(
                window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                TheAttackee = chara.index;
            }
        }

        chara.tick();
        chara.render();
        if(!chara.Dead) {
            if (chara.Protagonist) {
                image1.loadFromFile("Pictures/CharCreate/hairchoices.png");
                texture1.loadFromImage(image1, {(32 * hair), 0, 32, 32});
                image2.loadFromFile("Pictures/CharCreate/uniformchoice.png");
                texture2.loadFromImage(image2, {(32 * uniform), 0, 32, 32});
                image3.loadFromFile("Pictures/CharCreate/skinchoice.png");
                texture3.loadFromImage(image3, {(32 * skin), 0, 32, 32});


                chara.shape2.setTexture(&texture1);
                chara.shape1.setTexture(&texture2);
                chara.shape.setTexture(&texture3);

                window.draw(chara.shape);
                window.draw(chara.shape2);
                window.draw(chara.shape1);
            } else
                window.draw(chara.shape);
        }
    }

    window.display();
}

