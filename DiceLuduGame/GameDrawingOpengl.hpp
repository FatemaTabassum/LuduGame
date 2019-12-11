//
//  GameDrawingOpengl.hpp
//  DiceLuduGame
//
//  Created by Fatema on 12/5/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#ifndef OpengLGameDrawing_hpp
#define OpengLGameDrawing_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>
#include <time.h>
#include "GameHelperObjects.h"
#include "GameSimulator.hpp"
#include <SOIL.h>


using namespace std;


/************* Macros *************/

//#define TOTAL_SCREEN_WIDTH 650
#define SCREEN_WIDTH 570 // must be a divisor of 15
#define SCREEN_HEIGHT SCREEN_WIDTH // height is equal to width
#define DIVIDER_CONSTANT 15 // 35 * 6 // a = 6b, 2a + 3b = width, 12b + 3b = width, 15b = width, width = height
#define LUDU_BOARD_LENGTH 400
#define COLOR_LINE_WIDTH 5
#define TOTAL_SMALL_SQUARE_SHARED 53
#define TOTAL_SMALL_SQUARE ( 53 + 20 )

#define TOTAL_TOKEN 1
#define pb(x) push_back(x)

#endif
extern Colors playerColor[];
extern Dice dice;
extern Colors playerTokenColor[];
extern int numberOfTotalPlayers;
extern vector <Player> playerCurrentlyPlayingList;
extern const GLfloat smallSquareLength;
extern const GLfloat bigSquareLength;

extern vector <Square> smallSquareSharedPositionVector;
extern vector <Square> smallSquarePlayerSpecificVector;
extern vector <Square> bigSquareVector;
extern Square diceSquare;


int initialize_window();
void addEventToTheScreen();
void saveAllSqueares();
void printNumOfSquares();
void drawTokens();

/************* Functions **********/
void render_opengl();


