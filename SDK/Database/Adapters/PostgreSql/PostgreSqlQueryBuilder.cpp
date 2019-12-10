//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlQueryBuilder.h"
#include "PostgreSqlSelectQueryBuilder.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;


PostgreSqlQueryBuilder::PostgreSqlQueryBuilder(const TransformationProvider &provider) :
    DatabaseQueryBuilder(provider)
{

}

unique_ptr<DatabaseSelectQueryBuilder> PostgreSqlQueryBuilder::createSelectQueryBuilder() const {
    return move(unique_ptr<DatabaseSelectQueryBuilder>{new PostgreSqlSelectQueryBuilder(_provider)});
}

