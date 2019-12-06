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
    memset(_data, 0, UUID_BYTES);
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

[[nodiscard]] inline bool is_correct_part(char symbol) {
    return (symbol >= '0' && symbol <= '9') || (symbol >= 'a' && symbol <= 'f') || (symbol >= 'a' && symbol <= 'f');
}

bool Uuid::TryParse(std::string_view data, Uuid &uid) {
    uint8_t state = 0, num = 0;
    const char *ptr = data[0] == '{' ? data.data() : data.data() + 1;
    return false;
}

Uuid Uuid::Parse(std::string_view data) {
    Uuid uid;
    if (!TryParse(data, uid)) {
        throw std::invalid_argument("Входная строка не является корректным UUID.");
    }
    return uid;
}

#include <iostream>

std::string Uuid::toString() const {
#ifdef ENVIRONMENT64
    return fmt::format("{:08x}-{:04x}-{:04x}-{:04x}-{:012x}",
                       static_cast<uint32_t>((_data[0] & 0xFFFFFFFF00000000u) >> 32u),
                       static_cast<uint16_t>((_data[0] & 0x00000000FFFF0000u) >> 16u),
                       static_cast<uint16_t>((_data[0] & 0x000000000000FFFFu)),
                       static_cast<uint16_t>((_data[1] & 0xFFFF000000000000u) >> 40u),
                       static_cast<uint64_t>((_data[1] & 0x0000FFFFFFFFFFFFu)));
#else
    return fmt::format("{:08x}-{:04x}-{:04x}-{:04x}-{:4x}{:8x}",
                       _data[0],
                       static_cast<uint16_t>((_data[1] & 0xFFFF0000u) >> 8u),
                       static_cast<uint16_t>((_data[1] & 0x0000FFFFu)),
                       static_cast<uint16_t>((_data[2] & 0xFFFF0000u) >> 8u),
                       static_cast<uint16_t>((_data[2] & 0x0000FFFFu)),
                       _data[3]);
#endif
}

#ifdef ENVIRONMENT64

Uuid::Uuid(const uint64_t *data) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    memcpy(_data, data, UUID_DATA_PARTS);
}

Uuid::Uuid(uint64_t p1, uint64_t p2) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    _data[0] = p1;
    _data[1] = p2;
}

#else

Uuid::Uuid(const uint32_t *data) {
    memcpy(_data, data, UUID_DATA_PARTS);
}

Uuid::Uuid(uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4) {
    _data[0] = p1;
    _data[1] = p2;
    _data[2] = p3;
    _data[3] = p4;
}

#endif

#undef UUID_DATA_PARTS
#undef UUID_BYTES