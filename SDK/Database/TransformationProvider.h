//
// Created by vinokurov on 10.12.2019.
//

#ifndef ENERGO_TRANSFORMATIONPROVIDER_H
#define ENERGO_TRANSFORMATIONPROVIDER_H

#include <string>
#include <string_view>
#include "../Types/Uuid.h"
#include "../global.h"
#include "../os.h"

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
    [[nodiscard]] virtual std::string escapeFieldNameIfNeeded(std::string_view fieldName) const = 0;

    /**
     * Экранировать наименование таблицы, если это необходимо.
     * @param fieldName Наименование колонки.
     * @return
     */
    [[nodiscard]] virtual std::string escapeTableNameIfNeeded(std::string_view tableName) const = 0;

    [[nodiscard]] virtual std::string formatValue(uint8_t value) const;

    [[nodiscard]] virtual std::string formatValue(uint16_t value) const;

    [[nodiscard]] virtual std::string formatValue(uint32_t value) const;

    [[nodiscard]] virtual std::string formatValue(int8_t value) const;

    [[nodiscard]] virtual std::string formatValue(int16_t value) const;

    [[nodiscard]] virtual std::string formatValue(int32_t value) const;

#ifdef ENVIRONMENT64
    [[nodiscard]] virtual std::string formatValue(uint64_t value) const;

    [[nodiscard]] virtual std::string formatValue(int64_t value) const;
#endif

    [[nodiscard]] virtual std::string formatValue(const energo::types::Uuid &value) const;

    [[nodiscard]] virtual std::string formatValue(std::string_view value) const;

    [[nodiscard]] virtual std::string formatValue(float value) const;

    [[nodiscard]] virtual std::string formatValue(double value) const;
};

}

#endif //ENERGO_TRANSFORMATIONPROVIDER_H
