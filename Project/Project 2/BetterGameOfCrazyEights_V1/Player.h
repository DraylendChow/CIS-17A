/* 
 * File:   Player.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 10:46 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Stats.h"

class Player {
    private:
        string name;
        unsigned int cardAmount = 5;
        string *hand;
        Stats *record;
    public:
        Player();
        Player(string);
        ~Player();
        
        string getName() {return name;}
        unsigned int getCardAmount() {return cardAmount;}
        string* getHand() {return hand;}
        Stats* getRecord() {return record;}
        
        void setName(string name) {this->name = name;}
        void setCardAmount(unsigned int amount) {cardAmount = amount;}
        void setHand(string *cards) {hand = cards;}
};

#endif /* PLAYER_H */

