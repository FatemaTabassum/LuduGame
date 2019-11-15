//
//  Player.cpp
//  DiceLuduGame
//
//  Created by Fatema on 11/13/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include <stdio.h>


class Position
{
private:
    int x,y;
    
public:
    void setcoord(int x,int y){ // set coordinate
        this->x=x;
        this->y=y;
    }
    void display(int b) {
        printf("Liza int b = %d\n", b);
    }
    
    //    void display(int b){
    //        setcolor(15);
    //        circle(x,y,10);
    //        if(b==1){
    //            setfillstyle(SOLID_FILL,RED);
    //            floodfill(x,y,15);
    //        }
    //        if(b==2){
    //            setfillstyle(SOLID_FILL,YELLOW);
    //            floodfill(x,y,15);
    //        }
    //        if(b==3){
    //            setfillstyle(SOLID_FILL,GREEN);
    //            floodfill(x,y,15);
    //        }
    //        if(b==4){
    //            setfillstyle(SOLID_FILL,BLUE);
    //            floodfill(x,y,15);
    //        }
    //    }
};







class Player{
private:
    Position pos;//player has attribute of type class Position
    
public:
    int posindex;
    int status;
    int homeway;
    
//    Player(){
//        status=0;
//        homeway=0;
//    }
//
//    void setposition(int pindex,Position p){
//        posindex=pindex;
//        pos=p;
//    }
//
//    void display(int b){
//        pos.display(b);
//    }
    
};


