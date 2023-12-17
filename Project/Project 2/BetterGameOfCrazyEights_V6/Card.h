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
    protected:
        char value;
        char suit;
        int ptVal;
    public:
        Card();
        Card(char, char, int);
        
        char getValue() {return value;}
        char getSuit() {return suit;}
        int getPtVal() {return ptVal;}
        
        void setValue(char value) {this->value = value;}
        void setSuit(char suit) {this->suit = suit;}
        virtual void setPtVal(int ptVal) {this->ptVal = ptVal;}
        
        const Card operator=(Card);
        friend ostream &operator<<(ostream &, Card &);
};

#endif /* CARD_H */

