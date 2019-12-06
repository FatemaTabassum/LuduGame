//
//  Friend.cpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include "Friend.hpp"
using namespace std;
    
Friend::Friend()
{
    
}

Friend::Friend(string username,string ip,int port)
{
    this->username=username;
    ipaddress=ip;
    listeningPort=port;
}

bool Friend::isConnected()
{
    if(sockfd==-1)
    {
        return false;
    }
    return true;
}
