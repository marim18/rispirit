#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <jsoncpp/json/json.h>
#include "textbox.h"
#include <chrono>
#include <thread>
#include <TGUI/TGUI.hpp>
#include "overworld.h"
#include "../Menu/CharacterCreation.h"


//Function to handle collision between player and tiles
int overworld::collision(std::map<int, sf::RectangleShape> currentMap, sf::RectangleShape protagonist, std::map<int,int> mapColor,std::string *currentState) {
    int returnVal = 0; //Return at the end så walls don't overshadow map change
    for(const auto& val : currentMap){
        int num = mapColor[val.first]; //Determine tile type based on color
        if(num == 0){ //Check collision with walls and objects
            if(val.second.getPosition().x < protagonist.getPosition().x + protagonist.getSize().x && val.second.getPosition().y < protagonist.getPosition().y + protagonist.getSize().y && val.second.getPosition().x + val.second.getSize().x > protagonist.getPosition().x && val.second.getPosition().y + val.second.getSize().y > protagonist.getPosition().y+(protagonist.getSize().y/2)){
                returnVal = 1;
            }
        }
    }
    return returnVal;
}
//Function to handle collision between player and tiles
int overworld::objectCollision(std::map<int, sf::RectangleShape> currentMap, sf::RectangleShape protagonist, std::map<int,int> mapColor,std::string *currentState) {
    int returnVal = 0; //Return at the end så walls don't overshadow map change
    bool activeNPC = false; //To make sure only 1 NPC activates
    for(const auto& val : currentMap){
        int num = mapColor[val.first]; //Determine tile type based on color
        if(num == 1){ //Map change 0
            //Check collision
            if(val.second.getPosition().x < protagonist.getPosition().x + protagonist.getSize().x && val.second.getPosition().y < protagonist.getPosition().y + protagonist.getSize().y && val.second.getPosition().x + val.second.getSize().x > protagonist.getPosition().x && val.second.getPosition().y + val.second.getSize().y > protagonist.getPosition().y+(protagonist.getSize().y/2)){
                for(const auto& val3 : nextMap){
                    for(const auto& val4 : val3.second){
                        if(val3.first == exitNr[val.first]){ //Find info for exit 0
                            protagPos = val4.second; //Reset player coordinates
                            loadMap(val4.first); //Load new map
                            return 0; //Exit function
                        }
                    }
                }
            }

        }
        else if(num == 0 || num == 2){ //Check collision with walls and objects
            if(val.second.getPosition().x < protagonist.getPosition().x + protagonist.getSize().x && val.second.getPosition().y < protagonist.getPosition().y + protagonist.getSize().y && val.second.getPosition().x + val.second.getSize().x > protagonist.getPosition().x && val.second.getPosition().y + val.second.getSize().y > protagonist.getPosition().y+(protagonist.getSize().y/2)){
                returnVal = 1;
            }
        }else if(num == 3){ //Check collision with regular floors for random encounters

            if(val.second.getPosition().x < protagonist.getPosition().x + protagonist.getSize().x && val.second.getPosition().y < protagonist.getPosition().y + protagonist.getSize().y && val.second.getPosition().x + val.second.getSize().x > protagonist.getPosition().x && val.second.getPosition().y + val.second.getSize().y > protagonist.getPosition().y+(protagonist.getSize().y/2)){
                
                if(RECounter > 75){ //Counter for number of ticks between each check
                    RECounter = 0; //Reset counter on hit
                    int random = (rand() % 1000); //Generate random number
                    if( random< REChance){ //Check if random number is inside parameters
                        REChance = 20; //Reset chance parameters
                        RECounter = -2000; //Delay counter to stop spam encounters
                        *currentState = "Battle"; //Change state
                        enemyType = "enemy";
                    }
                    else{
                        REChance += 5; //Increase chance parameters to ensure encounters
                    }
                } else{
                    RECounter++; //Increase counter
                }

            }
        }
        if(num == 2 && !activeNPC){ //Check if in range of NPC
            if(val.second.getPosition().x-100 < protagonist.getPosition().x + protagonist.getSize().x && val.second.getPosition().y-100 < protagonist.getPosition().y + protagonist.getSize().y && val.second.getPosition().x + val.second.getSize().x + 100 > protagonist.getPosition().x && val.second.getPosition().y + val.second.getSize().y + 100> protagonist.getPosition().y+(protagonist.getSize().y/2)){
                textbox.buttonPromt(protagPos.x,protagPos.y,"e"); //Create prompt
                activeNPCnr = val.first; //Set which NPC is active
                activeNPC = true;
            }
            else{
                textbox.activeButton = false; //Take away prompt
            }
        }
    }
    return returnVal;
}


//Function to load map information from file
void overworld::loadMap(std::string fileName) {
    sf::Image map;
    sf::Image objects;
    currentMapName = fileName; //Assign variable for use in battle
    map.loadFromFile("Pictures/Maps/"+fileName+".png"); //Loads image from file
    objects.loadFromFile("Pictures/Maps/"+fileName+"Objects.png");

    sf::Vector2u mapSize = map.getSize(); //Gets size of image for later calculations
    sf::Vector2u objectMapSize = objects.getSize();

    Json::Value root;
    std::ifstream inFile;
    inFile.open("MapInfo/NextMap.json"); //Loads name and starting position of next map
    Json::CharReaderBuilder builder;
    std::string error;
    //Check if Json file is readable
    bool parsingSuccessful = Json::parseFromStream(builder,inFile,&root,&error);
    if(!parsingSuccessful){ std::cout <<"Shits fucked yo"<<std::endl;}

    //Clears all maps to ensure no overlay
    nextMap.clear();
    mapColor.clear();
    currentMap.clear();
    currentObjectMap.clear();
    objectMapColor.clear();

    for(int i = 1; i<5; i++){
    //Reads from file
    std::string j = std::to_string(i);
        std::string nextName = root[fileName]["Exit_"+j]["Name"].asString();
        int nextX = root[fileName]["Exit_"+j]["X"].asInt();
        int nextY = root[fileName]["Exit_"+j]["Y"].asInt();
        nextMap[i-1][nextName] = sf::Vector2f(nextX,nextY); //Inserts info into map
    }
    int counter = 0;
    for(int i =0; i<mapSize.x;i++){ //Draws map based on image size
        for(int j = 0; j<mapSize.y;j++){
            sf::Color currentColor = map.getPixel(i,j); //Gets the color of pixels in the image
            sf::RectangleShape currentShape(sf::Vector2f(50,50)); //Creates a new shape
            int color = 0; //Creates a separate variable for color for later checks in collision
            if(currentColor == sf::Color(255,255,255)){
                continue; //Stops blank tiles being added to map
            }
            else if(currentColor == sf::Color(0,0,0)){ //Checks if color is correct
                currentShape.setTexture(&tileTextures[0]); //Assigns appropriate texture - Wall top 1
                color = 0; //Sets color value for collision / 0 = Regular collison
            }
            else if(currentColor == sf::Color(158,158,158)){
                currentShape.setTexture(&tileTextures[1]);
                color = 1; // 1 = Random encounter
            }
            else if(currentColor == sf::Color(183,28,28)){
                currentShape.setTexture(&tileTextures[2]); //Hallway 1
                color = 1;
            }
            else if(currentColor == sf::Color(3,146,207)) {
                currentShape.setTexture(&tileTextures[3]); //Classroom 1
                color = -1; // -1 = nothing
            }
            else if(currentColor == sf::Color(123,192,67)) {
                currentShape.setTexture(&tileTextures[4]); //Side wall 1
                color = 0;
            }

            currentShape.setPosition(i*50 ,j*50 ); //Determines position of shape based on position in image
            currentMap[counter] = currentShape; //Inserts shape into map
            mapColor[counter] = color; //Inserts color into map
            counter++;
        }
    }
    counter = 0;
    for(int i =0; i<objectMapSize.x;i++){ //Draws map based on image size
        for(int j = 0; j<objectMapSize.y;j++){
            sf::Color currentColor = objects.getPixel(i,j); //Gets the color of pixels in the image
            sf::RectangleShape currentShape(sf::Vector2f(50,50)); //Creates a new shape
            int color = 0; //Creates a separate variable for color for later checks in collision / 0 = Regular collision
            std::string currentNPC;
            bool boss;
            int exit;
            if(currentColor == sf::Color(255,255,255)||currentColor == sf::Color(0,0,0)){
                continue;
            }
            else if(currentColor == sf::Color(237,31,17)){ //Checks if color is correct
                currentShape.setTexture(&objectTextures[0]);
                color = 0;  //Basic collision
            }
            else if(currentColor == sf::Color(156,39,176)){ //Checks if color is correct
                color = 0;
                currentShape.setTexture(&objectTextures[3]);
            }
            else if(currentColor == sf::Color(63,81,181)){ //Checks if color is correct // Vertical Long Desk
                //Change size of objects
                currentShape = sf::RectangleShape(sf::Vector2f(50,150));
                currentShape.setTexture(&objectTextures[4]);
                color = 0;
            }
            else if(currentColor == sf::Color(63, 111, 151)) { // Horizontal Long Desk
                currentShape = sf::RectangleShape(sf::Vector2f(150, 50));
                currentShape.setTexture(&objectTextures[6]);
                color = 0;
            }
            else if(currentColor == sf::Color(207, 30, 48)) { // Chair Reversed
                currentShape = sf::RectangleShape(sf::Vector2f(50, 50));
                currentShape.setTexture(&objectTextures[5]);
                color = 0;
            }
            else if(currentColor == sf::Color(77, 77, 77)) { // Flower 1
                currentShape = sf::RectangleShape(sf::Vector2f(50, 50));
                currentShape.setTexture(&objectTextures[8]);
                color = 0;
            }
            else if(currentColor == sf::Color(38, 196, 254)) { // Locker
                currentShape = sf::RectangleShape(sf::Vector2f(50, 50));
                currentShape.setTexture(&objectTextures[9]);
                color = 0;
            }
            else if(currentColor == sf::Color(63,71,191)){ //Checks if color is correct // Vertical Big Desk
                //Change size of objects
                currentShape = sf::RectangleShape(sf::Vector2f(100,200));
                currentShape.setTexture(&objectTextures[4]);
                color = 0;
            }
            else if(currentColor == sf::Color(252,130,38)){ //Checks if color is correct // Door
                //Change size of objects
                currentShape = sf::RectangleShape(sf::Vector2f(100,50));
                currentShape.setTexture(&objectTextures[23]);
                color = 1;
                exit = 2;
            }
            else if(currentColor == sf::Color(73,148,24)){ //Checks if color is correct
                //currentShape.setFillColor(sf::Color::Transparent); //Make tile seethrough
                currentShape = sf::RectangleShape(sf::Vector2f(100,100));
                currentShape.setTexture(&objectTextures[2]);
                color = 1;  // 1 = Exit
                exit = 0;
            }
            else if(currentColor == sf::Color(53, 168, 24)) {
                currentShape = sf::RectangleShape(sf::Vector2f(100, 100));
                currentShape.setTexture(&objectTextures[7]);
                color = 1;
                exit = 1;
            }
            else if(currentColor == sf::Color(237,150,29)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[1]);
                color = 2; // 2 = NPC
                currentNPC = "Red";
                boss = false;
            }
            else if(currentColor == sf::Color(230,156,29)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[11]);
                color = 2; // 2 = NPC
                currentNPC = "Green";
                boss = false;
            }
            else if(currentColor == sf::Color(230,150,29)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[12]);
                color = 2; // 2 = NPC
                currentNPC = "Enemy_Girl_Intro";
                boss = true;
            }
            else if(currentColor == sf::Color(230,149,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[13]);
                color = 2; // 2 = NPC
                currentNPC = "Blue";
                boss = false;
            }
            else if(currentColor == sf::Color(220,158,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[14]);
                color = 2; // 2 = NPC
                currentNPC = "Professor Ironwood";
                boss = false;
            }
            else if(currentColor == sf::Color(210,169,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[15]);
                color = 2; // 2 = NPC
                currentNPC = "Ms Wackerbotom";
                boss = false;
            }
            else if(currentColor == sf::Color(200,178,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[16]);
                color = 2; // 2 = NPC
                currentNPC = "Edna";
                boss = false;
            }
            else if(currentColor == sf::Color(190,190,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[17]);
                color = 2; // 2 = NPC
                currentNPC = "Not Arne";
                boss = false;
            }
            else if(currentColor == sf::Color(180,199,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[18]);
                color = 2; // 2 = NPC
                currentNPC = "Not Halvard";
                boss = false;
            }
            else if(currentColor == sf::Color(171,209,35)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[19]);
                color = 2; // 2 = NPC
                currentNPC = "Master Rochi";
                boss = false;
            }
            else if(currentColor == sf::Color(70,209,135)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[12]);
                color = 2; // 2 = NPC
                currentNPC = "Mean Rebecca";
                boss = false;
            }
            else if(currentColor == sf::Color(60,209,144)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[20]);
                color = 2; // 2 = NPC
                currentNPC = "Mean Kim";
                boss = false;
            }
            else if(currentColor == sf::Color(50,209,156)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[21]);
                color = 2; // 2 = NPC
                currentNPC = "Mean Helen";
                boss = false;
            }
            else if(currentColor == sf::Color(40,209,164)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[22]);
                color = 2; // 2 = NPC
                currentNPC = "Mean Jessy";
                boss = false;
            }
            else if(currentColor == sf::Color(207,35,107)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[25]);
                color = 2; // 2 = NPC
                currentNPC = "Old Britta";
                boss = false;
            }
            else if(currentColor == sf::Color(181,47,105)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[26]);
                color = 2; // 2 = NPC
                currentNPC = "Old Malin";
                boss = false;
            }
            else if(currentColor == sf::Color(135,5,62)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[27]);
                color = 2; // 2 = NPC
                currentNPC = "Old Anna";
                boss = false;
            }
            else if(currentColor == sf::Color(191,84,132)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[28]);
                color = 2; // 2 = NPC
                currentNPC = "Old Sophia";
                boss = false;
            }
            else if(currentColor == sf::Color(36,184,189)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[29]);
                color = 2; // 2 = NPC
                currentNPC = "Nice Froya";
                boss = false;
            }
            else if(currentColor == sf::Color(37,133,135)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[30]);
                color = 2; // 2 = NPC
                currentNPC = "Nice Tilde";
                boss = false;
            }
            else if(currentColor == sf::Color(13,78,79)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[31]);
                color = 2; // 2 = NPC
                currentNPC = "Nice Camilla";
                boss = false;
            }
            else if(currentColor == sf::Color(158,227,227)){ //Checks if color is correct
                currentShape = sf::RectangleShape(sf::Vector2f(75,75));
                currentShape.setTexture(&objectTextures[32]);
                color = 2; // 2 = NPC
                currentNPC = "Nice Gwen";
                boss = false;
            }
            else if(currentColor == sf::Color(251,251,5)){ //Checks if color is correct
                color = 3; //Color 3 = random encounter
                currentShape.setFillColor(sf::Color::Transparent);
            } else if(currentColor == sf::Color(251,208,128)){
                currentShape = sf::RectangleShape(sf::Vector2f(100,100));
                currentShape.setTexture(&objectTextures[10]);
                color = 2;
                currentNPC = "Chris Ybua";
                boss = true;
            }
            else if(currentColor == sf::Color(49,27,146)){
                currentShape = sf::RectangleShape(sf::Vector2f(100,100));
                currentShape.setTexture(&objectTextures[24]);
                color = 2;
                currentNPC = "Secret Boss";
                boss = true;
            }
            currentShape.setPosition(i*50,j*50); //Determines position of shape based on position in image
            currentObjectMap[counter] = currentShape; //Inserts shape into map
            objectMapColor[counter] = color; //Inserts color into map
            NPCMap[counter] = currentNPC; //Create NPCs
            NPCType[counter] = boss;
            exitNr[counter] = exit;
            counter++;
        }
    }
}

//Initializes class
overworld::overworld() {
    //Assign class variables
    
    REChance = 20;
    moveSpeed = 4;
    protagPos = sf::Vector2f(500,1300);
    protagonist = sf::RectangleShape(sf::Vector2f(50,75));
    protagonist_2 = sf::RectangleShape(sf::Vector2f(60,85));
    protagonist_3 = sf::RectangleShape(sf::Vector2f(50,75));

    sf::Image tileMap;
    sf::Texture texture;
    tileMap.loadFromFile("Pictures/Tiles/wall_top.png"); //Loads in tilemap
    texture.loadFromImage(tileMap); //Get texture from tilemap
    tileTextures.push_back(texture); //Add texture to vector
    tileMap.loadFromFile("Pictures/Leaf.png");
    texture.loadFromImage(tileMap);
    tileTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Tiles/Hallway.png");
    texture.loadFromImage(tileMap);
    tileTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Tiles/classroom.png");
    texture.loadFromImage(tileMap);
    tileTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Tiles/wall_side.png");
    texture.loadFromImage(tileMap);
    tileTextures.push_back(texture);

    tileMap.loadFromFile("Pictures/Objects/chair.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Characters.png");
    texture.loadFromImage(tileMap, {1,1,32,32}); // Red
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/stair_up.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/desk.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/vertical_long_desk.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/chair_reverse.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/horizontal_long_desk.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/stair_down.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/Flower_1.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/locker.png");
    texture.loadFromImage(tileMap);
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{32*4,1,32,32}); // Chris Ybua
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Characters.png");
    texture.loadFromImage(tileMap,{32*2,1,32,32}); // Green
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/Enemy.png");
    texture.loadFromImage(tileMap,{1,1,32,32}); // Mean Rebecca
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Characters.png");
    texture.loadFromImage(tileMap,{32,1,32,32}); // Blue
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{1,1,32,32}); // Professor Ironwood
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{32,1,32,32}); // Ms Wackerbottom
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{32*2,1,32,32}); // Edna
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{32*3,1,32,32}); // Not Arne
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{32*5,1,32,32}); // Not Halvard
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Charlist1.png");
    texture.loadFromImage(tileMap,{32*6,1,32,32}); // Master Rochi
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/Enemy.png");
    texture.loadFromImage(tileMap,{32,1,32,32}); // Mean Kim
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/Enemy.png");
    texture.loadFromImage(tileMap,{32*2,1,32,32}); // Mean Helen
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/Enemy.png");
    texture.loadFromImage(tileMap,{32*3,1,32,32}); // Mean Jessy
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Objects/door.png");
    texture.loadFromImage(tileMap); // Door
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/NPC/Characters.png");
    texture.loadFromImage(tileMap,{32*3,1,32,32}); // Secret Boss
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys2.png");
    texture.loadFromImage(tileMap,{1,1,32,32}); // Old Britta
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys2.png");
    texture.loadFromImage(tileMap,{32,1,32,32}); // Old Malin
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys2.png");
    texture.loadFromImage(tileMap,{32*2,1,32,32}); // Old Anna
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys2.png");
    texture.loadFromImage(tileMap,{32*2,1,32,32}); // Old Sophia
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys3.png");
    texture.loadFromImage(tileMap,{1,1,32,32}); // Nice Froya
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys3.png");
    texture.loadFromImage(tileMap,{32,1,32,32}); // Nice Tilde
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys3.png");
    texture.loadFromImage(tileMap,{32*2,1,32,32}); // Nice Camilla
    objectTextures.push_back(texture);
    tileMap.loadFromFile("Pictures/Enemy/enemyys3.png");
    texture.loadFromImage(tileMap,{32*3,1,32,32}); // Nice Gwn
    objectTextures.push_back(texture);



    loadMap("Map_Layout_Intro"); //Load map using function
}

//Main function running when state is active
void overworld::runOverworld(sf::RenderWindow *window,std::string *currentState) {
    sf::Event event; //Create an event for closing window
    float zoom = 1;
    if (!textbox.activeDialog) { //Make sure you can't move while dialog is active
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && textbox.activeButton) {
            if(NPCType[activeNPCnr]){
                *currentState = "Battle";
                enemyType = "boss";
            }
            else{
                //Create dialog when pressing prompt above NPC
                textbox.createBox(currentObjectMap[activeNPCnr].getPosition().x,
                                  currentObjectMap[activeNPCnr].getPosition().y, NPCMap[activeNPCnr]);
            }

        }
        // Retrieve the window's default view
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { //Reacts when directional key is pressed
            protagPos.x -= moveSpeed; //Move player in correct direction
            protagonist.setPosition(protagPos.x, protagPos.y); //Set position of player shape
            protagonist_2.setPosition(protagPos.x, protagPos.y - hairDifferenceY);
            protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            while (collision(currentMap, protagonist, mapColor, currentState) == 1 ||
                   objectCollision(currentObjectMap, protagonist, objectMapColor, currentState) == 1) { //Check for collision
                protagPos.x += 1; //When colliding with walls or objects, move in opposite direction untill no longer in contact
                protagonist.setPosition(protagPos.x, protagPos.y); //Set position so collision function works
                protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
                protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            protagPos.x += moveSpeed;
            protagonist.setPosition(protagPos.x, protagPos.y);
            protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
            protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            while (collision(currentMap, protagonist, mapColor, currentState) == 1 ||
                   objectCollision(currentObjectMap, protagonist, objectMapColor, currentState) == 1) {
                protagPos.x -= 1;
                protagonist.setPosition(protagPos.x, protagPos.y);
                protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
                protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            protagPos.y -= moveSpeed;
            protagonist.setPosition(protagPos.x, protagPos.y);
            protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
            protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            while (collision(currentMap, protagonist, mapColor, currentState) == 1 ||
                   objectCollision(currentObjectMap, protagonist, objectMapColor, currentState) == 1) {
                protagPos.y += 1;
                protagonist.setPosition(protagPos.x, protagPos.y);
                protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
                protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            protagPos.y += moveSpeed;
            protagonist.setPosition(protagPos.x, protagPos.y);
            protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
            protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);
            while (collision(currentMap, protagonist, mapColor, currentState) == 1 ||
                   objectCollision(currentObjectMap, protagonist, objectMapColor, currentState) == 1) {
                protagPos.y -= 1;
                protagonist.setPosition(protagPos.x, protagPos.y);
                protagonist_2.setPosition(protagPos.x - hairDifferenceX, protagPos.y - hairDifferenceY);
                protagonist_3.setPosition(protagPos.x, protagPos.y + uniformDifference);

            }
        }
    }
    //Advance dialog when space is pressed
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && textbox.activeDialog){
        textbox.updateBox(); //Update dialog
        _sleep(500); //Sleep code to avoid instantly running through dialog
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        std::cout << *currentState << std::endl;
        *currentState = "Pause";
        std::cout << *currentState << std::endl;
    }


    // This was used to find the position of the character during production
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        std::cout << protagPos.x << std::endl;
        std::cout << protagPos.y << std::endl;
    }


    protagonist.setPosition(protagPos.x,protagPos.y); //Set position if it has been changed
    protagonist_2.setPosition(protagPos.x - hairDifferenceX,protagPos.y - hairDifferenceY);
    protagonist_3.setPosition(protagPos.x,protagPos.y + uniformDifference);

    //Creates a view to ensure the player is always in the center of the screen

    sf::View view(sf::FloatRect(-800/2+25,-800/2,window->getSize().x,window->getSize().y));
    //Zoom in if higher resolution and sets new center
    if(sf::VideoMode::getDesktopMode().width > 1920) {

        view.reset(sf::FloatRect(-1600/2+25,-1600/2,window->getSize().x,window->getSize().y));
        zoom = std::min(.5f, zoom + .1f);
        moveSpeed = 5;
        view.move(protagonist.getPosition().x,protagonist.getPosition().y);


        view.setSize(window->getDefaultView().getSize());
        view.zoom(zoom);
        window->setView(view);

    }else{
        view.move(protagonist.getPosition().x,protagonist.getPosition().y); //Focus view on player
    }

   // Update our view
    view.setSize(window->getDefaultView().getSize()); // Reset the size
    view.zoom(zoom); // Apply the zoom level (this transforms the view)
    window->setView(view);

    // Read all events from the window
    while (window->pollEvent(event))
    {
        // Quit when the user presses 'x', ignore all other events
        if (event.type == sf::Event::Closed)
            window->close();
    }

    // Clear the window to black
    window->clear();

    // Draw map
    for(const auto& val : currentMap){
        window->draw(val.second);
    }
    for(const auto& val : currentObjectMap){
        window->draw(val.second);
    }

    window->setView(view); //Assign view to the window
    window->draw(protagonist); //Draw player
    window->draw(protagonist_3);
    window->draw(protagonist_2);
    if(textbox.activeButton){ //Draw prompt when active
        window->draw(textbox.promptBox);
    }
    if(textbox.activeDialog){ //Draw dialog and text when active
        window->draw(textbox.dialogBox);
        window->draw(textbox.text);
    }

    window->display(); //Display what is drawn
}