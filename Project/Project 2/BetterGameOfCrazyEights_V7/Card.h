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
        char value; //Card Value
        char suit;  //Card Suit
        int ptVal;  //Point Value
    public:
        Card();                 //Constructor
        Card(char, char, int);  //Overloaded Constructor
        
        char getValue() {return value;} //Returns card value
        char getSuit() {return suit;}   //Returns card suit
        int getPtVal() {return ptVal;}  //Returns point value
        
        void setValue(char value) {this->value = value;}        //Sets the card value
        void setSuit(char suit) {this->suit = suit;}            //Sets the card suit
        virtual void setPtVal(int ptVal) {this->ptVal = ptVal;} //Sets the point value
        
        const Card operator=(Card);                     //Overloaded assignment operator
        friend ostream &operator<<(ostream &, Card &);  //Overloaded output operator
};

#endif /* CARD_H */