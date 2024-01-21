#include <iostream>
#include <string>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib")
using namespace std;

int main() {
    WSAData wsa;
    SOCKET clientsock;

    WSAStartup(0x0202, &wsa);
    clientsock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    connect(clientsock, (struct sockaddr*)&server, sizeof(server));
    char display[1024];
    int size;
    string tosend;
    while (true) {
        size = recv(clientsock, display, 1024, 0);
        cout << string(display, size) << endl;
        fflush(stdout);
        getline(cin, tosend);
        send(clientsock, tosend.data(), tosend.size(), 0);
        size = recv(clientsock, display, 1024, 0);
        cout << string(display, size) << endl;
        fflush(stdout);
        getline(cin, tosend);
        send(clientsock, tosend.data(), tosend.size(), 0);
    }  
}