//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_DATABASESELECTQUERYBUILDER_H
#define ENERGO_DATABASESELECTQUERYBUILDER_H

#include <string_view>
#include <vector>
#include <utility>
#include <optional>
#include "TransformationProvider.h"

namespace energo::db {

class DatabaseSelectQueryBuilder {
protected:
    const TransformationProvider &_provider;
    std::string _tableName;
    std::string _whereClause;
    std::string _fields;
    std::string _schema;
    std::optional<size_t> _limit;
    std::optional<size_t> _offset;
    
public:
    using TFieldWithAliasList = std::vector<std::pair<std::string_view, std::optional<std::string_view>>>;

    explicit DatabaseSelectQueryBuilder(const TransformationProvider &provider, std::string_view tableName);
    
    DatabaseSelectQueryBuilder &where(std::string_view where);
    
    DatabaseSelectQueryBuilder &fields(const TFieldWithAliasList &fields);
    
    DatabaseSelectQueryBuilder &fields(std::string_view rawFields);
    
    DatabaseSelectQueryBuilder &limit(size_t limit);

    DatabaseSelectQueryBuilder &offset(size_t offset);
    
    DatabaseSelectQueryBuilder &schema(std::string_view schema);
    
    [[nodiscard]] virtual std::string build() const = 0;
};

}

#endif //ENERGO_DATABASESELECTQUERYBUILDER_H
