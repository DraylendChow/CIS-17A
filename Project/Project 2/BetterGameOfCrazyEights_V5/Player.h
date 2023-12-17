/* 
 * File:   Player.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 10:46 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Stats.h"
#include "Person.h"

class Player : public Person {
    private:
        int num;
        unsigned int cardAmount = 5;
        Card **hand;
        Stats *record;
    public:
        Player();
        Player(string, int);
        ~Player();
        
        string getName() const {return "Player " + to_string(num) + ": " + name;}
        unsigned int getCardAmount() {return cardAmount;}
        Card** getHand() {return hand;}
        Stats* getRecord() {return record;}
        
        void setName(string name) {this->name = name;}
        void setCardAmount(unsigned int amount) {cardAmount = amount;}
        void setHand(Card **cards) {hand = cards;}
        
        void drawCard(Card*);
        void removeCard(int);
};

#endif /* PLAYER_H */

