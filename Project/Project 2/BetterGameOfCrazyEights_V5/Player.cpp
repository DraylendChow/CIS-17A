/* 
 * File:   Player.cpp
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 10:55 AM
 */

#include "Player.h"

Player::Player() : Person() {
    num = 0;
    hand = NULL;
    record = new Stats(0, 0, 0, 0, 0, 0, 0.0f);
    record->setUsername(name);
}

Player::Player(string name, int num) : Person(name) {
    this->num = num;
    hand = NULL;
    record = new Stats(0, 0, 0, 0, 0, 0, 0.0f);
    record->setUsername(name);
}

Player::~Player() {
    delete record;
    
    for(int i = 0; i < cardAmount; ++i)
    {
        delete hand[i];
    }
    delete[] hand;
}

void Player::drawCard(Card *newCard) {
    Card **newHand = new Card*[cardAmount + 1]; //Create new array +1 size
    
    //Assign old values to new array
    for(int i = 0; i < cardAmount; i++) {
        newHand[i] = hand[i];
    } //End of for loop
    newHand[cardAmount] = newCard; //Adds new card to hand
  
    cardAmount++;
    
    delete[] hand;
    hand = newHand; //Assign new hand to player
}

void Player::removeCard(int index) {
    Card **newHand = new Card*[cardAmount - 1];  //Create new array -1 size
    int count = 0;                               //Index of player hand
  
    cardAmount--;
    
    //Assign old values to new array
    for(int i = 0; i < cardAmount; i++) {
        if(count == index) {
            //This skips card being removed
            count++;
        } //End of independent if
        newHand[i] = hand[count];
        count++;
    } //End of for loop

    delete[] hand;
    hand = newHand; //Assign new hand to player
}

