//
// Created by vinokurov on 13.12.2019.
//

#include <fmt/format.h>
#include "SqlConditionBuilder.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;

std::string SqlConditionBuilder::Eq(std::string_view left, std::string_view right) {
    return fmt::format("{0}={1}",
                       left,
                       right);
}

std::string SqlConditionBuilder::Gr(std::string_view left, std::string_view right) {
    return fmt::format("{0}>{1}",
                       left,
                       right);
}

std::string SqlConditionBuilder::Ge(std::string_view left, std::string_view right) {
    return fmt::format("{0}>={1}",
                       left,
                       right);
}

std::string SqlConditionBuilder::Ls(std::string_view left, std::string_view right) {
    return fmt::format("{0}<{1}",
                       left,
                       right);
}

std::string SqlConditionBuilder::Le(std::string_view left, std::string_view right) {
    return fmt::format("{0}<={1}",
                       left,
                       right);
}

std::string SqlConditionBuilder::Like(std::string_view left, std::string_view right) {
    return fmt::format("{0} like {1}",
                       left,
                       right);
}

std::string SqlConditionBuilder::And(std::string_view left, std::string_view right) {
    return fmt::format("({0}) AND ({1})",
            left,
            right);
}

std::string SqlConditionBuilder::Or(std::string_view left, std::string_view right) {
    return fmt::format("({0}) OR ({1})",
                       left,
                       right);
}

std::string SqlConditionBuilder::Not(std::string_view value) {
    return fmt::format("NOT({0})", value);
}
