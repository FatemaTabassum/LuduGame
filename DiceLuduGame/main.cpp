//
//  main.cpp
//  DiceLuduGame
//
//  Created by Fatema on 10/24/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include <iostream>
#include "GameDrawingOpengl.hpp"

using namespace std;


#pragma mark Main
int main(void) {
    
    saveAllSqueares();
    if (initialize_window() == 1) {
        return -1;
    }
    addEventToTheScreen();
    render_opengl();
    return 0;
}






