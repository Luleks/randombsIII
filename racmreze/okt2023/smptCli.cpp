#include <iostream>
#include <string>
#include <string.h>
#include <winsock.h>
#pragma comment(lib, "winsock32.lib")
using namespace std;

string msg1 = "HELO ";
string msg21 = "MAIL FROM: ";
string msg31 = "MAIL TO: ";
string msg4 = "DATA";
string msg5 = "QUIT";


int main() {
    WSAData wsa;
    SOCKET client;

    WSAStartup(0x0202, &wsa);
    client = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(9000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client, (struct sockaddr*)&server, sizeof(server));

    string user, sender, recicever, data;
    string dummy = "";
    string msg;

    char display[1024];
    int size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;
    cout << msg1;
    fflush(stdout);
    cin >> user;
    send(client, user.data(), user.size() + 1, 0);

    size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;
    cout << msg21;
    fflush(stdout);
    cin >> sender;
    send(client, sender.data(), sender.size() + 1, 0);
    size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;

    cout << msg31;
    fflush(stdout);
    cin >> recicever;
    send(client, recicever.data(), recicever.size() + 1, 0);
    size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;

    cout << msg4 << endl;
    fflush(stdout);
    send(client, dummy.data(), dummy.size() + 1, 0);
    size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;
    fflush(stdout);
    while (msg != ".") {
        cin >> msg;
        data.append("\n").append(msg);
    }
    send(client, data.data(), data.size() + 1, 0);
    size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;
    cout << msg5 << endl;
    fflush(stdout);
    send(client, dummy.data(), dummy.size() + 1, 0);
    size = recv(client, display, 1024, 0);
    cout.write(display, size);
    cout << endl;

    closesocket(client);
    WSACleanup();
}