//
// Created by Eier on 08.11.2019.
//

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Extras.h"
#include "../AudioHandler.h"

void Extras::loadExtras(tgui::Gui& gui, std::string& curentstate, AudioHandler& audio){// to load the tgui::Gui, aka a initializer for the GUI.

    tgui::Theme theme("Themes/Custom.txt");// the looks of the widgets

    auto picture = tgui::Picture::create("Pictures/creditsd.png");// creates the background picture
    picture->setSize({"100%", "100%"});// sets size of the background


    auto Back = tgui::Button::create("Back");// creates a tgui button with initilizers
    Back->setRenderer(theme.getRenderer("Button"));
    Back->setSize("20%", "4%");
    Back->setTextSize(34);
    Back->setPosition({"15%", "90%"});

    // adding to the GUI
    gui.add(picture);

    gui.add(Back);

    //functions for the button
    Back->connect("pressed", [&](){curentstate = "Menu"; audio.playSound("Audio/Sound.wav"); update = false;});

}


void Extras::Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *currentstate, AudioHandler& audio) {// the part of the game loop that draws what is on the screen

    if (!update) {// initializes and updates the tgui::gui once. if this is in the loop aka initializes it multiple times causes the buttons to not work
        gui->removeAllWidgets();
        loadExtras(*gui, *currentstate, audio);
        update = true;
    }

    sf::Event event;

    while (window->pollEvent(event)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        if (event.type == sf::Event::Closed)
            window->close();

        gui->setView(window->getView());
        gui->handleEvent(event);

    }

    window->clear(sf::Color::White);
    //========[render objects]========//
    gui->draw();
    //================================//
    window->display();

}