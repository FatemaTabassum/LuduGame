//
//  GameHelperObjects.h
//  DiceLuduGame
//
//  Created by Fatema on 12/5/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#ifndef GameHelperObjects_h
#define GameHelperObjects_h

#include <vector>
using namespace std;

#endif /* GameHelperObjects_h */

#pragma mark Colors
enum Colors {
    RED, // used as big square
    GREEN, // used as big square
    BLUE, // used as drawlines
    YELLOW, // used as big square
    WHITE, // can be used as token
    PURPLE, // can be used as token
    CYAN, // used as big square
    DARKGREEN, // can be used as token
    BLACK, // can be used as token
    NONE
};

class Position {
private:
    //float xPos2;
    float xPos;
    float yPos;
    float zPos = 0;
public:
    Position();
    Position(float x, float y);
    void setCoord(float x,float y);
    void display();
    float getxPos();
    float getyPos();
};


class Token {
private:
    Position pos;
    unsigned int token_id;
    bool isHome;
    
public:
    Token();
    Token(unsigned int token_id);
    Token (Position pos, unsigned int token_id, bool isHome );
    void setPos(Position pos);
    void setTokenId(unsigned int id);
    unsigned int getTokenId();
    bool getIsHome();
    void setIsHome(bool isHome);
    Position getPos();
    unsigned int getToken_id();
};


class Player {
private:
    unsigned int player_id;
    Position pos;
    vector< Token > tokenList;
    //player has attribute of type class Position
    
public:
    int posindex;
    int status;
    int homeway;
    Colors color;
    
    Player();
    Player(unsigned int player_id);
    Player(Position p);
    void setPosition(int pindex,Position p);
    void setColor(Colors color);
    unsigned int getPlayer_id();
    void initializeTokenList();
};

class Square {
private:
    Position leftBottomPos;
    Position rightBottomPos;
    Position leftUpperPos;
    Position rightUpperPos;
    std::vector <Player> playerList;
    float squareWidth;
    float squareHeight;
    float midX;
    float midY;
    
public:
    bool isEmpty = true;
    Square();
    void setLeftBottomPos(Position pos);
    void setRightBottomPos(Position pos);
    void setLeftUpperPos(Position pos);
    void setRightUpperPos(Position pos);
    void setSquareWidth(float w);
    
    void setSquareHeight(float h);
    Position getLeftBottomPos();
    Position getRightBottomPos();
    Position getLeftUpperPos();
    Position getRightUpperPos();
    void addPlayerToPlayerList(Player player);
    
    void removePlayerFromPlayerList(Player player);
    void setMidX(float x);
    void setMidY(float x);
    float getmidX();
    float getmidY();
};
