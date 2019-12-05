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
#include "GameHelperObjects.h"

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

#define TOTAL_TOKEN 4
#define pb(x) push_back(x)

#endif /* GameDrawingOpengl_hpp */

//extern GLFWwindow *window;
//extern const GLfloat halfScreenWidth ;
//extern const GLfloat halfScreenHeight ;
//extern const GLfloat halfSideLength ;
//extern const GLfloat smallSquareLength ;
//extern const GLfloat bigSquareLength ;
//extern const GLfloat numberOfBigSquare ;
//extern int screenWidth, screenHeight, gameScreenWidth, gameScreenheight;
//extern Position currentMousePos;
//extern const int numberOfTotalPlayers ;
//extern const float radius ;
//extern vector <Player> playerCurrentlyPlayingList;
//extern float cursorPosX, cursorPosY;
//
//extern Colors playerColor[] = {GREEN, YELLOW, CYAN, RED};
//extern Colors playerTokenColor[] = {WHITE, PURPLE, DARKGREEN, BLACK};
//
//extern const int totalTok;
//
//extern vector <Square> smallSquareSharedPositionVector;
//extern vector <Square> smallSquarePlayerSpecificVector;
//extern vector <Square> bigSquareVector;
int initialize_window();
void addEventToTheScreen();



/************* Functions **********/
void render_opengl();


