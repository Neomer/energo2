//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLQUERYBUILDER_H
#define ENERGO_POSTGRESQLQUERYBUILDER_H

#include "../../DatabaseQueryBuilder.h"

namespace energo::db::adapters {

class PostgreSqlQueryBuilder: DatabaseQueryBuilder {
public:
    explicit PostgreSqlQueryBuilder(const TransformationProvider &provider);
    
    [[nodiscard]] std::unique_ptr<DatabaseSelectQueryBuilder> createSelectQueryBuilder(std::string_view tableName) const override;
};

}

#endif //ENERGO_POSTGRESQLQUERYBUILDER_H
