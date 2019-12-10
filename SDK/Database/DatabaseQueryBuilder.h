//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_DATABASEQUERYBUILDER_H
#define ENERGO_DATABASEQUERYBUILDER_H

#include <memory>
#include <string_view>
#include "TransformationProvider.h"
#include "DatabaseSelectQueryBuilder.h"

namespace energo::db {

class DatabaseQueryBuilder {
protected:
    const TransformationProvider &_provider;
    
public:
    explicit DatabaseQueryBuilder(const TransformationProvider &provider);
    virtual ~DatabaseQueryBuilder() = default;
    
    [[nodiscard]] virtual std::unique_ptr<DatabaseSelectQueryBuilder> createSelectQueryBuilder(std::string_view tableName) const = 0;
    
};

}

#endif //ENERGO_DATABASEQUERYBUILDER_H
