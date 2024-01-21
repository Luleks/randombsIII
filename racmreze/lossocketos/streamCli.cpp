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
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);
    connect(clientsock, (struct sockaddr*)&server, sizeof(server));

    string msg;
    char recvd[1024];
    while (true) {
        cout << "Poruka: ";
        fflush(stdout);
        getline(cin, msg);
        send(clientsock, msg.data(), msg.size(), 0);
        if (msg == "END")
            break;
        int size = recv(clientsock, recvd, 1024, 0);
        cout << recvd << endl;
    }
    closesocket(clientsock);
    WSACleanup();
}