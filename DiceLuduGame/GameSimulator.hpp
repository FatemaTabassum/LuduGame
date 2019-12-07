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

extern int currentPlayerId;

void createAndInitPlayers(int num_of_players);
void simulateGame();
#endif /* GameSimulator_hpp */
