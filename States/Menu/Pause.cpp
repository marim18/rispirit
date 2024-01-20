#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Pause.h"
#include "../AudioHandler.h"

void Pause::loadPause(tgui::Gui& gui, std::string& PrevState, std::string& curentstate, AudioHandler& audio){//initializing the gui

    tgui::Theme theme("Themes/Custom.txt");// the looks of the widgets

    auto MainMenu = tgui::Button::create("Main Menu");// create buttons with tgui and sets parameters for the buttons
    MainMenu->setRenderer(theme.getRenderer("Button"));
    MainMenu->setSize("25%", "6,3%");
    MainMenu->setTextSize(34);
    MainMenu->setPosition({"37,5%", "37,5%"});

    auto Save = tgui::Button::create("Save");// create buttons with tgui and sets parameters for the buttons
    Save->setRenderer(theme.getRenderer("Button"));;
    Save->setSize("25%", "6,3%");
    Save->setTextSize(34);
    Save->setPosition({"37,5%", "44,4%"});

    auto Settings = tgui::Button::create("Settings");// create buttons with tgui and sets parameters for the buttons
    Settings->setRenderer(theme.getRenderer("Button"));
    Settings->setSize("25%", "6,3%");
    Settings->setTextSize(34);
    Settings->setPosition({"37,5%", "51,3%"});

    auto Exit = tgui::Button::create("Back");// create buttons with tgui and sets parameters for the buttons
    Exit->setRenderer(theme.getRenderer("Button"));
    Exit->setSize("25%", "6,3%");
    Exit->setTextSize(34);
    Exit->setPosition({"37,5%", "58,1%"});

    // add the widgets to the gui
    gui.add(MainMenu);
    gui.add(Save);
    gui.add(Settings);
    gui.add(Exit);

    //functions of the buttons
    MainMenu->connect("pressed", [&](){curentstate = "Menu"; audio.playSound("Audio/Sound.wav"); update = false;});
    Save->connect("pressed", [&](){curentstate = "Save"; audio.playSound("Audio/Sound.wav"); update = false;});
    Settings->connect("pressed",  [&](){curentstate = "Settings"; PrevState = "Pause"; audio.playSound("Audio/Sound.wav"); update = false;});
    Exit->connect("pressed", [&](){curentstate = "Overworld"; audio.playSound("Audio/Sound.wav"); update = false;});

}

void Pause::Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *PrevState, std::string *currentstate, AudioHandler& audio) {// a piece of the game loop that draws what is on the screen


    if(!update){//initializes and updates the tgui::gui once. if this is in the loop aka initializes it multiple times causes the buttons to not work
        gui->removeAllWidgets();
        loadPause(*gui, *PrevState, *currentstate, audio);
        update = true;
    }

    sf::Event event;

    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed)
            window->close();

        gui->setView(window->getView());
        gui->handleEvent(event);

    }

    sf::View view(sf::FloatRect(-800/2+25,-800/2,window->getSize().x,window->getSize().y));
    view.move(375,400); //Focus view on player

    window->setView(view);

    window->clear(AlphaBlack);
    //========[render objects]========//
    gui->draw();
    //================================//
    window->display();

}
