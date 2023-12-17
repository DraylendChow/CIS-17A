/*
 * File:    main.cpp
 * Author:  Draylend Chow
 * Created on December 9th at 10:32 AM
 * Purpose: Project 2: To simulate a game of Crazy Eights implementing
 *                     all concepts learned from Ch (13-16).
 */

#include "GameMaster.h"

using namespace std;

//Execution begins heres
int main() {
    //Set the Random Seed
    srand(static_cast<unsigned int>(time(0)));

    char input; //User choice in menu

    cout << "Welcome to Virtual Crazy Eights!" << endl;
    cout << "\nHere are the rules:\nPlayers are each given 5 cards at the start. The top card from the deck will be revealed. "
        "\nPlayers must place a card of the same suit or number value. If unable to play a card, players must draw from the "
        "\npile until a play is available. Players may choose to draw from the pile even if they can make a play. If the draw "
        "\npile is exhausted, players must pass if they are unable to make a play. As the name implies, 8\'s are wild cards, "
        "\nmeaning a player can change the value of the top card by placing an 8 and choosing a suit of their choice. The game "
        "\nends when a player uses all of their cards. The player who finishes first will gain points based on the values of the "
        "\ncards remaining in the other players hands." << endl;
    //Loop until user stops playing
    while(true) {
        //Ask user for their choice
        cout << "\nWould you like to play? Enter:\n<Y> for Yes\n<N> for No\n<i> for Info on a Player\n<G> for Generate File on all Players\n\nEnter: ";
        cin >> input;
        cin.ignore(256, '\n');
        if(toupper(input) == 'Y') {
            //Start the game
            //Ask user for how many players
            cout << "\nHow many players are playing (2-8)?: ";
            cin >> input;
            cin.ignore(256, '\n');
            //Test for validation
            while(static_cast<int>(input)-48 < 2 || static_cast<int>(input)-48 > 8 || isdigit(input) == 0) {
                cout << "Invalid input. Please try again." << endl;
                cout << "\nHow many players are playing (2-8)?: ";
                cin >> input;
                cin.ignore(256, '\n');
            } //End of nested while loop
            int playerSize = static_cast<int>(input)-48;    //Convert char into int to get playerSize
            cout << "You have selected " << playerSize << " players." << endl;
            GameMaster master(playerSize);
        } else if(toupper(input) == 'I') {
            
            //Search for player data
            string id; //Create char array to hold name from user input
            cout << "Please enter the name of the user you wish to view (CASE SENSITIVE): ";
            cin >> id; //Get input
            bool found = false;
            string fileName;
            //Check if the player has existing data
            GameMaster temp;
            for(int i = 0; i < temp.getFilesCreated(); i++) { 
                found = temp.checkForFile(id, (i+1));
                if(found == true) {
                    //Store fileName as a valid file
                    fileName = "stats" + to_string(i+1) + ".dat";
                    break;
                } //End of independent if
            } //End of for loop
            if(found == true) {
                //Display stats of searched player
                fstream inputFile;
                Stats *person = temp.readFromFile(inputFile, fileName);
                cout << *person << endl;
                
                delete person;
            } else {
                cout << "Data for that person does not exist. Please complete one game to register data." << endl;
            } //End of nested dependent else
        } else if(toupper(input) == 'G') { 
            //Generate txt file of all players data
            GameMaster temp;
            try {
                temp.generateTextFile();
                cout << "File has been created." << endl;
            } catch(const char *msg) {
                cout << msg << endl;
            }
        } else if(toupper(input) == 'N') {
            //Exit menu
            cout << "\nGoodbye!" << endl;
            break;
        } else {
            //Input validation on menu
            cout << "\nInvalid input. Please try again." << endl;
        } //End of dependent else
    } //Exit while loop

    //Exit program
    return 0;
}