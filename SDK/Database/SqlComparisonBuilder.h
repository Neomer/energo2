//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_SQLCOMPARISONBUILDER_H
#define ENERGO_SQLCOMPARISONBUILDER_H

#include "../classes.h"

namespace energo::db {

class SqlComparisonBuilder final {
    STATIC_CLASS(SqlComparisonBuilder)

public:
    [[nodiscard]] static std::string Eq(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Gr(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Ge(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Ls(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Le(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Like(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string And(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Or(std::string_view left, std::string_view right) ;

    [[nodiscard]] static std::string Not(std::string_view value) ;
};

}

#endif //ENERGO_SQLCOMPARISONBUILDER_H
