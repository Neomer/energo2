//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_SQLCONDITIONBUILDER_H
#define ENERGO_SQLCONDITIONBUILDER_H

#include <string>
#include <string_view>
#include "../global.h"
#include "../classes.h"

namespace energo::db {

/**
 * Билдер для построения условий в SQL-запросах.
 */
class EXPORTS SqlConditionBuilder final {
    STATIC_CLASS(SqlConditionBuilder)

public:
    /**
     * Построение условия вида [left] = [right].
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Eq(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида [left] > [right].
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Gr(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида [left] >= [right].
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Ge(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида [left] < [right].
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Ls(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида [left] <= [right].
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Le(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида [left] like [right].
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Like(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида ([left]) AND ([right]).
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string And(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида ([left]) OR ([right]).
     * @param left Левая часть условия
     * @param right Правая часть условия.
     * @return
     */
    [[nodiscard]] static std::string Or(std::string_view left, std::string_view right) ;

    /**
     * Построение условия вида NOT([value]).
     * @param value Значение для отрицания.
     * @return
     */
    [[nodiscard]] static std::string Not(std::string_view value) ;
};

}

#endif //ENERGO_SQLCONDITIONBUILDER_H
