//
// Created by vinokurov on 10.12.2019.
//

#include "TransformationProvider.h"

using namespace std;
using namespace energo::db;
using namespace std::string_literals;

string TransformationProvider::EscapeFieldNameIfNeeded(string_view fieldName) const {
    return "\""s + fieldName.data() + "\"";
}

std::string TransformationProvider::EscapeTableNameIfNeeded(std::string_view tableName) const {
    return "\""s + tableName.data() + "\"";
}
