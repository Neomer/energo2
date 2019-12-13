//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_SQLSELECTQUERYBUILDER_H
#define ENERGO_SQLSELECTQUERYBUILDER_H

#include <string_view>
#include <vector>
#include <utility>
#include <optional>
#include "TransformationProvider.h"

namespace energo::db {

/**
 * Абстрактный билдер для Select запроса.
 */
class EXPORTS SqlSelectQueryBuilder {
protected:
    const TransformationProvider &_provider;
    std::string _tableName;
    std::string _whereClause;
    std::string _schema;
    std::string _fields;
    std::optional<size_t> _limit;
    std::optional<size_t> _offset;
    
public:
    /**
     * Класс для алиасов таблиц.
     */
    using TFieldWithAliasList = std::vector<std::pair<std::string_view, std::optional<std::string_view>>>;

    explicit SqlSelectQueryBuilder(const TransformationProvider &provider, std::string_view tableName);

    SqlSelectQueryBuilder &where(std::string_view where);
    
    SqlSelectQueryBuilder &fields(const TFieldWithAliasList &fields);
    
    SqlSelectQueryBuilder &fields(std::string_view rawFields);
    
    SqlSelectQueryBuilder &limit(size_t limit);

    SqlSelectQueryBuilder &offset(size_t offset);
    
    SqlSelectQueryBuilder &schema(std::string_view schema);
    
    [[nodiscard]] virtual std::string build() const = 0;
};

}

#endif //ENERGO_SQLSELECTQUERYBUILDER_H
