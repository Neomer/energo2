//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_POSTGRESQLINSERTQUERYBUILDER_H
#define ENERGO_POSTGRESQLINSERTQUERYBUILDER_H

#include "../../SqlInsertQueryBuilder.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlInsertQueryBuilder : public SqlInsertQueryBuilder {
public:
    PostgreSqlInsertQueryBuilder(const TransformationProvider &provider, const std::string_view &tableName);

    std::string build() const override;
};

}

#endif //ENERGO_POSTGRESQLINSERTQUERYBUILDER_H
