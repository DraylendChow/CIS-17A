/* 
 * File:   GameMaster.h
 * Author: Draylend Chow
 *
 * Created on December 9, 2023, 1:52 PM
 */

#include "GameMaster.h"

int GameMaster::filesCreated = 0;

GameMaster::GameMaster() {
    players = NULL;
    theCards = NULL;
    playerSize = 0;
}

GameMaster::GameMaster(int playerSize) {
    players = new Player*[playerSize]; //Dynamically create array of Players
    this->playerSize = playerSize;
            
    //Ask for names of players
    for(int i = 0; i < playerSize; i++) {
        cout << "What is the name of Player " << (i+1) << "? (Please enter less than 10 characters and no spaces): ";
        string name;
        cin >> name;
        players[i] = new Player(name, i+1);
    } //End of for loop
    
    shuffleCards();
    startGame();
}

GameMaster::~GameMaster() {
    delete[] theCards; //Delete dynamically created shuffled cards
    
    /*for(int i = 0; i < playerSize; i++) {
        //Delete the pointers in player array
        delete players[i];
    } //End of for loop*/

    delete []players; //Delete dynamically created array of players
}

void GameMaster::shuffleCards() {
    theCards = new Card*[52];  //The deck of shuffled cards
    int numbers[52];           //Keep track of which cards have been used
    int count = 0;             //Index counter for theCards

    //Initialize numbers array
    for(int i = 0; i < 52; i++) {
        numbers[i] = -1;
    } //End of for loop
    //Generate random number to choose card and assign to theCards
    while(count < 52) {
        int randCard = (rand() % (52));
        if(numbers[randCard] == -1) {
            theCards[count] = &stdDeck[randCard];
            count++;
            numbers[randCard] = 0;
        } //End of independent if
    } //End of while loop
}

void GameMaster::dealCards() {
    //Create array of cards for each player
    for(int i = 0; i < playerSize; i++) {
        Card **c = new Card*[players[i]->getCardAmount()];
        players[i]->setHand(c);
    } //End of for loop

    int currentCard = 0;
    //Assign cards to players
    for(int i = 0; i < (playerSize*5);) {
        for(int j = 0; j < playerSize; j++) {
            players[j]->getHand()[currentCard] = theCards[i];      //Assign card to players hand
            i++;
        } //End of nested for loop
        currentCard++; //Increment index shuffled cards
    } //End of for loop
}

void GameMaster::shiftUp(int cardCount, int currentCard) {
    int randNum = rand() % (3 + 1) + 1;                 //Generate random number
    int index = (cardCount/2) - randNum + currentCard;  //Calculate number in middle of deck

    Card *temp = theCards[index];               //Holding old value of middle card
    theCards[index] = theCards[currentCard];    //Swapping top card to middle card
    //Shift all values up
    for(int i = index; i > currentCard; i--) {
        Card *temp2 = theCards[i-1];
        theCards[i-1] = temp;
        temp = temp2;
    } //End of for loop
}

bool GameMaster::checkDeck(Card **hand, int size, Card *topCard) {
    bool valid = false; //If player has a valid card to play
  
    //Check to see if player has any cards they can use
    for(int i = 0; i < size; i++) {
        Card *currentCard = hand[i];
        if(currentCard->getValue() == '8' || currentCard->getSuit() == topCard->getSuit() || currentCard->getValue() == topCard->getValue()) {
            valid = true;
            break;
        } //End of independent if
    } //End of for loop

    return valid;
}

void GameMaster::startGame() {
    bool gameOver = false;                          //Decides when games ends
    int currentCount = playerSize * 5;              //Current index in the shuffled cards
    int cardCount = 52 - currentCount;              //How many cards are left
    int *round = new int;                           //Current round
    *round = 1;
    Card *topCard = theCards[currentCount];         //The top card on the deck

    dealCards(); //Deal cards out to players
    
    //Check if the top card is 8
    if(topCard->getValue() == '8') {
        while(topCard->getValue() == '8') {
            shiftUp(cardCount, currentCount);   //Shuffle card back into deck
            topCard = theCards[currentCount];   //New top card
        } //End of while
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
                cout << "\nThis is the top card: " << *(topCard) << endl << endl;
                char input;
                //Check if player can make a move
                bool check = checkDeck(players[i]->getHand(), players[i]->getCardAmount(), topCard);
                cout << "It is " << players[i]->getName() << "'s turn!\nHere is your current hand: [";
                //Print out players hand
                for(int j = 0; j < players[i]->getCardAmount(); j++) {
                    cout << *(players)[i]->getHand()[j];
                    if(j+1 < players[i]->getCardAmount()) {
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
                        for(int j = 0; j < players[i]->getCardAmount(); j++) {
                            cout << (j+1) << ". " << *(players)[i]->getHand()[j] << endl;
                        } //End of nested for loop
                        int choice;
                        cout << "\nChoose an option: ";
                        cin >> choice;
                        cin.ignore(256, '\n');
                        //If choice is valid
                        if(choice >= 1 && choice <= players[i]->getCardAmount()) {
                            Card *cardChosen = players[i]->getHand()[choice - 1];
                            if(cardChosen->getValue() == '8') {
                                //If player uses a crazy eight
                                cout << "You have placed a Crazy Eight! Please choose a suit from the following menu (1-4):\n\n1. Heart\n2. Club\n3. Diamond\n4. Spade" << endl;
                                char suit;
                                cout << "\nChoose an option: ";
                                cin >> suit;
                                cin.ignore(256, '\n');
                                //Player chooses suit
                                if(suit == '1') {
                                    topCard->setValue('0');                 //Change top card to chosen suit
                                    topCard->setSuit('H');                  //Change top card to chosen suit
                                    players[i]->removeCard(choice-1);       //Remove card from hand
                                } else if(suit == '2') {
                                    topCard->setValue('0');                 //Change top card to chosen suit
                                    topCard->setSuit('C');                  //Change top card to chosen suit
                                    players[i]->removeCard(choice-1);       //Remove card from hand
                                } else if(suit == '3') {
                                    topCard->setValue('0');                 //Change top card to chosen suit
                                    topCard->setSuit('D');                  //Change top card to chosen suit
                                    players[i]->removeCard(choice-1);       //Remove card from hand
                                } else if(suit == '4') {
                                    topCard->setValue('0');                 //Change top card to chosen suit
                                    topCard->setSuit('S');                  //Change top card to chosen suit
                                    players[i]->removeCard(choice-1);       //Remove card from hand
                                } else {
                                    //Invalid choice in suit
                                    cout << "Invalid choice. Returning back to menu." << endl;
                                    playerDone = false; //Change to repeat user turn
                                } //End of dependent else
                            } else if(cardChosen->getValue() == topCard->getValue() || cardChosen->getSuit() == topCard->getSuit()) {
                                //Regular card chosen
                                topCard = cardChosen;               //Update top card
                                players[i]->removeCard(choice-1);  //Remove card from hand
                            } else {
                                //Invalid choice
                                cout << "You cannot play that card. The suit or number value must match." << endl;
                                playerDone = false; //Change to repeat user turn
                            } //End of dependent else
                            
                            //If user has no more cards
                            if(players[i]->getCardAmount() == 0) {
                                cout << players[i]->getName() << " has used all of their cards. They have won the game!" << endl;
                                gameOver = true; //End game
                                
                                players[i]->getRecord()->setWins(1); //Increment winners games win stat

                                fstream outputFile;
                                //Update all players stats
                                for(int j = 0; j < playerSize; j++) {
                                    if(i != j) {
                                        //For losing players
                                        players[j]->getRecord()->setLosses(1);   //Update losses
                                        players[j]->getRecord()->setWins(0);     //Update wins
                                        players[j]->getRecord()->setRatio(0);    //Set Ratio
                                    } else {
                                        //For winner
                                        players[j]->getRecord()->setTotalPts(calcPts(playerSize)); //Tally points
                                        players[j]->getRecord()->setFstRnd(*round); //Record Round
                                        players[j]->getRecord()->setLngRnd(*round); //Record Round
                                        players[j]->getRecord()->setRatio(100);     //Set Ratio
                                    } //End of dependent else
                                    players[j]->getRecord()->setTotalGms(1);    //Increment games played

                                    bool found = false;
                                    string fileName;
                                    //Check through all files
                                    for(int k = 0; k < filesCreated; k++) { 
                                        found = checkForFile(players[j]->getName(), (k+1)); //Check if player has a file
                                        if(found == true) {
                                            //Update player file
                                            fileName = "stats" + to_string(k+1) + ".dat";
                                            rewriteToFile(players[j]->getRecord(), outputFile, fileName);
                                            break;
                                        } //End of dependent else
                                    } //End of nested for loop
                                    if(found == false) {
                                        //Create new player file
                                        filesCreated++;
                                        fileName = "stats" + to_string(filesCreated) + ".dat";
                                        writeToFile(players[j]->getRecord(), outputFile, fileName);
                                    } //End of independent if
                                } //End of nested for loop

                                i = playerSize; //End game immediately
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
                                cout << "You have drawn a card: " << *(theCards)[currentCount] << endl;
                                players[i]->drawCard(theCards[currentCount]); //Draw card
                                counter++;
                                keepDraw = checkDeck(players[i]->getHand(), players[i]->getCardAmount(), topCard); //Check if player still needs to draw cards
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
                            cout << "You have drawn a card: " << *(theCards)[currentCount] << endl;
                            players[i]->drawCard(theCards[currentCount]);
                            cardCount--;    //Amount of cards left
                            currentCount++; //Current index in shuffled cards
                            playerDone = false; //Change to repeat user turn
                        } //End of dependent else
                    } else {
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
}

int GameMaster::calcPts(int) {
    char values[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'};    //Array for point values
    int total = 0;                                                                          //Total points
    
    //Cycle through all players cards
    for(int i = 0; i < playerSize; i++) {
        for(int j = 0; j < players[i]->getCardAmount(); j++) {
            for(int k = 0; k < 13; k++) {
                Card *card = players[i]->getHand()[j];
                if(card->getValue() == values[k]) {
                    total += card->getPtVal();
                    break;
                } //End of independent if
            } //End of nested for loop
        } //End of nested for loop
    } //End of for loop
    
    return total; //Return total points
}

bool GameMaster::checkForFile(string name, int index) {
    bool found = false;                                     //If file for person exists
    fstream file;                                           //File object
    string fileName = "stats" + to_string(index) + ".dat";  //The name of file being accessed
    string nameFile;                                        //Name from file
    
    //Check if name exists within all files
    file.open(fileName, ios::in);   //Open file for input
    if(file.is_open()) {
        //If file exists
        for(int i = 8; i < 30; i++) {
            char ch;
            file.seekg(i, ios::beg); //Read in name from file
            file.get(ch);
            if(isalpha(ch) != 0) {
                //If name is still being read
                nameFile += ch;
            } else {
                //If name ends
                break;
            } //End of dependent else
        } //End of for loop
    } //End of independent if
    
    if(name == nameFile) {
        found = true;
    } //End of independent if
    file.close();
    
    return found; //Return outcome
}

void GameMaster::writeToFile(Stats *info, fstream &outputFile, string fileName) {
    outputFile.open(fileName, ios::out | ios::binary);  //Open file in binary
    outputFile.write((char*)info, sizeof(Stats));      //Write to file in binary
    
    outputFile.close(); //Close file
}

void GameMaster::rewriteToFile(Stats *info, fstream &outputFile, string fileName) {
    Stats *temp = new Stats();
    outputFile.open(fileName, ios::in | ios::out | ios::binary);    //Open file in binary
    //Retrieve data from file
    if(outputFile.is_open()) {
        //If file exists
        outputFile.read((char*)temp, sizeof(Stats)); //Read from file in binary
        
        info->setWins(info->getWins() + temp->getWins());               //Update wins
        info->setLosses(info->getLosses() + temp->getLosses());         //Update losses
        info->setTotalGms(info->getTotalGms() + temp->getTotalGms());   //Update total games played
        info->setTotalPts(info->getTotalPts() + temp->getTotalPts());   //Update total points

        //Update data in file
        if(info->getFstRnd() > temp->getFstRnd()) {
            //If round is faster
            info->setFstRnd(temp->getFstRnd());
        } //End of independent if
        if(info->getLngRnd() < temp->getLngRnd()) {
            //If round is longer
            info->setLngRnd(temp->getLngRnd());
        } //End of independent if
        float num = info->getWins();
        info->setRatio((num / info->getTotalGms()) * 100); //Calculate new win percent

        outputFile.seekp(0, ios::beg);
        outputFile.write((char*)info, sizeof(Stats)); //Write to file in binary
        
        delete temp;
    } else {
        //If file doesn't exist
        cout << "The file does not exist." << endl;
    } //End of dependent else
    
    outputFile.close();
}

Stats* GameMaster::readFromFile(fstream &binFile, string fileName) {
    Stats *person = new Stats();                                   //Player's stats
    binFile.open(fileName, ios::in | ios::binary);  //Open file in binary
    //Retrieve data from file
    if(binFile.is_open()) {
        //If file exists
        binFile.read((char*)person, sizeof(Stats)); //Read from file in binary
        binFile.close(); //Close file
    } else {
        //If file doesn't exist
        cout << "The file does not exist." << endl;
    } //End of dependent else
    
    binFile.open(fileName, ios::in);
    string name = "";
    for(int i = 8; i < 30; i++) {
        char ch;
        binFile.seekg(i, ios::beg); //Read in name from file
        binFile.get(ch);
        if(isalpha(ch) != 0) {
            //If name is still being read
            name += ch;
        } else {
            //If name ends
            break;
        } //End of dependent else
    } //End of for loop
    person->setUsername(name);
    binFile.close();
    
    return person; //Return player's stats
}

void GameMaster::generateTextFile() {
    fstream txtFile;    //File object
    string fileName;    //File name
    Stats *person;      //Player's stats
    
    txtFile.open("allStats.txt", ios::out); //Open file
    //Create text file with all player stats
    if(filesCreated == 0) {
        //If there are no existing files
        txtFile << "There is nothing to display yet.";
        txtFile.close(); //Close file
        throw "There is no data to display yet.";
    } else {
        //If there are files
        for(int i = 0; i < filesCreated; i++) {
            //Display stats
            fileName = "stats" + to_string(i+1) + ".dat";
            fstream tempFile;
            person = readFromFile(tempFile, fileName); //Get data from file
            txtFile << person->getUsername() << "\'s Stats" << endl << endl;
            txtFile << "Wins:\t\t\t" << person->getWins() << endl;
            txtFile << "Losses:\t\t\t" << person->getLosses() << endl;
            txtFile << fixed << setprecision(2); //Format win percent
            txtFile << "Win Percentage:\t\t" << person->getRatio() << "%" << endl;
            txtFile << setprecision(0);
            txtFile << "Total Games Played:\t" << person->getTotalGms() << endl;
            txtFile << "Total Points Earned:\t" << person->getTotalPts() << endl;
            txtFile << "Fastest Round to Win:\t" << person->getFstRnd() << endl;
            txtFile << "Longest Round to Win:\t" << person->getLngRnd() << endl;
            txtFile << endl << "-----------------------------------------" << endl << endl;
            
            delete person;
        } //End of for loop
        txtFile.close(); //Close file
    } //End of dependent else
}