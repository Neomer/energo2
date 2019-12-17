//
// Created by kir on 14.12.2019.
//

#include <iostream>
#include <string>
#include <Types/Uuid.h>

using namespace std;
using namespace energo::types;

int main(int argc, char **argv) {
    string inp;
    while (true) {
        cin >> inp;
        if (inp == "q") {
            break;
        }
        Uuid uid;
        if (Uuid::TryParse(inp, uid)) {
            auto data = uid.rawData();
#ifdef ENVIRONMENT64
            cout << "energo::types::Uuid{" << data[0] << "ull, " << data[1] << "ull}\n";
#else
            cout << "energo::types::Uuid{" << data[0] << "ul, " << data[1] <<  "ul, " << data[2] <<  "ul, " << data[3] << "ul}\n";
#endif
        } else {
            cout << "Wrong format\n";
        }

    }

}