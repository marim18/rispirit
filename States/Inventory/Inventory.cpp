#include "../Battlestate/BattleControlls.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <algorithm>
#define SFML_NO_DEPRECATED_WARNINGS
#include <TGUI/TGUI.hpp>
#include "Items.h"
#include "Inventory.h"
Inventory::Inventory(){
    //

}
void Inventory::DrawInv(sf::RenderWindow& window,std::string& curentstate){//Will optimize

    listOfStuff listy;

    Igui.setTarget(window);

    std::string title;
    auto child = tgui::ChildWindow::create();
    tgui::Theme theme("Themes/Black.txt");
    child->setRenderer(theme.getRenderer("ChildWindow"));
    child->setSize(400, 800);
    child->setPosition(0, 0);
    child->setTitle("Yer weapons");

    auto listBox = tgui::ListBox::create();
    listBox->setSize(400,600);
    listBox->setPosition(0,0);
    listBox->setRenderer(theme.getRenderer("ListBox"));

if(menu){
    for(int i=0; i<listy.listOfWeapons.size(); i++){
        std::string number = std::to_string(listy.listOfWeapons[i].standardDamage);
        std::string number1 = std::to_string(listy.listOfWeapons[i].magicDamage);
        std::string temp =listy.listOfPotions[i].name+" Dmg"+number+" Magic Dmg"+number1;
        listBox->addItem(temp);
        title = "Yer weapons";
    }
}else if(!menu){
    for(int i=0; i<listy.listOfArmour.size(); i++){
        std::string number = std::to_string(listy.listOfArmour[i].standardProtection);
        std::string number1 = std::to_string(listy.listOfArmour[i].magicProtection);
        std::string temp =listy.listOfPotions[i].name+" Dmg"+number+" Magic Dmg"+number1;
        listBox->addItem(temp);
        title = "Yer armour";
    }
}
    auto btn = tgui::Button::create();
    btn->setPosition(0,150);
    btn->setSize(70,30);
    btn->setText("Equip");
    btn->setRenderer(theme.getRenderer("Button"));

    auto swap = tgui::Button::create();
    swap->setPosition(0,750);
    swap->setSize(200,50);
    swap->setText("Change menu");
    swap->setRenderer(theme.getRenderer("Button"));
    swap->connect("pressed",[&](){menu = !menu;});

    auto exit = tgui::Button::create();
    exit->setRenderer(theme.getRenderer("Button"));
    exit->setSize(180,30);
    exit->setPosition(620,770);
    exit->setText("Return");
    exit->connect("pressed", [&](){curentstate = "Overworld";});
    auto equip = tgui::Button::create();
    equip->setRenderer(theme.getRenderer("Button"));
    equip->setSize(180,30);
    equip->setPosition(620,730);
    equip->setText("Equip");
    equip->connect("pressed", [&](){std::cout << "Equipped";});

    sf::Event event;//Exit button
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
            window.close();}
        //battle.Bgui.handleEvent(event);
        Igui.handleEvent(event);
    }
    window.clear();

    child->add(listBox);
    Igui.add(child);
    Igui.add(equip);
    Igui.add(exit);
    Igui.draw();

    window.display();
}