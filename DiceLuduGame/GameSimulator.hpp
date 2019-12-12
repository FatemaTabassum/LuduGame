//
//  GameSimulator.hpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#ifndef GameSimulator_hpp
#define GameSimulator_hpp

#include "GameDrawingOpengl.hpp"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>

extern int currentPlayerId;

// Client information from servers
extern int numberOfTotalPlayers;
extern string currentPlayerUsername;
extern vector <Player> playersVector;
extern vector <string> playersStringVector;
extern bool mouseClickAvailable;
extern string myUsername;

void createAndInitPlayers(int num_of_players);
//void startPlayingGame(int numberOfOnlinePlayers, string username);
void simulateGame();
void initializeConstantsValues();
#endif /* GameSimulator_hpp */
