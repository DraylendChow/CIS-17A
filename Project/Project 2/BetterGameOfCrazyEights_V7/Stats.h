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

template<class T>
class Stats; //Forward declaration

template<class T>
ostream &operator << (ostream &, const Stats<T> &);

template<class T>
class Stats {
    private:
        string username;    //Name of player
        T wins;             //Number of wins
        T losses;           //Number of losses
        T fstRnd;           //Fasted time to win
        T lngRnd;           //Longest time to win
        T totalGms;         //Total games played
        T totalPts;         //Total points
        float ratio;        //Win percentage
    public:
        Stats();                        //Constructor
        Stats(T, T, T, T, T, T, float); //Overloaded Constructor
        Stats(const Stats &);           //Copy Constructor
        
        T getWins() {return wins;}              //Returns wins
        T getLosses() {return losses;}          //Returns losses
        T getFstRnd() {return fstRnd;}          //Returns fastest round
        T getLngRnd() {return lngRnd;}          //Returns longest round
        T getTotalGms() {return totalGms;}      //Returns total games
        T getTotalPts() {return totalPts;}      //Returns total points
        float getRatio() {return ratio;}        //Returns win percentage
        string getUsername() {return username;} //Returns username
        
        void setWins(T val) {wins = val;}               //Sets wins
        void setLosses(T val) {losses = val;}           //Sets losses
        void setFstRnd(T val) {fstRnd = val;}           //Sets fastest round
        void setLngRnd(T val) {lngRnd = val;}           //Sets longest round
        void setTotalGms(T val) {totalGms = val;}       //Sets total games
        void setTotalPts(T val) {totalPts = val;}       //Sets total points
        void setRatio(float val) {ratio = val;}         //Sets win percentage
        void setUsername(string name) {username = name;}//Sets username
};

//Overloaded output operator
template<class T>
ostream &operator << (ostream &strm, Stats<T> &data) {
    strm << "\nName: " << data.getUsername() << endl;
    strm << "Wins: " << data.getWins() << endl;
    strm << "Losses: " << data.getLosses() << endl;
    strm << fixed << setprecision(2) << endl;
    strm << "Win Percentage: " << data.getRatio() << "%" << endl;
    strm << setprecision(0);
    strm << "Total Games Played: " << data.getTotalGms() << endl;
    strm << "Total Points Accumulated: " << data.getTotalPts() << endl;
    strm << "Fastest Round to Win: " << data.getFstRnd() << endl;
    strm << "Longest Round to Win: " << data.getLngRnd();

    return strm;
}

#endif /* STATS_H */