//
//  Clientfunc.hpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#ifndef Clientfunc_hpp
#define Clientfunc_hpp

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unordered_map>
#include <unordered_set>
#include "GameSimulator.hpp"

using namespace std;


#define BUFFER_SIZE 4096
#define OPTYPE_DELIM '~'
#define MAIN_DELIM '|'
#define VALUE_DELIM ':'
#define OP_TYPE_LOGIN "login"
#define OP_TYPE_REGISTER "register"
#define OP_TYPE_LOCATION "location"
#define OP_TYPE_MESSAGE "message"
#define OP_TYPE_INVITE "invite"
#define OP_TYPE_PLAY "play"
#define OP_TYPE_ACCEPT_INVITE "accept_invite"
#define OP_TYPE_LOGOUT "logout"
#define VALUE_TYPE_USERNAME "username"
#define VALUE_TYPE_PASSWORD "password"
#define VALUE_TYPE_PORT "port"
#define VALUE_TYPE_IP "ip"
#define VALUE_TYPE_MESSAGE "message"
#define VALUE_TYPE_FROMUSER "fromuser"
#define VALUE_TYPE_TOUSER "touser"
#define VALUE_TYPE_NUM_OF_PLAYERS "numofplayers"


void *runClient(void * arg);
int connectToRemoteMachine(const char *ip, int port,bool exitIferror);
string creatLoginPayloadString(string username, string password);
string creatRegisterPayloadString(string username, string password);
string createLocationPayloadString(string username, int listeningport);
string createMessagePayloadString(string fromuser, string message);
string createInvitePayload(string targetUsername, string message);
string createAcceptInvitePayload(string inviterUsername, string message);
string createLogoutPayload();
void parseConfigFile(char *filename, string &servhost, int &servport);
void parseServerMessage(int sockfd,char *buf);
void createPeerServerSocket(int peerServPort);
void parseFriendLocationMessage(string messageBody);
void sendMessageToFriend(string friendUsername,string message);
void startReadThreadForSocket(int sockfd);
void removeFromOnilneFriends(int fd);
void removeFromOnilneFriends(string friendUsername);
void parseMessageFromFriend(string messageBody, int sockfd);
void logoutFromServer(bool showpromt);
void parseInviteMessage(string messageBody);
void userInitialPromt();
void userAfterLoginPromt();
void sig_int(int signo);
void *acceptPeerConnection(void *arg);
void *processServerConection(void *arg);
void *process_connection(void *arg);

string createReqToStartPayload(string targetUsername, string message);
void parsePlayInviteMessage(string messageBody);
#endif /* Clientfunc_hpp */

