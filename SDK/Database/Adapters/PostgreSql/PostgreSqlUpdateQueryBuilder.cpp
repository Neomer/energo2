//
// Created by vinokurov on 13.12.2019.
//

#include <fmt/format.h>
#include "PostgreSqlUpdateQueryBuilder.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;

PostgreSqlUpdateQueryBuilder::PostgreSqlUpdateQueryBuilder(const TransformationProvider &transformationProvider, string_view tableName) :
        SqlUpdateQueryBuilder(transformationProvider, tableName)
{

}

string PostgreSqlUpdateQueryBuilder::build() const {
    std::string sql = "update " +
            _transformationProvider.escapeFieldNameIfNeeded(_schema.empty() ? "public" : _schema) + "." +
            _transformationProvider.escapeTableNameIfNeeded(_tableName) + " set " + _values;

    if (!_whereClause.empty()) {
        sql += " where " + _whereClause;
    }
    if (_limit) {
        sql += " limit " + fmt::to_string(_limit.value());
    }
    return sql + ";";
}
