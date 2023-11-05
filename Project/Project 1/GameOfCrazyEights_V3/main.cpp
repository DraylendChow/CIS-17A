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

const unsigned int DECK_SIZE = 52;  //Standard Playing Card Size
const unsigned int PLAYER_HAND = 5; //Standard Starting Amount
const unsigned int NAME_SIZE = 31;  //Name Size + 1 for Null Terminator

//  Stat Structure to hold statistics on game
struct Stats {
    char name[NAME_SIZE];
    int wins = 0, losses = 0, fstRnd = 0, lngRnd = 0, totalGms = 0, totalPts = 0;
    float ratio;
};

//  Player Structure to hold information
struct Player {
    char name[NAME_SIZE];
    string *cards;
    unsigned int cardAmount = PLAYER_HAND;
    Stats record;
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
    Player *players;
    string *theCards;
    int playerSize;
    int filesCreated = 0;
    char input; 

    cout << "Welcome to Virtual Crazy Eights!" << endl;
    cout << "\nHere are the rules:\nPlayers are each given 5 cards at the start. The top card from the deck will be revealed. "
        "\nPlayers must place a card of the same suit or number value. If unable to play a card, players must draw from the "
        "\npile until a play is available. Players may choose to draw from the pile even if they can make a play. If the draw "
        "\npile is exhausted, players must pass if they are unable to make a play. As the name implies, 8\'s are wild cards, "
        "\nmeaning a player can change the value of the top card by placing an 8 and choosing a suit of their choice. The game "
        "\nends when a player uses all of their cards. The player who finishes first will gain points based on the values of the "
        "\ncards remaining in the other players hands." << endl;
    while(true) {
        cout << "\nWould you like to play? Enter:\n<Y> for Yes\n<N> for No\n<i> for Info on a Player\n<G> for Generate File on all Players\n\nEnter: ";
        cin >> input;
        cin.ignore(256, '\n');
        if(toupper(input) == 'Y') {
            cout << "\nHow many players are playing (2-8)?: ";
            cin >> input;
            cin.ignore(256, '\n');
            while(static_cast<int>(input)-48 < 2 || static_cast<int>(input)-48 > 8 || isdigit(input) == 0) {
                cout << "Invalid input. Please try again." << endl;
                cout << "\nHow many players are playing (2-8)?: ";
                cin >> input;
                cin.ignore(256, '\n');
            }
            playerSize = static_cast<int>(input)-48;
            players = new Player[playerSize];
            cout << "You have selected " << playerSize << " players." << endl;
            for(int i = 0; i < playerSize; i++) {
                cout << "What is the name of player " << (i+1) << "? (Please enter less than 30 characters): ";
                cin.getline((players+i)->name, NAME_SIZE);
            }
            theCards = shuffleCards(REFERENCE);
            startGame(players, theCards, playerSize, filesCreated);
            cleanUp(players, playerSize);
        } else if(toupper(input) == 'I') {
            char id[NAME_SIZE];
            cout << "Please enter the name of the user you wish to view (CASE SENSITIVE): ";
            cin.getline(id, NAME_SIZE);
            bool found = false;
            string fileName;
            for(int i = 0; i < filesCreated; i++) { 
                found = checkForFile(id, (i+1));
                if(found == true) {
                    //Delete later
                    //cout << "The name was found!" << endl;
                    fileName = "stats" + to_string(i+1) + ".dat";
                    break;
                }
            }
            if(found == true) {
                fstream inputFile;
                Stats person = readFromFile(inputFile, fileName);
                cout << "\nName: " << person.name << endl;
                cout << "Wins: " << person.wins << endl;
                cout << "Losses: " << person.losses << endl;
                cout << "Win Percentage: " << person.ratio << "%" << endl;
                cout << "Total Games Played: " << person.totalGms << endl;
                cout << "Total Points Accumulated: " << person.totalPts << endl;
                cout << "Fastest Round to Win: " << person.fstRnd << endl;
                cout << "Longest Round to Win: " << person.lngRnd << endl;
            } else {
                cout << "Data for that person does not exist. Please complete one game to register data." << endl;
            }
        } else if(toupper(input) == 'G') {
            generateTextFile(filesCreated);
            cout << "File has been created." << endl;
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

void dealCards(Player *players, string *theCards, int playerSize) {
    for(int i = 0; i < playerSize; i++) {
        string *c = new string[(players+i)->cardAmount];
        (players+i)->cards = c;
    }

    int currentCard = 0;
    for(int i = 0; i < (playerSize*5);) {
        for(int j = 0; j < playerSize; j++) {
            (players+j)->cards[currentCard] = *(theCards + i);
            *(theCards + i) = "NULL";
            i++;
        }
        currentCard++;
    }
}

void shiftUp(string *theCards, int cardCount, int currentCard) {
    int randNum = rand() % (3 + 1) + 1;
    int index = (cardCount/2) - randNum + currentCard;

    string temp = *(theCards + index);
    *(theCards + index) = *(theCards + currentCard);
    for(int i = index; i > currentCard; i--) {
        string temp2 = *(theCards + (i-1));
        *(theCards + (i-1)) = temp;
        temp = temp2;
    }
}

bool checkDeck(string *deck, int size, string topCard) {
    bool valid = false;

    for(int i = 0; i < size; i++) {
        string card = *(deck + i);
        if(card[0] == '8' || card[0] == topCard[0] || card[1] == topCard[1]) {
            valid = true;
            break;
        }
    }

    return valid;
}

void drawCard(Player &player, string theCards) {
    string *newHand = new string[player.cardAmount + 1];

    for(int i = 0; i < player.cardAmount; i++) {
        *(newHand + i) = *(player.cards + i);
    }
    *(newHand + player.cardAmount) = theCards;
    player.cardAmount++;

    delete []player.cards;
    player.cards = newHand;
}

void removeCard(Player &player, int index) {
    string *newHand = new string[player.cardAmount - 1];
    int count = 0;

    player.cardAmount--;
    for(int i = 0; i < player.cardAmount; i++) {
        if(count == index) {
            count++;
        }
        *(newHand + i) = player.cards[count];
        count++;
    }

    delete []player.cards;
    player.cards = newHand;
}

void startGame(Player *players, string *theCards, const int playerSize, int &filesCreated) {
    bool gameOver = false;
    int currentCount = playerSize * 5;
    int cardCount = 52 - currentCount;
    int round = 1;
    string topCard = *(theCards + currentCount);

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
        cout << "\nRound " << round << endl;
        for(int i = 0; i < playerSize; i++) {   
            cout << "\nThis is the top card: " << topCard << endl << endl;
            char input;
            bool check = checkDeck((players+i)->cards, (players+i)->cardAmount, topCard);
            cout << "It is " << (players+i)->name << "'s turn!\nHere is your current hand: [";
            for(int j = 0; j < (players+i)->cardAmount; j++) {   
                cout << (players+i)->cards[j];
                if(j+1 < (players+i)->cardAmount) {
                    cout << ", ";
                } else {
                    cout << "]" << endl;
                }
            }
            cout << "\nPlease choose from the following menu:" << endl;
            cout << "1. Place a Card\n2. Draw a Card\n\nChoose an option: ";
            cin >> input;
            cin.ignore(256, '\n');
            if(input == '1') {
                cout << "You chose to place a card." << endl;
                if(check == true) {
                    cout << "Please choose a card from your deck or input an invalid choice to go back:" << endl;
                    for(int j = 0; j < (players+i)->cardAmount; j++) {
                        cout << (j+1) << ". " << (players+i)->cards[j] << endl;
                    } 
                    //When user inputs char it bugs out.. fix?
                    short choice;
                    cout << "\nChoose an option: ";
                    cin >> choice;
                    cin.ignore(256, '\n');
                    if(choice >= 1 && choice <= (players+i)->cardAmount) {
                        string cardChosen = (players+i)->cards[choice - 1];
                        if(cardChosen[0] == '8') {
                            cout << "You have placed a Crazy Eight! Please choose a suit from the following menu (1-4):\n\n1. Heart\n2. Club\n3. Diamond\n4. Spade" << endl;
                            char suit;
                            cout << "\nChoose an option: ";
                            cin >> suit;
                            cin.ignore(256, '\n');
                            if(suit == '1') {
                                topCard = "0H";
                                removeCard(*(players+i), (choice-1));
                            } else if(suit == '2') {
                                topCard = "0C";
                                removeCard(*(players+i), (choice-1));
                            } else if(suit == '3') {
                                topCard = "0D";
                                removeCard(*(players+i), (choice-1));
                            } else if(suit == '4') {
                                topCard = "0S";
                                removeCard(*(players+i), (choice-1));
                            } else {
                                cout << "Invalid choice. Returning back to menu." << endl;
                                i--;
                            }
                        } else if(cardChosen[0] == topCard[0] || cardChosen[1] == topCard[1]){
                            topCard = cardChosen;
                            removeCard(*(players+i), (choice-1));
                        } else {
                            cout << "You cannot play that card. The suit or number value must match." << endl;
                            i--;
                        }

                        if((players+i)->cardAmount == 0) {
                            cout << (players+i)->name << " has used all of their cards. They have won the game!" << endl;
                            gameOver = true;

                            if((players+i)->record.fstRnd == 0 || (players+i)->record.fstRnd > round) {
                                (players+i)->record.fstRnd = round;
                            }
                            if((players+i)->record.lngRnd < round) {
                                (players+i)->record.lngRnd = round;
                            }
                            (players+i)->record.wins++;

                            fstream outputFile;
                            for(int j = 0; j < playerSize; j++) {
                                strcpy((players+j)->record.name, (players+j)->name);
                                if(i != j) {
                                    (players+j)->record.losses++;
                                } else {
                                   (players+j)->record.totalPts = calcPts(players, playerSize); 
                                }
                                (players+j)->record.totalGms++;
                                (players+j)->record.ratio = ((players+j)->record.wins / (players+j)->record.totalGms / 1.0) * 100;

                                bool found = false;
                                string fileName;
                                for(int k = 0; k < filesCreated; k++) { 
                                    found = checkForFile((players+j)->name, (k+1));
                                    if(found == true) {
                                        fileName = "stats" + to_string(k+1) + ".dat";
                                        rewriteToFile((players+j)->record, outputFile, fileName);
                                        break;
                                    }
                                }
                                if(found == false) {
                                    filesCreated++;
                                    fileName = "stats" + to_string(filesCreated) + ".dat";
                                    writeToFile((players+j)->record, outputFile, fileName);
                                }
                            }

                            break;
                        }
                    } else {
                        cout << "Invalid choice. Returning back to menu." << endl;
                        i--;
                    }
                } else {
                    cout << "You have no cards that can be placed. Please draw a card instead." << endl;
                    i--;
                }
            } else if(input == '2') {
                if(cardCount > 0) {
                    if(check == false) {
                        int counter = 0;
                        bool keepDraw = false;
                        while(!keepDraw) {
                            cout << "You have drawn a card: " << *(theCards + currentCount) << endl;
                            drawCard(*(players+i), *(theCards + currentCount));
                            counter++;
                            keepDraw = checkDeck((players+i)->cards, (players+i)->cardAmount, topCard);
                            cardCount--;
                            currentCount++;
                            if(cardCount == 0) {
                                break;
                            }
                        }
                        cout << "You drew a total of " << counter << " cards." << endl;
                        i--;
                    } else {
                        cout << "You have drawn a card: " << *(theCards + currentCount) << endl;
                        drawCard(*(players+i), *(theCards + currentCount));
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
        round++;
    }

    delete []theCards;
}

int calcPts(Player *losers, int playerSize) {
    char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'};
    int total = 0;

    for(int i = 0; i < playerSize; i++) {
        for(int j = 0; j < (losers+i)->cardAmount; j++) {
            for(int k = 0; k < 13; k++) {
                string card = (losers+i)->cards[j];
                if(card[0] == values[k]) {
                    if(card[0] == 8) {
                        total += 50;
                    } else if(card[0] == 'X' || card[0] == 'J' || card[0] == 'Q' || card[0] == 'K') {
                        total += 10;
                    } else {
                        total += k+1;
                    }
                    break;
                }
            }
        }
    }

    return total;
}

bool checkForFile(char nameInput[], int index) {
    bool found = false;
    fstream file;
    string fileName = "stats" + to_string(index) + ".dat";
    string temp;
    const char *nameFile;
    file.open(fileName, ios::in);
    if(file.is_open()) {
        for(long j = 0; j < NAME_SIZE; j++) {
            char ch;
            file.seekg(j, ios::beg);
            //Fix this, this means spaces aren't allowed in name
            if(ch != '\n') {
                file.get(ch);
                temp += ch;
            } else {
                break;
            }
        }
    }
    nameFile = temp.c_str();

    //Delete later
    /*cout << "This is the name from the file: " << nameFile << endl;
    cout << "This is the name from input: " << nameInput << endl;*/

    if(strcmp(nameInput, nameFile) == 0) {
        //cout << "Name was found! Found is true" << endl;
        found = true;
    }

    return found;
}

void writeToFile(Stats info, fstream &outputFile, string fileName) {
    outputFile.open(fileName, ios::out | ios::binary);
    outputFile.write(reinterpret_cast<char*>(&info), sizeof(Stats));

    outputFile.close();
}

void rewriteToFile(Stats info, fstream &outputFile, string fileName) {
    Stats temp = readFromFile(outputFile, fileName);
    info.wins += temp.wins;
    info.losses += temp.losses;
    info.totalGms += temp.totalGms;
    info.totalPts += temp.totalPts;

    info.fstRnd = temp.fstRnd;
    info.lngRnd = temp.lngRnd;
    info.ratio = (info.wins / info.totalGms / 1.0) * 100;

    outputFile.open(fileName, ios::out | ios::binary);
    outputFile.write(reinterpret_cast<char*>(&info), sizeof(Stats));

    outputFile.close();
}

Stats readFromFile(fstream &binFile, string fileName) {
    Stats person;
    binFile.open(fileName, ios::in | ios::binary);
    if(binFile.is_open()) {
        binFile.read(reinterpret_cast<char*>(&person), sizeof(Stats));
        binFile.close();
    } else {
        cout << "The file does not exist." << endl;
    }

    return person;
}

void generateTextFile(const int filesCreated) {
    fstream txtFile;
    string fileName;
    Stats person;

    txtFile.open("allStats.txt", ios::out);
    if(filesCreated == 0) {
        txtFile << "There is nothing to display yet.";
    } else {
        for(int i = 0; i < filesCreated; i++) {
            fileName = "stats" + to_string(i+1) + ".dat";
            fstream tempFile;
            person = readFromFile(tempFile, fileName);
            txtFile << person.name << "\'s Stats" << endl << endl;
            txtFile << "Wins:\t\t\t" << person.wins << endl;
            txtFile << "Losses:\t\t\t" << person.losses << endl;
            txtFile << fixed << setprecision(2);
            txtFile << "Win Percentage:\t\t" << person.ratio << "%" << endl;
            txtFile << setprecision(0);
            txtFile << "Total Games Played:\t" << person.totalGms << endl;
            txtFile << "Total Points Earned:\t" << person.totalPts << endl;
            txtFile << "Fasted Round to Win:\t" << person.fstRnd << endl;
            txtFile << "Longest Round to Win:\t" << person.lngRnd << endl;
            txtFile << endl << "-----------------------------------------" << endl << endl;
        }
    }
    txtFile.close();
}

void cleanUp(Player *players, int playerSize) {
    for(int i = 0; i < playerSize; i++) {
        delete [](players+i)->cards;
    }

    delete []players;
}