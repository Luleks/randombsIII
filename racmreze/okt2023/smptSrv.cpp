#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib");
using namespace std;

string msg1 = "220 luka.elfak";
string msg21 = "250 Hello ", msg22 = ", pleased to meet you";
string msg31 = "250 ", msg32="... Sender ok";
string msg41 = "250 ", msg42="... Recipient ok";
string msg51 = "354 Enter mail, end with \".\" on a line by itself";
string msg61 = "250 Message accepted for delivery";
string msg71 = "luka.elfak closing connection"; 

int num = 0;

int main() {
    WSAData wsa;
    SOCKET listensock;

    WSAStartup(0x0202, &wsa);
    listensock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(listensock, (struct sockaddr*)&server, sizeof(server));
    listen(listensock, 3);

    while (true) {
        sockaddr_in client;
        int clen = sizeof(client);
        SOCKET clientsock = accept(listensock, (struct sockaddr*)&client, &clen);

        send(clientsock, msg1.data(), msg1.size(), 0);
        char user[512];
        recv(clientsock, user, 512, 0);
        cout << user << endl;

        string msg = msg21.append(string(user)).append(msg22);
        send(clientsock, msg.data(), msg.size(), 0);
        char sender[512];
        recv(clientsock, sender, 512, 0);
        cout << sender << endl;
        msg = msg31.append(string(sender)).append(msg32);
        send(clientsock, msg.data(), msg.size(), 0);
        char reciever[512];
        recv(clientsock, reciever, 512, 0);
        cout << reciever << endl;
        msg = msg41.append(string(reciever)).append(msg42);
        send(clientsock, msg.data(), msg.size(), 0);
        char buf[5];
        recv(clientsock, buf, 5, 0);
        send(clientsock, msg51.data(), msg51.size(), 0);
        char message[1024];
        recv(clientsock, message, 1024, 0);
        cout << message << endl;
        send(clientsock, msg61.data(), msg61.size(), 0);
        recv(clientsock, buf, 5, 0);
        send(clientsock, msg71.data(), msg71.size(), 0);

        string filename = string(sender).append("_").append(string(reciever)).append("_").append(to_string(num));
        num += 1;
        
        ofstream izl(filename);
        izl << sender << endl << reciever << endl << message;
        izl.close();
    }
}