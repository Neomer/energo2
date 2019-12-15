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

SqlInsertQueryBuilder &SqlInsertQueryBuilder::fields(std::vector<std::string> fields) {
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

SqlInsertQueryBuilder &SqlInsertQueryBuilder::values(std::vector<std::string> values) {
    string value;
    for (auto it = values.begin(); it != values.end(); ++it) {
        value += *it;
        if (next(it) != values.end()) {
            value += ", ";
        }
    }
    _values.push_back(value);
    return *this;
}

SqlInsertQueryBuilder &SqlInsertQueryBuilder::returns(std::vector<std::string> fields) {
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
