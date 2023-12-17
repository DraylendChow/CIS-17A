/* 
 * File:   Stats.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 11:09 AM
 */

#include "Stats.h"

Stats::Stats() {
    wins = 0;
    losses = 0;
    fstRnd = 0;
    lngRnd = 0;
    totalGms = 0;
    totalPts = 0;
    ratio = 0;
    username = "";
}

Stats::Stats(int wins, int losses, int fstRnd, int lngRnd, int totalGms, int totalPts, float ratio) {
    this->wins = wins;
    this->losses = losses;
    this->fstRnd = fstRnd;
    this->lngRnd = lngRnd;
    this->totalGms = totalGms;
    this->totalPts = totalPts;
    this->ratio = ratio;
    username = "";
}

