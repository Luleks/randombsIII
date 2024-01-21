#include <iostream>
#include <string>
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
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    bind(listensock, (struct sockaddr*)&server, sizeof(server));
    listen(listensock, 3);

    while(true) {
        sockaddr_in client;
        int clen = sizeof(client);
        SOCKET clientsock = accept(listensock, (struct sockaddr*)&client, &clen);

        char* data = new char[1024];
        int size = recv(clientsock, data, 1024, 0);
        cout.write(data, size);
        cout << endl;
        fflush(stdout);

        while (size > 0) {
            send(clientsock, data, strlen(data)+1, 0);
            int size = recv(clientsock, data, 1024, 0);
            cout.write(data, size);
            cout << endl;
            fflush(stdout);
        }
        closesocket(clientsock);
    }
    closesocket(listensock);
    WSACleanup();
}