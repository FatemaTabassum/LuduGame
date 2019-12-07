#include <iostream>
#include "GameDrawingOpengl.hpp"
#include "Backend.hpp"
#include "GameSimulator.hpp"

using namespace std;


void libraryInitialization();

#pragma mark Main
int main(void) {
    
    //takeInput();
    if (initialize_window() == 1) {
        return -1;
    }
    addEventToTheScreen();
    render_opengl();
    printNumOfSquares();
    return 0;
}


