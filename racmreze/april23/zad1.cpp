#include <iostream>
#include <memory.h>
#include <string>
using namespace std;

string parse(string query) {
    int pos1 = query.find("x=", 0);
    int pos2 = query.find("&", pos1);
    int pos3 = query.find("y=", pos2);

    int x = stoi(query.substr(pos1 + 2, pos2 - pos1 + 2));
    int y = stoi(query.substr(pos3 + 2));

    if (x + y > 100)
        return "Crna";
    else
        return "Bela";
}

void output(string boja) {
    cout << "Content-type: text/html\n\n";
    cout << "<html> <head>\n";
    cout << "<title>Zadatak</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<p>" << "Kliknuta je strana " << boja << "</p>\n";
    cout << "</body> </html>";
}

int main() {
    string method = getenv("REQUEST_METHOD");
    string q_string = getenv("QUERY_STRING");
    int br_byte = atoi(getenv("CONTENT_LENGTH"));

    if (method == "GET") {
        if (!q_string.empty()) {
            string res = parse(q_string);
            output(res);
        }
    }
    else if (method == "POST") {
        if (!q_string.empty()) {
            string res = parse(q_string);
            output(res);
        }
        if (br_byte > 0) {
            char postInputString[100];
            memset(postInputString, 0, 100);
            cin.read(postInputString, br_byte);
            string res = parse(string(postInputString));
            output(res);
        }
    }
}