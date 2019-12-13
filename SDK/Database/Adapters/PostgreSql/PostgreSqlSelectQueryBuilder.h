//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLSELECTQUERYBUILDER_H
#define ENERGO_POSTGRESQLSELECTQUERYBUILDER_H

#include "../../SqlSelectQueryBuilder.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlSelectQueryBuilder: public SqlSelectQueryBuilder {
public:
    explicit PostgreSqlSelectQueryBuilder(const TransformationProvider &provider, std::string_view tableName);
    
    [[nodiscard]] std::string build() const override;
};

}


#endif //ENERGO_POSTGRESQLSELECTQUERYBUILDER_H
