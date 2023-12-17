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
        Card stdDeck[52] = {Card('2', 'H', 2), Card('2', 'C', 2), Card('2', 'D', 2), Card('2', 'S', 2),
                            Card('3', 'H', 3), Card('3', 'C', 3), Card('3', 'D', 3), Card('3', 'S', 3),
                            Card('4', 'H', 4), Card('4', 'C', 4), Card('4', 'D', 4), Card('4', 'S', 4),
                            Card('5', 'H', 5), Card('5', 'C', 5), Card('5', 'D', 5), Card('5', 'S', 5),
                            Card('6', 'H', 6), Card('6', 'C', 6), Card('6', 'D', 6), Card('6', 'S', 6),
                            Card('7', 'H', 7), Card('7', 'C', 7), Card('7', 'D', 7), Card('7', 'S', 7),
                            Card('8', 'H', 50), Card('8', 'C', 50), Card('8', 'D', 50), Card('8', 'S', 50),
                            Card('9', 'H', 9), Card('9', 'C', 9), Card('9', 'D', 9), Card('9', 'S', 9),
                            Card('X', 'H', 10), Card('X', 'C', 10), Card('X', 'D', 10), Card('X', 'S', 10),
                            Card('J', 'H', 10), Card('J', 'C', 10), Card('J', 'D', 10), Card('J', 'S', 10),
                            Card('Q', 'H', 10), Card('Q', 'C', 10), Card('Q', 'D', 10), Card('Q', 'S', 10),
                            Card('K', 'H', 10), Card('K', 'C', 10), Card('K', 'D', 10), Card('K', 'S', 10),
                            Card('A', 'H', 1), Card('A', 'C', 1), Card('A', 'D', 1), Card('A', 'S', 1)};
        
        Player **players;           //All the Players in the game
        Card **theCards;            //The shuffled cards used
        int playerSize;             //The amount of players playing
        static int filesCreated;    //Amount of files created (1 for each new player)
        
        void shuffleCards();                    //Shuffle Cards
        void dealCards();                       //Deal 5 Cards to All Players
        void shiftUp(int, int);                 //Add top card into middle and shifts up
        bool checkDeck(Card **, int, Card *);   //Check to see if Player can make a move
        void startGame();                       //Start the game
        int calcPts(int);                       //Calculate all the points earned
    public:
        GameMaster();       //Constructor
        GameMaster(int);    //Overloaded Constructor
        ~GameMaster();      //Destructor
        
        void setPlayers(Player **players) {this->players = players;}  //Assigns an array of players
        void setPlayerSize(int amount) {playerSize = amount;}         //Sets the playerSize
        int getFilesCreated() {return filesCreated;}                  //Returns amount of filesCreated
                
        void writeToFile(Stats *, fstream &, string);       //Creates a new file
        void rewriteToFile(Stats *, fstream &, string);     //Updates an existing file
        Stats* readFromFile(fstream &, string);             //Gathers data from file
        bool checkForFile(string, int);                     //Checks to see if file for person exists
        void generateTextFile();                            //Generate a text file to view all statistics
};

#endif /* GAMEMASTER_H */

