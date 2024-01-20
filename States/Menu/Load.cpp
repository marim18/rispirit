//
// Created by Eier on 08.11.2019.
//

#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>

#include "Load.h"

void Load::ReadFile(std::string focus){
    Json::Value root;

    //setup readable file
    std::ifstream inputfilestream("States/Menu/Saves.json");

    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    bool parsingSuccsessful = Json::parseFromStream(readerBuilder, inputfilestream, &root, &errors);
    if(!parsingSuccsessful){
        std::cout << errors << std::endl;
    }
    //end

    if(root[focusSave]["InUse"].asBool() && !focusSave.empty()){ //if file is in use, read
        name = root[focusSave]["Name"].asString();
        levelState = root[focusSave]["LevelState"].asString();

        fromsave = focusSave;

        protvec.x = root[focusSave]["Position"]["x"].asFloat();
        protvec.y = root[focusSave]["Position"]["y"].asFloat();

        Head = root[focusSave]["Sprite"]["Head"].asInt();
        Uniform = root[focusSave]["Sprite"]["Uniform"].asInt();
        Skin = root[focusSave]["Sprite"]["Skin"].asInt();
        std::cout << Head <<std::endl;

        protText.clear();
        protText.push_back(mainTexture(1));
        protText.push_back(mainTexture(2));
        protText.push_back(mainTexture(3));
        pro->setTexture(&protText[0]);
        pro_2->setTexture(&protText[1]);
        pro_3->setTexture(&protText[2]);
        update = false;

        *currentstate = "Overworld";

    }else{
        std::cout << "nothing happened" << std::endl;
    }

    Save1txt = root["Save1"]["Name"].asString();
    Save2txt = root["Save2"]["Name"].asString();
    Save3txt = root["Save3"]["Name"].asString();
    Save4txt = root["Save4"]["Name"].asString();

    inputfilestream.close();
}

void Load::loadLoad(tgui::Gui& gui, AudioHandler& audio){// initializes what is on the gui

    tgui::Theme theme("Themes/Custom.txt");// the looks of the widgets
    auto picture = tgui::Picture::create("Pictures/Menu/WierdBook.png");//creates a background picture
    picture->setSize({"100%", "100%"});

    auto Save1 = tgui::Button::create(Save1txt);// creates a tgui button with initializers
    Save1->setRenderer(theme.getRenderer("Button"));
    Save1->setSize({"40%", "20%"});
    Save1->setTextSize(34);
    Save1->setPosition({"50%", "9%"});

    auto Save2 = tgui::Button::create(Save2txt);// creates a tgui button with initializers
    Save2->setRenderer(theme.getRenderer("Button"));
    Save2->setSize({"40%", "20%"});
    Save2->setTextSize(34);
    Save2->setPosition({"50%", "30%"});

    auto Save3 = tgui::Button::create(Save3txt);// creates a tgui button with initializers
    Save3->setRenderer(theme.getRenderer("Button"));
    Save3->setSize({"40%", "20%"});
    Save3->setTextSize(34);
    Save3->setPosition({"50%", "51%"});

    auto Save4 = tgui::Button::create(Save4txt);// creates a tgui button with initializers
    Save4->setRenderer(theme.getRenderer("Button"));
    Save4->setSize({"40%", "20%"});
    Save4->setTextSize(34);
    Save4->setPosition({"50%", "72%"});

    auto Back = tgui::Button::create("Back");// creates a tgui button with initializers
    Back->setRenderer(theme.getRenderer("Button"));
    Back->setSize("200", "50");
    Back->setTextSize(34);
    Back->setPosition({"10%", "85%"});


    //add the buttons the the gui
    gui.add(picture);
    gui.add(Save1);
    gui.add(Save2);
    gui.add(Save3);
    gui.add(Save4);
    gui.add(Back);

    //functions for the buttons
    Save1->connect("pressed", [&](){focusSave = "Save1"; update = true; ReadFile("Save1");});
    Save2->connect("pressed", [&](){focusSave = "Save2"; update = true; ReadFile("Save2");});
    Save3->connect("pressed", [&](){focusSave = "Save3"; update = true; ReadFile("Save3");});
    Save4->connect("pressed", [&](){focusSave = "Save4"; update = true; ReadFile("Save4");});

    Back->connect("pressed", [&](){*currentstate = "Menu"; audio.playSound("Audio/Sound.wav"); update = false;});
}


sf::Texture Load::mainTexture(int option){
    sf::Image picture;
    sf::Texture mainTexture;
    if (option == 1) {
        picture.loadFromFile("Pictures/CharCreate/skinchoice.png");
        mainTexture.loadFromImage(picture, {(32 * Skin) + 6, 0, 21, 32});
    } else if (option == 2) {
        picture.loadFromFile("Pictures/CharCreate/hairchoices.png");
        mainTexture.loadFromImage(picture, {(32 * Head) + 4, 0, 25, 32});
    } else if (option == 3) {
        picture.loadFromFile("Pictures/CharCreate/uniformchoice.png");
        mainTexture.loadFromImage(picture, {(32 * Uniform) + 6, 0, 21, 32});
    }
    return mainTexture;
}

void Load::getname(){
    Json::Value root;

    //setup readable file
    std::ifstream inputfilestream("States/Menu/Saves.json");

    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    bool parsingSuccsessful = Json::parseFromStream(readerBuilder, inputfilestream, &root, &errors);//clones the file into json::value root so we can easely accsess the value
    if(!parsingSuccsessful){
        std::cout << errors << std::endl;
    }

    Save1txt = root["Save1"]["Name"].asString();
    Save2txt = root["Save2"]["Name"].asString();
    Save3txt = root["Save3"]["Name"].asString();
    Save4txt = root["Save4"]["Name"].asString();

    inputfilestream.close();

}

void Load::Run(tgui::Gui *gui, sf::RenderWindow *window, AudioHandler& audio) {// a piece of the game loop that draws what is on the screen

    if(!update){//initializes and updates the tgui::gui once. if this is in the loop aka initializes it multiple times causes the buttons to not work
        getname();
        loadLoad(*gui, audio);
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