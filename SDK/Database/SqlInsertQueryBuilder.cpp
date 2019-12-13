//
// Created by vinokurov on 13.12.2019.
//

#include "SqlInsertQueryBuilder.h"

using namespace std;
using namespace energo::db;

SqlInsertQueryBuilder::SqlInsertQueryBuilder(const TransformationProvider &provider, std::string_view tableName) :
    _provider{provider},
    _tableName{tableName}
{

}

SqlInsertQueryBuilder &SqlInsertQueryBuilder::fields(std::string_view fields) {
    _fields = fields;
    return *this;
}

SqlInsertQueryBuilder &SqlInsertQueryBuilder::fields(std::vector<std::string_view> fields) {
    _fields = "";
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        auto field = *it;
        _fields += _provider.escapeFieldNameIfNeeded(field.data());
        if (next(it) != fields.end()) {
            _fields += ", ";
        }
    }
    return *this;
}

SqlInsertQueryBuilder &SqlInsertQueryBuilder::values(std::vector<std::string_view> values) {
    _values = "";
    for (auto it = values.begin(); it != values.end(); ++it) {
        auto field = *it;
        _values += field.data();
        if (next(it) != values.end()) {
            _values += ", ";
        }
    }
    return *this;
}

SqlInsertQueryBuilder &SqlInsertQueryBuilder::returns(std::vector<std::string_view> fields) {
    _returns = "";
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        auto field = *it;
        _returns += _provider.escapeFieldNameIfNeeded(field);
        if (next(it) != fields.end()) {
            _returns += ", ";
        }
    }
    return *this;
}

SqlInsertQueryBuilder &SqlInsertQueryBuilder::schema(std::string_view schema) {
    _schema = schema;
    return *this;
}
