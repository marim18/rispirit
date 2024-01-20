#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "../AudioHandler.h"

void Menu::loadMenu(tgui::Gui& gui, std::string& prevstate, std::string& curentstate, AudioHandler& audio){//initializing the gui

    tgui::Theme theme("Themes/Custom.txt");// the looks of the widgets


    auto picture = tgui::Picture::create("Pictures/Menu/MenuTitle.jpg");// creates the background
    picture->setSize({"100%", "100%"});




    auto StartGame = tgui::Button::create("Start Game");// create buttons with tgui and sets parameters for the buttons
    StartGame->setRenderer(theme.getRenderer("Button"));
    StartGame->setSize("25%", "5%");
    StartGame->setTextSize(34);
    StartGame->setPosition({"37%", "52%"});


    auto Load = tgui::Button::create("Load");// create buttons with tgui and sets parameters for the buttons
    Load->setRenderer(theme.getRenderer("Button"));;
    Load->setSize("25%", "5%");
    Load->setTextSize(34);
    Load->setPosition({"37%", "59%"});

    auto Settings = tgui::Button::create("Settings");// create buttons with tgui and sets parameters for the buttons
    Settings->setRenderer(theme.getRenderer("Button"));
    Settings->setSize("25%", "5%");
    Settings->setTextSize(34);
    Settings->setPosition({"37%", "66%"});

    auto Extras = tgui::Button::create("Extras");// create buttons with tgui and sets parameters for the buttons
    Extras->setRenderer(theme.getRenderer("Button"));
    Extras->setSize("25%", "5%");
    Extras->setTextSize(34);
    Extras->setPosition({"37%", "73%"});

    auto Exit = tgui::Button::create("Exit");// create buttons with tgui and sets parameters for the buttons
    Exit->setRenderer(theme.getRenderer("Button"));
    Exit->setSize("25%", "5%");
    Exit->setTextSize(34);
    Exit->setPosition({"37%", "80%"});

    // add the widgets to the gui
    gui.add(picture);
    gui.add(StartGame);
    gui.add(Load);
    gui.add(Settings);
    gui.add(Extras);
    gui.add(Exit);


    //functions of the buttons
    StartGame->connect("pressed", [&](){curentstate = "StartGame"; audio.playSound("Audio/Sound.wav"); update = false;});
    Load->connect("pressed", [&](){curentstate = "Load"; audio.playSound("Audio/Sound.wav"); update = false;});
    Settings->connect("pressed",  [&](){curentstate = "Settings"; prevstate = "Menu"; audio.playSound("Audio/Sound.wav"); update = false;});
    Extras->connect("pressed",  [&](){curentstate = "Extras"; audio.playSound("Audio/Sound.wav"); update = false;});
    Exit->connect("pressed", [&](){curentstate = "Exit"; audio.playSound("Audio/Sound.wav"); update = false;});

}

void Menu::Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *prevState, std::string *curentState, AudioHandler& audio) {// a piece of the game loop that draws what is on the screen


    if(!update){
        gui->removeAllWidgets();
        if(!audio.IfMusicPlaying())
        audio.playmusic("Audio/Music.ogg");
        loadMenu(*gui, *prevState, *curentState, audio);
        update = true;
    }

    sf::Event event;

    while(window->pollEvent(event)){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        if(event.type == sf::Event::Closed)
            window->close();

        gui->setView(window->getView());
        gui->handleEvent(event);

    }

    window->clear(sf::Color::Black);
    //========[render objects]========//
    gui->draw();
    //================================//
    window->display();

}
