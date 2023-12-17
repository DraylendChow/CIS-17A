/* 
 * File:   GameMaster.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 12:58 PM
 */

#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <ctime>

#include "Player.h"

using namespace std;

class GameMaster {
    private:
        //Standard Playing Deck //Note: I swapped 10's for X's for consistency in size
        Card stdDeck[52] = {Card('2', 'H'), Card('2', 'C'), Card('2', 'D'), Card('2', 'S'),
                            Card('3', 'H'), Card('3', 'C'), Card('3', 'D'), Card('3', 'S'),
                            Card('4', 'H'), Card('4', 'C'), Card('4', 'D'), Card('4', 'S'),
                            Card('5', 'H'), Card('5', 'C'), Card('5', 'D'), Card('5', 'S'),
                            Card('6', 'H'), Card('6', 'C'), Card('6', 'D'), Card('6', 'S'),
                            Card('7', 'H'), Card('7', 'C'), Card('7', 'D'), Card('7', 'S'),
                            Card('8', 'H'), Card('8', 'C'), Card('8', 'D'), Card('8', 'S'),
                            Card('9', 'H'), Card('9', 'C'), Card('9', 'D'), Card('9', 'S'),
                            Card('X', 'H'), Card('X', 'C'), Card('X', 'D'), Card('X', 'S'),
                            Card('J', 'H'), Card('J', 'C'), Card('J', 'D'), Card('J', 'S'),
                            Card('Q', 'H'), Card('Q', 'C'), Card('Q', 'D'), Card('Q', 'S'),
                            Card('K', 'H'), Card('K', 'C'), Card('K', 'D'), Card('K', 'S'),
                            Card('A', 'H'), Card('A', 'C'), Card('A', 'D'), Card('A', 'S')};
        
        Player **players;           //All the Players in the game
        Card **theCards;            //The shuffled cards used
        int playerSize;             //The amount of players playing
        static int filesCreated;    //Amount of files created (1 for each new player)
        
        void shuffleCards();                                    //Shuffle Cards
        void dealCards();                                       //Deal 5 Cards to All Players
        void shiftUp(int, int);                                 //Add top card into middle and shifts up
        bool checkDeck(Card **, int, Card *);                   //Check to see if Player can make a move
        void startGame();                                       //Start the game
        int calcPts(int);                                       //Calculate all the points earned
    public:
        GameMaster();
        GameMaster(int);
        ~GameMaster();
        
        void setPlayers(Player **players) {this->players = players;}
        void setPlayerSize(int amount) {playerSize = amount;}
        int getFilesCreated() {return filesCreated;}
                
        void writeToFile(Stats *, fstream &, string);       //Creates a new file
        void rewriteToFile(Stats *, fstream &, string);     //Updates an existing file
        Stats* readFromFile(fstream &, string);             //Gathers data from file
        bool checkForFile(string, int);                     //Checks to see if file for person exists
        void generateTextFile();                            //Generate a text file to view all statistics
};

#endif /* GAMEMASTER_H */

