//
// Created by kir on 10.12.2019.
//

#include "SqlSelectQueryBuilder.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;

SqlSelectQueryBuilder::SqlSelectQueryBuilder(const TransformationProvider &provider, std::string_view tableName):
        _provider{provider},
        _tableName{tableName},
        _limit{nullopt},
        _offset{nullopt}
{
    _fields.reserve(256);
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::where(std::string_view where) {
    _whereClause = where;
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::fields(std::string_view rawFields) {
    _fields = rawFields;
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::fields(const vector<pair<string_view, optional<string_view>>> &fields) {
    _fields = "";
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        auto field = *it;
        _fields += _provider.escapeFieldNameIfNeeded(field.first.data());
        if (field.second) {
            _fields += " as "s + _provider.escapeFieldNameIfNeeded(field.second.value());
        }
        if (std::next(it) != fields.end()) {
            _fields += ", ";
        }
    }
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::limit(size_t limit) {
    _limit = limit;
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::schema(std::string_view schema) {
    _schema = schema;
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::offset(size_t offset) {
    _offset = offset;
    return *this;
}

