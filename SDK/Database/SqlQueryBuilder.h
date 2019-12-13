//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_SQLQUERYBUILDER_H
#define ENERGO_SQLQUERYBUILDER_H

#include <memory>
#include <string_view>
#include "TransformationProvider.h"
#include "SqlSelectQueryBuilder.h"
#include "SqlInsertQueryBuilder.h"
#include "SqlUpdateQueryBuilder.h"
#include "SqlDeleteQueryBuilder.h"

namespace energo::db {

/**
 * Абстрактный класс для билдеров SQL-запросов.
 */
class EXPORTS SqlQueryBuilder {
protected:
    const TransformationProvider &_provider;
    
public:
    explicit SqlQueryBuilder(const TransformationProvider &provider);
    virtual ~SqlQueryBuilder() = default;

    /**
     * Создает билдер для Select запроса.
     * @param tableName Наименование таблицы
     * @return
     */
    [[nodiscard]] virtual std::unique_ptr<SqlSelectQueryBuilder> createSelectQueryBuilder(std::string_view tableName) const = 0;

    /**
     * Создает билдер для Insert запроса.
     * @param tableName Наименование таблицы
     * @return
     */
    [[nodiscard]] virtual std::unique_ptr<SqlInsertQueryBuilder> createInsertQueryBuilder(std::string_view tableName) const = 0;

    /**
     * Создает билдер для Update запроса.
     * @param tableName Наименование таблицы
     * @return
     */
    [[nodiscard]] virtual std::unique_ptr<SqlUpdateQueryBuilder> createUpdateQueryBuilder(std::string_view tableName) const = 0;

    /**
     * Создает билдер для Delete запроса.
     * @param tableName Наименование таблицы
     * @return
     */
    [[nodiscard]] virtual std::unique_ptr<SqlDeleteQueryBuilder> createDeleteQueryBuilder(std::string_view tableName) const = 0;
};

}

#endif //ENERGO_SQLQUERYBUILDER_H
