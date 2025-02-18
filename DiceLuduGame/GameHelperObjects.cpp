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
#include "GameDrawingOpengl.hpp"

using namespace std;

bool shouldStartGame = false;
bool isGameRunning = false;


Position::Position() {
    
}
Position::Position(float x, float y) {
    xPos = x;
    yPos = y;
    zPos = 0;
}
void Position::setCoord(float x,float y){ // set coordinate
    xPos = x;
    yPos = y;
}
void Position::display() {
    cout << " xPos " << xPos << " yPos " << yPos << endl;
}
float Position::getxPos() {
    return this->xPos;
}
float Position:: getyPos() {
    return this->yPos;
}




Token::Token() {
    
}
Token::Token(unsigned int token_id) {
    this->token_id = token_id;
    this->squareNumber = -1;
    this->ishidden = false;
}
Token::Token (Position pos, unsigned int token_id, bool isHome ) {
    this->pos = pos;
    this->token_id = token_id;
    this->squareNumber = -1;
    this->ishidden = false;
}
void Token::setPos(Position pos) {
    this->pos = pos;
}
void Token::setTokenId(unsigned int id) {
    this->token_id = id;
}
unsigned int Token::getTokenId() {
    return this->token_id;
}
Position Token::getPos() {
    return  this->pos;
}
unsigned int Token::getToken_id() {
    return  token_id;
}

void Token::setTokenColor(Colors color){
    this->tokenColor = color;
}
Colors  Token::getTokenColor() {
    return this->tokenColor;
}
void Token::setSquareNumber(int n){
    this->squareNumber = n;
}
int Token:: getSquareNumber() {
    return this->squareNumber;
}

bool Token:: getIsHidden() {
    return this->ishidden;
}
void Token:: setIsHidden(bool isHidden) {
    this->setIsHidden(ishidden);
}



Player::Player() {
    
}
Player::Player(unsigned int player_id) {
    this->player_id = player_id;
    this->isHome = false;
    this->playerSpecificStartingTokenFlag = false;
}
Player::Player(Position p) {
    pos = pos;
    posindex = 0;
    status = 0;
    isHome = false;
    this->playerSpecificStartingTokenFlag = false;
}
void Player:: setPosition(int pindex,Position p) {
    posindex = pindex;
    pos = p;
}
void Player:: setColor(Colors color) {
    this->color = color;
}

void Player:: setTokenList(vector <Token> list) {
    this->tokenList = list;
}

void Player:: setIsHome(bool isHome){
    this->isHome = isHome;
}

bool Player:: getIsHome(){
    return this->isHome;
}

void Player:: setUsername(string username) {
    this->username = username;
}
string Player:: getUsername() {
    return this->username;
}

void Player:: setPlayerSpecificStartingSquare(int playerSpecificStartingSquare) {
    this->playerSpecificStartingSquare = playerSpecificStartingSquare;
}

int Player:: getPlayerSpecificStartingSquare() {
    return this->playerSpecificStartingSquare;
}


void Player:: setPlayerSpecificStartingTokenFlag(bool playerSpecificStartingTokenFlag) {
    this->playerSpecificStartingTokenFlag = playerSpecificStartingTokenFlag;
}
bool Player:: getPlayerSpecificStartingTokenFlag() {
    return this->playerSpecificStartingTokenFlag;
}

unsigned int Player:: getPlayer_id() {
    return this->player_id;
}
void Player:: initializeTokenList(Colors tokenColor) {
    for (int i = 0; i < TOTAL_TOKEN; i++) {
        Token tok = Token(i);
        tok.setTokenColor(tokenColor);
        float centerX=bigSquareLength/2;
        float centerY = bigSquareLength/2;
        
        //printf("%lu %lu\n",player_id,bigSquareVector.size());
        if(player_id < bigSquareVector.size()){
            centerX = bigSquareVector[player_id].getmidX();
            centerY = bigSquareVector[player_id].getmidY();
        }
        Position pos = Position(centerX, centerY);
        tok.setPos(pos);
        this->tokenList.push_back(tok);
    }
}
vector<Token> Player::getTokenList() {
    return this->tokenList;
}



Square::Square() {
}
void Square::setLeftBottomPos(Position pos) {
    this->leftBottomPos = Position(pos.getxPos(), pos.getyPos());
    
}
void Square:: setRightBottomPos(Position pos) {
    this->rightBottomPos = Position(pos.getxPos(), pos.getyPos());
}
void Square:: setLeftUpperPos(Position pos) {
    this->leftUpperPos = Position(pos.getxPos(), pos.getyPos());
}
void Square:: setRightUpperPos(Position pos) {
    this->rightUpperPos = Position(pos.getxPos(), pos.getyPos());
}
void Square:: setSquareWidth(float w) {
    this->squareWidth = w;
}

void Square:: setSquareHeight(float h) {
    this->squareHeight = h;
}
Position Square:: getLeftBottomPos() {
    return this->leftBottomPos;
}
Position Square:: getRightBottomPos() {
    return this->rightBottomPos;
}
Position Square:: getLeftUpperPos() {
    return this->leftUpperPos;
}
Position Square:: getRightUpperPos() {
    return this->rightUpperPos;
}
void Square:: addPlayerToPlayerList(Player player) {
    this->playerList.push_back(player);
}

void Square:: removePlayerFromPlayerList(Player player) {
    //this->playerList.;
}
void Square:: setMidX(float x) {
    this->midX = x;
}
void Square:: setMidY(float x) {
    this->midY = x;
}
float Square:: getmidX() {
    return this->midX;
}
float Square:: getmidY() {
    return this->midY;
}

