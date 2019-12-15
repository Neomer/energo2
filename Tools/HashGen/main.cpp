//
// Created by kir on 14.12.2019.
//

#include <iostream>
#include <string>

using namespace std;

static hash<string_view> sHash;

void printHash(string_view data) {
    cout << data << ": " << sHash(data) << endl;
}

int main(int argc, char **argv) {
    for (auto idx = 1; idx < argc; ++idx) {
        printHash(argv[idx]);
    }
    
    string inp;
    while (true) {
        cin >> inp;
        if (inp == "q") {
            break;
        }
        printHash(inp);
    }

}