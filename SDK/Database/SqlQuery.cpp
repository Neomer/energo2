//
// Created by kir on 07.12.2019.
//

#include <stdexcept>
#include "SqlQuery.h"

using namespace std;
using namespace energo::db;
using namespace string_literals;

SqlQuery::SqlQuery(std::unique_ptr<DatabaseResultAdapter> adapter) :
    _adapter{std::move(adapter)},
    _rowIdx{0}
{

}

int SqlQuery::getRowsCount() const {
    return _adapter->getRowsCount();
}

bool SqlQuery::isValid() const {
    return _adapter->isValid();
}

bool SqlQuery::any() const {
    return _adapter->any();
}

bool SqlQuery::next() {
    if (getRowsCount() - _rowIdx <= 1) {
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

SqlQueryReader SqlQuery::getReader() const {
    return SqlQueryReader(_adapter, _rowIdx);
}

SqlQueryReader SqlQuery::getReader(int row) const {
    if (row < 0 || row >= getRowsCount()) {
        throw range_error("Индекс строки: "s + to_string(row) + " входит за диапазон допустимх значений.");
    }
    return SqlQueryReader(_adapter, row);
}
