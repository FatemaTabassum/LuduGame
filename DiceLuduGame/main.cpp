#include <iostream>
#include "GameDrawingOpengl.hpp"
#include "Backend.hpp"
#include "GameSimulator.hpp"
using namespace std;


#pragma mark Main
int main(void) {
    
    //takeInput();
    createAndInitPlayers(numberOfTotalPlayers);
    if (initialize_window() == 1) {
        return -1;
    }
    addEventToTheScreen();
    render_opengl();
    printNumOfSquares();
    return 0;
}

