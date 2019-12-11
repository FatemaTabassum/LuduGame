//
//  Clientfunc.cpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#include "Clientfunc.hpp"
#include "Friend.hpp"

/*************Global Declarations*************/
int serverSockfd;
int peerServport=5100;
string username="";
vector<int> peerSockVector;
unordered_map <string,Friend> onlineFriends;
unordered_set <string> inviterUsers;
bool userLoggedIn=false;

/*************Main Function*************/

void *runClient(void * arg) {
    struct RunClientParameters * clientParams = ( struct RunClientParameters *)arg;
    
    string servhost = clientParams->serverName ;
    int servport = clientParams->serverPort;
    onlineFriends.clear();
    int *sock_ptr;
    
    string bufferString,password,payloadString;
    pthread_t tid;
    
    
    struct sigaction abc;
    abc.sa_handler = sig_int;
    sigemptyset(&abc.sa_mask);
    abc.sa_flags = 0;
    
    sigaction(SIGINT, &abc, NULL);
    
    serverSockfd=connectToRemoteMachine(servhost.c_str(),servport,true);
    peerServport = 0;
    
    sock_ptr = (int *)malloc(sizeof(int));
    *sock_ptr = serverSockfd;
    
    pthread_create(&tid, NULL, &processServerConection, (void*)sock_ptr);
    
    //Command Definitions
    
    string messageCommand="m ";
    string inviteCommand="i ";
    string accpectInviteCommand="ia ";
    istringstream inputMessageStream("");
    string forUser;
    string messageString;
    userInitialPromt();
    
    ///Command Checking and Execution
    
    while (getline(cin, bufferString))
    {
        //return from this
        if(bufferString.compare("play")==0)
        {
            payloadString = createReqToStartPayload(username, "Start_game");
            cout<< "play is sending: "<<payloadString<<endl;
            write(serverSockfd, payloadString.c_str(), strlen(payloadString.c_str())+1);
        }
        ///User Registration
        if(bufferString.compare("r")==0)
        {
            cout<<"Username:";
            cin>>username;
            cout<<"Password:";
            cin>>password;
            payloadString=creatRegisterPayloadString(username,password);
            write(serverSockfd, payloadString.c_str(), strlen(payloadString.c_str())+1);
        }
        //User Login
        else if(bufferString.compare("l")==0)
        {
            if(userLoggedIn)
            {
                cout<<"Already logged in user"<<endl;
                continue;
            }
            cout<<"Username:";
            cin>>username;
            cout<<"Password:";
            cin>>password;
            payloadString=creatLoginPayloadString(username,password);
            write(serverSockfd, payloadString.c_str(), strlen(payloadString.c_str())+1);
        }
        //Quit the Program
        else if(bufferString.compare("exit")==0)
        {
            logoutFromServer(false);
            close(serverSockfd);
            exit(0);
        }
        //Logout from the Server
        else if(bufferString.compare("logout")==0)
        {
            if(!userLoggedIn)
            {
                cout<<"No user is logged in"<<endl;
                continue;
            }
            logoutFromServer(true);
            
        }
        else
        {
            //Message Command
            if(strncmp(bufferString.c_str(),messageCommand.c_str(),strlen(messageCommand.c_str()))==0)
            {
                inputMessageStream.clear();
                inputMessageStream.str(bufferString);
                getline(inputMessageStream,forUser,' ');
                getline(inputMessageStream,forUser,' ');
                getline(inputMessageStream,messageString,' ');
                sendMessageToFriend(forUser,messageString);
            }
            //Invite Users
            else if(strncmp(bufferString.c_str(),inviteCommand.c_str(),strlen(inviteCommand.c_str()))==0)
            {
                inputMessageStream.clear();
                inputMessageStream.str(bufferString);
                getline(inputMessageStream,forUser,' ');
                getline(inputMessageStream,forUser,' ');
                getline(inputMessageStream,messageString,' ');
                
                payloadString=createInvitePayload(forUser,messageString);
                write(serverSockfd, payloadString.c_str(), strlen(payloadString.c_str())+1);
                
            }
            //Accept Invitations
            else if(strncmp(bufferString.c_str(),accpectInviteCommand.c_str(),strlen(accpectInviteCommand.c_str()))==0)
            {
                inputMessageStream.clear();
                inputMessageStream.str(bufferString);
                getline(inputMessageStream,forUser,' ');
                getline(inputMessageStream,forUser,' ');
                getline(inputMessageStream,messageString,' ');
                
                auto itr=inviterUsers.find(forUser);
                if(itr==inviterUsers.end())
                {
                    cout<<"No invitation found from "<<forUser<<endl;
                    continue;
                }
                
                payloadString=createAcceptInvitePayload(forUser,messageString);
                write(serverSockfd, payloadString.c_str(), strlen(payloadString.c_str())+1);
                
            }
            
        }
    }
    return NULL; // Recheck
    
}

/*************Sending Message to Friend****************/
void sendMessageToFriend(string friendUsername,string message)
{
    
    auto it=onlineFriends.find(friendUsername);
    if(it != onlineFriends.end())
    {
        Friend friendUser=it->second;
        if(!friendUser.isConnected())
        {
            int friendSockfd=connectToRemoteMachine(friendUser.ipaddress.c_str(),friendUser.listeningPort,false);
            if(friendSockfd!=-1)
            {
                friendUser.sockfd=friendSockfd;
                it->second=friendUser;
                startReadThreadForSocket(friendSockfd);
                peerSockVector.push_back(friendSockfd);
            }
            else
            {
                cout<<"Could not connect to peer"<<endl;
                removeFromOnilneFriends(friendUser.username);
                return;
            }
        }
        
        string payload=createMessagePayloadString(username,message);
        write(friendUser.sockfd,payload.c_str(),strlen(payload.c_str())+1);
    }
    else
    {
        cout<<"Friend "<<friendUsername<<" is not online"<<endl;
    }
}

void writeToSocket(int sockfd,string payload)
{
    
    write(sockfd, payload.c_str(), strlen(payload.c_str())+1);
}

void createPeerServerSocket(int peerServPort)
{
    int serv_sockfd;
    struct sockaddr_in serv_addr;
    pthread_t tid;
    serv_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero((void*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(peerServPort);
    
    bind(serv_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    listen(serv_sockfd, 5);
    
    int * sock_ptr;
    sock_ptr = (int *)malloc(sizeof(int));
    *sock_ptr = serv_sockfd;
    pthread_create(&tid, NULL, &acceptPeerConnection, (void*)sock_ptr);
}

/*************Parsing Server Message****************/

void parseServerMessage(int sockfd,char *buf)
{
    string sbuf(buf);
    istringstream message(sbuf);
    string messageBody,response;
    getline(message,messageBody,OPTYPE_DELIM);
    
    if(messageBody.compare(OP_TYPE_LOGIN)==0)
    {
        getline(message,messageBody,OPTYPE_DELIM);
        if(messageBody.compare("200")==0)
        {
            userLoggedIn=true;
            cout<<"Login successful"<<endl;
            userAfterLoginPromt();
            createPeerServerSocket(peerServport);
            writeToSocket(sockfd,createLocationPayloadString(username,peerServport));
        }
        else
        {
            cout<<"Login failed. Please try again"<<endl;
        }
    }
    else if(messageBody.compare(OP_TYPE_REGISTER)==0)
    {
        getline(message,messageBody,OPTYPE_DELIM);
        if(messageBody.compare("200")==0)
        {
            cout<<"Registration successful"<<endl;
            
        }
        else
        {
            cout<<"Registration failed. Please try again"<<endl;
        }
        
    }
    else if(messageBody.compare(OP_TYPE_LOCATION)==0)
    {
        getline(message,messageBody,OPTYPE_DELIM);
        parseFriendLocationMessage(messageBody);
    }
    else if(messageBody.compare(OP_TYPE_INVITE)==0)
    {
        getline(message,messageBody,OPTYPE_DELIM);
        parseInviteMessage(messageBody);
    }
    else if(messageBody.compare(OP_TYPE_PLAY)==0)
    {
        getline(message,messageBody,OPTYPE_DELIM);
        parsePlayInviteMessage(messageBody);
    }
    message.clear();
}

/*************Parsing Invite Message****************/

void parseInviteMessage(string messageBody)
{
    string s,fromuser, invitemessage;
    istringstream mesageBodyStream(messageBody);
    istringstream valueStream("");
    while(getline(mesageBodyStream,s,MAIN_DELIM))
    {
        valueStream.clear();
        valueStream.str(s);
        getline(valueStream,s,VALUE_DELIM);
        if(s.compare(VALUE_TYPE_FROMUSER)==0)
        {
            getline(valueStream,fromuser,VALUE_DELIM);
        }
        else if(s.compare(VALUE_TYPE_MESSAGE)==0)
        {
            getline(valueStream,invitemessage,VALUE_DELIM);
        }
        
    }
    
    cout<<"You have received an invitation from "<<fromuser<<endl;
    
    if(invitemessage.size()>1)
    {
        cout<<fromuser;
        cout<<">>"<<invitemessage<<endl;
    }
    else
    {
        cout<<endl;
    }
    auto it=inviterUsers.find(fromuser);
    if(it==inviterUsers.end())
    {
        inviterUsers.insert(fromuser);
    }
    mesageBodyStream.clear();
    valueStream.clear();
    
    
}

/*******************Parsing Play Message*********************/

void parsePlayInviteMessage(string messageBody){
    cout<<"Got an invitaiton to play: "<<messageBody<<endl;
    string s,fromuser, num_of_players;
    istringstream mesageBodyStream(messageBody);
    istringstream valueStream("");
    while(getline(mesageBodyStream,s,MAIN_DELIM))
    {
        valueStream.clear();
        valueStream.str(s);
        getline(valueStream,s,VALUE_DELIM);
        if(s.compare(VALUE_TYPE_USERNAME)==0)
        {
            getline(valueStream,fromuser,VALUE_DELIM);
        }
        else if(s.compare(VALUE_TYPE_NUM_OF_PLAYERS)==0)
        {
            getline(valueStream,num_of_players,VALUE_DELIM);
        }
        
    }
    
    cout<<"Invited by: "<<fromuser<<", total players: "<<stoi(num_of_players)<<endl;
    //Now you can start the Game haha
    shouldStartGame = true;
    
    printf("Signaling condition variable cond1\n");
    pthread_cond_signal(&cond1);
    printf("thread cond1\n");
    //startPlayingGame(stoi(num_of_players), fromuser);
    
}
/*************Parsing Friend Location Message****************/

void parseFriendLocationMessage(string messageBody)
{
    string s,username, ipaddress, listetingport;
    istringstream mesageBodyStream(messageBody);
    istringstream valueStream("");
    while(getline(mesageBodyStream,s,MAIN_DELIM))
    {
        valueStream.clear();
        valueStream.str(s);
        getline(valueStream,s,VALUE_DELIM);
        if(s.compare(VALUE_TYPE_USERNAME)==0)
        {
            getline(valueStream,username,VALUE_DELIM);
        }
        else if(s.compare(VALUE_TYPE_IP)==0)
        {
            getline(valueStream,ipaddress,VALUE_DELIM);
        }
        else if(s.compare(VALUE_TYPE_PORT)==0)
        {
            getline(valueStream,listetingport,VALUE_DELIM);
        }
    }
    
    cout<<"Friend:"<<username<<" is online"<<endl;
    mesageBodyStream.clear();
    valueStream.clear();
    Friend onlineFriend(username,ipaddress,stoi(listetingport));
    onlineFriends.insert({username,onlineFriend});
}

/*************Connecting to Remote Machine****************/

int connectToRemoteMachine(const char *ip, int port,bool exitIferror)
{
    int sockfd=-1;
    
    
    int rv, flag;
    struct addrinfo hints, *res, *ressave;
    bzero(&hints, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if ((rv = getaddrinfo(ip, to_string(port).c_str() , &hints, &res)) != 0)
    {
        cout << "getaddrinfo wrong: " << gai_strerror(rv) << endl;
        if(exitIferror)
        {
            exit(1);
            
        }
        return sockfd;
    }
    
    ressave = res;
    flag = 0;
    do
    {
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sockfd < 0)
            continue;
        if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
        {
            flag = 1;
            break;
        }
        close(sockfd);
    }
    while ((res = res->ai_next) != NULL);
    freeaddrinfo(ressave);
    
    if (flag == 0)
    {
        fprintf(stderr, "cannot connect\n");
        if(exitIferror)
        {
            exit(1);
        }
        
    }
    return sockfd;
}

/*************Parsing Client Configuration Message****************/

void parseConfigFile(char *filename, string &servhost, int &servport)
{
    ifstream infile;
    infile.open(filename);
    string s,sbuf;
    
    for(int i=0; i<2; i++)
    {
        getline(infile,s);
        istringstream lineStream(s);
        getline(lineStream,sbuf,':');
        
        if(sbuf.compare("servhost")==0)
        {
            getline(lineStream,servhost,':');
            
        }
        else if(sbuf.compare("servport")==0)
        {
            getline(lineStream,sbuf,':');
            servport=stoi(sbuf);
        }
        
    }
}

/*************Parsing Message from Friend****************/

void parseMessageFromFriend(string messageBody, int sockfd)
{
    string s,username, message;
    istringstream mesageBodyStream(messageBody);
    istringstream valueStream("");
    
    getline(mesageBodyStream,s,OPTYPE_DELIM);
    
    if(s.compare(OP_TYPE_MESSAGE)==0)
    {
        
        while(getline(mesageBodyStream,s,MAIN_DELIM))
        {
            valueStream.clear();
            valueStream.str(s);
            getline(valueStream,s,VALUE_DELIM);
            if(s.compare(VALUE_TYPE_USERNAME)==0)
            {
                getline(valueStream,username,VALUE_DELIM);
            }
            else if(s.compare(VALUE_TYPE_MESSAGE)==0)
            {
                getline(valueStream,message,VALUE_DELIM);
            }
        }
        
        cout<<username<<">>"<<message<<endl;
        mesageBodyStream.clear();
        valueStream.clear();
        auto it=onlineFriends.find(username);
        if(it!=onlineFriends.end())
        {
            Friend onlineFriend=it->second;
            if(onlineFriend.sockfd==-1)
            {
                onlineFriend.sockfd=sockfd;
            }
            it->second=onlineFriend;
        }
    }
    
    
}

/* Payloads */

string createMessagePayloadString(string fromuser, string message)
{
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_MESSAGE<<OPTYPE_DELIM<<VALUE_TYPE_USERNAME<<VALUE_DELIM<<fromuser<<MAIN_DELIM<<VALUE_TYPE_MESSAGE<<VALUE_DELIM<<message;
    payload=buffer.str();
    buffer.clear();
    return payload;
    
}

string createLocationPayloadString(string username, int listeningport)
{
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_LOCATION<<OPTYPE_DELIM<<VALUE_TYPE_USERNAME<<VALUE_DELIM<<username<<MAIN_DELIM<<VALUE_TYPE_PORT<<VALUE_DELIM<<to_string(listeningport);
    payload=buffer.str();
    buffer.clear();
    return payload;
    
}

string creatLoginPayloadString(string username, string password)
{
    
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_LOGIN<<OPTYPE_DELIM<<VALUE_TYPE_USERNAME<<VALUE_DELIM<<username<<MAIN_DELIM<<VALUE_TYPE_PASSWORD<<VALUE_DELIM<<password;
    payload=buffer.str();
    buffer.clear();
    return payload;
}

string creatRegisterPayloadString(string username, string password)
{
    
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_REGISTER<<OPTYPE_DELIM<<VALUE_TYPE_USERNAME<<VALUE_DELIM<<username<<MAIN_DELIM<<VALUE_TYPE_PASSWORD<<VALUE_DELIM<<password;
    payload=buffer.str();
    buffer.clear();
    return payload;
}

string createInvitePayload(string targetUsername, string message)
{
    
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_INVITE<<OPTYPE_DELIM<<VALUE_TYPE_FROMUSER<<VALUE_DELIM<<username<<MAIN_DELIM<<VALUE_TYPE_TOUSER<<VALUE_DELIM<<targetUsername<<MAIN_DELIM<<VALUE_TYPE_MESSAGE<<VALUE_DELIM<<message;
    payload=buffer.str();
    buffer.clear();
    return payload;
}

string createReqToStartPayload(string targetUsername, string message){
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_PLAY<<OPTYPE_DELIM<<VALUE_TYPE_USERNAME<<VALUE_DELIM<<username<<MAIN_DELIM<<VALUE_TYPE_MESSAGE<<VALUE_DELIM<<message;
    payload=buffer.str();
    buffer.clear();
    return payload;
}

string createAcceptInvitePayload(string inviterUsername, string message)
{
    
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_ACCEPT_INVITE<<OPTYPE_DELIM<<VALUE_TYPE_FROMUSER<<VALUE_DELIM<<username<<MAIN_DELIM<<VALUE_TYPE_TOUSER<<VALUE_DELIM<<inviterUsername<<MAIN_DELIM<<VALUE_TYPE_MESSAGE<<VALUE_DELIM<<message;
    payload=buffer.str();
    buffer.clear();
    return payload;;
}

string createLogoutPayload()
{
    
    ostringstream buffer;
    string payload;
    buffer<<OP_TYPE_LOGOUT<<OPTYPE_DELIM<<VALUE_TYPE_USERNAME<<VALUE_DELIM<<username;
    payload=buffer.str();
    buffer.clear();
    return payload;;
}

/* Process Server Connection */

void *processServerConection(void *arg)
{
    int n;
    int sockfd;
    char buf[BUFFER_SIZE];
    sockfd = *((int *)arg);
    free(arg);
    pthread_detach(pthread_self());
    while (1)
    {
        n = (int)read(sockfd, buf, BUFFER_SIZE);
        if (n == 0)
        {
            printf("Server Crashed!!!\n");
            close(sockfd);
            exit(0);
        }
        parseServerMessage(sockfd, buf);
    }
}

/* Update currently available frindlist */

void removeFromOnilneFriends(string friendUsername)
{
    Friend onlineFriend;
    auto it=onlineFriends.find(friendUsername);
    if(it!=onlineFriends.end())
    {
        it=onlineFriends.erase(it);
        cout<<"Friend "<<friendUsername<<" is offline"<<endl;
        return;
    }
    
}

void removeFromOnilneFriends(int fd)
{
    Friend onlineFriend;
    auto it=onlineFriends.begin();
    while(it!=onlineFriends.end())
    {
        onlineFriend=it->second;
        if(onlineFriend.sockfd==fd)
        {
            it=onlineFriends.erase(it);
            cout<<"Friend "<<onlineFriend.username<<" is offline"<<endl;
            return;
        }
        ++it;
    }
}

/* Process Connection */

void *process_connection(void *arg)
{
    int sockfd;
    ssize_t n;
    char buf[BUFFER_SIZE];
    string bufferString;
    sockfd = *((int *)arg);
    free(arg);
    
    pthread_detach(pthread_self());
    while ((n = read(sockfd, buf, BUFFER_SIZE)) > 0)
    {
        buf[n] = '\0';
        bufferString=buf;
        parseMessageFromFriend(bufferString,sockfd);
    }
    if (n == 0)
    {
        cout << "peer closed" << endl;
        
    }
    else
    {
        cout << "something wrong" << endl;
    }
    removeFromOnilneFriends(sockfd);
    close(sockfd);
    return(NULL);
}

/* Accepting Connection from Friends */

void *acceptPeerConnection(void *arg)
{
    struct sockaddr_in cli_addr;
    socklen_t sock_len;
    int cli_sockfd;
    int serv_sockfd;
    
    serv_sockfd = *((int *)arg);
    free(arg);
    
    for (; ;)
    {
        sock_len = sizeof(cli_addr);
        cli_sockfd = accept(serv_sockfd, (struct sockaddr *)&cli_addr, &sock_len);
        peerSockVector.push_back(cli_sockfd);
        startReadThreadForSocket(cli_sockfd);
    }
    return(NULL);
}

/* Starting Read Thread for Socket */

void startReadThreadForSocket(int sockfd)
{
    int *sock_ptr;
    sock_ptr = (int *)malloc(sizeof(int));
    *sock_ptr = sockfd;
    pthread_t tid;
    pthread_create(&tid, NULL, &process_connection, (void*)sock_ptr);
}

/* Client Logout from Server */

void logoutFromServer(bool showpromt)
{
    auto itr = peerSockVector.begin();
    while (itr != peerSockVector.end())
    {
        int fd;
        fd = *itr;
        close(fd);
        ++itr;
    }
    onlineFriends.clear();
    writeToSocket(serverSockfd,createLogoutPayload());
    userLoggedIn=false;
    if(showpromt)
    {
        userInitialPromt();
    }
    
}

/*************Prompt Messages****************/

void userInitialPromt()
{
    cout<<"1. Enter 'r' for Registration"<<endl;
    cout<<"2. Enter 'l' to login"<<endl;
}

void userAfterLoginPromt()
{
    cout << "1. Enter 'play' to start play" <<endl;
    cout << "2. Enter 'quit' to quit game" << endl;
}

/* Ctrl-C: SIGINT Occurred */

void sig_int(int signo)
{
    cout<<endl<<"SIGINT"<<endl;
    logoutFromServer(false);
    close(serverSockfd);
    exit(0);
}

