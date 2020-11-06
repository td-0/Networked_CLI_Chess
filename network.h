#ifndef NETWORK_H
#define NETWORK_H


#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8025


using namespace std;

class Network {
private:

    string ip_address;

    int sock;

public:

    Network();

    Network(string);

    bool createServer();

    bool createClient();

    void sendOut(string);

    string receiveIn();

};

#endif
