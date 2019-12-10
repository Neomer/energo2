//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLSELECTQUERYBUILDER_H
#define ENERGO_POSTGRESQLSELECTQUERYBUILDER_H

#include "../../DatabaseSelectQueryBuilder.h"

namespace energo::db::adapters {

class PostgreSqlSelectQueryBuilder: public DatabaseSelectQueryBuilder {
public:
    explicit PostgreSqlSelectQueryBuilder(const TransformationProvider &provider);
    
    [[nodiscard]] std::string build() const override;
};

}


#endif //ENERGO_POSTGRESQLSELECTQUERYBUILDER_H
