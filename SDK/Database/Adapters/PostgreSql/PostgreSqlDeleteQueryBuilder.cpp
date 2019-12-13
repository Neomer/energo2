//
// Created by vinokurov on 13.12.2019.
//

#include <fmt/format.h>
#include "PostgreSqlDeleteQueryBuilder.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;

PostgreSqlDeleteQueryBuilder::PostgreSqlDeleteQueryBuilder(const TransformationProvider &transformationProvider, const std::string_view &tableName) :
    SqlDeleteQueryBuilder{transformationProvider, tableName}
{

}

string PostgreSqlDeleteQueryBuilder::build() const {
    std::string sql = "delete from " + _transformationProvider.escapeTableNameIfNeeded(_schema.empty() ? "public" : _schema) + "." +
            _transformationProvider.escapeTableNameIfNeeded(_tableName);

    if (!_whereClause.empty()) {
        sql += " where " + _whereClause;
    }
    if (_limit) {
        sql += " limit " + fmt::to_string(_limit.value());
    }
    return sql + ";";
}
