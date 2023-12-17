/* 
 * File:   Card.cpp
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 10:44 AM
 */

#include "Card.h"

Card::Card() {
    value = 0;
    suit = 0;
}

Card::Card(char value, char suit) {
    this->value = value;
    this->suit = suit;
}

const Card Card::operator=(Card card) {
    value = card.getValue();
    suit = card.getSuit();
}

ostream &operator << (ostream &strm, Card &card) {
    strm << card.getValue() << card.getSuit();
    return strm;
}