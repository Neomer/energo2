//
// Created by vinokurov on 04.12.2019.
//

#include <cstring>
#include <random>
#include <stdexcept>
#include <sstream>
#include <fmt/format.h>
#include "Uuid.h"

#ifdef ENVIRONMENT64
#define UUID_DATA_PARTS          2
#else
#define UUID_DATA_PARTS          4
#endif
#define UUID_BYTES               16

using namespace std;
using namespace energo::types;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-member-init"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
Uuid::Uuid() {
    memset(_data, 0, UUID_DATA_PARTS);
}
#pragma clang diagnostic pop

bool Uuid::equals(const Uuid &other) const {
    return !memcmp(_data, other._data, UUID_DATA_PARTS);
}

bool Uuid::operator==(const Uuid &other) const {
    return equals(other);
}

Uuid Uuid::Empty() {
    return Uuid();
}

Uuid Uuid::Random(std::random_device &rd) {
#ifdef ENVIRONMENT64
    mt19937_64 env(rd());
    uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);
#else
    mt19937 env(rd());
    uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);
#endif

    Uuid uid;
    for (uint8_t idx = 0; idx < UUID_DATA_PARTS; ++idx) { // NOLINT(modernize-loop-convert)
        uid._data[idx] = dist(env);
    }

    return uid;
}

bool Uuid::TryParse(std::string_view data, Uuid &uid) {
    return false;
}

Uuid Uuid::Parse(std::string_view data) {
    Uuid uid;
    if (!TryParse(data, uid)) {
        throw std::invalid_argument("Входная строка не является корректным UUID.");
    }
    return uid;
}

std::string Uuid::toString() const {
    return fmt::format(FMT_STRING("{:x}"), _data[0]);
}

#undef UUID_DATA_PARTS
#undef UUID_BYTES