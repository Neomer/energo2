//
// Created by vinokurov on 10.12.2019.
//

#include <fmt/format.h>
#include "TransformationProvider.h"

std::string energo::db::TransformationProvider::formatValue(uint8_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(uint16_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(uint32_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(int8_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(int16_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(int32_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(uint64_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(int64_t value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(const energo::types::Uuid &value) const {
    return fmt::format(R"('{0}')", value.toString());
}

std::string energo::db::TransformationProvider::formatValue(std::string_view value) const {
    return fmt::format(R"('{0}')", value);
}

std::string energo::db::TransformationProvider::formatValue(float value) const {
    return fmt::to_string(value);
}

std::string energo::db::TransformationProvider::formatValue(double value) const {
    return fmt::to_string(value);
}
