//
//  GameSimulator.cpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//


#include "GameSimulator.hpp"

using namespace std;

#pragma mark Globals
int currentPlayerId = -1;

// Client information , from server
int numberOfTotalPlayers;
string currentPlayerUsername;
vector <string> playersStringVector;
bool mouseClickAvailable;

#pragma mark TEST
int numberOfOnlinePlayers = 0;

#pragma mark Functions Prototypes

int getRandomNumber();

void initializeConstantsValues() {
    numberOfTotalPlayers = 0;
    currentPlayerUsername = "";
    mouseClickAvailable = false;;
}


void updateValueOfPreviousPlayer(string previousPlayer, int diceValue) {

    for (int i = 0; i < playerCurrentlyPlayingList.size(); i++) {
        if ((previousPlayer.compare(playerCurrentlyPlayingList[i].getUsername())) == 0) {
            vector<Token>toklist = playerCurrentlyPlayingList[i].getTokenList();
            Token tok = toklist[0];
            int nextSquareForToken;
            if (playerCurrentlyPlayingList[i].getIsHome() == true) {
                playerCurrentlyPlayingList[i].setIsHome(false);
                nextSquareForToken = 13 * i + 1 + diceValue;
            } else {
                nextSquareForToken = (tok.getSquareNumber() + diceValue) %  52;
            }
            tok.setSquareNumber(nextSquareForToken);
            float midX = smallSquareSharedPositionVector[nextSquareForToken].getmidX();
            float midY = smallSquareSharedPositionVector[nextSquareForToken].getmidY();
            tok.setPos(Position(midX, midY));
            toklist.clear();
            toklist.push_back(tok);
            playerCurrentlyPlayingList[i].setTokenList(toklist);
            dice = static_cast<Dice>(diceValue);
            break;
        }
    }
}

void createAndInitPlayers(int num_of_players){
    playerCurrentlyPlayingList.clear();
    for(int i=0;i<num_of_players;i++){
        Player newPlayer;
        newPlayer = Player(i);
        newPlayer.setUsername(playersStringVector[i]);
        newPlayer.setIsHome(true);
        newPlayer.setColor(playerColor[i]);
        newPlayer.initializeTokenList(playerTokenColor[i]);
        newPlayer.setPlayerSpecificStartingSquare(13 * i - 1);
        playerCurrentlyPlayingList.push_back(newPlayer);
    }
}

void simulateGame() {
   
}

int getRandomNumber() {
    srand(NULL);
    int rnd = (rand() % 6) + 1;
    return rnd;
}
