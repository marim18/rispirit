//
// Created by Eier on 08.11.2019.
//

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "CharacterCreation.h"

void CharacterCreation::loadCC(tgui::Gui& gui, std::string& curentstate, AudioHandler& audio){//to load the tgui::Gui, aka a initializer for the GUI.

    tgui::Theme theme("Themes/Custom.txt");//how the button and other widgets look

    auto picture = tgui::Picture::create("Pictures/CharCreate/tempbackground.png");//setting the background
    picture->setSize({"170%", "100%"});//setting size of the background

    sf::Texture hairtexture;
    sf::Texture bodytexture;
    sf::Texture uniformtexture;
    hairtexture.loadFromFile("Pictures/CharCreate/hairchoices.png");
    bodytexture.loadFromFile("Pictures/CharCreate/skinchoice.png");
    uniformtexture.loadFromFile("Pictures/CharCreate/uniformchoice.png");

    auto SmallPanel = tgui::Picture::create("Pictures/CharCreate/smalpanel.png");//set pictures for panels
    SmallPanel->setSize({"100%", "100%"});//setting size of the picture
    //===============================================================//
    // create buttons with tgui and sets parameters for the buttons
    auto HBL = tgui::Button::create("<-");
    HBL->setRenderer(theme.getRenderer("Button"));
    HBL->setSize("5%","5%");
    HBL->setPosition("14%","20%");

    // create buttons with tgui and sets parameters for the buttons
    auto HBR = tgui::Button::create("->");
    HBR->setRenderer(theme.getRenderer("Button"));
    HBR->setSize("5%","5%");
    HBR->setPosition("41%","20%");

    // create a panel with tgui and sets parameter and pictures
    auto topPanel = tgui::Panel::create();
    topPanel->setSize("20%", "20%");
    topPanel->setPosition("20%", "12%");
    topPanel->add(SmallPanel);

    auto HeadPicture = tgui::Picture::create({hairtexture, {32 * Head, 0, 32, 32}});//set a picture/sprite (this is temporary)
    HeadPicture->setSize({"100%", "100%"});//setting size of the picture
    topPanel->add(HeadPicture);
    //===============================================================//

    //===============================================================//

    // create buttons with tgui and sets parameters for the buttons
    auto BBL = tgui::Button::create("<-");
    BBL->setRenderer(theme.getRenderer("Button"));
    BBL->setSize("5%","5%");
    BBL->setPosition("14%","42%");

    // create buttons with tgui and sets parameters for the buttons
    auto BBR = tgui::Button::create("->");
    BBR->setRenderer(theme.getRenderer("Button"));
    BBR->setSize("5%","5%");
    BBR->setPosition("41%","42%");

    // create a panel with tgui and sets parameter and pictures
    auto MiddlePanel = tgui::Panel::create();
    MiddlePanel->setSize("20%", "20%");
    MiddlePanel->setPosition("20%", "34%");
    MiddlePanel->add(SmallPanel);

    auto BodyPicture = tgui::Picture::create({uniformtexture, {32 * Uniform, 0, 32, 32}});//set a picture/sprite (this is temporary)
    BodyPicture->setSize({"100%", "100%"});//setting size of the picture
    MiddlePanel->add(BodyPicture);
    //===============================================================//

    //===============================================================//
    // create buttons with tgui and sets parameters for the buttons
    auto FBL = tgui::Button::create("<-");
    FBL->setRenderer(theme.getRenderer("Button"));
    FBL->setSize("5%","5%");
    FBL->setPosition("14%","64%");

    // create buttons with tgui and sets parameters for the buttons
    auto FBR = tgui::Button::create("->");
    FBR->setRenderer(theme.getRenderer("Button"));
    FBR->setSize("5%","5%");
    FBR->setPosition("41%","64%");

    // create a panel with tgui and sets parameter and pictures
    auto BottomPanel = tgui::Panel::create();
    BottomPanel->setSize("20%", "20%");
    BottomPanel->setPosition("20%", "56%");
    BottomPanel->add(SmallPanel);

    auto FeetPicture = tgui::Picture::create({bodytexture, {32 * Skin, 32, 32, 32}});//set a picture/sprite (this is temporary)
    FeetPicture->setSize({"100%", "100%"});//setting size of the picture
    BottomPanel->add(FeetPicture);
    //===============================================================//


    // create buttons with tgui and sets parameters for the buttons
    auto StartGame = tgui::Button::create("StartGame");
    StartGame->setRenderer(theme.getRenderer("Button"));
    StartGame->setSize("20%", "10%");
    StartGame->setTextSize(20);
    StartGame->setPosition({"75%", "85%"});

    // create buttons with tgui and sets parameters for the buttons
    auto Back = tgui::Button::create("Back");
    Back->setRenderer(theme.getRenderer("Button"));
    Back->setSize("20%", "10%");
    Back->setTextSize(20);
    Back->setPosition({"5%", "85%"});

    // create a "edit box" which lets you write something and then save it.
    tgui::EditBox::Ptr NameBox = tgui::EditBox::create();
    NameBox->setSize("88%", "8%");
    NameBox->setRenderer(theme.getRenderer("EditBox"));
    NameBox->setTextSize(20);
    NameBox->setPosition("6%","88%");
    NameBox->setMaximumCharacters(17);
    if(name.empty()){
        NameBox->setDefaultText("Enter Name");
    }

    // create a picture for another widget
    auto pic = tgui::Picture::create("Pictures/CharCreate/Panel.png");
    pic->setSize({"100%","100%"});
    //=====================================================================================//
    auto TopPart = tgui::Picture::copy(HeadPicture);//set a picture/sprite (this is temporary)
    TopPart->setSize({"80%", "60%"});//setting size of the picture
    TopPart->setPosition({"10%", "-1%"});

    auto MiddlePart = tgui::Picture::copy(BodyPicture);
    MiddlePart->setSize({"80%", "60%"});//setting size of the picture
    MiddlePart->setPosition("10%", "25%");

    auto BottomPart = tgui::Picture::create({bodytexture, {32 * Skin, 0, 32, 32}});//set a picture/sprite (this is temporary)
    BottomPart->setSize({"80%", "60%"});//setting size of the picture
    BottomPart->setPosition("10%", "10%");
    //=====================================================================================//

    // create a panel with tgui and sets parameter and pictures
    auto Cpanel = tgui::Panel::create();
    Cpanel->setSize("40%", "60%");
    Cpanel->setPosition("50%", "12%");
    Cpanel->add(pic);
    Cpanel->add(BottomPart);
    Cpanel->add(MiddlePart);
    Cpanel->add(TopPart);
    Cpanel->add(NameBox);

    //adding all the widgets to the gui
    gui.add(picture);
    gui.add(topPanel);  gui.add(MiddlePanel);   gui.add(BottomPanel);
    gui.add(HBL);   gui.add(HBR);
    gui.add(FBL);   gui.add(FBR);
    gui.add(BBL);   gui.add(BBR);
    gui.add(Cpanel);
    gui.add(Back);
    gui.add(StartGame);

    //function of the editbox and buttons
    HBR->connect("pressed", [&](){Head++; if(Head > 5) Head = 0; update = false; audio.playSound("Audio/Sound.wav");});
    HBL->connect("pressed", [&](){Head--; if(Head < 0) Head = 5; update = false; audio.playSound("Audio/Sound.wav");});
    BBR->connect("pressed", [&](){Uniform++; if(Uniform > 5) Uniform = 0; update = false; audio.playSound("Audio/Sound.wav");});
    BBL->connect("pressed", [&](){Uniform--; if(Uniform < 0) Uniform = 5; update = false; audio.playSound("Audio/Sound.wav");});
    FBR->connect("pressed", [&](){Skin++; if(Skin > 5) Skin = 0; update = false; audio.playSound("Audio/Sound.wav");});
    FBL->connect("pressed", [&](){Skin--; if(Skin < 0) Skin = 5; update = false; audio.playSound("Audio/Sound.wav");});
    NameBox->connect("TextChanged", [=](){ name = NameBox->getText().toAnsiString();});
    Back->connect("pressed", [&](){curentstate = "Menu"; audio.playSound("Audio/Sound.wav"); update = false;});
    StartGame->connect("pressed", [&](){
        if(!name.empty()){
            curentstate = "Overworld";
            audio.playSound("Audio/Sound.wav");
            //audio.stopMusic();

            protText.clear();
            protText.push_back(mainTexture(1));
            protText.push_back(mainTexture(2));
            protText.push_back(mainTexture(3));
            pro->setTexture(&protText[0]);
            pro_2->setTexture(&protText[1]);
            pro_3->setTexture(&protText[2]);

            update = false;
            }
        else{
            std::cout << "please enter name" << std::endl;
        }
    });
}

sf::Texture CharacterCreation::mainTexture(int option){
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

void CharacterCreation::Run(tgui::Gui *gui, sf::RenderWindow *window, std::string *currentstate, AudioHandler& audio){// a piece of the game loop that draws what is on the screen

    if(!update){//initializes and updates the tgui::gui once. if this is in the loop aka initializes it multiple times causes the buttons to not work
        gui->removeAllWidgets();
        loadCC(*gui, *currentstate, audio);
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