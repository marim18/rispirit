#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "States/Overworld/overworld.h"
#include "States/Menu/Menu.h"
#include "States/Menu/Load.h"
#include "States/Menu/Save.h"
#include "States/Menu/Settings.h"
#include "States/Menu/Extras.h"
#include "States/Menu/CharacterCreation.h"
#include "States/Menu/Pause.h"
#include "States/Battlestate/BattleControlls.h"
#include "States/Inventory/Inventory.h"

int main() {
    AudioHandler audio;

    sf::VideoMode videoMode;
    float zoom = 1;
    if(sf::VideoMode::getDesktopMode().width > 1920) {

        videoMode.width = 1600;
        videoMode.height = 1600;
        //sf::RenderWindow window{sf::VideoMode{1200,1200}, "test"};


    }else{
        videoMode.width = 800;
        videoMode.height = 800;
    }

    std::cout << sf::VideoMode::getDesktopMode().width;
    //Create window to be used
    sf::RenderWindow window{videoMode, "Project Riverspirit"};
    tgui::Gui gui(window);
    window.setVerticalSyncEnabled(true);
    // Enable vertical sync - prevents tearing and locks framerate to display

    sf::Image icon;
    icon.loadFromFile("Pictures/Leaf.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
   /* sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x /2,view.getSize().y /2);
    view.setCenter(view.getCenter().x /2, view.getCenter().y /2);
    window.setView(view);
*/

    std::string currentState = "Menu"; //Determine current state
    std::string prevState;

    overworld overworld; //Initialize overworld class

    Menu menu;
    Load load(&currentState);
    Save save;
    Settings settings(&audio);
    //settings//
    audio.mastervolume(settings.Mastervolume);
    audio.soundvolume(settings.Soundvolume);
    audio.MusicVolume(settings.Musicvolume);
    //========//
    Extras extras;
    CharacterCreation CC;
    BattleControlls battle(&currentState);
    Pause pause;
    Inventory inv;

    sf::View view = window.getDefaultView();

    while(window.isOpen()){ //Keep running while game is active
        if(currentState == "Overworld"){ //Check current state
            overworld.runOverworld(&window,&currentState); //Run main overworld function by inserting pointers to the window and state
        }
        else if(currentState == "Battle"){
            battle.setEnemy(overworld.currentMapName , overworld.enemyType);
            battle.drawAll(window, currentState);
        }
        else if(currentState == "Exit"){
            window.close();
        }
        else if(currentState == "Menu"){
            menu.Run(&gui, &window, &prevState ,&currentState, audio);
            CC.setName("");
        }
        else if(currentState == "StartGame"){
            CC.Run(&gui, &window, &currentState, audio);
            CC.pro = &overworld.protagonist;
            CC.pro_2 = &overworld.protagonist_2;
            CC.pro_3 = &overworld.protagonist_3;
            overworld.protagPos = sf::Vector2f(500, 1300);
            overworld.loadMap("Map_Layout_Intro");
            battle.SetAlly(CC.getHeadIndex(), CC.getSkinIndex(), CC.getUniformIndex(), CC.getName(), "Default");
            save.setCharacterCreation(CC.getName(), CC.getHeadIndex(), CC.getUniformIndex(),  CC.getSkinIndex()); //get int of texture of the charracter and name
        }
        else if(currentState == "Save") {
            save.Run(&gui, &window, &currentState, audio);
            save.setLevelState(overworld.currentMapName);
            save.setposition(overworld.protagPos);
            save.setUnits(battle.UnitList);
        }
        else if(currentState == "Inventory"){
            inv.DrawInv(window, currentState);
        }
        else if(currentState == "Load") {
            load.Run(&gui, &window, audio);
            overworld.protagPos = load.protvec;
            overworld.loadMap(load.levelState);
            load.pro = &overworld.protagonist;
            load.pro_2 = &overworld.protagonist_2;
            load.pro_3 = &overworld.protagonist_3;
            battle.SetAlly(load.Head, load.Skin, load.Uniform, load.name, load.fromsave);
            save.setCharacterCreation(load.name, load.Head, load.Uniform, load.Skin);

        }
        else if(currentState == "Settings"){
            settings.Run(&gui, &window, &prevState, &currentState);
        }
        else if(currentState == "Extras"){
            extras.Run(&gui, &window, &currentState, audio);
        }
        else if(currentState == "Pause"){
            pause.Run(&gui, &window, &prevState ,&currentState, audio);
        }
    }


    return 0;
}