//
// Created by vinokurov on 13.12.2019.
//

#include "SqlDeleteQueryBuilder.h"

using namespace std;
using namespace energo::db;

SqlDeleteQueryBuilder::SqlDeleteQueryBuilder(const TransformationProvider &transformationProvider, string_view tableName) :
        _transformationProvider(transformationProvider),
        _tableName(tableName)
{

}

SqlDeleteQueryBuilder &SqlDeleteQueryBuilder::schema(std::string_view schema) {
    _schema = schema;
    return *this;
}

SqlDeleteQueryBuilder &SqlDeleteQueryBuilder::where(std::string_view where) {
    _whereClause = where;
    return *this;
}

SqlDeleteQueryBuilder &SqlDeleteQueryBuilder::limit(size_t limit) {
    _limit = limit;
    return *this;
}
