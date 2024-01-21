#include <iostream>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib")
using namespace std;

int main() {
    WSAData wsa;
    SOCKET serversock;

    WSAStartup(0x0202, &wsa);
    serversock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(serversock, (struct sockaddr*)&server, sizeof(server));

    sockaddr_in client;
    int clen = sizeof(client);
    char* data = new char[1024];
    while (true) {
        int size = recvfrom(serversock, data, 1024, 0, (struct sockaddr*)&client, &clen);
        if (size <= 0)
            break;
        cout << data;
        sendto(serversock, data, strlen(data) + 1, 0, (struct sockaddr*)&client, clen);
    }
    closesocket(serversock);
    WSACleanup();
}