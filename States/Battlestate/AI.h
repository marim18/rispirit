//
// Created by Eier on 09.12.2019.
//

#ifndef RISPIRIT_AI_H
#define RISPIRIT_AI_H

#include <vector>
#include "Units.h"

// decides who to hit first by enmity, then Class, then HP
int AI100IQ(std::vector<Units> list){
    int choice = 0;
    float prev = 0;

    // the for loop under looks for the unit with highest enmity stat and chooses that.
    // if enmity is equal to each other it checks for who has a certan type of class.
    // if that is the same, it laslty checks for highest HP.
    for(int i = 0 ; i < 4; i++) {

        if (prev < list.at(i).Emnity && !list.at(i).Dead) {//Emnity
            choice = i;
            prev = list.at(i).Emnity;
        } else if (prev == list.at(i).Emnity) { //Class
            if (list.at(i).Class == "Healer" && !list.at(i).Dead) { //Healer
                choice = i;
            } else if (list.at(i).Class == "Mage" && !list.at(i).Dead) { //Mage
                choice = i;
            } else if (list.at(i).Class == "Ranger" && !list.at(i).Dead) { //ranger
                choice = i;
            } else if (list.at(i).Class == "Fighter" && !list.at(i).Dead) {  //Fighter
                choice = i;
            } else if (list.at(i).Class == "Tank" && !list.at(i).Dead) {    //Tank
                choice = i;

            } else if (prev > list.at(i).HP && !list.at(i).Dead) { //HP
                choice = i;
            }

        }
    }

    std::cout << choice << std::endl;
    std::cout << list.at(choice).Class << std::endl;
    return choice;
}


// decides who is hit by Emnity first, then HP
int AI50IQ(std::vector<Units> list){
    int choice = 0;
    float prev = 0;
    for(int i = 0 ; i < 4; i++){
        if(list.at(i).tag == "Ally"){ //check if selected is ally
            if(prev == list.at(i).Emnity){ // Compares Emnity
                if(prev > list.at(i).HP){
                    choice = i;
                    prev = list.at(i).HP;
                }
            }else if(prev < list.at(i).Emnity){ // selects the enemy with highest Emnity
                choice = i;
                prev = list.at(i).Emnity;
            }
        }
    }
    return choice;
}

// decides who to hit by checking HP
int AI1IQ(std::vector<Units> list){
    int choice = 0;
    float prev = 0;
    for(int i = 0 ; i < 5; i++){
        if(list.at(i).tag == "Ally"){
            if(prev < list.at(i).HP){
                choice = i;
                prev = list.at(i).HP;
            }
        }
    }
    return choice;
}


#endif //RISPIRIT_AI_H
