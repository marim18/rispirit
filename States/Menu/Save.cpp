#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>

#include "Save.h"
#include "../AudioHandler.h"

void Save::WriteToFile(){
    Json::Value root;

    //setup readable file
    std::ifstream inputfilestream("States/Menu/Saves.json");

    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    bool parsingSuccsessful = Json::parseFromStream(readerBuilder, inputfilestream, &root, &errors);//clones the file into json::value root so we can easely accsess the value
    if(!parsingSuccsessful){
        std::cout << errors << std::endl;
    }
    //end
    if(!focusSave.empty() && !root[focusSave]["InUse"].asBool()) {
        root[focusSave]["InUse"] = true;
        root[focusSave]["Name"] = name;
        root[focusSave]["LevelState"] = levelState;

        root[focusSave]["Position"]["x"] = x;
        root[focusSave]["Position"]["y"] = y;

        root[focusSave]["Sprite"]["Head"] = Head;
        root[focusSave]["Sprite"]["Uniform"] = Uniform;
        root[focusSave]["Sprite"]["Skin"] = Skin;

        if(!allylist.empty()){
            for (int i = 0; i < 4; i++) {
                root[focusSave]["Ally"][std::to_string(i)]["Sprite"] = allylist.at(i).skinpath;
                root[focusSave]["Ally"][std::to_string(i)]["SpritePos"] = allylist.at(i).spritepos;

                root[focusSave]["Ally"][std::to_string(i)]["Name"] = allylist.at(i).Name;

                root[focusSave]["Ally"][std::to_string(i)]["level"] = allylist.at(i).level;
                root[focusSave]["Ally"][std::to_string(i)]["currentExp"] = allylist.at(i).currentExp;
                root[focusSave]["Ally"][std::to_string(i)]["ExpNextLvL"] = allylist.at(i).ExpNextLvL;

                root[focusSave]["Ally"][std::to_string(i)]["HP"] = allylist.at(i).HP;
                root[focusSave]["Ally"][std::to_string(i)]["MP"] = allylist.at(i).MP;
                root[focusSave]["Ally"][std::to_string(i)]["Attack"] = allylist.at(i).Attack;
                root[focusSave]["Ally"][std::to_string(i)]["Defence"] = allylist.at(i).Defence;
                root[focusSave]["Ally"][std::to_string(i)]["MagicAttack"] = allylist.at(i).MagicAttack;
                root[focusSave]["Ally"][std::to_string(i)]["MagicDefence"] = allylist.at(i).MagicDefence;
                root[focusSave]["Ally"][std::to_string(i)]["Accuracy"] = allylist.at(i).Accuracy;
                root[focusSave]["Ally"][std::to_string(i)]["Evade"] = allylist.at(i).Evade;
                root[focusSave]["Ally"][std::to_string(i)]["Emnity"] = allylist.at(i).Emnity;

                root[focusSave]["Ally"][std::to_string(i)]["Class"] = allylist.at(i).Class;
            }
        }
    }
    //setup writable file
    Json::StreamWriterBuilder writerBuilder;
    const std::unique_ptr<Json::StreamWriter> streamwriter(writerBuilder.newStreamWriter());
    std::ofstream outputfilestream("States/Menu/Saves.json");
    streamwriter->write(root,&outputfilestream);//gets the value in root and writes it to the file
    //end


    Save1txt = root["Save1"]["Name"].asString();
    Save2txt = root["Save2"]["Name"].asString();
    Save3txt = root["Save3"]["Name"].asString();
    Save4txt = root["Save4"]["Name"].asString();

    //we open the file in both ways so that we can read and write to the file without losing any information(without open it rewrites the whole file not just the values)
    outputfilestream.close();
    inputfilestream.close();
}

void Save::ResetSave() {
    Json::Value root;
    Json::Value root2;

    //setup readable file
    std::ifstream inputfilestream("States/Menu/Saves.json");
    std::ifstream inputfilestream2("States/Menu/Saves.json");


    Json::CharReaderBuilder readerBuilder;
    std::string errors;
    bool parsingSuccsessful = Json::parseFromStream(readerBuilder, inputfilestream, &root, &errors);//clones the file into json::value root so we can easely accsess the value
    if(!parsingSuccsessful){
        std::cout << errors << std::endl;
    }

    Json::CharReaderBuilder readerBuilder2;
    std::string errors2;
    bool parsingSuccsessful2 = Json::parseFromStream(readerBuilder, inputfilestream2, &root2, &errors);//clones the file into json::value root so we can easely accsess the value
    if(!parsingSuccsessful2){
        std::cout << errors << std::endl;
    }
    //end
    std::cout << "hello" << std::endl;
    root2[focusSave]["InUse"] = false;
    root2[focusSave]["Name"] = "No Save";
    root2[focusSave]["LevelState"] = "Map_Layout_Intro";

    root2[focusSave]["Position"]["x"] = 500;
    root2[focusSave]["Position"]["y"] = 1300;

    root2[focusSave]["Sprite"]["Head"] = 0;
    root2[focusSave]["Sprite"]["Uniform"] = 0;
    root2[focusSave]["Sprite"]["Skin"] = 0;

    for(int i = 0; i < 4; i++){
        root2[focusSave]["Ally"][std::to_string(i)]["Sprite"] = root["Default"]["Ally"][std::to_string(i)]["Sprite"].asString();
        root2[focusSave]["Ally"][std::to_string(i)]["SpritePos"] = root["Default"]["Ally"][std::to_string(i)]["SpritePos"].asInt();
        
        root2[focusSave]["Ally"][std::to_string(i)]["Name"] = root["Default"]["Ally"][std::to_string(i)]["Name"].asString();
        root2[focusSave]["Ally"][std::to_string(i)]["level"] = root["Default"]["Ally"][std::to_string(i)]["level"].asInt();
        root2[focusSave]["Ally"][std::to_string(i)]["currentExp"] = root["Default"]["Ally"][std::to_string(i)]["currentExp"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["ExpNextLvL"] = root["Default"]["Ally"][std::to_string(i)]["ExpNextLvL"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["HP"] = root["Default"]["Ally"][std::to_string(i)]["HP"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["MP"] = root["Default"]["Ally"][std::to_string(i)]["MP"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["Attack"] = root["Default"]["Ally"][std::to_string(i)]["Attack"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["Defence"] = root["Default"]["Ally"][std::to_string(i)]["Defence"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["MagicAttack"] = root["Default"]["Ally"][std::to_string(i)]["MagicAttack"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["MagicDefence"] = root["Default"]["Ally"][std::to_string(i)]["MagicDefence"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["Accuracy"] = root["Default"]["Ally"][std::to_string(i)]["Accuracy"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["Evade"] = root["Default"]["Ally"][std::to_string(i)]["Evade"].asFloat();
        root2[focusSave]["Ally"][std::to_string(i)]["Emnity"] = root["Default"]["Ally"][std::to_string(i)]["Enmity"].asFloat();

        root2[focusSave]["Ally"][std::to_string(i)]["Class"] = root["Default"]["Ally"][std::to_string(i)]["Class"].asString();
    }
    //setup writable file
    Json::StreamWriterBuilder writerBuilder;
    const std::unique_ptr<Json::StreamWriter> streamwriter(writerBuilder.newStreamWriter());
    std::ofstream outputfilestream("States/Menu/Saves.json");
    streamwriter->write(root2,&outputfilestream);//gets the value in root and writes it to the file
    //end



    //we open the file in both ways so that we can read and write to the file without losing any information(without open it rewrites the whole file not just the values)
    outputfilestream.close();
    inputfilestream.close();
}

void Save::loadSave(tgui::Gui& gui, std::string& curentstate, AudioHandler& audio){//initializing the gui

    tgui::Theme theme("Themes/Custom.txt");// the looks of the widgets
    auto picture = tgui::Picture::create("Pictures/Menu/WierdBook.png");//creates a background picture
    picture->setSize({"100%", "100%"});

    auto Save1 = tgui::Button::create(Save1txt);// creates a tgui button with initializers
    Save1->setRenderer(theme.getRenderer("Button"));
    Save1->setSize({"40%", "20%"});
    Save1->setTextSize(34);
    Save1->setPosition({"50%", "9%"});

    auto removeSave1 = tgui::Button::create("Delete");// creates a tgui button with initializers
    removeSave1->setRenderer(theme.getRenderer("Button"));
    removeSave1->setSize({"10%", "10%"});
    removeSave1->setTextSize(15);
    removeSave1->setPosition({"89%", "14%"});

    auto Save2 = tgui::Button::create(Save2txt);// creates a tgui button with initializers
    Save2->setRenderer(theme.getRenderer("Button"));
    Save2->setSize({"40%", "20%"});
    Save2->setTextSize(34);
    Save2->setPosition({"50%", "30%"});

    auto removeSave2 = tgui::Button::create("Delete");// creates a tgui button with initializers
    removeSave2->setRenderer(theme.getRenderer("Button"));
    removeSave2->setSize({"10%", "10%"});
    removeSave2->setTextSize(15);
    removeSave2->setPosition({"89%", "35%"});

    auto Save3 = tgui::Button::create(Save3txt);// creates a tgui button with initializers
    Save3->setRenderer(theme.getRenderer("Button"));
    Save3->setSize({"40%", "20%"});
    Save3->setTextSize(34);
    Save3->setPosition({"50%", "51%"});

    auto removeSave3 = tgui::Button::create("Delete");// creates a tgui button with initializers
    removeSave3->setRenderer(theme.getRenderer("Button"));
    removeSave3->setSize({"10%", "10%"});
    removeSave3->setTextSize(15);
    removeSave3->setPosition({"89%", "56%"});

    auto Save4 = tgui::Button::create(Save4txt);// creates a tgui button with initializers
    Save4->setRenderer(theme.getRenderer("Button"));
    Save4->setSize({"40%", "20%"});
    Save4->setTextSize(34);
    Save4->setPosition({"50%", "72%"});

    auto removeSave4 = tgui::Button::create("Delete");// creates a tgui button with initializers
    removeSave4->setRenderer(theme.getRenderer("Button"));
    removeSave4->setSize({"10%", "10%"});
    removeSave4->setTextSize(15);
    removeSave4->setPosition({"89%", "77%"});

    auto Back = tgui::Button::create("Back");// creates a tgui button with initializers
    Back->setRenderer(theme.getRenderer("Button"));
    Back->setSize("200", "50");
    Back->setTextSize(34);
    Back->setPosition({"10%", "85%"});


    //add the buttons the the gui
    gui.add(picture);
    gui.add(Save1);
    gui.add(removeSave1);
    gui.add(Save2);
    gui.add(removeSave2);
    gui.add(Save3);
    gui.add(removeSave3);
    gui.add(Save4);
    gui.add(removeSave4);
    gui.add(Back);

    //functions for the buttons
    Save1->connect("pressed", [&](){focusSave = "Save1"; WriteToFile(); update = false;});
    Save2->connect("pressed", [&](){focusSave = "Save2"; WriteToFile(); update = false;});
    Save3->connect("pressed", [&](){focusSave = "Save3"; WriteToFile(); update = false;});
    Save4->connect("pressed", [&](){focusSave = "Save4"; WriteToFile(); update = false;});

    removeSave1->connect("pressed", [&](){focusSave = "Save1"; ResetSave(); update = false;});
    removeSave2->connect("pressed", [&](){focusSave = "Save2"; ResetSave(); update = false;});
    removeSave3->connect("pressed", [&](){focusSave = "Save3"; ResetSave(); update = false;});
    removeSave4->connect("pressed", [&](){focusSave = "Save4"; ResetSave(); update = false;});

    Back->connect("pressed", [&](){curentstate = "Pause"; audio.playSound("Audio/Sound.wav"); update = false; name = "";});
}

void Save::getname(){
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

void Save::Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *currentstate, AudioHandler& audio) {// a piece of the game loop that draws what is on the screen


    if(!update){//initializes and updates the tgui::gui once. if this is in the loop aka initializes it multiple times causes the buttons to not work
        getname();
        gui->removeAllWidgets();
        std::cout << name << std::endl;
        loadSave(*gui, *currentstate, audio);
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
