//
// Created by vinokurov on 13.12.2019.
//

#include <fmt/format.h>
#include "SqlComparisonBuilder.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;

std::string SqlComparisonBuilder::Eq(std::string_view left, std::string_view right) {
    return fmt::format("{0}={1}",
                       left,
                       right);
}

std::string SqlComparisonBuilder::Gr(std::string_view left, std::string_view right) {
    return fmt::format("{0}>{1}",
                       left,
                       right);
}

std::string SqlComparisonBuilder::Ge(std::string_view left, std::string_view right) {
    return fmt::format("{0}>={1}",
                       left,
                       right);
}

std::string SqlComparisonBuilder::Ls(std::string_view left, std::string_view right) {
    return fmt::format("{0}<{1}",
                       left,
                       right);
}

std::string SqlComparisonBuilder::Le(std::string_view left, std::string_view right) {
    return fmt::format("{0}<={1}",
                       left,
                       right);
}

std::string SqlComparisonBuilder::Like(std::string_view left, std::string_view right) {
    return fmt::format("{0} like {1}",
                       left,
                       right);
}

std::string SqlComparisonBuilder::And(std::string_view left, std::string_view right) {
    return fmt::format("({0}) AND ({1})",
            left,
            right);
}

std::string SqlComparisonBuilder::Or(std::string_view left, std::string_view right) {
    return fmt::format("({0}) OR ({1})",
                       left,
                       right);
}

std::string SqlComparisonBuilder::Not(std::string_view value) {
    return fmt::format("NOT({0})", value);
}
