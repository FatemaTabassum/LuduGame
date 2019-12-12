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
//    for (int i = 0; i < playerCurrentlyPlayingList.size(); i++) {
//        for (int j = 0; j < playersStringVector.size(); ) {
//            if () {
//
//            }
//        }
//    }
    for (int i = 0; i < playerCurrentlyPlayingList.size(); i++) {
        if ((previousPlayer.compare(playerCurrentlyPlayingList[i].getUsername())) == 0) {
            Player plyr = playerCurrentlyPlayingList[i];
            vector<Token>toklist = plyr.getTokenList();
            Token tok = toklist[0];
            int nextSquareForToken;
            if (plyr.getIsHome() == true) {
                plyr.setIsHome(false);
                nextSquareForToken = 13 * i + 1;
            } else {
                nextSquareForToken = tok.getSquareNumber() + diceValue;
            }
            tok.setSquareNumber(nextSquareForToken);
            float midX = smallSquareSharedPositionVector[nextSquareForToken].getmidX();
            float midY = smallSquareSharedPositionVector[nextSquareForToken].getmidY();
            tok.setPos(Position(midX, midY));
            toklist.clear();
            toklist.push_back(tok);
            playerCurrentlyPlayingList[i].setTokenList(toklist);
            break;
            
            // since we have given only one token playing right now.
            //
            //            if (rnd == 6 && player.getIsHome() == true) {
            //                int nextSquareForToken = 13 * i + 1; // first square to start for player is defined by the equeation 13 * n + 1
            //
            //                float midX = smallSquareSharedPositionVector[nextSquareForToken].getmidX();
            //                float midY = smallSquareSharedPositionVector[nextSquareForToken].getmidY();
            //                tok.setPos(Position(midX, midY));
            //                tokList.clear();
            //                tokList.push_back(tok);
            //                playerCurrentlyPlayingList[i].setTokenList(tokList);
            //            }
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
        playerCurrentlyPlayingList.push_back(newPlayer);
    }
}

//void startPlayingGame(int numberOfOnlinePlayers, string username) {
//    createAndInitPlayers(numberOfOnlinePlayers);
//    //render_opengl();
//}

void simulateGame() {
    int rnd;
    for (int i = 0; i < playerCurrentlyPlayingList.size(); i++) {
        Player player = playerCurrentlyPlayingList[i];
//        if (player.getUsername().compare(currentPlayerUsername) == 0 ) {
//        }
//        if (i == currentPlayerId) {
//            rnd = getRandomNumber();
//            rnd = 6;
//            Player player = playerCurrentlyPlayingList[i];
//            vector<Token> tokList =  player.getTokenList();
//            Token tok = tokList[0]; // since we have given only one token playing right now.
//
//            if (rnd == 6 && player.getIsHome() == true) {
//                int nextSquareForToken = 13 * i + 1; // first square to start for player is defined by the equeation 13 * n + 1
//
//                float midX = smallSquareSharedPositionVector[nextSquareForToken].getmidX();
//                float midY = smallSquareSharedPositionVector[nextSquareForToken].getmidY();
//                tok.setPos(Position(midX, midY));
//                tokList.clear();
//                tokList.push_back(tok);
//                playerCurrentlyPlayingList[i].setTokenList(tokList);
//            }
//            currentPlayerId++;
//        }
    }
}

int getRandomNumber() {
    srand(NULL);
    int rnd = (rand() % 6) + 1;
    return rnd;
}
