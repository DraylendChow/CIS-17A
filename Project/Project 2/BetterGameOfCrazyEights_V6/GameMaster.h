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
#include "NormalCard.h"
#include "FaceCard.h"
#include "SpecialCard.h"

using namespace std;

class GameMaster {
    private:
        //Standard Playing Deck //Note: I swapped 10's for X's for consistency in size
        Card stdDeck[52] = {NormalCard('2', 'H', 0), NormalCard('2', 'C', 0), NormalCard('2', 'D', 0), NormalCard('2', 'S', 0),
                            NormalCard('3', 'H', 0), NormalCard('3', 'C', 0), NormalCard('3', 'D', 0), NormalCard('3', 'S', 0),
                            NormalCard('4', 'H', 0), NormalCard('4', 'C', 0), NormalCard('4', 'D', 0), NormalCard('4', 'S', 0),
                            NormalCard('5', 'H', 0), NormalCard('5', 'C', 0), NormalCard('5', 'D', 0), NormalCard('5', 'S', 0),
                            NormalCard('6', 'H', 0), NormalCard('6', 'C', 0), NormalCard('6', 'D', 0), NormalCard('6', 'S', 0),
                            NormalCard('7', 'H', 0), NormalCard('7', 'C', 0), NormalCard('7', 'D', 0), NormalCard('7', 'S', 0),
                            SpecialCard('8', 'H', 0), SpecialCard('8', 'C', 0), SpecialCard('8', 'D', 0), SpecialCard('8', 'S', 0),
                            NormalCard('9', 'H', 0), NormalCard('9', 'C', 0), NormalCard('9', 'D', 0), NormalCard('9', 'S', 0),
                            FaceCard('X', 'H', 0), FaceCard('X', 'C', 0), FaceCard('X', 'D', 0), FaceCard('X', 'S', 0),
                            FaceCard('J', 'H', 0), FaceCard('J', 'C', 0), FaceCard('J', 'D', 0), FaceCard('J', 'S', 0),
                            FaceCard('Q', 'H', 0), FaceCard('Q', 'C', 0), FaceCard('Q', 'D', 0), FaceCard('Q', 'S', 0),
                            FaceCard('K', 'H', 0), FaceCard('K', 'C', 0), FaceCard('K', 'D', 0), FaceCard('K', 'S', 0),
                            NormalCard('A', 'H', 0), NormalCard('A', 'C', 0), NormalCard('A', 'D', 0), NormalCard('A', 'S', 0)};
        
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

