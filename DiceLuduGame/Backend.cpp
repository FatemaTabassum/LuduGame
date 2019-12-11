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


pthread_t tid;
RunClientParameters * runClientParams;
RunClientParameters  runClien;

void takeInput(){
    string serverHost;
    int servers_port_num, peers_port_num;
    //take server's hostname,
    cout << "Enter Server's Host name:\n";
    cin >> serverHost;
    //server's port number
    cout << "Enter Server's Port num:\n";
    cin >> servers_port_num;
    //from the client
    runClien.serverPort = servers_port_num;
    runClien.serverName = serverHost;
    runClientParams = &runClien;
    pthread_create(&tid, NULL, &runClient, (void*) runClientParams);
    (void)pthread_join(tid, NULL);
}
