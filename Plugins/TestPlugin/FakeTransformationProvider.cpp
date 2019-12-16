//
// Created by kir on 16.12.2019.
//

#include "FakeTransformationProvider.h"

using namespace std;
using namespace energo::db::adapters;

string FakeTransformationProvider::escapeFieldNameIfNeeded(string_view fieldName) const {
    return string{fieldName};
}

string FakeTransformationProvider::escapeTableNameIfNeeded(string_view tableName) const {
    return string{tableName};
}
