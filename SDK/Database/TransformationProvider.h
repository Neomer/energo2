//
// Created by vinokurov on 10.12.2019.
//

#ifndef ENERGO_TRANSFORMATIONPROVIDER_H
#define ENERGO_TRANSFORMATIONPROVIDER_H

#include <string>
#include <string_view>
#include "../global.h"

namespace energo::db {

/**
 * Хэлпер для создания корректных SQL-запросов. Содержит набор правил для экранирования наименований таблиц, колонок и пр.
 */
class EXPORTS TransformationProvider {
public:
    TransformationProvider() = default;
    virtual ~TransformationProvider() = default;

    /**
     * Экранировать наименование колонки, если это необходимо.
     * @param fieldName Наименование колонки.
     * @return
     */
    [[nodiscard]] virtual std::string EscapeFieldNameIfNeeded(std::string_view fieldName) const = 0;

    /**
     * Экранировать наименование таблицы, если это необходимо.
     * @param fieldName Наименование колонки.
     * @return
     */
    [[nodiscard]] virtual std::string EscapeTableNameIfNeeded(std::string_view tableName) const = 0;
};

}

#endif //ENERGO_TRANSFORMATIONPROVIDER_H
