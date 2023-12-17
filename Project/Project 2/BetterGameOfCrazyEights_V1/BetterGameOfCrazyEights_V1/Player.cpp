/* 
 * File:   Player.cpp
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 10:55 AM
 */

#include "Player.h"

Player::Player() {
    name = "NULL";
    hand = NULL;
    record = new Stats(0, 0, 0, 0, 0, 0, 0.0f);
    record->setUsername(name);
}

Player::Player(string name) {
    this->name = name;
    hand = NULL;
    record = new Stats(0, 0, 0, 0, 0, 0, 0.0f);
    record->setUsername(name);
}

Player::~Player() {
    delete record;
    delete[] hand;
}