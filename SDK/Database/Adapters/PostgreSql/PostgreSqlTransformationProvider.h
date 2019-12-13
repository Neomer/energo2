//
// Created by vinokurov on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLTRANSFORMATIONPROVIDER_H
#define ENERGO_POSTGRESQLTRANSFORMATIONPROVIDER_H

#include "../../../global.h"
#include "../../TransformationProvider.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlTransformationProvider: public TransformationProvider {
public:
    PostgreSqlTransformationProvider() = default;
    ~PostgreSqlTransformationProvider() override = default;

    [[nodiscard]] std::string escapeFieldNameIfNeeded(std::string_view fieldName) const override;

    [[nodiscard]] std::string escapeTableNameIfNeeded(std::string_view tableName) const override;
};

}

#endif //ENERGO_POSTGRESQLTRANSFORMATIONPROVIDER_H
