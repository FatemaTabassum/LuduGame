//
//  main.cpp
//  DiceLuduGame
//
//  Created by Fatema on 10/24/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#pragma mark INCLUDES
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include "GameHelperObjects.cpp"

using namespace std;

/************* Macros *************/

#define SCREEN_WIDTH 570 // must be a divisor of 15
#define SCREEN_HEIGHT SCREEN_WIDTH // height is equal to width
#define DIVIDER_CONSTANT 15 // 35 * 6 // a = 6b, 2a + 3b = width, 12b + 3b = width, 15b = width, width = height
#define LUDU_BOARD_LENGTH 400
#define COLOR_LINE_WIDTH 5
#define TOTAL_SMALL_SQUARE_SHARED 53
#define TOTAL_SMALL_SQUARE ( 53 + 20 )

#define pb(x) push_back(x)

#pragma mark Structures
/******** Structures ************/

struct MousePosition {
    double xPos;
    double yPos;
};


#pragma mark Global Variables
/********* Global Variables **********/

GLFWwindow *window;
const GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
const GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
const GLfloat halfSideLength = 200;
const GLfloat smallSquareLength = SCREEN_WIDTH / DIVIDER_CONSTANT;
const GLfloat bigSquareLength = smallSquareLength * 6;
const GLfloat numberOfBigSquare = 4;
int screenWidth, screenHeight;
Position currentMousePos;
int numberOfTotalPlayers = 4;
vector <Player> playerCurrentlyPlayingList;

Colors playerColor[] = {GREEN, YELLOW, CYAN, RED};

vector <Square> smallSquareSharedPositionVector;
vector <Square> smallSquarePlayerSpecificVector;
vector <Square> bigSquareVector;


/*********** Function Prototype **********/
#pragma mark Functions Prototype
void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides );
int initialize_window();
void render_opengl();
void setColor(Colors clr);
static void cursorPositionCallBack( GLFWwindow *window, double xPos, double yPos);
void cursorEnterCallBack( GLFWwindow *window, int entered );
void mouseButtonCallBack( GLFWwindow *window, int button, int action, int mods);
void addEventToTheScreen();
void addBackgroundAestheticWithFrame( int screenWidth,  int screenHeight);
void drawGameBoards(int screenWidth, int screenHeight);
void drawSmallSquares();
void drawBigSquares();

#pragma mark Main
int main(void) {
    if (initialize_window() == 1) {
        return -1;
    }
    addEventToTheScreen();
    render_opengl();
    return 0;
}

#pragma mark Render Opengl
void render_opengl() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        addBackgroundAestheticWithFrame(screenWidth, screenHeight);
        //Render opengl here
        drawGameBoards(screenWidth, screenHeight);
        drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 20, 36);
        
        
        //Swap front and back buffers
        glfwSwapBuffers(window);
        //Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
}


#pragma mark SetColor
void setColor(Colors clr) {
    glLineWidth(COLOR_LINE_WIDTH);
    switch (clr) {
        case RED:
            glColor3f (1.0, 0.0, 0.0);  /* the current RGB color is RED: */
            break;
        case GREEN:
            glColor3f (0.0, 1.0, 0.0);  /* the current RGB color is GREEN: */
            break;
        case BLUE:
            glColor3f (0.0, 0.0, 1.0);  /* the current RGB color is BLUE: */
            break;
        case YELLOW:
            glColor3f (1.0, 1.0, 0.0);  /* the current RGB color is YELLOW: */
            break;
        case WHITE:
            glColor3f (1.0, 1.0, 1.0);  /* the current RGB color is WHITE: */
            break;
        case PURPLE:
            glColor3f (1.0, 0.0, 1.0 );  /* the current RGB color is PURPLE: */
            break;
        case CYAN:
            glColor3f (0.0, 1.0, 1.0 );  /* the current RGB color is CYAN: */
            break;
        case DARKGREEN:
            glColor3f (0.0, 0.5, 0.0 );  /* the current RGB color is DARKGREEN: */
            break;
        case BLACK:
            glColor3f (0.0, 0.0, 0.0 );  /* the current RGB color is BLACK: */
            break;
        default:
            break;
    }

}

#pragma mark Event
void addEventToTheScreen() {
    glfwSetCursorPosCallback(window, cursorPositionCallBack);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetCursorEnterCallback(window, cursorEnterCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallBack);
}
static void cursorPositionCallBack(GLFWwindow *window, double xPos, double yPos) {
    cout << xPos << "   " << yPos << endl;
    currentMousePos.setCoord(xPos, yPos);
}

//void cursorEnterCallBack( GLFWwindow *window, int entered ) {
////    if (entered) {
////        cout << "Entered Window" << endl;
////    } else {
////        cout << "Left Window" << endl;
////    }
//}

void mouseButtonCallBack( GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        cout << "Right button Pressed " << endl;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        cout << "Right Button Released " << endl;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        cout << "Left Button Pressed " << endl;
        
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        cout << "Left Button Released " << endl;
        //cout << currentMousePos.xPos << "  " << currentMousePos.yPos << endl;
    }
}

#pragma mark Draw
void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides ) {
    GLint numberOfVertices = numberOfSides + 1;
    GLfloat doublePi = 2.0f * M_PI;
    vector<GLfloat>circleVerticesX;
    vector<GLfloat>circleVerticesY;
    vector<GLfloat>circleVerticesZ;
    
    for (int i = 0; i < numberOfVertices; i++) {
        circleVerticesX.pb(x + (radius * cos(i * doublePi / numberOfSides)));
        circleVerticesY.pb(y + (radius * sin(i * doublePi / numberOfSides)));
        circleVerticesZ.pb(z);
    }
    GLfloat allCircleVertices[numberOfVertices * 3];
    for (int i = 0; i < numberOfVertices; i++) {
        allCircleVertices[i * 3] = circleVerticesX[i];
        allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
        allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
    }
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    setColor(RED);
    glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    
}



void addBackgroundAestheticWithFrame(int screenWidth, int screenHeight) {
    GLfloat x = (GLfloat)screenWidth;
    GLfloat y = (GLfloat)screenHeight;
    GLfloat allRectVertices[] = {
        0, 0, 0,
        x, 0, 0,
        x, y, 0,
        0, y, 0
    };
    glEnableClientState( GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allRectVertices);
    setColor(WHITE);
    glDrawArrays(GL_POLYGON, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawShape(GLfloat allRectVertices[], Colors clr, unsigned int shapeType) {
    glEnableClientState( GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allRectVertices);
    setColor(clr);
    glDrawArrays(shapeType, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void saveBigSquareVertex(GLfloat x, GLfloat y, GLfloat z, int ind) {
    Position pos;
    pos.setCoord(x, y);
    //bigSquarePositionV[ind].push_back(s); have to save coordinate of bigsquarePosition later
    return;
}

#pragma mark CreatePlayersAndTokens
void createPlayersAndTokens() {
    for (int i = 0; i < numberOfTotalPlayers; i++) {
        int player_id =  i;
        Player player = Player(player_id);
        player.initializeTokenList();
        playerCurrentlyPlayingList.push_back(player);
    }
    //cout << "liza" << endl;
}

void drawTokensForEachPlayer() {
    
    //drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 20, 36);
    
    int rectWidth = bigSquareLength - 20;
    int circleWidth = (rectWidth/2) - 20;
    
}

void drawGameBoards(int screenWidth, int screenHeight) {
    drawBigSquares();
    drawSmallSquares();
    createPlayersAndTokens();
    drawTokensForEachPlayer();
}

#pragma mark Display Small Square
void renderSmallSquare( Position leftBottom, Position rightBottom, Position rightUpper, Position leftUpper, Colors clr) {
    GLfloat allRectVertices[] = {
        leftBottom.getxPos(), leftBottom.getyPos(), 0,
        rightBottom.getxPos(), rightBottom.getyPos(), 0,
        rightUpper.getxPos(), rightUpper.getyPos(), 0,
        leftUpper.getxPos(), leftUpper.getyPos(), 0
    };
    if (clr == NONE) {
        drawShape(allRectVertices, BLUE, GL_LINE_LOOP);
    } else {
        drawShape(allRectVertices, clr, GL_LINE_LOOP);
    }
}

#pragma mark Display Big Square
void renderBigSquare( Position leftBottom, Position rightBottom, Position rightUpper, Position leftUpper, Colors clr) {
    GLfloat allRectVertices[] = {
        leftBottom.getxPos(), leftBottom.getyPos(), 0,
        rightBottom.getxPos(), rightBottom.getyPos(), 0,
        rightUpper.getxPos(), rightUpper.getyPos(), 0,
        leftUpper.getxPos(), leftUpper.getyPos(), 0
    };
    drawShape(allRectVertices, clr, GL_POLYGON);
}


#pragma mark Save Big Square
void makeAndStoreBigSquare(vector <Position> &posVect) {
    Square sq = Square();
    sq.setLeftBottomPos(posVect[0]);
    sq.setRightBottomPos(posVect[1]);
    sq.setRightUpperPos(posVect[2]);
    sq.setLeftUpperPos(posVect[3]);
#warning have to calculate
//    float abs = fabs(posVect[0] - posVect[1]);
//    sq.setSquareWidth(abs);
//    sq.setSquareHeight(abs);
    bigSquareVector.push_back(sq);
}


#pragma mark Save Small Square
void makeAndStoreShareSquare(vector <Position> &posVect) {
    Square sq = Square();
    sq.setLeftBottomPos(posVect[0]);
    sq.setRightBottomPos(posVect[1]);
    sq.setRightUpperPos(posVect[2]);
    sq.setLeftUpperPos(posVect[3]);
    smallSquareSharedPositionVector.push_back(sq);
}

// can merge these two functions

void makeAndStoreShareSquarePlyr(vector <Position> &posVect) {
    Square sq = Square();
    sq.setLeftBottomPos(posVect[0]);
    sq.setRightBottomPos(posVect[1]);
    sq.setRightUpperPos(posVect[2]);
    sq.setLeftUpperPos(posVect[3]);
    smallSquarePlayerSpecificVector.push_back(sq);
}

#pragma mark Build Cases

void buildSmallSquaresForCase_0() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos =  bigSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = 0;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position(xPosVector[k], startingYPos + j * smallSquareLength );
            } else if (k == 1) {
                pos = Position(xPosVector[k], startingYPos + j * smallSquareLength );
            } else if ( k == 2) {
                pos = Position(xPosVector[k], startingYPos + (j+1) * smallSquareLength );
            } else if (k == 3) {
                pos = Position(xPosVector[k], startingYPos + (j+1) * smallSquareLength );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_1() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingYPos = bigSquareLength;
    startingYPos2 = startingYPos + smallSquareLength;
    startingXPos = bigSquareLength;
    
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos2);
    yPosVector.pb(startingYPos2);

    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position( startingXPos - (j+1) * smallSquareLength, yPosVector[k] );
            } else if (k == 1) {
                pos = Position( startingXPos - j * smallSquareLength, yPosVector[k] );
            } else if ( k == 2) {
                pos = Position( startingXPos - j * smallSquareLength, yPosVector[k] );
            } else if (k == 3) {
                pos = Position( startingXPos - (j+1) * smallSquareLength, yPosVector[k] );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_2() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos = 0;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = bigSquareLength + smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int k = 0; k < 4; k++) {
        Position pos;
        if (k == 0) {
            pos = Position(xPosVector[k], startingYPos );
        } else if (k == 1) {
            pos = Position(xPosVector[k], startingYPos );
        } else if ( k == 2) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        } else if (k == 3) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        }
        posVect.pb(pos);
    }
    makeAndStoreShareSquare(posVect);
    renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
}

void buildSmallSquaresForCase_3() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingYPos = bigSquareLength + 2 * smallSquareLength;
    startingYPos2 = startingYPos + smallSquareLength;
    startingXPos = 0;
    
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos2);
    yPosVector.pb(startingYPos2);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position( startingXPos + j * smallSquareLength, yPosVector[k] );
            } else if (k == 1) {
                pos = Position( startingXPos + (j+1) * smallSquareLength, yPosVector[k] );
            } else if ( k == 2) {
                pos = Position( startingXPos + (j+1) * smallSquareLength, yPosVector[k] );
            } else if (k == 3) {
                pos = Position( startingXPos + j * smallSquareLength, yPosVector[k] );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_4() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos =  bigSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = bigSquareLength + 3 * smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position(xPosVector[k], startingYPos + j * smallSquareLength );
            } else if (k == 1) {
                pos = Position(xPosVector[k], startingYPos + j * smallSquareLength );
            } else if ( k == 2) {
                pos = Position(xPosVector[k], startingYPos + (j+1) * smallSquareLength );
            } else if (k == 3) {
                pos = Position(xPosVector[k], startingYPos + (j+1) * smallSquareLength );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_5() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos = bigSquareLength + smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos =  bigSquareLength + 8 *  smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int k = 0; k < 4; k++) {
        Position pos;
        if (k == 0) {
            pos = Position(xPosVector[k], startingYPos );
        } else if (k == 1) {
            pos = Position(xPosVector[k], startingYPos );
        } else if ( k == 2) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        } else if (k == 3) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        }
        posVect.pb(pos);
    }
    makeAndStoreShareSquare(posVect);
    renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
}

void buildSmallSquaresForCase_6() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos =  bigSquareLength + 2 * smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = bigSquareLength + 8 *  smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position(xPosVector[k], startingYPos - j * smallSquareLength );
            } else if (k == 1) {
                pos = Position(xPosVector[k], startingYPos - j * smallSquareLength);
            } else if ( k == 2) {
                pos = Position(xPosVector[k], startingYPos -  (j-1) * smallSquareLength );
            } else if (k == 3) {
                pos = Position(xPosVector[k], startingYPos -  (j-1) * smallSquareLength );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_7() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingYPos = bigSquareLength + 2 * smallSquareLength;
    startingYPos2 = startingYPos + smallSquareLength;
    startingXPos = bigSquareLength + 3 * smallSquareLength;
    
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos2);
    yPosVector.pb(startingYPos2);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position( startingXPos + j * smallSquareLength, yPosVector[k] );
            } else if (k == 1) {
                pos = Position( startingXPos + (j+1) * smallSquareLength, yPosVector[k] );
            } else if ( k == 2) {
                pos = Position( startingXPos + (j+1) * smallSquareLength, yPosVector[k] );
            } else if (k == 3) {
                pos = Position( startingXPos + j * smallSquareLength, yPosVector[k] );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_8() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos = bigSquareLength + 8 * smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = bigSquareLength + smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int k = 0; k < 4; k++) {
        Position pos;
        if (k == 0) {
            pos = Position(xPosVector[k], startingYPos );
        } else if (k == 1) {
            pos = Position(xPosVector[k], startingYPos );
        } else if ( k == 2) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        } else if (k == 3) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        }
        posVect.pb(pos);
    }
    makeAndStoreShareSquare(posVect);
    renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
}

void buildSmallSquaresForCase_9() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingYPos = bigSquareLength;
    startingYPos2 = startingYPos + smallSquareLength;
    startingXPos = bigSquareLength + 8 * smallSquareLength;
    
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos2);
    yPosVector.pb(startingYPos2);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position( startingXPos - j * smallSquareLength, yPosVector[k] );
            } else if (k == 1) {
                pos = Position( startingXPos - (j - 1) * smallSquareLength, yPosVector[k] );
            } else if ( k == 2) {
                pos = Position( startingXPos - (j - 1) * smallSquareLength, yPosVector[k] );
            } else if (k == 3) {
                pos = Position( startingXPos - j * smallSquareLength, yPosVector[k] );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_10() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos =  bigSquareLength + 2 * smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = bigSquareLength - smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position(xPosVector[k], startingYPos - j * smallSquareLength );
            } else if (k == 1) {
                pos = Position(xPosVector[k], startingYPos - j * smallSquareLength );
            } else if ( k == 2) {
                pos = Position(xPosVector[k], startingYPos - (j-1) * smallSquareLength );
            } else if (k == 3) {
                pos = Position(xPosVector[k], startingYPos - (j-1) * smallSquareLength );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        posVect.clear();
    }
}

void buildSmallSquaresForCase_11() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos = bigSquareLength + smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = 0;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int k = 0; k < 4; k++) {
        Position pos;
        if (k == 0) {
            pos = Position(xPosVector[k], startingYPos );
        } else if (k == 1) {
            pos = Position(xPosVector[k], startingYPos );
        } else if ( k == 2) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        } else if (k == 3) {
            pos = Position(xPosVector[k], startingYPos + smallSquareLength );
        }
        posVect.pb(pos);
    }
    makeAndStoreShareSquare(posVect);
    renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
}


void buildSmallSqrPlayer_0() {
   
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos =  bigSquareLength + smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = 0;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position(xPosVector[k], startingYPos + j * smallSquareLength );
            } else if (k == 1) {
                pos = Position(xPosVector[k], startingYPos + j * smallSquareLength );
            } else if ( k == 2) {
                pos = Position(xPosVector[k], startingYPos + (j+1) * smallSquareLength );
            } else if (k == 3) {
                pos = Position(xPosVector[k], startingYPos + (j+1) * smallSquareLength );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquarePlyr(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[0]);
        posVect.clear();
    }
    //smallSquarePlayerSpecificVector
}

void buildSmallSqrPlayer_1() {
    
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingYPos = bigSquareLength + smallSquareLength;
    startingYPos2 = startingYPos + smallSquareLength;
    startingXPos = 0;
    
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos2);
    yPosVector.pb(startingYPos2);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position( startingXPos + j * smallSquareLength, yPosVector[k] );
            } else if (k == 1) {
                pos = Position( startingXPos + (j+1) * smallSquareLength, yPosVector[k] );
            } else if ( k == 2) {
                pos = Position( startingXPos + (j+1) * smallSquareLength, yPosVector[k] );
            } else if (k == 3) {
                pos = Position( startingXPos + j * smallSquareLength, yPosVector[k] );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[1]);
        posVect.clear();
    }
}

void buildSmallSqrPlayer_2() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingXPos =  bigSquareLength + smallSquareLength;
    startingXPos2 = startingXPos + smallSquareLength;
    startingYPos = bigSquareLength + 8 *  smallSquareLength;
    
    xPosVector.pb(startingXPos);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos2);
    xPosVector.pb(startingXPos);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position(xPosVector[k], startingYPos - j * smallSquareLength );
            } else if (k == 1) {
                pos = Position(xPosVector[k], startingYPos - j * smallSquareLength);
            } else if ( k == 2) {
                pos = Position(xPosVector[k], startingYPos -  (j-1) * smallSquareLength );
            } else if (k == 3) {
                pos = Position(xPosVector[k], startingYPos -  (j-1) * smallSquareLength );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[2]);
        posVect.clear();
    }
}

void buildSmallSqrPlayer_3() {
    vector <GLfloat> xPosVector;
    vector <GLfloat> yPosVector;
    vector <Position> posVect;
    GLfloat startingYPos, startingYPos2, startingXPos, startingXPos2;
    
    startingYPos = bigSquareLength + smallSquareLength;
    startingYPos2 = startingYPos + smallSquareLength;
    startingXPos = bigSquareLength + 8 * smallSquareLength;
    
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos);
    yPosVector.pb(startingYPos2);
    yPosVector.pb(startingYPos2);
    
    for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 4; k++) {
            Position pos;
            if (k == 0) {
                pos = Position( startingXPos - j * smallSquareLength, yPosVector[k] );
            } else if (k == 1) {
                pos = Position( startingXPos - (j - 1) * smallSquareLength, yPosVector[k] );
            } else if ( k == 2) {
                pos = Position( startingXPos - (j - 1) * smallSquareLength, yPosVector[k] );
            } else if (k == 3) {
                pos = Position( startingXPos - j * smallSquareLength, yPosVector[k] );
            }
            posVect.pb(pos);
        }
        makeAndStoreShareSquare(posVect);
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[3]);
        posVect.clear();
    }
}

void drawSmallSquares() {
    
    for (int i = 0; i < 12 ; i++) {
        
        switch (i) {
            case 0: {
                buildSmallSquaresForCase_0();
                break;
            }
            case 1: {
                buildSmallSquaresForCase_1();
                break;
            }
            case 2: {
                buildSmallSquaresForCase_2();
                break;
            }
            case 3: {
                buildSmallSquaresForCase_3();
                break;
            }
            case 4: {
                buildSmallSquaresForCase_4();
                break;
            }
            case 5: {
                buildSmallSquaresForCase_5();
                break;
            }
            case 6: {
                buildSmallSquaresForCase_6();
                break;
            }
            case 7: {
                buildSmallSquaresForCase_7();
                break;
            }
            case 8: {
                buildSmallSquaresForCase_8();
                break;
            }
            case 9: {
                buildSmallSquaresForCase_9();
                break;
            }
            case 10: {
                buildSmallSquaresForCase_10();
                break;
            }
            case 11: {
                buildSmallSquaresForCase_11();
                break;
            }
                
            default:
                break;
        }
    }
    for (int i = 0; i < 4; i++) {
        
        switch (i) {
            case 0:
                buildSmallSqrPlayer_0();
                break;
            case 1:
                buildSmallSqrPlayer_1();
                break;
            case 2:
                buildSmallSqrPlayer_2();
                break;
            case 3:
                buildSmallSqrPlayer_3();
                break;
            default:
                break;
        }
    }
}

void drawBigSquares() {
    for (int i = 0; i < numberOfBigSquare; i++) {
        if (i == 0) {
//            saveBigSquareVertex(0, 0, 0, i);
//            saveBigSquareVertex(bigSquareLength, 0, 0, i);
//            saveBigSquareVertex(bigSquareLength, bigSquareLength, 0, i);
//            saveBigSquareVertex(0, bigSquareLength, 0, i);
            
            
            vector <Position> posVect;
            posVect.pb(Position(0, 0));
            posVect.pb(Position(bigSquareLength, 0));
            posVect.pb(Position(bigSquareLength, bigSquareLength));
            posVect.pb(Position(0, bigSquareLength));
            makeAndStoreBigSquare(posVect);
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
//            GLfloat allRectVertices[] = {
//                0, 0, 0,
//                bigSquareLength, 0, 0,
//                bigSquareLength, bigSquareLength, 0,
//                0, bigSquareLength, 0
//            };
            //drawShape(allRectVertices, GREEN, GL_POLYGON);
        } else if( i == 1) {
            
//            saveBigSquareVertex(0, (bigSquareLength + 3 * smallSquareLength), 0, i);
//            saveBigSquareVertex(bigSquareLength, (bigSquareLength + 3 * smallSquareLength), 0, i);
//            saveBigSquareVertex(bigSquareLength, (2 * bigSquareLength + 3 * smallSquareLength), 0, i);
//            saveBigSquareVertex(0, (2 * bigSquareLength + 3 * smallSquareLength), 0, i);
            
            
            
            vector <Position> posVect;
            posVect.pb(Position(0, (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(bigSquareLength, (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(bigSquareLength, (2 * bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(0, (2 * bigSquareLength + 3 * smallSquareLength)));
            makeAndStoreBigSquare(posVect);
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
            
//            GLfloat allRectVertices[] = {
//                0, (bigSquareLength + 3 * smallSquareLength), 0,
//                bigSquareLength, (bigSquareLength + 3 * smallSquareLength), 0,
//                bigSquareLength, (2 * bigSquareLength + 3 * smallSquareLength), 0,
//                0, (2 * bigSquareLength + 3 * smallSquareLength), 0,
//            };
//            drawShape(allRectVertices, YELLOW, GL_POLYGON);
        } else if( i == 2) {
            
//            saveBigSquareVertex((bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength), 0, i);
//            saveBigSquareVertex((2 * bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength), 0, i);
//            saveBigSquareVertex((2 * bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength), 0, i);
//            saveBigSquareVertex((bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength), 0, i);
//
//
            
            vector <Position> posVect;
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength)));
            makeAndStoreBigSquare(posVect);
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
            
            
//
//            GLfloat allRectVertices[] = {
//                (bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength), 0,
//                (2 * bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength), 0,
//                (2 * bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength), 0,
//                (bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength), 0,
//            };
//            drawShape(allRectVertices, CYAN, GL_POLYGON);
        }
        else if( i == 3) {
            
//            saveBigSquareVertex((bigSquareLength + 3 * smallSquareLength), 0, 0, i);
//            saveBigSquareVertex((2 * bigSquareLength + 3 * smallSquareLength), 0, 0, i);
//            saveBigSquareVertex((2 * bigSquareLength + 3 * smallSquareLength), bigSquareLength, 0, i);
//            saveBigSquareVertex((bigSquareLength + 3 * smallSquareLength), bigSquareLength, 0, i);
//            
//            
//            
            
            
            vector <Position> posVect;
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), 0));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), 0));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), bigSquareLength));
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), bigSquareLength));
            makeAndStoreBigSquare(posVect);
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
            
            
            
            
//            GLfloat allRectVertices[] = {
//                (bigSquareLength + 3 * smallSquareLength), 0, 0,
//                (2 * bigSquareLength + 3 * smallSquareLength), 0, 0,
//                (2 * bigSquareLength + 3 * smallSquareLength), bigSquareLength, 0,
//                (bigSquareLength + 3 * smallSquareLength), bigSquareLength, 0,
//
//            };
//            drawShape(allRectVertices, RED, GL_POLYGON);
        }
    }
}


#pragma mark Initialize
int initialize_window() {
    if(!glfwInit()) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DICE GAME", NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
        glfwTerminate();
        return -1;
    }
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    //make the windows context current
    glfwMakeContextCurrent(window);
    
    /* From new tutorial */
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    
    glViewport(0.0f, 0.0f, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    return 0;
}

