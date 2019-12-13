//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_SQLDELETEQUERYBUILDER_H
#define ENERGO_SQLDELETEQUERYBUILDER_H

#include <optional>
#include "TransformationProvider.h"

namespace energo::db {

class SqlDeleteQueryBuilder {

protected:
    const TransformationProvider &_transformationProvider;
    std::string _tableName;
    std::string _schema, _whereClause;
    std::optional<size_t> _limit;

public:
    SqlDeleteQueryBuilder(const TransformationProvider &transformationProvider, std::string_view tableName);

    SqlDeleteQueryBuilder &schema(std::string_view schema);

    SqlDeleteQueryBuilder &where(std::string_view where);

    SqlDeleteQueryBuilder &limit(size_t limit);

    [[nodiscard]] virtual std::string build() const = 0;
};

}


#endif //ENERGO_SQLDELETEQUERYBUILDER_H
