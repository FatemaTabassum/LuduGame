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


#pragma mark Globals
pthread_t tid;
RunClientParameters * runClientParams;
RunClientParameters  runClien;
// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
// declaring mutex
pthread_mutex_t lock_1 = PTHREAD_MUTEX_INITIALIZER;

#pragma mark Function Prototypes
void startOpenglAndGame();

void takeInput() {
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
    
    
    pthread_mutex_lock(&lock_1);
    pthread_create(&tid, NULL, &runClient, (void*) runClientParams);
    pthread_cond_wait(&cond1, &lock_1);
    
    pthread_mutex_unlock(&lock_1); 
    
    cout<<"main"<<endl;
    startOpenglAndGame();
    (void)pthread_join(tid, NULL);
}

void startOpenglAndGame() {
    shouldStartGame = true;
    if (initialize_window() == 1) {
        cout << "Error initialize window" <<endl;
    }
    addEventToTheScreen();
    render_opengl();
}
