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

#pragma mark TEST
int numberOfOnlinePlayers = 0;

#pragma mark Functions Prototypes

int getRandomNumber();

void createAndInitPlayers(int num_of_players){
    playerCurrentlyPlayingList.clear();
    for(int i=0;i<num_of_players;i++){
        Player newPlayer;
        newPlayer = Player(i);
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
        if (i == currentPlayerId) {
            rnd = getRandomNumber();
            rnd = 6;
            Player player = playerCurrentlyPlayingList[i];
            vector<Token> tokList =  player.getTokenList();
            Token tok = tokList[0]; // since we have given only one token playing right now.
            
            if (rnd == 6 && player.getHomeway() == false) {
                int nextSquareForToken = 13 * i + 1; // first square to start for player is defined by the equeation 13 * n + 1
                
                float midX = smallSquareSharedPositionVector[nextSquareForToken].getmidX();
                float midY = smallSquareSharedPositionVector[nextSquareForToken].getmidY();
                tok.setPos(Position(midX, midY));
                tokList.clear();
                tokList.push_back(tok);
                playerCurrentlyPlayingList[i].setTokenList(tokList);
            }
            currentPlayerId++;
        }
    }
}

int getRandomNumber() {
    srand(NULL);
    int rnd = (rand() % 6) + 1;
    return rnd;
}
