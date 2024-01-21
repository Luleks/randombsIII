#include <iostream>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib");
using namespace std;

int main() {
    WSAData wsa;
    SOCKET clientsock;

    WSAStartup(0x0202, &wsa);
    
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char* data = new char[1024];
    while (true) {
        cout << "Poruka: ";
        fflush(stdout);
        cin >> data;
        send(clientsock, data, strlen(data)+1, 0);
        recv(clientsock, data, 1024, 0);
        cout << data << endl;
        fflush(stdout);
    }
    closesocket(clientsock);
    WSACleanup();
}