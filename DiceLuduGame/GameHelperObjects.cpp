//
//  GameHelperObjects.cpp
//  DiceLuduGame
//
//  Created by Fatema on 11/13/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

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

//0.0 0.5 0.0 dark green
//0.0 1.0 1.0 cyan
//1.0 0.0 1.0 purple

class Position {
private:
    //float xPos2;
    float xPos;
    float yPos;
    float zPos = 0;
public:
    Position() {
        
    }
    Position(float x, float y) {
        xPos = x;
        yPos = y;
        zPos = 0;
    }
    void setCoord(float x,float y){ // set coordinate
        xPos = x;
        xPos = y;
    }
    void display() {
        cout << " xPos " << xPos << " yPos " << yPos << endl;
    }
    float getxPos() {
        return this->xPos;
    }
    float getyPos() {
        return this->yPos;
    }
};


class Token {
private:
    Position pos;
    unsigned int token_id;
    bool isHome;
    
public:
    Token() {
        
    }
    Token(unsigned int token_id) {
        this->token_id = token_id;
        this->isHome = true;
    }
    Token (Position pos, unsigned int token_id, bool isHome ) {
        this->pos = pos;
        this->token_id = token_id;
        this->isHome = isHome;
    }
    void setPos(Position pos) {
        this->pos = pos;
    }
    void setTokenId(unsigned int id) {
        this->token_id = id;
    }
    unsigned int getTokenId() {
        return this->token_id;
    }
    bool getIsHome() {
        return isHome;
    }
    void setIsHome(bool isHome) {
        this->isHome = isHome;
    }
    Position getPos() {
        return  this->pos;
    }
    unsigned int getToken_id() {
        return  token_id;
    }
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
    
    Player() {
        
    }
    Player(unsigned int player_id) {
        this->player_id = player_id;
    }
    Player(Position p) {
        pos = pos;
        posindex = 0;
        status = 0;
        homeway = 0;
    }
    void setPosition(int pindex,Position p) {
        posindex=pindex;
        pos=p;
    }
    void setColor(Colors color) {
        this->color = color;
    }
//    void addTokenToTokenList(int token_id) {
//        Token tok = Token(token_id);
//        this->tokenList.push_back(tok);
//    }
//    void removeTokenFromTokenList(int token_id) {
//
//    }
    unsigned int getPlayer_id() {
        return this->player_id;
    }
    void initializeTokenList() {
        int totalTok = 4;
        for (int i = 0; i < totalTok; i++) {
            Token tok = Token(i);
            this->tokenList.push_back(tok);
        }
    }
//    void display(int b){
//        pos.display(b);
//    }
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
    Square() {
    }
    void setLeftBottomPos(Position pos) {
        this->leftBottomPos = Position(pos.getxPos(), pos.getyPos());
        
    }
    void setRightBottomPos(Position pos) {
        this->rightBottomPos = Position(pos.getxPos(), pos.getyPos());
    }
    void setLeftUpperPos(Position pos) {
        this->leftUpperPos = Position(pos.getxPos(), pos.getyPos());
    }
    void setRightUpperPos(Position pos) {
        this->rightUpperPos = Position(pos.getxPos(), pos.getyPos());
    }
    void setSquareWidth(float w) {
        this->squareWidth = w;
    }
    
    void setSquareHeight(float h) {
        this->squareHeight = h;
    }
    Position getLeftBottomPos() {
        return this->leftBottomPos;
    }
    Position getRightBottomPos() {
        return this->rightBottomPos;
    }
    Position getLeftUpperPos() {
        return this->leftUpperPos;
    }
    Position getRightUpperPos() {
        return this->rightUpperPos;
    }
    void addPlayerToPlayerList(Player player) {
        this->playerList.push_back(player);
    }
    
    void removePlayerFromPlayerList(Player player) {
        //this->playerList.;
    }
    void setMidX(float x) {
        this->midX = x;
    }
    void setMidY(float x) {
        this->midY = x;
    }
    float getmidX() {
        return this->midX;
    }
    float getmidY() {
        return this->midY;
    }
    
};

