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
#include "AbsPlayer.h"

//Inherits AbsPlayer and Person
class Player : public AbsPlayer, public Person {
    private:
        int num;                //ID of player
        unsigned int cardAmount;//Size of hand
        Card **hand;            //Deck of cards
        Stats<int> *record;     //Player stats
    public:
        Player();           //Constructor
        Player(string, int);//Overloaded Constructor
        ~Player();          //Destructor
        
        virtual string getName() const {return "Player " + to_string(num) + ": " + name;}   //Returns name
        unsigned int getCardAmount() {return cardAmount;}                           //Returns card amount
        Card** getHand() {return hand;}                                             //Returns hand
        Stats<int>* getRecord() {return record;}                                    //Returns stats class
        
        void setName(string name) {this->name = name;}                  //Sets name
        void setCardAmount(unsigned int amount) {cardAmount = amount;}  //Sets card amount
        void setHand(Card **cards) {hand = cards;}                      //Sets hand
        
        void drawCard(Card*);   //Adds a card to hand
        void removeCard(int);   //Removes a card from hand
};

#endif /* PLAYER_H */