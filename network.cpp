#include "network.h"

using namespace std;


Network::Network() {

    // Used to Create Host

    ip_address = "None";

}


Network::Network(string ip) {

    // Used to Create Client

    ip_address = ip;

}


bool Network::createServer() {

    int newSocket;
    struct sockaddr_in address;

    int opted = 1;

    int address_length = sizeof(address);

    string connectMessage = "\nConnection to Server Established\n";

    char buffer[1024] = {0};

    // Create Socket
    if (( newSocket = socket ( AF_INET, SOCK_STREAM, 0)) == 0) {
        cout << "Error: Could Not Open To Network" << endl;
        return false;
    }

    if ( setsockopt(newSocket, SOL_SOCKET, SO_REUSEADDR, &opted, sizeof ( opted ))) {
        cout << "Error: Could Not Open To Network" << endl;
        return false;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Bind Socket
    if (bind(newSocket, ( struct sockaddr * )&address, sizeof(address)) < 0) {
        cout << "Error: Could Not Create Server" << endl;
        return false;
    }

    // Begin Listening to Socket
    if (listen ( newSocket, 3) < 0) {
        cout << "Error: Could Not Create Server" << endl;
        return false;
    }

    if ((sock = accept(newSocket, (struct sockaddr *)&address, (socklen_t*)&address_length)) < 0) {
        cout << "Accepted" << endl;
        return false;
    }

    // Connection to Client Established

    read(sock, buffer, 1024);
    cout << buffer << endl << endl;
    sendOut ( connectMessage );
    return true;

}


bool Network::createClient() {

    struct sockaddr_in serv_addr;

    string connectMessage = "\nConnection to Client Established\n";

    char buffer[1024] = {0};

    // Create Socket
    if (( sock = socket (AF_INET, SOCK_STREAM, 0) ) < 0) {
        cout << "Error: Could Not Establish Connection" << endl;
        return false;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Find IP Address
    if (inet_pton ( AF_INET, ip_address.c_str(), &serv_addr.sin_addr ) <= 0 ) {
        cout << "Error: Invalid IP Address" << endl;
        return false;
    }

    // Connect to Server
    if ( connect( sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr )) < 0) {
        cout << "Error: Could Not Establish Connection" << endl;
        cout << sizeof(serv_addr) << endl;
        return false;
    }

    // Connection to Server Established

    sendOut (connectMessage );
    read ( sock, buffer, 1024 );
    cout << buffer << endl << endl;
    return true;

}


void Network::sendOut(string message) {
    // Send Message to Remote
    int sent = send ( sock, message.c_str(), message.length(), 0 );
    while (sent != (int)message.length())
        sent = send ( sock, message.c_str(), message.length(), 0 );
}


string Network::receiveIn() {
    // Recieve Message from Remote
    char buffer[1024] = {0};
    read (sock, buffer, 1024);
    return buffer;
}
