//
// Created by kir on 08.12.2019.
//

#include <stdexcept>
#include <cstring>
#include <functional>
#include "SqlValue.h"

using namespace std;
using namespace energo::db;
using namespace energo::types;

template<typename T>
inline T parseNumber(const char *data, size_t length, function<T(const char *, char **, int)> comp) {
    char *end_ptr = nullptr;
    auto result = comp(data, &end_ptr, 10);
    if (static_cast<size_t>(end_ptr - data) < length) {
        throw invalid_argument("");
    }
    return result;
}

template<typename T>
inline T parseNumber(const char *data, size_t length, function<T(const char *, char **)> comp) {
    char *end_ptr = nullptr;
    auto result = comp(data, &end_ptr);
    if (static_cast<size_t>(end_ptr - data) < length) {
        throw invalid_argument("");
    }
    return result;
}

SqlValue::SqlValue(std::string_view data) :
    _data{data},
    _length{strlen(data.data())}
{

}

uint8_t SqlValue::asUInt8() const {
    return parseNumber<uint8_t>(_data.c_str(), _length, strtoul);
}

uint16_t SqlValue::asUInt16() const {
    return parseNumber<uint16_t>(_data.c_str(), _length, strtoul);
}

uint32_t SqlValue::asUInt32() const {
    return parseNumber<uint16_t>(_data.c_str(), _length, strtoul);
}

int8_t SqlValue::asInt8() const {
    return parseNumber<int8_t>(_data.c_str(), _length, strtol);
}

int16_t SqlValue::asInt16() const {
    return parseNumber<int16_t>(_data.c_str(), _length, strtol);
    
}

int32_t SqlValue::asInt32() const {
    return parseNumber<int32_t>(_data.c_str(), _length, strtol);
    
}

#ifdef ENVIRONMENT64

uint64_t SqlValue::asUint64() const {
    return parseNumber<int64_t>(_data.c_str(), _length, strtoul);
    
}

int64_t SqlValue::asInt64() const {
    return parseNumber<int64_t>(_data.c_str(), _length, strtol);
}

#endif

std::string SqlValue::asString() const {
    return std::string(_data);
}

Uuid SqlValue::asUuid() const {
    return Uuid::Parse(_data);
}

double_t SqlValue::asDouble() const {
    return parseNumber<double_t>(_data.c_str(), _length, strtod);
}

float_t SqlValue::asFloat() const {
    return parseNumber<double_t>(_data.c_str(), _length, strtof);
}

bool SqlValue::asBool() const {
    return !strcasecmp(_data.c_str(), "1") || !strcasecmp(_data.c_str(), "t") || !strcasecmp(_data.c_str(), "true");
}
