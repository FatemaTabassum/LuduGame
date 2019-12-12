#include <iostream>
#include "GameDrawingOpengl.hpp"
#include "Backend.hpp"
#include "GameSimulator.hpp"

using namespace std;

void libraryInitialization();

#pragma mark Main
int main(void) {
    
    takeInput();
    cout<<"main"<<endl;
    printNumOfSquares();
    return 0;
}


