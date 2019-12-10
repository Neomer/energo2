//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_SQLQUERYREADER_H
#define ENERGO_SQLQUERYREADER_H

#include <memory>
#include <vector>
#include <cinttypes>
#include "DatabaseResultAdapter.h"
#include "SqlValue.h"

namespace energo::db {

class EXPORTS SqlQueryReader {
    std::shared_ptr<DatabaseResultAdapter> _adapter;
    int _rowIdx;

public:
    SqlQueryReader(std::shared_ptr<DatabaseResultAdapter> adapter, int row);

    /**
     * @return Количество колонок в результате.
     */
    [[nodiscard]] uint16_t getFieldsCount() const;

    /**
     * @param fieldIndex Номер колонки.
     * @return Значение указанной колонки в текущей строке. Поменять значение текущей строки можно с помощью методов next() и previous().
     */
    [[nodiscard]] SqlValue value(int fieldIndex) const;

    /**
     * @param fieldIndex Наименование колонки.
     * @return Значение указанной колонки в текущей строке. Поменять значение текущей строки можно с помощью методов next() и previous().
     * @throws std::range_error Колонки с указанным наименованием не найдено.
     */
    [[nodiscard]] SqlValue value(std::string_view fieldName) const;

    /**
     * @return Список наименований колонок.
     */
    void getFieldNames(std::vector<const char *> &fields) const;

};

}

#endif //ENERGO_SQLQUERYREADER_H
