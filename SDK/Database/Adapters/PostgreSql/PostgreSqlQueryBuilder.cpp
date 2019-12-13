//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlQueryBuilder.h"
#include "PostgreSqlSelectQueryBuilder.h"

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

