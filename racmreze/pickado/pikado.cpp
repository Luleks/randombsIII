#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double width = 300;
double r = 150;
double centerX = 150, centerY = 150;

double dist(double x, double y) {
    return sqrt((centerX - x) * (centerX - x) + (centerY -y ) * (centerY - y));
}

string parse(string query) {
    int pos1 = query.find("x=");
    int pos2 = query.find("&", pos1);
    int pos3 = query.find("y=", pos2);

    double x = static_cast<double>(stoi(query.substr(pos1+2, pos2-pos1-2)));
    double y = static_cast<double>(stoi(query.substr(pos3+2)));
    double dist_ = dist(x, y);
    if (dist_ > r)
        return "0 Poena";
    else if (dist_ < r / 3)
        return "5 Poena";
    else if (dist_ < 2 * r / 3)
        return "10 Poena";
    else
        return "15 Poena";
}

void output(string brpoena) {
    cout << "Content-Type: text/html\n\n";
    cout << "<html><head>\n";
    cout << "<title>Pikado</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<p>" << brpoena << "</p>\n";
    cout << "</body></html>\n";
}

int main() {
    string method = getenv("REQUEST_METHOD");
    string q_string = getenv("QUERY_STRING");

    if (method == "GET") {
        if (!q_string.empty()) {
            output(parse(q_string));
        }
    }
    else {
        output("Nepodrzan metod");
    }
}