//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLQUERYBUILDER_H
#define ENERGO_POSTGRESQLQUERYBUILDER_H

#include "../../SqlQueryBuilder.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlQueryBuilder: public SqlQueryBuilder {
public:
    explicit PostgreSqlQueryBuilder(const TransformationProvider &provider);
    
    [[nodiscard]] std::unique_ptr<SqlSelectQueryBuilder> createSelectQueryBuilder(std::string_view tableName) const override;
};

}

#endif //ENERGO_POSTGRESQLQUERYBUILDER_H
