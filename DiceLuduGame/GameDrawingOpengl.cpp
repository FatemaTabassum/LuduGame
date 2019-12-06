//
//  GameDrawingOpengl.cpp
//  DiceLuduGame
//
//  Created by Fatema on 12/5/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include "GameDrawingOpengl.hpp"
/********* Global Variables **********/

GLFWwindow *window;
const GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
const GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
const GLfloat halfSideLength = 200;
const GLfloat smallSquareLength = SCREEN_WIDTH / DIVIDER_CONSTANT;
const GLfloat bigSquareLength = smallSquareLength * 6;
const GLfloat numberOfBigSquare = 4;
int screenWidth, screenHeight, gameScreenWidth, gameScreenheight;
Position currentMousePos;
const float radius = 20;
int numberOfTotalPlayers = 4;
vector <Player> playerCurrentlyPlayingList;
float cursorPosX, cursorPosY;
bool firstTimeFlagSmallSharedSquare = true;
bool firstTimeFlagBigSquare = true;
bool firstTimeFlagPlayerSpecificSquare = true;
int circleInWhichSquare=0;
double timeStampInSec = 0.1;

Colors playerColor[] = {GREEN, YELLOW, CYAN, RED};
Colors playerTokenColor[] = {DARKGREEN, PURPLE, DARKGREEN, BLACK};

vector <Square> smallSquareSharedPositionVector;
vector <Square> smallSquarePlayerSpecificVector;
vector <Square> bigSquareVector;


#pragma mark functions Prototype
int initialize_window();
void render_opengl();
void drawGameBoards(int screenWidth, int screenHeight);
void setColor(Colors clr);
void addEventToTheScreen();
static void cursorPositionCallBack(GLFWwindow *window, double xPos, double yPos);
void mouseButtonCallBack( GLFWwindow *window, int button, int action, int mods);
void addBackgroundAestheticWithFrame(int screenWidth, int screenHeight);
void drawBigSquares();
void drawSmallSquares();

void saveBigSquares();
void saveAllSqueares();
void buildSmallSquaresForCase_0();
void buildSmallSquaresForCase_1();
void buildSmallSquaresForCase_2();
void buildSmallSquaresForCase_3();
void buildSmallSquaresForCase_4();
void buildSmallSquaresForCase_5();
void buildSmallSquaresForCase_6();
void buildSmallSquaresForCase_7();
void buildSmallSquaresForCase_8();
void buildSmallSquaresForCase_9();
void buildSmallSquaresForCase_10();
void buildSmallSquaresForCase_11();

void buildSmallSqrPlayer_0();
void buildSmallSqrPlayer_1();
void buildSmallSqrPlayer_2();
void buildSmallSqrPlayer_3();


void makeAndStoreBigSquare(vector <Position> &posVect);
void makeAndStoreSharedSquare(vector <Position> &posVect);
void makeAndStorePlayerSpecificSquare(vector <Position> &posVect);



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


#pragma mark Draw
void drawShape(GLfloat allRectVertices[], Colors clr, unsigned int shapeType) {
    glEnableClientState( GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, allRectVertices);
    setColor(clr);
    glDrawArrays(shapeType, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void drawCircle( GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, unsigned int playerId ) {
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
    
    int i;
    int triangleAmount = 1000;
    GLfloat twicePi = 2.0f * 3.1415;
    glEnable(GL_LINE_SMOOTH);
    
    setColor(playerTokenColor[playerId]);
    glLineWidth(5.0);
    
    glBegin(GL_LINES);
    setColor(playerTokenColor[playerId]);
    //glColor4f(1.0, 0.0, 0.0, 1.0);
    for(i = 0; i < triangleAmount; i++)
    {
        glVertex2f( x, y);
        glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
    }
    glEnd();
    
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
    setColor(playerTokenColor[(playerId+1)%4]);
    glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
    glDisableClientState(GL_VERTEX_ARRAY);
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



#pragma mark Render Opengl
void render_opengl() {
    saveAllSqueares();
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        addBackgroundAestheticWithFrame(screenWidth, screenHeight);
        drawGameBoards(screenWidth, screenHeight);
        drawTokens();
        //drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 20, 36, NONE);
        //Swap front and back buffers
        glfwSwapBuffers(window);
        //Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
}
#pragma mark Draw Game Boards
void drawGameBoards(int screenWidth, int screenHeight) {
    drawBigSquares();
    drawSmallSquares();
}

#pragma mark Event
void addEventToTheScreen() {
    glfwSetCursorPosCallback(window, cursorPositionCallBack);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetCursorEnterCallback(window, cursorEnterCallBack);
    glfwSetMouseButtonCallback(window, mouseButtonCallBack);
}

#pragma mark Callback Cursor Position
static void cursorPositionCallBack(GLFWwindow *window, double xPos, double yPos) {
    //    cout << xPos << "   " << yPos << endl;
    //    cursorPosX = xPos;
    //    cursorPosY = yPos;
    //    currentMousePos.setCoord(xPos, yPos);
    //    cout << "small Square Player specific vector sizes " << smallSquarePlayerSpecificVector.size() << endl;
    //    cout << "small Square shared vector sizes " << smallSquareSharedPositionVector.size() << endl;
    
}

#pragma mark Callback Mouse Button
void mouseButtonCallBack( GLFWwindow *window, int button, int action, int mods) {
    //    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    //        cout << "Right button Pressed " << endl;
    //    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    //        cout << "Right Button Released " << endl;
    //    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    //        cout << "Left Button Pressed " << endl;
    //    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    //        cout << "Left Button Released " << endl;
    //        //cout << currentMousePos.xPos << "  " << currentMousePos.yPos << endl;
    //    }
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
}

#pragma make Background color White
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

#pragma mark Draw Small Squares ---must change name
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


#pragma mark Draw Big Square
void drawBigSquares() {
    for (int i = 0; i < numberOfBigSquare; i++) {
        if (i == 0) {
            vector <Position> posVect;
            posVect.pb(Position(0, 0));
            posVect.pb(Position(bigSquareLength, 0));
            posVect.pb(Position(bigSquareLength, bigSquareLength));
            posVect.pb(Position(0, bigSquareLength));
            
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            }
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
        } else if( i == 1) {
            
            vector <Position> posVect;
            posVect.pb(Position(0, (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(bigSquareLength, (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(bigSquareLength, (2 * bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(0, (2 * bigSquareLength + 3 * smallSquareLength)));
            
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            }
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
        } else if( i == 2) {
            
            vector <Position> posVect;
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength)));
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            }
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
        }
        else if( i == 3) {
            
            vector <Position> posVect;
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), 0));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), 0));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), bigSquareLength));
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), bigSquareLength));
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            }
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            
        }
    }
    firstTimeFlagBigSquare = false;
}


#pragma mark Save Square
void makeAndStoreBigSquare(vector <Position> &posVect) {
    Square sq = Square();
    sq.setLeftBottomPos(posVect[0]);
    sq.setRightBottomPos(posVect[1]);
    sq.setRightUpperPos(posVect[2]);
    sq.setLeftUpperPos(posVect[3]);
    GLfloat midx = posVect[0].getxPos() + bigSquareLength/2;
    GLfloat midy = posVect[0].getyPos() + bigSquareLength/2;
    sq.setMidX(midx);
    sq.setMidY(midy);
    
#warning have to calculate or may be not
    //    float abs = fabs(posVect[0] - posVect[1]);
    //    sq.setSquareWidth(abs);
    //    sq.setSquareHeight(abs);
    bigSquareVector.push_back(sq);
}



void makeAndStoreSharedSquare(vector <Position> &posVect) {
    Square sq = Square();
    sq.setLeftBottomPos(posVect[0]);
    sq.setRightBottomPos(posVect[1]);
    sq.setRightUpperPos(posVect[2]);
    sq.setLeftUpperPos(posVect[3]);
    GLfloat midx = posVect[0].getxPos() + smallSquareLength/2;
    GLfloat midy = posVect[0].getyPos() + smallSquareLength/2;
    sq.setMidX(midx);
    sq.setMidY(midy);
    smallSquareSharedPositionVector.push_back(sq);
}


// can merge these two functions

void makeAndStorePlayerSpecificSquare(vector <Position> &posVect) {
    Square sq = Square();
    sq.setLeftBottomPos(posVect[0]);
    sq.setRightBottomPos(posVect[1]);
    sq.setRightUpperPos(posVect[2]);
    sq.setLeftUpperPos(posVect[3]);
    
    GLfloat midx = posVect[0].getxPos() + smallSquareLength/2;
    GLfloat midy = posVect[0].getyPos() + smallSquareLength/2;
    sq.setMidX(midx);
    sq.setMidY(midy);
    smallSquarePlayerSpecificVector.push_back(sq);
}


#pragma mark Initialize Opengl Window
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

#pragma mark Build Cases
void buildSmallSquaresForCase_0() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        
        posVect.clear();
    }
    //cout << " liza 0 " << endl;
}

void buildSmallSquaresForCase_1() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        
        posVect.clear();
    }
    
    //cout << " liza 1 " << endl;
}

void buildSmallSquaresForCase_2() {
    vector <GLfloat> xPosVector;
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
    if (firstTimeFlagSmallSharedSquare == true) {
        makeAndStoreSharedSquare(posVect);
    } else {
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
    }
    
    posVect.clear();
    
    //cout << " liza 2 " << endl;
}

void buildSmallSquaresForCase_3() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        posVect.clear();
    }
    
    //cout << " liza 3 " << endl;
}

void buildSmallSquaresForCase_4() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        posVect.clear();
    }
    
    //cout << " liza 4 " << endl;
}

void buildSmallSquaresForCase_5() {
    vector <GLfloat> xPosVector;
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
    if (firstTimeFlagSmallSharedSquare == true) {
        makeAndStoreSharedSquare(posVect);
    } else {
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
    }
    
    posVect.clear();
    //cout << " liza 5 " << endl;
}

void buildSmallSquaresForCase_6() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        
        posVect.clear();
    }
    
    //cout << " liza 6 " << endl;
}

void buildSmallSquaresForCase_7() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        
        posVect.clear();
    }
    
    //cout << " liza 7 " << endl;
}

void buildSmallSquaresForCase_8() {
    vector <GLfloat> xPosVector;
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
    if (firstTimeFlagSmallSharedSquare == true) {
        makeAndStoreSharedSquare(posVect);
    } else {
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
    }
    
    posVect.clear();
    //cout << " liza 8 " << endl;
}

void buildSmallSquaresForCase_9() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        
        posVect.clear();
    }
    
    //cout << " liza 9 " << endl;
}

void buildSmallSquaresForCase_10() {
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagSmallSharedSquare == true) {
            makeAndStoreSharedSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
        }
        
        posVect.clear();
    }
    
    //cout << " liza 10 " << endl;
}

void buildSmallSquaresForCase_11() {
    vector <GLfloat> xPosVector;
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
    if (firstTimeFlagSmallSharedSquare == true) {
        makeAndStoreSharedSquare(posVect);
    } else {
        renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], NONE);
    }
    
    posVect.clear();
    //cout << " liza 11 " << endl;
}


void buildSmallSqrPlayer_0() {
    
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagPlayerSpecificSquare == true && j!= 0) {
            makeAndStorePlayerSpecificSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[0]);
        }
        posVect.clear();
    }
    
    //cout << " liza  " << endl;
    //smallSquarePlayerSpecificVector
}

void buildSmallSqrPlayer_1() {
    
    vector <GLfloat> xPosVector;
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
        if (firstTimeFlagPlayerSpecificSquare == true && j!= 0) {
            makeAndStorePlayerSpecificSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[1]);
        }
        posVect.clear();
    }
}

void buildSmallSqrPlayer_2() {
    vector <GLfloat> xPosVector;
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
        
        if (firstTimeFlagPlayerSpecificSquare == true && j!= 0) {
            makeAndStorePlayerSpecificSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[2]);
        }
        posVect.clear();
    }
}

void buildSmallSqrPlayer_3() {
    vector <GLfloat> xPosVector;
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
        
        if (firstTimeFlagPlayerSpecificSquare == true && j!= 0) {
            makeAndStorePlayerSpecificSquare(posVect);
        } else {
            renderSmallSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[3]);
        }
        posVect.clear();
    }
}

void saveBigSquares() {
    for (int i = 0; i < numberOfBigSquare; i++) {
        if (i == 0) {
            vector <Position> posVect;
            posVect.pb(Position(0, 0));
            posVect.pb(Position(bigSquareLength, 0));
            posVect.pb(Position(bigSquareLength, bigSquareLength));
            posVect.pb(Position(0, bigSquareLength));
            
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            } else {
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            }
            
        } else if( i == 1) {
            
            vector <Position> posVect;
            posVect.pb(Position(0, (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(bigSquareLength, (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(bigSquareLength, (2 * bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position(0, (2 * bigSquareLength + 3 * smallSquareLength)));
            
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            } else {
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            }
            
        } else if( i == 2) {
            
            vector <Position> posVect;
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), (bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength)));
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), (2 * bigSquareLength + 3 * smallSquareLength)));
            
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            } else {
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            }
            
        }
        else if( i == 3) {
            
            vector <Position> posVect;
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), 0));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), 0));
            posVect.pb(Position((2 * bigSquareLength + 3 * smallSquareLength), bigSquareLength));
            posVect.pb(Position((bigSquareLength + 3 * smallSquareLength), bigSquareLength));
            if (firstTimeFlagBigSquare == true) {
                makeAndStoreBigSquare(posVect);
            } else {
            renderBigSquare(posVect[0], posVect[1], posVect[2], posVect[3], playerColor[i]);
            }
            
        }
    }
    firstTimeFlagBigSquare = false;
}

void saveAllSqueares() {
    
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
    
    firstTimeFlagSmallSharedSquare = false;
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
    firstTimeFlagPlayerSpecificSquare = false;
    saveBigSquares();
}

void drawTokens() {
    for(int i=0;i<numberOfTotalPlayers;i++){
        Player pl = playerCurrentlyPlayingList[i];
        vector<Token> tokens = pl.getTokenList();
        for(int j=0;j<tokens.size();j++){
            Position pos = tokens[j].getPos();
            drawCircle(pos.getxPos(), pos.getyPos(), 0, 20, 36,pl.getPlayer_id());
        }
    }
}

void printNumOfSquares(){
    cout << " smallSquareSharedPositionVector.size()  " << smallSquareSharedPositionVector.size() << endl;
    cout << " smallSquarePlayerSpecificVector.size()  " << smallSquarePlayerSpecificVector.size() << endl;
    cout << " bigSquareVector.size()  " << bigSquareVector.size() << endl;
}

void animateToken(){
    double time = glfwGetTime();
    if((timeStampInSec+0.1) < time){
        timeStampInSec = time;
        circleInWhichSquare++;
    }
    circleInWhichSquare = circleInWhichSquare%smallSquareSharedPositionVector.size();
    drawCircle(smallSquareSharedPositionVector[circleInWhichSquare].getmidX(),
               smallSquareSharedPositionVector[circleInWhichSquare].getmidY(), 0, 20, 36, NONE);
}

