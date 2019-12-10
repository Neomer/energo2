//
// Created by vinokurov on 09.12.2019.
//

#include <stdexcept>
#include "SqlQueryReader.h"
#include "TransformationProvider.h"

using namespace std;
using namespace energo::db;

SqlQueryReader::SqlQueryReader(shared_ptr<DatabaseResultAdapter> adapter, int row) :
        _adapter{adapter},
        _rowIdx{row}
{

}

uint16_t SqlQueryReader::getFieldsCount() const {
    return _adapter->getFieldsCount();
}

SqlValue SqlQueryReader::value(int fieldIndex) const {
    return _adapter->value(fieldIndex, _rowIdx);
}

SqlValue SqlQueryReader::value(string_view fieldName) const {
    auto fieldIdx = _adapter->getFieldIndexByName(fieldName);
    if (fieldIdx == -1) {
        throw range_error("Колонки с указанным наименованием не найдено.");
    }
    return _adapter->value(fieldIdx, _rowIdx);
}

void SqlQueryReader::getFieldNames(std::vector<const char *> &fields) const {
    _adapter->getFieldNames(fields);
}

