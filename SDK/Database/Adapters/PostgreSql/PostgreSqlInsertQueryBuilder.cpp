//
// Created by vinokurov on 13.12.2019.
//

#include <fmt/format.h>
#include "PostgreSqlInsertQueryBuilder.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;

PostgreSqlInsertQueryBuilder::PostgreSqlInsertQueryBuilder(const TransformationProvider &provider, const string_view &tableName) :
        SqlInsertQueryBuilder(provider, tableName)
{

}

string PostgreSqlInsertQueryBuilder::build() const {
    std::string sql = "insert into ";
    sql.reserve(512);

    sql += _provider.escapeTableNameIfNeeded(_schema.empty() ? "public" : _schema) + ".";
    sql += _provider.escapeTableNameIfNeeded(_tableName);
    if (!_fields.empty()) {
        sql += " (" + _fields + ")";
    }
    sql += " values (" + _values + ")";
    if (!_returns.empty()) {
        sql += " returns "s + _returns + ";";
    } else {
        sql += ";";
    }
    return sql;
}
