/* 
 * File:   NormalCard.h
 * Author: Draylend Chow
 *
 * Created on December 12, 2023, 3:42 PM
 */

#ifndef NORMALCARD_H
#define NORMALCARD_H

#include "Card.h"

//Inheritance of Card
class NormalCard : public Card{
    public:
        NormalCard() : Card(){  //Constructor
            ptVal = 0;
        };
        NormalCard(char value, char suit, int num) : Card(value, suit, num) {   //Overloaded Constructor
            if(value == 'A') {
                ptVal = 1;
            } else {
                ptVal = (value-'0');
            }
        };
};

#endif /* NORMALCARD_H */