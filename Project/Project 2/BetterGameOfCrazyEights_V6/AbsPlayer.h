/* 
 * File:   AbsPlayer.h
 * Author: Draylend Chow
 *
 * Created on December 12, 2023, 4:29 PM
 */

#ifndef ABSPLAYER_H
#define ABSPLAYER_H

#include <string>
#include "Card.h"
#include "Stats.h"

using namespace std;

class AbsPlayer {
    public:
        virtual string getName() const = 0;
        virtual unsigned int getCardAmount() = 0;
        virtual Card** getHand() = 0;
        virtual Stats* getRecord() = 0;
        
        virtual void setName(string) = 0;
        virtual void setCardAmount(unsigned int) = 0;
        virtual void setHand(Card **) = 0;
        
        virtual void drawCard(Card*) = 0;
        virtual void removeCard(int) = 0;
};

#endif /* ABSPLAYER_H */