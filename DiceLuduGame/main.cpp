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


#pragma mark DEFINE
#define SCREEN_WIDTH 525 // must be a divisor of 15
#define SCREEN_HEIGHT 525 // height is equal to width
#define SMALL_SQUARE 35 // 525/15 = 35
#define BIG_SQUARE 210 // 35 * 6 // a = 6b, 2a + 3b = width, 12b + 3b = width, 15b = width, width = height
#define LUDU_BOARD_LENGTH 400
#define COLOR_LINE_WIDTH 5
#define TOTAL_SQUARE_SHARED 53
#define TOTAL_SQUARE ( 53 + 20 )

#define pb(x) push_back(x)

#pragma mark Enums
//enum Colors {
//    RED,
//    GREEN,
//    BLUE,
//    YELLOW,
//    WHITE
//};

struct MousePosition {
    double xPos;
    double yPos;
};


#pragma mark variables
GLFWwindow *window;
const GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
const GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
const GLfloat halfSideLength = 200;
int screenWidth, screenHeight;
MousePosition currentMousePos;


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
void drawGameBoards(screenWidth, screenHeight);

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
            glColor3f (1.0, 0.0, 0.0);  /* the current RGB color is red: */
            break;
        case GREEN:
            glColor3f (0.0, 1.0, 0.0);  /* the current RGB color is red: */
            break;
        case BLUE:
            glColor3f (0.0, 0.0, 1.0);  /* the current RGB color is red: */
            break;
        case YELLOW:
            glColor3f (1.0, 1.0, 0.0);  /* the current RGB color is red: */
            break;
        case WHITE:
            glColor3f (1.0, 1.0, 1.0);  /* the current RGB color is red: */
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
    currentMousePos.xPos = xPos;
    currentMousePos.yPos = yPos;
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
        cout << currentMousePos.xPos << "  " << currentMousePos.yPos << endl;
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

void drawGameBoards(screenWidth, screenHeight) {
    
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




#pragma mark Other_Unnecessary_Codes

//        glBegin (GL_POINTS);
//        glVertex3fv(allCircleVertices);
//        glEnd ();




//    GLfloat vertices[] = { // top left corner
//        halfScreenWidth, halfScreenHeight + halfSideLength, 0.0, // top center vertex
//        halfScreenWidth - halfSideLength, halfScreenHeight - halfSideLength, 0.0, // bottom left corner
//        halfScreenWidth + halfSideLength, halfScreenHeight - halfSideLength, 0.0 // bottom right corner
//    };


/* draw Triangles */
// glVertexPointer(3, GL_FLOAT, 0, vertices); // Point to the vertices to be used



//glBegin (GL_TRIANGLES);
//setColor(WHITE);  /* the current RGB color is red: */
//glVertex3fv(vertices);
//glEnd ();
//glColorPointer(3, GL_FLOAT, 0, colour);
//glDrawArrays(GL_TRIANGLES, 0, 3);//draw the vertices
//glDisableClientState(GL_COLOR_ARRAY);


//glEnableClientState(GL_VERTEX_ARRAY); // tell opengl that you are using a vertex array for fixed-funtion attribute
//glDisableClientState(GL_VERTEX_ARRAY);//tell Opengl that you are finished using the vertex array attribute

