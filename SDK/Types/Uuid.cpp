//
// Created by vinokurov on 04.12.2019.
//

#include <cstring>
#include <random>
#include "Uuid.h"

#ifdef ENVIRONMENT64
#define UUID_DATA_PARTS          2
#else
#define UUID_DATA_PARTS          4
#endif
#define UUID_BYTES               16

using namespace std;
using namespace energo::types;

Uuid::Uuid() {

}

bool Uuid::equals(const Uuid &other) const {
    return !memcmp(_data, other._data, UUID_DATA_PARTS);
}

bool Uuid::operator==(const Uuid &other) const {
    return equals(other);
}

Uuid Uuid::Empty() {
    Uuid uid;
    memset(uid._data, 0, UUID_DATA_PARTS);
    return uid;
}

Uuid Uuid::Random() {
    random_device rd;

#ifdef ENVIRONMENT64
    mt19937_64 env(rd());
    uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
#else
    mt19937 env(rd());
    uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);
#endif

    Uuid uid;
    for (auto idx: uid._data) {
        idx = dist(env);
    }
    return uid;
}

#undef UUID_DATA_PARTS
#undef UUID_BYTES