/* 
 * File:   Stats.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 11:09 AM
 */

#include "Stats.h"

template class Stats<int>;
template class Stats<float>;
template class Stats<double>;
template class Stats<char>;

template<class T>
Stats<T>::Stats() {
    wins = 0;
    losses = 0;
    fstRnd = 0;
    lngRnd = 0;
    totalGms = 0;
    totalPts = 0;
    ratio = 0;
    username = "";
}

template<class T>
Stats<T>::Stats(T wins, T losses, T fstRnd, T lngRnd, T totalGms, T totalPts, float ratio) {
    this->wins = wins;
    this->losses = losses;
    this->fstRnd = fstRnd;
    this->lngRnd = lngRnd;
    this->totalGms = totalGms;
    this->totalPts = totalPts;
    this->ratio = ratio;
    username = "";
}

template<class T>
Stats<T>::Stats(const Stats<T> &obj) {
    wins = obj.wins;
    losses = obj.losses;
    fstRnd = obj.fstRnd;
    lngRnd = obj.lngRnd;
    totalGms = obj.totalGms;
    totalPts = obj.totalPts;
    ratio = obj.ratio;
    username = obj.username;
}