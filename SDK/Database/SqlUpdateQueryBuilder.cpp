//
// Created by vinokurov on 13.12.2019.
//

#include <fmt/format.h>
#include "SqlUpdateQueryBuilder.h"

using namespace std;
using namespace energo::db;


SqlUpdateQueryBuilder::SqlUpdateQueryBuilder(const energo::db::TransformationProvider &transformationProvider, string_view tableName) :
        _transformationProvider(transformationProvider),
        _tableName(tableName)
{

}

SqlUpdateQueryBuilder &SqlUpdateQueryBuilder::schema(std::string_view schema) {
    _schema = schema;
    return *this;
}

SqlUpdateQueryBuilder &SqlUpdateQueryBuilder::where(std::string_view where) {
    _whereClause = where;
    return *this;
}

/*
SqlUpdateQueryBuilder &SqlUpdateQueryBuilder::values(std::vector<std::pair<std::string_view, std::string_view>> values) {
    _values = "";
    for (auto it = values.begin(); it != values.end(); ++it) {
        auto value = *it;
        _values += fmt::format("{0}={1}",
                _transformationProvider.escapeFieldNameIfNeeded(value.first.data()),
                value.second);
        if (std::next(it) != values.end()) {
            _values += ", ";
        }
    }
    return *this;
}
 */

SqlUpdateQueryBuilder &SqlUpdateQueryBuilder::limit(size_t limit) {
    _limit = limit;
    return *this;
}

SqlUpdateQueryBuilder &SqlUpdateQueryBuilder::values(std::vector<std::pair<std::string, std::string>> values) {
    _values = "";
    for (auto it = values.begin(); it != values.end(); ++it) {
        auto value = *it;
        _values += fmt::format("{0}={1}",
                               _transformationProvider.escapeFieldNameIfNeeded(value.first.data()),
                               value.second);
        if (std::next(it) != values.end()) {
            _values += ", ";
        }
    }
    return *this;
}
