//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlQueryBuilder.h"
#include "PostgreSqlSelectQueryBuilder.h"
#include "PostgreSqlInsertQueryBuilder.h"
#include "PostgreSqlUpdateQueryBuilder.h"
#include "PostgreSqlDeleteQueryBuilder.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;


PostgreSqlQueryBuilder::PostgreSqlQueryBuilder(const TransformationProvider &provider) :
        SqlQueryBuilder(provider)
{

}

unique_ptr<SqlSelectQueryBuilder> PostgreSqlQueryBuilder::createSelectQueryBuilder(std::string_view tableName) const {
    return move(unique_ptr<SqlSelectQueryBuilder>{new PostgreSqlSelectQueryBuilder(_provider, tableName)});
}

unique_ptr<SqlInsertQueryBuilder> PostgreSqlQueryBuilder::createInsertQueryBuilder(std::string_view tableName) const {
    return move(unique_ptr<SqlInsertQueryBuilder>{new PostgreSqlInsertQueryBuilder(_provider, tableName)});
}

unique_ptr<SqlUpdateQueryBuilder> PostgreSqlQueryBuilder::createUpdateQueryBuilder(std::string_view tableName) const {
    return move(unique_ptr<SqlUpdateQueryBuilder>{new PostgreSqlUpdateQueryBuilder(_provider, tableName)});
}

unique_ptr<SqlDeleteQueryBuilder> PostgreSqlQueryBuilder::createDeleteQueryBuilder(std::string_view tableName) const {
    return move(unique_ptr<SqlDeleteQueryBuilder>{new PostgreSqlDeleteQueryBuilder(_provider, tableName)});
}

