/*
 * File:    main.cpp
 * Author:  Draylend Chow
 * Created on October 14th at 6:25 PM
 * Purpose: Project 1: To simulate a game of Crazy Eights using all the
 *          concepts covered so far in class (Ch 9-12).
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const unsigned int DECK_SIZE = 52;  //Standard Playing Card Size
const unsigned int PLAYER_HAND = 5; //Standard Starting Amount
const unsigned int NAME_SIZE = 31;  //Name Size + 1 for Null Terminator

//Point values of special cards
enum specialValues {faceCard = 10, eight = 50};

//Stat Structure to hold statistics on game
struct Stats {
    char name[NAME_SIZE];   //Name of Player
    int wins = 0, losses = 0, fstRnd = 0, lngRnd = 0, totalGms = 0, totalPts = 0; //Stats on game
    float ratio;            //Win percentage
};

//Player Structure to hold information
struct Player {
    char name[NAME_SIZE];                   //Name of player
    string *cards;                          //Players deck
    unsigned int cardAmount = PLAYER_HAND;  //Amount of cards in hand
    Stats record;                           //Statistics of player
};

string* shuffleCards(const string []);                  //Shuffle Cards
void dealCards(Player *, string*, int);                 //Deal 5 Cards to All Players
void shiftUp(string *, int, int);                       //Add top card into middle and shifts up
bool checkDeck(string *, int, string);                  //Check to see if Player can make a move
void drawCard(Player &, string);                        //Draw a card from the pile
void removeCard(Player &, int);                         //Remove a card from the Player's Hand
void startGame(Player *, string*, const int, int &);    //Start the Game
int calcPts(Player *, int);                             //Calculate all the points earned
bool checkForFile(char [], int);                        //Checks to see if file for person exists
void writeToFile(Stats, fstream &, string);             //Creates a new file
void rewriteToFile(Stats, fstream &, string);           //Updates an existing file
Stats readFromFile(fstream &, string);                  //Gathers data from file
void generateTextFile(const int);                       //Generate a text file to view all statistics
void cleanUp(Player *, int);                            //Delete dynamically created array(s)

//Execution begins heres
int main() {
    //Set the Random Seed
    srand(static_cast<unsigned int>(time(0)));

    //Standard Playing Deck //Note: I swapped 10's for X's for consistency in size
    const string REFERENCE[DECK_SIZE] = {"2H", "2C", "2D", "2S",
                                         "3H", "3C", "3D", "3S",
                                         "4H", "4C", "4D", "4S",
                                         "5H", "5C", "5D", "5S",
                                         "6H", "6C", "6D", "6S",
                                         "7H", "7C", "7D", "7S",
                                         "8H", "8C", "8D", "8S",
                                         "9H", "9C", "9D", "9S",
                                         "XH", "XC", "XD", "XS",
                                         "JH", "JC", "JD", "JS",
                                         "QH", "QC", "QD", "QS",
                                         "KH", "KC", "KD", "KS",
                                         "AH", "AC", "AD", "AS"};
    
    //Declare all Major Variables here
    Player *players;        //All the Players in the game
    string *theCards;       //The shuffled cards used
    int playerSize;         //The amount of players playing
    int filesCreated = 0;   //Amount of files created (1 for each new player)
    char input;             //User choice in menu

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
            playerSize = static_cast<int>(input)-48;    //Convert char into int to get playerSize
            players = new Player[playerSize];           //Dynamically create array of Players
            cout << "You have selected " << playerSize << " players." << endl;
            //Ask for names of players
            for(int i = 0; i < playerSize; i++) {
                cout << "What is the name of player " << (i+1) << "? (Please enter less than 30 characters and no spaces): ";
                cin.getline((players+i)->name, NAME_SIZE);
            } //End of for loop
            theCards = shuffleCards(REFERENCE);                     //Shuffle the Cards
            startGame(players, theCards, playerSize, filesCreated); //Start the game
            cleanUp(players, playerSize);                           //Delete all dynamically created objects
        } else if(toupper(input) == 'I') {
            //Search for player data
            char id[NAME_SIZE]; //Create char array to hold name from user input
            cout << "Please enter the name of the user you wish to view (CASE SENSITIVE): ";
            cin.getline(id, NAME_SIZE); //Get input
            bool found = false;
            string fileName;
            //Check if the player has existing data
            for(int i = 0; i < filesCreated; i++) { 
                found = checkForFile(id, (i+1));
                if(found == true) {
                    //Store fileName as a valid file
                    fileName = "stats" + to_string(i+1) + ".dat";
                    break;
                } //End of independent if
            } //End of for loop
            if(found == true) {
                //Display stats of searched player
                fstream inputFile;
                Stats person = readFromFile(inputFile, fileName);
                cout << "\nName: " << person.name << endl;
                cout << "Wins: " << person.wins << endl;
                cout << "Losses: " << person.losses << endl;
                cout << fixed << setprecision(2) << endl;
                cout << "Win Percentage: " << person.ratio << "%" << endl;
                cout << setprecision(0);
                cout << "Total Games Played: " << person.totalGms << endl;
                cout << "Total Points Accumulated: " << person.totalPts << endl;
                cout << "Fastest Round to Win: " << person.fstRnd << endl;
                cout << "Longest Round to Win: " << person.lngRnd << endl;
            } else {
                cout << "Data for that person does not exist. Please complete one game to register data." << endl;
            } //End of nested dependent else
        } else if(toupper(input) == 'G') { 
            //Generate txt file of all players data
            generateTextFile(filesCreated);
            cout << "File has been created." << endl;
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

string* shuffleCards(const string REF[]) {
    string *theCards = new string[DECK_SIZE];   //The deck of shuffled cards
    int numbers[DECK_SIZE];                     //Keep track of which cards have been used
    int count = 0;                              //Index counter for theCards

    //Initialize numbers array
    for(int i = 0; i < DECK_SIZE; i++) {
        numbers[i] = -1;
    } //End of for loop
    //Generate random number to choose card and assign to theCards
    while(count < DECK_SIZE) {
        int randCard = (rand() % (52));
        if(numbers[randCard] == -1) {
            *(theCards + count) = REF[randCard];
            count++;
            numbers[randCard] = 0;
        } //End of independent if
    } //End of while loop

    return theCards;
}

void dealCards(Player *players, string *theCards, int playerSize) {
    //Create array of cards for each player
    for(int i = 0; i < playerSize; i++) {
        string *c = new string[(players+i)->cardAmount];
        (players+i)->cards = c;
    } //End of for loop

    int currentCard = 0;
    //Assign cards to players
    for(int i = 0; i < (playerSize*5);) {
        for(int j = 0; j < playerSize; j++) {
            (players+j)->cards[currentCard] = *(theCards + i);  //Assign card to players hand
            *(theCards + i) = "NULL";                           //Delete card from shuffled cards
            i++;
        } //End of nested for loop
        currentCard++; //Increment index shuffled cards
    } //End of for loop
}

void shiftUp(string *theCards, int cardCount, int currentCard) {
    int randNum = rand() % (3 + 1) + 1;                 //Generate random number
    int index = (cardCount/2) - randNum + currentCard;  //Calculate number in middle of deck

    string temp = *(theCards + index);                  //Holding old value of middle card
    *(theCards + index) = *(theCards + currentCard);    //Swapping top card to middle card
    //Shift all values up
    for(int i = index; i > currentCard; i--) {
        string temp2 = *(theCards + (i-1));
        *(theCards + (i-1)) = temp;
        temp = temp2;
    } //End of for loop
}

bool checkDeck(string *deck, int size, string topCard) {
    bool valid = false; //If player has a valid card to play
  
    //Check to see if player has any cards they can use
    for(int i = 0; i < size; i++) {
        string card = *(deck + i);
        if(card[0] == '8' || card[0] == topCard[0] || card[1] == topCard[1]) {
            valid = true;
            break;
        } //End of independent if
    } //End of for loop

    return valid;
}

void drawCard(Player &player, string theCards) {
    string *newHand = new string[player.cardAmount + 1]; //Create new array +1 size
    
    //Assign old values to new array
    for(int i = 0; i < player.cardAmount; i++) {
        *(newHand + i) = *(player.cards + i);
    } //End of for loop
    *(newHand + player.cardAmount) = theCards; //Adds new card to hand
    player.cardAmount++;
  
    delete []player.cards;  //Delete old player hand
    player.cards = newHand; //Assign new hand to player
}

void removeCard(Player &player, int index) {
    string *newHand = new string[player.cardAmount - 1];    //Create new array -1 size
    int count = 0;                                          //Index of player hand
  
    player.cardAmount--;
    //Assign old values to new array
    for(int i = 0; i < player.cardAmount; i++) {
        if(count == index) {
            //This skips card being removed
            count++;
        } //End of independent if
        *(newHand + i) = player.cards[count];
        count++;
    } //End of for loop

    delete []player.cards;  //Delete old player hand
    player.cards = newHand; //Assign new hand to player
}

void startGame(Player *players, string *theCards, const int playerSize, int &filesCreated) {
    bool gameOver = false;                          //Decides when games ends
    int currentCount = playerSize * 5;              //Current index in the shuffled cards
    int cardCount = 52 - currentCount;              //How many cards are left
    int *round = new int;                           //Current round
    *round = 1;
    string topCard = *(theCards + currentCount);    //The top card on the deck

    dealCards(players, theCards, playerSize);   //Deal cards out to players
    //Check if the top card is 8
    if(topCard[0] == '8') {
        while(topCard[0] == '8') {
            shiftUp(theCards, cardCount, currentCount); //Shuffle card back into deck
            topCard = *(theCards + currentCount);       //New top card
        } //End of while
        *(theCards + currentCount) = "NULL";    //Delete card
        cardCount--;                            //Update cards left
        currentCount++;                         //Update index on shuffled cards
    } else {
        cardCount--;    //Update cards left
        currentCount++; //Update index on shuffled cards
    } //End of dependent else
  
    while(!gameOver) {
        cout << "\nRound " << *round << endl;
        //Loop through all players turn
        for(int i = 0; i < playerSize; i++) {
            bool playerDone = false; //Decide when players turn is over
            while(!playerDone) {
                playerDone = true;
                cout << "\nThis is the top card: " << topCard << endl << endl;
                char input;
                //Check if player can make a move
                bool check = checkDeck((players+i)->cards, (players+i)->cardAmount, topCard);
                cout << "It is " << (players+i)->name << "'s turn!\nHere is your current hand: [";
                //Print out players hand
                for(int j = 0; j < (players+i)->cardAmount; j++) {   
                    cout << (players+i)->cards[j];
                    if(j+1 < (players+i)->cardAmount) {
                        cout << ", ";
                    } else {
                        cout << "]" << endl;
                    } //End of dependent else
                } //End of nested for loop
                cout << "\nPlease choose from the following menu:" << endl;
                cout << "1. Place a Card\n2. Draw a Card\n\nChoose an option: ";
                cin >> input;
                cin.ignore(256, '\n');
                if(input == '1') {
                    //When player chooses to place a card
                    cout << "You chose to place a card." << endl;
                    if(check == true) {
                        cout << "Please choose a card from your deck or input an invalid number to go back:" << endl;
                        //Display all cards in deck as a list
                        for(int j = 0; j < (players+i)->cardAmount; j++) {
                            cout << (j+1) << ". " << (players+i)->cards[j] << endl;
                        } //End of nested for loop
                        int choice;
                        cout << "\nChoose an option: ";
                        cin >> choice;
                        cin.ignore(256, '\n');
                        //If choice is valid
                        if(choice >= 1 && choice <= (players+i)->cardAmount) {
                            string cardChosen = (players+i)->cards[choice - 1];
                            if(cardChosen[0] == '8') {
                                //If player uses a crazy eight
                                cout << "You have placed a Crazy Eight! Please choose a suit from the following menu (1-4):\n\n1. Heart\n2. Club\n3. Diamond\n4. Spade" << endl;
                                char suit;
                                cout << "\nChoose an option: ";
                                cin >> suit;
                                cin.ignore(256, '\n');
                                //Player chooses suit
                                if(suit == '1') {
                                    topCard = "0H";                         //Change top card to chosen suit
                                    removeCard(*(players+i), (choice-1));   //Remove card from hand
                                } else if(suit == '2') {
                                    topCard = "0C";                         //Change top card to chosen suit
                                    removeCard(*(players+i), (choice-1));   //Remove card from hand
                                } else if(suit == '3') {
                                    topCard = "0D";                         //Change top card to chosen suit
                                    removeCard(*(players+i), (choice-1));   //Remove card from hand
                                } else if(suit == '4') {
                                    topCard = "0S";                         //Change top card to chosen suit
                                    removeCard(*(players+i), (choice-1));   //Remove card from hand
                                } else {
                                    //Invalid choice in suit
                                    cout << "Invalid choice. Returning back to menu." << endl;
                                    playerDone = false; //Change to repeat user turn
                                } //End of dependent else
                            } else if(cardChosen[0] == topCard[0] || cardChosen[1] == topCard[1]) {
                                //Regular card chosen
                                topCard = cardChosen;                      //Update top card
                                removeCard(*(players+i), (choice-1));   //Remove card from hand
                            } else {
                                //Invalid choice
                                cout << "You cannot play that card. The suit or number value must match." << endl;
                                playerDone = false; //Change to repeat user turn
                            } //End of dependent else     

                            //If user has no more cards
                            if((players+i)->cardAmount == 0) {
                                cout << (players+i)->name << " has used all of their cards. They have won the game!" << endl;
                                gameOver = true; //End game
                                (players+i)->record.wins++; //Increment winners games won stat

                                fstream outputFile;
                                //Update all players stats
                                for(int j = 0; j < playerSize; j++) {
                                    strcpy((players+j)->record.name, (players+j)->name);
                                    if(i != j) {
                                        //For losing players
                                        (players+j)->record.losses++;   //Update losses
                                    } else {
                                        //For winner
                                       (players+j)->record.totalPts = calcPts(players, playerSize); //Tally points
                                       (players+j)->record.fstRnd = *round; //Record Round
                                       (players+j)->record.lngRnd = *round; //Record Round
                                    } //End of dependent else
                                    (players+j)->record.totalGms++;         //Increment games played
                                    float temp = (players+j)->record.wins;  //Increment wins
                                    (players+j)->record.ratio = (temp / (players+j)->record.totalGms) * 100; //Calculate win percent

                                    bool found = false;
                                    string fileName;
                                    //Check through all files
                                    for(int k = 0; k < filesCreated; k++) { 
                                        found = checkForFile((players+j)->name, (k+1)); //Check if player has a file
                                        if(found == true) {
                                            //Update player file
                                            fileName = "stats" + to_string(k+1) + ".dat";
                                            rewriteToFile((players+j)->record, outputFile, fileName);
                                            break;
                                        } //End of dependent else
                                    } //End of nested for loop
                                    if(found == false) {
                                        //Create new player file
                                        filesCreated++;
                                        fileName = "stats" + to_string(filesCreated) + ".dat";
                                        writeToFile((players+j)->record, outputFile, fileName);
                                    } //End of independent if
                                } //End of nested for loop

                                i = playerSize;
                            } //End of independent if
                        } else {
                            //Invalid choice from card chosen
                            cout << "Invalid choice. Returning back to menu." << endl;
                            playerDone = false; //Change to repeat user turn
                        } //End of dependent else
                    } else {
                        //When player has no valid cards
                        cout << "You have no cards that can be placed. Please draw a card instead." << endl;
                        playerDone = false; //Change to repeat user turn
                    } //End of dependent else
                } else if(input == '2') {
                    //When player chooses to draw a card
                    if(cardCount > 0) {
                        //If there are still cards to draw
                        if(check == false) {
                            //If player is forced to draw a card
                            int counter = 0;
                            bool keepDraw = false;
                            while(!keepDraw) {
                                cout << "You have drawn a card: " << *(theCards + currentCount) << endl;
                                drawCard(*(players+i), *(theCards + currentCount)); //Draw card
                                counter++;
                                keepDraw = checkDeck((players+i)->cards, (players+i)->cardAmount, topCard); //Check if player still needs to draw cards
                                cardCount--;    //Amount of cards left
                                currentCount++; //Current index in shuffled cards
                                if(cardCount == 0) {
                                    //If there are no more cards left to draw
                                    break;
                                } //End of independent if
                            } //End of nested while loop
                            cout << "You drew a total of " << counter << " cards." << endl;
                            playerDone = false; //Change to repeat user turn
                        } else {
                            //If user chose to draw a card
                            cout << "You have drawn a card: " << *(theCards + currentCount) << endl;
                            drawCard(*(players+i), *(theCards + currentCount));
                            cardCount--;    //Amount of cards left
                            currentCount++; //Current index in shuffled cards
                            playerDone = false; //Change to repeat user turn
                        } //End of dependent else
                    } else  {
                        //If there are no more cards left to draw
                        cout << "There are no more cards to draw." << endl;
                        if(check == false) {
                            //If user is unable to do anything
                            cout << "You are unable to make anymore moves. Your turn has been passed." << endl;
                        } else {
                            //If user can still place a card down
                            playerDone = false; //Change to repeat user turn
                        }
                    } //End of dependent else
                } else {
                    //When player makes an invalid choice
                    cout << "\nInvalid input! Try again." << endl;
                    playerDone = false; //Change to repeat user turn
                } //End of dependent else
            } //End of nested while loop
        }
        *round += 1; //Increase round after all turns have passed
    }

    delete round;      //Delete dynamically created round
    delete []theCards; //Delete dynamically created shuffled cards
}

int calcPts(Player *losers, int playerSize) {
    char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'};    //Array for point values
    int total = 0;                                                                          //Total points
    
    //Cycle through all players cards
    for(int i = 0; i < playerSize; i++) {
        for(int j = 0; j < (losers+i)->cardAmount; j++) {
            for(int k = 0; k < 13; k++) {
                string card = (losers+i)->cards[j];
                if(card[0] == values[k]) {
                    if(card[0] == 8) {
                        //Add 50 pts for crazy eight
                        total += eight;
                    } else if(card[0] == 'X' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
                        //Add 10 pts for face cards and 10
                        total += faceCard;
                    } else {
                        //Add value of number card
                        total += k+1;
                    } //End of dependent else
                    break;
                } //End of independent if
            } //End of nested for loop
        } //End of nested for loop
    } //End of for loop
    
    return total; //Return total points
}

bool checkForFile(char nameInput[], int index) {
    bool found = false;                                     //If file for person exists
    fstream file;                                           //File object
    string fileName = "stats" + to_string(index) + ".dat";  //The name of file being accessed
    string temp;                                            //Store name from file
    const char *nameFile;                                   //Name from file
    
    //Check if name exists within all files
    file.open(fileName, ios::in);   //Open file for input
    if(file.is_open()) {
        //If file exists
        for(long i = 0; i < NAME_SIZE; i++) {
            char ch;
            file.seekg(i, ios::beg); //Read in name from file
            if(ch != '\n') {
                //If name is still being read
                file.get(ch);
                temp += ch;
            } else {
                //If name ends
                break;
            } //End of dependent else
        } //End of for loop
    } //End of independent if
    nameFile = temp.c_str(); //Convert to c-string
    
    if(strcmp(nameInput, nameFile) == 0) {
        found = true;
    } //End of independent if
    file.close();
    
    return found; //Return outcome
}

void writeToFile(Stats info, fstream &outputFile, string fileName) {
    outputFile.open(fileName, ios::out | ios::binary);              //Open file in binary
    outputFile.write(reinterpret_cast<char*>(&info), sizeof(Stats));//Write to file in binary
    
    outputFile.close(); //Close file
}

void rewriteToFile(Stats info, fstream &outputFile, string fileName) {
    Stats temp;
    outputFile.open(fileName, ios::in | ios::out | ios::binary);    //Open file in binary
    //Retrieve data from file
    if(outputFile.is_open()) {
        //If file exists
        outputFile.read(reinterpret_cast<char*>(&temp), sizeof(Stats)); //Read from file in binary
        
        info.wins += temp.wins;         //Update wins
        info.losses += temp.losses;     //Update losses
        info.totalGms += temp.totalGms; //Update total games played
        info.totalPts += temp.totalPts; //Update total points

        //Update data in file
        if(info.fstRnd > temp.fstRnd) {
            //If round is faster
            info.fstRnd = temp.fstRnd;
        } //End of independent if
        if(info.lngRnd < temp.lngRnd) {
            //If round is longer
            info.lngRnd = temp.lngRnd;
        } //End of independent if
        float num = info.wins;
        info.ratio = (num / info.totalGms) * 100; //Calculate new win percent

        outputFile.seekp(0, ios::beg);
        outputFile.write(reinterpret_cast<char*>(&info), sizeof(Stats));//Write to file in binary
    } else {
        //If file doesn't exist
        cout << "The file does not exist." << endl;
    } //End of dependent else
    
    outputFile.close();
}

Stats readFromFile(fstream &binFile, string fileName) {
    Stats person;                                   //Player's stats
    binFile.open(fileName, ios::in | ios::binary);  //Open file in binary
    //Retrieve data from file
    if(binFile.is_open()) {
        //If file exists
        binFile.read(reinterpret_cast<char*>(&person), sizeof(Stats)); //Read from file in binary
        binFile.close(); //Close file
    } else {
        //If file doesn't exist
        cout << "The file does not exist." << endl;
    } //End of dependent else
    
    return person; //Return player's stats
}

void generateTextFile(const int filesCreated) {
    fstream txtFile;    //File object
    string fileName;    //File name
    Stats person;       //Player's stats
    
    txtFile.open("allStats.txt", ios::out); //Open file
    //Create text file with all player stats
    if(filesCreated == 0) {
        //If there are no existing files
        txtFile << "There is nothing to display yet.";
    } else {
        //If there are files
        for(int i = 0; i < filesCreated; i++) {
            //Display stats
            fileName = "stats" + to_string(i+1) + ".dat";
            fstream tempFile;
            person = readFromFile(tempFile, fileName); //Get data from file
            txtFile << person.name << "\'s Stats" << endl << endl;
            txtFile << "Wins:\t\t\t" << person.wins << endl;
            txtFile << "Losses:\t\t\t" << person.losses << endl;
            txtFile << fixed << setprecision(2); //Format win percent
            txtFile << "Win Percentage:\t\t" << person.ratio << "%" << endl;
            txtFile << setprecision(0);
            txtFile << "Total Games Played:\t" << person.totalGms << endl;
            txtFile << "Total Points Earned:\t" << person.totalPts << endl;
            txtFile << "Fastest Round to Win:\t" << person.fstRnd << endl;
            txtFile << "Longest Round to Win:\t" << person.lngRnd << endl;
            txtFile << endl << "-----------------------------------------" << endl << endl;
        } //End of for loop
    } //End of dependent else
    txtFile.close(); //Close file
}

void cleanUp(Player *players, int playerSize) {
    //Delete all dynamic objects
    for(int i = 0; i < playerSize; i++) {
        //Delete the pointers in player array
        delete [](players+i)->cards;
    } //End of for loop
    
    delete []players; //Delete dynamically created array of players
}
