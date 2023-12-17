/* 
 * File:   Stats.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 11:04 AM
 */

#ifndef STATS_H
#define STATS_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Stats; //Forward declaration

ostream &operator << (ostream &, const Stats &);

class Stats {
    private:
        string username;
        int wins;
        int losses;
        int fstRnd;
        int lngRnd;
        int totalGms;
        int totalPts;
        float ratio;
    public:
        Stats();
        Stats(int, int, int, int, int, int, float);
        
        int getWins() {return wins;}
        int getLosses() {return losses;}
        int getFstRnd() {return fstRnd;}
        int getLngRnd() {return lngRnd;}
        int getTotalGms() {return totalGms;}
        int getTotalPts() {return totalPts;}
        float getRatio() {return ratio;}
        string getUsername() {return username;}
        
        void setWins(int val) {wins = val;}
        void setLosses(int val) {losses = val;}
        void setFstRnd(int val) {fstRnd = val;}
        void setLngRnd(int val) {lngRnd = val;}
        void setTotalGms(int val) {totalGms = val;}
        void setTotalPts(int val) {totalPts = val;}
        void setRatio(float val) {ratio = val;}
        void setUsername(string name) {username = name;}
        
        friend ostream &operator<<(ostream &, Stats &);
};

#endif /* STATS_H */

