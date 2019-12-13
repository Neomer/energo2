//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_SQLUPDATEQUERYBUILDER_H
#define ENERGO_SQLUPDATEQUERYBUILDER_H

#include <optional>
#include <utility>
#include "TransformationProvider.h"

namespace energo::db {

class EXPORTS SqlUpdateQueryBuilder {
protected:
    const TransformationProvider &_transformationProvider;
    std::string _tableName;
    std::string _whereClause, _schema, _values;
    std::optional<size_t> _limit;

public:
    SqlUpdateQueryBuilder(const TransformationProvider &transformationProvider, std::string_view tableName);

    SqlUpdateQueryBuilder &schema(std::string_view schema);

    SqlUpdateQueryBuilder &where(std::string_view where);

    SqlUpdateQueryBuilder &values(std::vector<std::pair<std::string_view, std::string_view>> values);

    SqlUpdateQueryBuilder &limit(size_t limit);

    [[nodiscard]] virtual std::string build() const = 0;
};

}

#endif //ENERGO_SQLUPDATEQUERYBUILDER_H
