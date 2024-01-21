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
    clientsock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);
    server.sin_family = AF_INET;
    int clen = sizeof(server);
    
    string msg;
    char data[1024];
    while (true) {
        cout << "Poruka: ";
        fflush(stdout);
        getline(cin, msg);
        sendto(clientsock, msg.data(), msg.size(), 0, (struct sockaddr*)&server, clen);
        if (msg == "END")
            break;
        int size = recvfrom(clientsock, data, 1024, 0, (struct sockaddr*)&server, &clen);
        cout << data << endl;
    }
    closesocket(clientsock);
    WSACleanup();
}