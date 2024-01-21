#include <iostream>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib");
using namespace std;

int main() {
    WSAData wsa;
    SOCKET clientsock;

    WSAStartup(0x0202, &wsa);
    clientsock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    int clen = sizeof(server);
    char data[1024];
    while(true) {
        cout << "Poruka: ";
        fflush(stdout);
        cin >> data;
        sendto(clientsock, data, strlen(data) + 1, 0, (struct sockaddr*)&server, clen);
        recvfrom(clientsock, data, 1024, 0, (struct sockaddr*)&server, &clen);
        cout << data << endl;
        fflush(stdout);
    }
    closesocket(clientsock);
    WSACleanup();
}