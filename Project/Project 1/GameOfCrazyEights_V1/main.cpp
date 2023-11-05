/*
 * File:    main.cpp
 * Author:  Draylend Chow
 * Created on October 14th at 6:25 PM
 * Purpose: To simulate a game of Crazy Eights
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

const unsigned int DECK_SIZE = 52; //Standard Playing Card Size
const unsigned int PLAYER_HAND = 5; //Standard Starting Amount

struct Player {
    string name;
    string *cards;
    unsigned int cardAmount = PLAYER_HAND;
    //Create stats structure (nested)
};

string* shuffleCards(const string []);
void startGame(Player [], string*, const int);
void dealCards(Player [], string*, int);
void shiftUp(string *, int, int);
void drawCard(Player &, string);
void removeCard(Player &, int);
bool checkDeck(string *, int, string);
void cleanUp(Player [], int);

int main() {
    srand(static_cast<unsigned int>(time(0)));

    const string REFERENCE[DECK_SIZE] = {"2H", "2C", "2D", "2S",
                                         "3H", "3C", "3D", "3S",
                                         "4H", "4C", "4D", "4S",
                                         "5H", "5C", "5D", "5S",
                                         "6H", "6C", "6D", "6S",
                                         "7H", "7C", "7D", "7S",
                                         "8H", "8C", "8D", "8S",
                                         "9H", "9C", "9D", "9S",
                                         "10H", "10C", "10D", "10S",
                                         "JH", "JC", "JD", "JS",
                                         "QH", "QC", "QD", "QS",
                                         "KH", "KC", "KD", "KS",
                                         "AH", "AC", "AD", "AS"};
    int playerSize;
    char input;

    cout << "Welcome to Virtual Crazy Eights!" << endl;

    while(true) {
        cout << "\nHere are the rules:\nPlayers are each given 5 cards at the start. The top card from the deck will be revealed. Players must place a card of the same suit or number value. If unable to play a card, players must draw from the pile until a play is available. Players may choose to draw from the pile even if they can make a play. If the draw pile is exhausted, players must pass if they are unable to make a play. As the name implies, 8\'s are wild cards, meaning a player can change the value of the top card by placing an 8 and choosing a suit of their choice. The game ends when a player uses all of their cards. The player who finishes first will gain points based on the values of the cards remaining in the other players hands." << endl;
        cout << "\nWould you like to play?\nEnter <Y> or <N>: ";
        cin >> input;
        cin.ignore(10000, '\n');
        if(toupper(input) == 'Y') {
            cout << "\nHow many players are playing (2-8)?: ";
            cin >> input;
            cin.ignore(10000, '\n');
            while(static_cast<int>(input)-48 < 2 || static_cast<int>(input)-48 > 8 || isdigit(input) == 0) {
                cout << "Invalid input. Please try again." << endl;
                cout << "\nHow many players are playing (2-8)?: ";
                cin >> input;
                cin.ignore(10000, '\n');
            }

            playerSize = static_cast<int>(input)-48;
            Player players[playerSize];
            cout << "You have selected " << playerSize << " players." << endl;
            for(int i = 0; i < playerSize; i++) {
                cout << "What is the name of player " << (i+1) << "?: ";
                getline(cin, players[i].name);
            }

            string *theCards = shuffleCards(REFERENCE);
            startGame(players, theCards, playerSize);
            cleanUp(players, playerSize);
        } else if(toupper(input) == 'N') {
            cout << "\nGoodbye!" << endl;
            break;
        } else {
            cout << "\nInvalid input. Please try again." << endl;
        }
    }

    return 0;
}

string* shuffleCards(const string REF[]) {
    string *theCards = new string[DECK_SIZE];
    int numbers[DECK_SIZE];
    int count = 0;

    for(int i = 0; i < DECK_SIZE; i++) {
        numbers[i] = -1;
    }
    while(count < DECK_SIZE) {
        int randCard = (rand() % (52));
        if(numbers[randCard] == -1) {
            *(theCards + count) = REF[randCard];
            count++;
            numbers[randCard] = 0;
        }
    }

    return theCards;
}

void dealCards(Player players[], string *theCards, int playerSize) {
    for(int i = 0; i < playerSize; i++) {
        string *c = new string[players[i].cardAmount];
        players[i].cards = c;
    }

    int currentCard = 0;
    for(int i = 0; i < (playerSize*5);) {
        for(int j = 0; j < playerSize; j++) {
            players[j].cards[currentCard] = *(theCards + i);
            *(theCards + i) = "NULL";
            i++;
        }
        currentCard++;
    }
}

void shiftUp(string *theCards, int cardCount, int currentCard) {
    int randNum = rand() % (3 + 1) + 1;
    int index = (cardCount/2) - randNum + currentCard;

    //Delete
    /*cout << "This is currentCard: " << currentCard << endl;
    cout << "This is index: " << index << endl;
    cout << "This is cardCount (total cards): " << cardCount << endl;*/

    //Delete //this is to check before shift up
    /*cout << "Before" << endl;
    for(int i = 0; i < 52; i++) {
        cout << *(theCards + i) << endl;
    }*/

    string temp = *(theCards + index);
    *(theCards + index) = *(theCards + currentCard);
    for(int i = index; i > currentCard; i--) {
        string temp2 = *(theCards + (i-1));
        *(theCards + (i-1)) = temp;
        temp = temp2;
    }

    //Delete  //this it to check that we did indeed shift everything up correctly
    /*cout << "After" << endl;
    for(int i = 0; i < 52; i++) {
        cout << *(theCards + i) << endl;
    }*/
}

bool checkDeck(string *deck, int size, string topCard) {
    bool valid = false;
  
    for(int i = 0; i < 5; i++) {
        string card = *(deck + i);
        if(card[0] == '8') {
            valid = true;
            break;
        } else if(card[1] == topCard[1]) {
            valid = true;
            break;
        } else if(card[0] == topCard[0]) {
            valid = true;
            break;
        }
    }

    return valid;
}

void drawCard(Player &player, string theCards) {
    string *newHand = new string[player.cardAmount + 1];

    //Delete later
    cout << "Old Hand: " << endl;
    for(int i = 0; i < player.cardAmount; i++) {
        cout << player.cards[i] << endl;
    }
    
    for(int i = 0; i < player.cardAmount; i++) {
        *(newHand + i) = *(player.cards + i);
    }
    *(newHand + player.cardAmount) = theCards;
    player.cardAmount++;
  
    delete []player.cards;
    player.cards = newHand;

    //Delete later
    cout << "New Hand: " << endl;
    for(int i = 0; i < player.cardAmount; i++) {
        cout << player.cards[i] << endl;
    }
}

void removeCard(Player &player, int index) {
    string *newHand = new string[player.cardAmount - 1];
    int count = 0;

    //Delete later
    cout << "Old Hand: " << endl;
    for(int i = 0; i < player.cardAmount; i++) {
        cout << player.cards[i] << endl;
    }
  
    for(int i = 0; i < player.cardAmount; i++) {
        if(count == index) {
            count++;
        }
        *(newHand + i) = player.cards[count];
        count++;
    }
    player.cardAmount--;

    delete []player.cards;
    player.cards = newHand;

    //Delete later
    cout << "New Hand: " << endl;
    for(int i = 0; i < player.cardAmount; i++) {
        cout << player.cards[i] << endl;
    }
}

void startGame(Player players[], string *theCards, const int playerSize) {
    bool gameOver = false;
    int currentCount = playerSize * 5;
    int cardCount = 52 - currentCount;
    string topCard = *(theCards + currentCount);

    //Delete later; this is to test the shiftUp function
    /**(theCards + currentCount) = "8Y";
    topCard = "8Y";*/

    //cout << "This is topCard: " << topCard[0] << endl;

    dealCards(players, theCards, playerSize);
    if(topCard[0] == '8') {
        while(topCard[0] == '8') {
            shiftUp(theCards, cardCount, currentCount);
            topCard = *(theCards + currentCount);
        }
        *(theCards + currentCount) = "NULL";
        cardCount--;
        currentCount++;
    } else {
        cardCount--;
        currentCount++;
    }
  
    while(!gameOver) {
        for(int i = 0; i < playerSize; i++) {   
            cout << "\nThis is the top card: " << topCard << endl << endl;
            char input;
            bool check = checkDeck(players[i].cards, players[i].cardAmount, topCard);
            cout << "It is " << players[i].name << "'s turn!\nHere is your current hand: [";
            for(int j = 0; j < players[i].cardAmount; j++) {   
                cout << players[i].cards[j];
                if(j+1 < players[i].cardAmount) {
                    cout << ", ";
                } else {
                    cout << "]" << endl;
                }
            }
            cout << "\nPlease choose from the following menu:" << endl;
            cout << "1. Place a Card\n2. Draw a Card\n\nChoose an option: ";
            cin >> input;
            cin.ignore(10000, '\n');
            if(input == '1') {
                cout << "You chose to place a card.";
                if(check == true) {
                    cout << "Please choose a following card from your deck or enter an invalid choice to go back:" << endl;
                    for(int j = 0; j < players[i].cardAmount; j++) {
                        cout << (j+1) << ". " << players[i].cards[j] << endl;
                    }
                    cout << "Enter a choice: ";
                    char choice;
                    cin >> choice;
                    cin.ignore(10000, '\n');
                    if(choice >= 49 && choice <= players[i].cardAmount + 48) {
                        string cardChosen = players[i].cards[choice - 49];
                        if(cardChosen[0] == '8') {
                            cout << "You have placed a Crazy Eight! Please choose a suit from the following menu (1-4):\n\n1. Heart\n2. Club\n3. Diamond\n4. Spade";
                            char suit;
                            cin >> suit;
                            cin.ignore(10000, '\n');
                            if(suit == '1') {
                                topCard = "0H";
                                removeCard(players[i], (static_cast<int>(choice)-49));
                            } else if(suit == '2') {
                                topCard = "0C";
                                removeCard(players[i], (static_cast<int>(choice)-49));
                            } else if(suit == '3') {
                                topCard = "0D";
                                removeCard(players[i], (static_cast<int>(choice)-49));
                            } else if(suit == '4') {
                                topCard = "0S";
                                removeCard(players[i], (static_cast<int>(choice)-49));
                            } else {
                                cout << "Invalid choice. Returning back to menu." << endl;
                                i--;
                            }
                        } else {
                            topCard = cardChosen;
                            removeCard(players[i], (static_cast<int>(choice)-49));
                        }
                        if(players[i].cardAmount == 0) {
                            cout << players[i].name << " has used all of their cards. They have won the game!" << endl;
                            gameOver = true;
                            //Add to stats and display current standings of all players with points based on cards left
                        }
                    } else {
                        cout << "Invalid choice. Returning back to menu." << endl;
                        i--;
                    }
                } else {
                    cout << "You have no cards that can be placed. Please draw a card instead.";
                    i--;
                }
            } else if(input == '2') {
                if(cardCount > 0) {
                    if(check == false) {
                        int counter = 0;
                        bool keepDraw = true;
                        while(keepDraw) {
                            cout << "You have drawn a card: " << *(theCards + currentCount) << endl;
                            drawCard(players[i], *(theCards + currentCount));
                            counter++;
                            keepDraw = checkDeck(players[i].cards, players[i].cardAmount, topCard);
                            cardCount--;
                            currentCount++;
                        }
                        cout << "You drew a total of " << counter << " cards." << endl;
                        i--;
                    } else {
                        cout << "You have drawn a card: " << *(theCards + currentCount) << endl;
                        drawCard(players[i], *(theCards + currentCount));
                        cardCount--;
                        currentCount++;
                        i--;
                    }
                } else  {
                    cout << "There are no more cards to draw." << endl;
                    if(check == false) {
                        cout << "You are unable to make anymore moves. Your turn has been passed." << endl;
                    } else {
                        i--;
                    }
                }
            } else {
              cout << "\nInvalid input! Try again." << endl;
              i--;
            }
        }
    }

    delete []theCards;
}

void cleanUp(Player players[], int playerSize) {
    for(int i = 0; i < playerSize; i++) {
        delete [] players[i].cards;
    }
}