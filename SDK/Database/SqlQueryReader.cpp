//
// Created by vinokurov on 09.12.2019.
//

#include <stdexcept>
#include "SqlQueryReader.h"
#include "TransformationProvider.h"

using namespace std;
using namespace energo::db;

SqlQueryReader::SqlQueryReader(PGresult *result, int row) :
        _result{result},
        _rowIdx{row}
{

}

uint16_t SqlQueryReader::getFieldsCount() const {
    return PQnfields(_result);
}

SqlValue SqlQueryReader::value(int fieldIndex) const {
    return SqlValue(
            PQgetvalue(
                    _result,
                    _rowIdx,
                    fieldIndex));
}

SqlValue SqlQueryReader::value(string_view fieldName) const {
    auto fieldIdx = PQfnumber(_result, fieldName.data());
    if (fieldIdx == -1) {
        throw range_error("Колонки с указанным наименованием не найдено.");
    }
    return SqlValue(
            PQgetvalue(
                    _result,
                    _rowIdx,
                    fieldIdx));
}

std::vector<const char *> SqlQueryReader::getFieldNames() const {
    std::vector<const char *> result;
    auto fields = getFieldsCount();
    for (auto idx = 0; idx < fields; ++idx) {
        result.push_back(PQfname(_result, idx));
    }
    return result;
}

