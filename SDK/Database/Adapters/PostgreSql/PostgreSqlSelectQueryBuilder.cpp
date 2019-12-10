//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlSelectQueryBuilder.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;
using namespace energo::db::adapters;

PostgreSqlSelectQueryBuilder::PostgreSqlSelectQueryBuilder(const TransformationProvider &provider, std::string_view tableName) :
    DatabaseSelectQueryBuilder(provider, tableName)
{

}

string PostgreSqlSelectQueryBuilder::build() const {
    std::string sql;
    sql.reserve(512);
    if (_tableName.empty()) {
        throw runtime_error("Имя таблицы не задано.");
    }
    
    sql +=  "select " + (_fields.empty() ? "*" : _fields);
    sql += " from " + _provider.EscapeTableNameIfNeeded(_schema.empty() ? "public" : _schema) + "." + _provider.EscapeTableNameIfNeeded(_tableName);
    if (!_whereClause.empty()) {
        sql += " where " + _whereClause;
    }
    sql += ";";
    return sql;
}
