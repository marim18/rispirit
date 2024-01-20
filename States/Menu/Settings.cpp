#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Settings.h"

void Settings::loadSettings(tgui::Gui& gui, std::string& PrevState, std::string& curentstate){

    tgui::Theme theme("Themes/Custom.txt");// the looks of the widgets

    auto picture = tgui::Picture::create("Pictures/Menu/settings.png");// creates the background picture
    picture->setSize({"100%", "100%"});
    gui.add(picture);

    auto Game = tgui::Button::create("Game");// create buttons with tgui and sets parameters for the buttons
    Game->setRenderer(theme.getRenderer("Button"));
    Game->setSize("12,5%", "5%");
    Game->setTextSize(14);
    Game->setPosition({"9,25%", "3,4%"});
    gui.add(Game);

    auto Volume = tgui::Button::create("Volume");// create buttons with tgui and sets parameters for the buttons
    Volume->setRenderer(theme.getRenderer("Button"));
    Volume->setSize("12,5%", "5%");
    Volume->setTextSize(14);
    Volume->setPosition({"21,8%", "3,4%"});
    gui.add(Volume);

    auto Keybinding = tgui::Button::create("Keybindings");// create buttons with tgui and sets parameters for the buttons
    Keybinding->setRenderer(theme.getRenderer("Button"));
    Keybinding->setSize("12,5%", "5%");
    Keybinding->setTextSize(14);
    Keybinding->setPosition({"34,3%", "3,4%"});
    gui.add(Keybinding);

    if(selected == 1){ //sets what to initialize

        Game->setFocused(true); // makes it so the button "Game" gets highlighted

        auto GTitle = tgui::Label::create("Game Settings");// add text to the gui
        GTitle->setPosition("12,5%","15,6%");
        GTitle->setTextSize(60);
        gui.add(GTitle);

        auto Vsync = tgui::Button::create();// create buttons with tgui and sets parameters for the buttons
        Vsync->setText("Vsync: " + vynchstring);
        Vsync->setRenderer(theme.getRenderer("Button"));
        Vsync->setSize("25%", "5%");
        Vsync->setTextSize(34);
        Vsync->setPosition({"14,5%", "29,8%"});
        gui.add(Vsync);

        Vsync->connect("pressed", [&](){
            if(VSync){
                VSync = false; vynchstring = "off";}
            else{
                VSync = true; vynchstring = "on";}
            audio->playSound("Audio/Sound.wav");
            update = false;
        });// functions for the button

    }

    if(selected == 2){//sets what to initialize

        Volume->setFocused(true);// makes it so the button "Game" gets highlighted

        auto GTitle = tgui::Label::create("Volume \n       Settings"); // add text to the gui
        GTitle->setPosition("15%","9,6%");
        GTitle->setTextSize(60);
        gui.add(GTitle);

        auto MasterVolumeText = tgui::Label::create("Master Volume:"); // add text to the gui
        MasterVolumeText->setTextSize(40);
        MasterVolumeText->setPosition({"14,4%", "30%"});
        gui.add(MasterVolumeText);

        auto SoundVolumeText = tgui::Label::create("Sound Volume:"); // add text to the gui
        SoundVolumeText->setTextSize(40);
        SoundVolumeText->setPosition({"14,4%", "45,6%"});
        gui.add(SoundVolumeText);

        auto MusicVolumeText = tgui::Label::create("Music Volume:"); // add text to the gui
        MusicVolumeText->setTextSize(40);
        MusicVolumeText->setPosition({"14,4%", "61,3%"});
        gui.add(MusicVolumeText);

        auto MstrVolSlider = tgui::Slider::create();// creates a tgui slider
        MstrVolSlider->setRenderer(theme.getRenderer("Slider"));
        MstrVolSlider->setPosition({"14,4%", "38,8%"});
        MstrVolSlider->setSize("34,4%", "2,3%");
        MstrVolSlider->setMaximum(50);
        MstrVolSlider->setMinimum(1);
        MstrVolSlider->setValue(Mastervolume);
        gui.add(MstrVolSlider);

        auto SoundVolSlider = tgui::Slider::create();// creates a tgui slider
        SoundVolSlider->setRenderer(theme.getRenderer("Slider"));
        SoundVolSlider->setPosition({"14,4%", "54,6%"});
        SoundVolSlider->setSize("34,4%", "2,3%");
        SoundVolSlider->setMaximum(100);
        SoundVolSlider->setMinimum(0);
        SoundVolSlider->setValue(Soundvolume);
        gui.add(SoundVolSlider);

        auto MscVolSlider = tgui::Slider::create();// creates a tgui slider
        MscVolSlider->setRenderer(theme.getRenderer("Slider"));
        MscVolSlider->setPosition({"14,4%", "70,4%"});
        MscVolSlider->setSize("34,4%", "2,3%");
        MscVolSlider->setMaximum(100);
        MscVolSlider->setMinimum(0);
        MscVolSlider->setValue(Musicvolume);
        gui.add(MscVolSlider);

        //functions for the sliders
        MstrVolSlider->connect("ValueChanged", [=](){Mastervolume = MstrVolSlider->getValue();});
        SoundVolSlider->connect("ValueChanged", [=](){Soundvolume = SoundVolSlider->getValue();});
        MscVolSlider->connect("ValueChanged", [=](){Musicvolume = MscVolSlider->getValue();});
    }

    if(selected == 3){//sets what to initialize

        Keybinding->setFocused(true);// makes it so the button "Game" gets highlighted

    }

    auto Back = tgui::Button::create("Back");// create buttons with tgui and sets parameters for the buttons
    Back->setRenderer(theme.getRenderer("Button"));
    Back->setSize("18,8%", "5%");
    Back->setTextSize(34);
    Back->setPosition({"14,5%", "84,6%"});
    gui.add(Back);

    //functions for the buttons
    Game->connect("pressed", [&](){selected = 1; audio->playSound("Audio/Sound.wav"); update = false;});
    Volume->connect("pressed", [&](){selected = 2; audio->playSound("Audio/Sound.wav"); update = false;});
    Keybinding->connect("pressed", [&](){selected = 3; audio->playSound("Audio/Sound.wav"); update = false;});
    Back->connect("pressed", [&](){selected = 1; curentstate = PrevState; audio->playSound("Audio/Sound.wav"); update = false;});
}

void Settings::Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *PrevState, std::string *currentstate) {// a piece of the game loop that draws what is on the screen

    if(!update){//initializes and updates the tgui::gui once. if this is in the loop aka initializes it multiple times causes the buttons to not work
        gui->removeAllWidgets();
        loadSettings(*gui, *PrevState, *currentstate);
        window->setVerticalSyncEnabled(VSync);
        update = true;
    }

    audio->soundvolume(Soundvolume);
    audio->MusicVolume(Musicvolume);
    audio->mastervolume(Mastervolume);

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
