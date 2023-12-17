/* 
 * File:   SpecialCard.h
 * Author: Draylend Chow
 *
 * Created on December 12, 2023, 3:46 PM
 */

#ifndef SPECIALCARD_H
#define SPECIALCARD_H

#include "Card.h"

//Inheritance of Card
class SpecialCard : public Card{
    public:
        SpecialCard() : Card(){ //Constructor
            ptVal = 0;
        };
        SpecialCard(char value, char suit, int num) : Card(value, suit, num) {  //Overloaded Constructor
            ptVal = 50;
        };
};

#endif /* SPECIALCARD_H */