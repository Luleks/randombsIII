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
    char data[1024];
    while (true) {
        int size = recvfrom(serversock, data, 1024, 0, (struct sockaddr*)&client, &clen);
        if (size > 0) {
            data[size] = '\0';
            cout << data << endl;
            if (strcmp(data, "END") == 0)
                continue;
            sendto(serversock, data, size + 1, 0, (struct sockaddr*)&client, clen);
        }
    }
    closesocket(serversock);
    WSACleanup();
}