//
// Created by kir on 10.12.2019.
//

#include "DatabaseSelectQueryBuilder.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;

DatabaseSelectQueryBuilder::DatabaseSelectQueryBuilder(const TransformationProvider &provider, std::string_view tableName):
        _provider{provider},
        _tableName{tableName},
        _limit{nullopt},
        _offset{nullopt}
{
    _fields.reserve(256);
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::where(std::string_view where) {
    _whereClause = where;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::fields(std::string_view rawFields) {
    _fields = rawFields;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::fields(const vector<pair<string_view, optional<string_view>>> &fields) {
    _fields = "";
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        auto field = *it;
        _fields += _provider.EscapeFieldNameIfNeeded(field.first.data());
        if (field.second) {
            _fields += " as "s + _provider.EscapeFieldNameIfNeeded(field.second.value());
        }
        if (std::next(it) != fields.end()) {
            _fields += ", ";
        }
    }
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::limit(size_t limit) {
    _limit = limit;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::schema(std::string_view schema) {
    _schema = schema;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::offset(size_t offset) {
    _offset = offset;
    return *this;
}

