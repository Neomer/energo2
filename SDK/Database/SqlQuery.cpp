//
// Created by kir on 07.12.2019.
//

#include <stdexcept>
#include "SqlQuery.h"

using namespace std;
using namespace energo::db;
using namespace string_literals;

SqlQuery::SqlQuery(PGresult *result) :
    _result{result},
    _rowIdx{0}
{

}

int SqlQuery::getRowsCount() const {
    return PQntuples(_result);
}

bool SqlQuery::isValid() const {
    auto status = PQresultStatus(_result);
    return status != PGRES_BAD_RESPONSE && status != PGRES_FATAL_ERROR;
}

bool SqlQuery::any() const {
    return PQresultStatus(_result) != PGRES_EMPTY_QUERY && getRowsCount() > 0;
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

SqlQuery::~SqlQuery() {
    PQclear(_result);
}

SqlQueryReader SqlQuery::getReader() const {
    return SqlQueryReader(_result, _rowIdx);
}

SqlQueryReader SqlQuery::getReader(int row) const {
    if (row < 0 || row >= getRowsCount()) {
        throw range_error("Индекс строки: "s + to_string(row) + " входит за диапазон допустимх значений.");
    }
    return SqlQueryReader(_result, row);
}
