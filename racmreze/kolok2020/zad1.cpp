#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <io.h>
#include <memory.h>
using namespace std;

void output(string filename, string ext) {
    ifstream f(filename.append(".").append(ext), ios::ate | ios::binary | ios::in);
    if (f.good()) {
        long fsize = f.tellg();
        cout << "Content-Type: img/" << ext << "\n";
        cout << "Content-Length: " << fsize << "\r\n\r\n";

        _setmode(_fileno(stdout), _O_BINARY);
        f.seekg(0, ios::beg);
        char* buffer = new char[fsize];
        f.read(buffer, fsize);
        cout.write(buffer, fsize);
        fflush(stdout);
        _setmode(_fileno(stdout), _O_TEXT);
        f.close();
    }
    else {
        cout << "Content-type: text/html\n\n";
        cout << "<html> <head>\n";
        cout << "<title>Zadatak</title>\n";
        cout << "</head>\n";
        cout << "<body>\n";
        cout << "<p>" << filename.append(".").append(ext) << " Slika nije pronadjena" << "</p>\n";
        cout << "</body> </html>";
    }
}

void parse(string query) {
    int pos1 = query.find("img=", 0);
    int pos2 = query.find("&", pos1);
    int pos3 = query.find("ext=.", pos2);

    string imgName = query.substr(pos1 + 4, pos2 - pos1 - 4);
    string ext = query.substr(pos3 + 5);
    string base = "C:\\www\\root\\";
    output(base.append(imgName), ext);
}

int main() {
    string method = getenv("REQUEST_METHOD");
    string q_string = getenv("QUERY_STRING");
    int br_byte = atoi(getenv("CONTENT_LENGTH"));

    if (method == "POST") {
        if (!q_string.empty()) {
            parse(q_string);
        }
        if (br_byte > 0) {
            char postInputString[100];
            memset(postInputString, 0, 100);
            cin.read(postInputString, br_byte);
            parse(string(postInputString));
        }
    }
}