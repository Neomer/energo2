//
// Created by kir on 07.12.2019.
//

#include "SqlQuery.h"

using namespace std;
using namespace energo::db;

SqlQuery::SqlQuery(PGresult *result) :
    _result{result},
    _rowIdx{0}
{

}

uint16_t SqlQuery::getFieldsCount() const {
    return PQnfields(_result);
}

int SqlQuery::getRowsCount() const {
    return PQntuples(_result);
}

bool SqlQuery::isValid() const {
    auto status = PQresultStatus(_result);
    return status != PGRES_BAD_RESPONSE && status != PGRES_FATAL_ERROR;
}

SqlValue SqlQuery::value(int fieldIndex) const {
    return SqlValue(
            PQgetvalue(
                    _result,
                    _rowIdx,
                    fieldIndex));
}

SqlValue SqlQuery::value(string_view fieldName) const {
    return SqlValue(
            PQgetvalue(
                    _result,
                    _rowIdx,
                    PQfnumber(_result, fieldName.data())));
}

std::vector<const char *> SqlQuery::getFieldNames() const {
    std::vector<const char *> result;
    auto fields = getFieldsCount();
    for (auto idx = 0; idx < fields; ++idx) {
        result.push_back(PQfname(_result, idx));
    }
    return result;
}

bool SqlQuery::any() const {
    return PQresultStatus(_result) != PGRES_EMPTY_QUERY && getFieldsCount() > 0;
}

bool SqlQuery::next() {
    if (_rowIdx >= getRowsCount()) {
        return false;
    }
    _rowIdx++;
    return true;
}

bool SqlQuery::previous() {
    if (_rowIdx <= 0) {
        return false;
    }
    _rowIdx--;
    return true;
}
