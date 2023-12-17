/* 
 * File:   Card.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 10:41 AM
 */

#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

class Card; //Forward declaration

ostream &operator << (ostream &, const Card &);

class Card {
    private:
        char value;
        char suit;
    public:
        Card();
        Card(char, char);
        
        char getValue() {return value;}
        char getSuit() {return suit;}
        
        void setValue(char value) {this->value = value;}
        void setSuit(char suit) {this->suit = suit;}
        
        const Card operator=(Card);
        friend ostream &operator<<(ostream &, Card &);
};

#endif /* CARD_H */

