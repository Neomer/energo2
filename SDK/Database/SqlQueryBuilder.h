//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_SQLQUERYBUILDER_H
#define ENERGO_SQLQUERYBUILDER_H

#include <memory>
#include <string_view>
#include "TransformationProvider.h"
#include "SqlSelectQueryBuilder.h"

namespace energo::db {

class EXPORTS SqlQueryBuilder {
protected:
    const TransformationProvider &_provider;
    
public:
    explicit SqlQueryBuilder(const TransformationProvider &provider);
    virtual ~SqlQueryBuilder() = default;
    
    [[nodiscard]] virtual std::unique_ptr<SqlSelectQueryBuilder> createSelectQueryBuilder(std::string_view tableName) const = 0;
    
};

}

#endif //ENERGO_SQLQUERYBUILDER_H
