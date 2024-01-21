#include <iostream>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib")
using namespace std;

int main() {
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

        char data[1024];
        strcpy(data, ".");
        int size;
        while (true) {
            size = recv(clientsock, data, 1024, 0);
            data[size] = '\0';
            if (strcmp(data, "END") == 0)
                break;
            send(clientsock, data, size + 1, 0);
            cout << data << endl;
        }
        closesocket(clientsock);
    }
    closesocket(listensock);
    WSACleanup();
}