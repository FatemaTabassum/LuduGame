//
//  GameSimulator.cpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include "GameSimulator.hpp"
#include "GameDrawingOpengl.hpp"
#include<stdio.h>
#include<iostream>
using namespace std;

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
