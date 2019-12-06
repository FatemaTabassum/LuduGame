//
//  Friend.hpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#ifndef Friend_hpp
#define Friend_hpp

#include <stdio.h>
#include <string>
using namespace std;
class Friend
{
public:
    int sockfd=-1;
    string ipaddress;
    int listeningPort;
    string username;
    
    Friend();
    Friend(string username,string ip,int port);
    bool isConnected();
};

#endif /* Friend_hpp */
