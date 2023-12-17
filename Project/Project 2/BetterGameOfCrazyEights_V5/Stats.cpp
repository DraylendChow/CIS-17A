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

Stats::Stats(const Stats &obj) {
    wins = obj.wins;
    losses = obj.losses;
    fstRnd = obj.fstRnd;
    lngRnd = obj.lngRnd;
    totalGms = obj.totalGms;
    totalPts = obj.totalPts;
    ratio = obj.ratio;
    username = obj.username;
}

ostream &operator << (ostream &strm, Stats &data) {
    strm << "\nName: " << data.getUsername() << endl;
    strm << "Wins: " << data.getWins() << endl;
    strm << "Losses: " << data.getLosses() << endl;
    strm << fixed << setprecision(2) << endl;
    strm << "Win Percentage: " << data.getRatio() << "%" << endl;
    strm << setprecision(0);
    strm << "Total Games Played: " << data.getTotalGms() << endl;
    strm << "Total Points Accumulated: " << data.getTotalPts() << endl;
    strm << "Fastest Round to Win: " << data.getFstRnd() << endl;
    strm << "Longest Round to Win: " << data.getLngRnd() << endl;
    
    return strm;
}

