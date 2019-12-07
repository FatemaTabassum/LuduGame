//
//  Backend.cpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include "Backend.hpp"
#include "Clientfunc.hpp"
#include <iostream>
using namespace std;
void takeInput(){
    string serverHost;
    int servers_port_num, peers_port_num;
    //take server's hostname,
    cout << "Enter Server's Host name:\n";
    cin >> serverHost;
    //server's port number
    cout << "Enter Server's Port num:\n";
    cin >> servers_port_num;
    //and peers port number
    cout << "Enter Peers port num:\n";
    cin >> peers_port_num;
    //from the client
    runClient(serverHost, servers_port_num, peers_port_num);
    runClient("localhost", 5100, 5542);
}
