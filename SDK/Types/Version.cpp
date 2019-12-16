//
// Created by kir on 15.12.2019.
//

#include <fmt/format.h>
#include <stdexcept>
#include "Version.h"

using namespace std;
using namespace energo::types;

Version::Version(uint16_t major, uint16_t minor, uint32_t patch, uint32_t build) :
    _major{major}, _minor{minor}, _patch{patch}, _build{build}
{

}

Version::Version() :
    _major{1}, _minor{0}, _patch{0}, _build{0}
{

}

inline bool is_valid_number(char sym) {
    return sym >= '0' && sym <= '9';
}

uint32_t parseNumber(const char **ptr) {
    uint32_t value = 0;
    while (is_valid_number(**ptr)) {
        value = value * 10 + (**ptr - '0');
        (*ptr)++;
    }
    return value;
}

bool Version::TryParse(std::string_view version, Version &result) {
    const char *ptr = version.data();
    
    // Пропускаем идущие вначале пробелы
    while (*ptr == ' ') {
        ++ptr;
    }
    if (!is_valid_number(*ptr)) {
        return false;
    }
    
    // Парсим мажор
    result._major = parseNumber(&ptr);
    if (*ptr == 0) {
        return true;
    }
    if (*ptr != '.') {
        return false;
    }
    ++ptr;
    if (!is_valid_number(*ptr)) {
        return false;
    }
    
    // Парсим минор
    result._minor = parseNumber(&ptr);
    if (*ptr == 0) {
        return true;
    }
    if (*ptr != '.') {
        return false;
    }
    ++ptr;
    if (!is_valid_number(*ptr)) {
        return false;
    }
    
    // Парсим патч
    result._patch = parseNumber(&ptr);
    
    if (*ptr == 0) {
        return true;
    }
    
    while (*ptr == ' ') {
        ++ptr;
    }
    if (*ptr == 0) {
        return true;
    }
    if (!is_valid_number(*ptr)) {
        return false;
    }
    result._build = parseNumber(&ptr);
    return true;
}

Version Version::Parse(std::string_view version) {
    Version instance;
    if (!TryParse(version, instance)) {
        throw invalid_argument("");
    }
    return instance;
}

uint16_t Version::getMajor() const {
    return _major;
}

void Version::setMajor(uint16_t major) {
    _major = major;
}

uint16_t Version::getMinor() const {
    return _minor;
}

void Version::setMinor(uint16_t minor) {
    _minor = minor;
}

uint32_t Version::getPatch() const {
    return _patch;
}

void Version::setPatch(uint32_t patch) {
    _patch = patch;
}

uint32_t Version::getBuild() const {
    return _build;
}

void Version::setBuild(uint32_t build) {
    _build = build;
}

std::string Version::toString() const {
    return (_build > 0) ? fmt::format("{}.{}.{} {}", _major, _minor, _patch, _build) : fmt::format("{}.{}.{}", _major, _minor, _patch);
}
