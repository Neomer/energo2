//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>
#include <random>
#include <Types/Uuid.h>

using namespace std;
using namespace energo::types;

int main(int argv, char **argc) {
    random_device rd;

    auto uid = Uuid::Random(rd),
        uid2 = Uuid::Empty();

    if (uid.equals(uid2)) {
        std::cout << "Random is empty\n";
    } else {
        std::cout << "Random is NOT empty\n";
    }

    return 0;
}

