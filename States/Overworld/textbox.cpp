#include "textbox.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <SFML/Graphics/Font.hpp>

textbox::textbox() {
    //Load font
    if(!font.loadFromFile("fonts/Arial.ttf")){
        std::cout<<"ERRROR";
    }
    //Set text options
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    //Create boxes
    promptBox = sf::RectangleShape(sf::Vector2f(50,35));
    dialogBox = sf::RectangleShape(sf::Vector2f(300,300));

    sf::Image image;
    sf::Texture texture;

    //Load dialog image
    image.loadFromFile("Pictures/dialogBox.png");
    texture.loadFromImage(image);
    dialogBoxTexture.push_back(texture);
    dialogBox.setTexture(&dialogBoxTexture[0]);

    std::ifstream inFile;
    inFile.open("MapInfo/NPC.json"); //Loads NPC dialogs
    Json::CharReaderBuilder builder;
    std::string error;
    //Check is Json works
    bool parsingSuccessful = Json::parseFromStream(builder,inFile,&root,&error);
    if(!parsingSuccessful){ std::cout <<"Shits fucked yo"<<std::endl;}
}

void textbox::createBox(int x, int y, std::string npc) {

    NPCdialog = npc; //Set npc name for use in update function
    std::string dialogStepString = std::to_string(dialogStep); //Make int to string
    if(root[NPCdialog]["Box"+dialogStepString].asString() == "EXIT"){
        //Exit if dialog is EXIT
        activeDialog = false;
        dialogStep = 1;
        return;
    }
    //Make text dialog
    text.setString(root[NPCdialog]["Box"+dialogStepString].asString());
    std::cout<<root[NPCdialog]["Box"+dialogStepString].asString()<<std::endl;
    //Set position of box and text
    dialogBox.setPosition(x-125,y-275);
    text.setPosition(x-75,y-200);
    //Activate box and diable prompt
    activeDialog = true;
    activeButton = false;

}

void textbox::updateBox() {
    //Rewrite box with new text
    dialogStep++;
    std::string dialogStepString = std::to_string(dialogStep);
    if(root[NPCdialog]["Box"+dialogStepString].asString() == "EXIT"){
        activeDialog = false;
        dialogStep = 1;
        return;
    }
    text.setString(root[NPCdialog]["Box"+dialogStepString].asString());
    std::cout<<root[NPCdialog]["Box"+dialogStepString].asString()<<std::endl;

}

void textbox::buttonPromt(int x, int y, std::string key) {
    sf::Image image;
    sf::Texture texture;
    activeButton = true;//Activate prompt
    image.loadFromFile("Pictures/Prompts/"+key+".png"); //Loads in image
    texture.loadFromImage(image); //Get texture from image
    promptTextures.push_back(texture);
    promptBox.setTexture(&promptTextures[0]);
    //Set position of prompt
    promptBox.setPosition(x,y-50);
}