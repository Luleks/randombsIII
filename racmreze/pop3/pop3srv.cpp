#include <iostream>
#include <string.h>
#include <string>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib")
using namespace std;

string ok = "+OK";
string err = "-ERR";
string msg1 = "POP3 server redy";
string msg2 = "user successfully logged in";

int userlen, passlen;
char* user;
char* pass;

string user_;
string pass_;


int main() {
    user = new char[50];
    pass = new char[50];
    WSAData wsa;
    SOCKET listensock;

    WSAStartup(0x0202, &wsa);
    listensock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(listensock, (struct sockaddr*)&server, sizeof(server));
    listen(listensock, 3);

    while (true) {
        sockaddr_in client;
        int clen = sizeof(client);
        SOCKET clientsock = accept(listensock, (struct sockaddr*)&client, &clen);

        send(clientsock, ok.append(msg1).data(), ok.append(msg1).size(), 0);
        int userlen = recv(clientsock, user, 50, 0);
        user_ = string(strstr(user, "user ") + 5);

        send(clientsock, ok.data(), ok.size(), 0);
        int passlen = recv(clientsock, pass, 50, 0);
        pass_ = string(strstr(pass, "pass ") + 5);

        cout << user_ << pass_ << endl;
    }
}