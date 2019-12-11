//
// Created by vinokurov on 10.12.2019.
//

#include "PostgreSqlTransformationProvider.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db::adapters;

string PostgreSqlTransformationProvider::EscapeFieldNameIfNeeded(string_view fieldName) const {
    return "\""s + fieldName.data() + "\"";
}

string PostgreSqlTransformationProvider::EscapeTableNameIfNeeded(std::string_view tableName) const {
    return "\""s + tableName.data() + "\"";
}