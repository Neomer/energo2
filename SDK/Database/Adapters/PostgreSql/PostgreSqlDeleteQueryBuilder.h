//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_POSTGRESQLDELETEQUERYBUILDER_H
#define ENERGO_POSTGRESQLDELETEQUERYBUILDER_H

#include "../../SqlDeleteQueryBuilder.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlDeleteQueryBuilder : public SqlDeleteQueryBuilder {
public:
    PostgreSqlDeleteQueryBuilder(const TransformationProvider &transformationProvider, const std::string_view &tableName);

    [[nodiscard]] std::string build() const override;
};

}

#endif //ENERGO_POSTGRESQLDELETEQUERYBUILDER_H
