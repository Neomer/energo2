//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_POSTGRESQLUPDATEQUERYBUILDER_H
#define ENERGO_POSTGRESQLUPDATEQUERYBUILDER_H

#include "../../SqlUpdateQueryBuilder.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlUpdateQueryBuilder : public SqlUpdateQueryBuilder {
public:
    PostgreSqlUpdateQueryBuilder(const TransformationProvider &transformationProvider, std::string_view tableName);

    [[nodiscard]] std::string build() const override;
};

}

#endif //ENERGO_POSTGRESQLUPDATEQUERYBUILDER_H
