//
// Created by kir on 10.12.2019.
//

#include "DatabaseSelectQueryBuilder.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;

DatabaseSelectQueryBuilder::DatabaseSelectQueryBuilder(const TransformationProvider &provider):
    _provider{provider}
{
    _fields.reserve(256);
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::tableName(std::string_view tableName) {
    _tableName = tableName;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::rawFilter(std::string_view whereClause) {
    _whereClause = whereClause;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::fields(std::string_view rawFields) {
    _fields = rawFields;
    return *this;
}

DatabaseSelectQueryBuilder &DatabaseSelectQueryBuilder::fields(const vector<pair<string_view, optional<string_view>>> &fields) {
    _fields = "";
    for (auto &field : fields) {
        _fields += _provider.EscapeFieldNameIfNeeded(field.first.data());
        if (field.second) {
            _fields += " as "s + _provider.EscapeFieldNameIfNeeded(field.second.value());
        }
        _fields += ", ";
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

