//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_SQLINSERTQUERYBUILDER_H
#define ENERGO_SQLINSERTQUERYBUILDER_H

#include <vector>
#include "TransformationProvider.h"

namespace energo::db {

class EXPORTS SqlInsertQueryBuilder {
protected:
    const TransformationProvider &_provider;
    std::string _fields, _returns, _schema;
    std::vector<std::string> _values;
    std::string _tableName;


public:
    explicit SqlInsertQueryBuilder(const TransformationProvider &provider, std::string_view tableName);

    SqlInsertQueryBuilder &schema(std::string_view schema);

    SqlInsertQueryBuilder &fields(std::string_view fields);

    SqlInsertQueryBuilder &fields(std::vector<std::string> fields);

    SqlInsertQueryBuilder &values(std::vector<std::string> values);

    SqlInsertQueryBuilder &returns(std::vector<std::string> fields);

    [[nodiscard]] virtual std::string build() const = 0;
};

}

#endif //ENERGO_SQLINSERTQUERYBUILDER_H
