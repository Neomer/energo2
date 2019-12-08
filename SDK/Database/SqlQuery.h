//
// Created by kir on 07.12.2019.
//

#ifndef ENERGO_SQLQUERY_H
#define ENERGO_SQLQUERY_H

#include <string>
#include <string_view>
#include <postgresql/libpq-fe.h>
#include <cinttypes>
#include <vector>
#include "../os.h"
#include "SqlValue.h"

namespace energo::db {

/**
 * Результат выполнения SQL-запроса.
 */
class SqlQuery {
public:
    explicit SqlQuery(PGresult *result);
    
    /**
     * @return Выполнение запроса прошло без ошибок.
     */
    [[nodiscard]] bool isValid() const;
    
    /**
     * @return Количество колонок в результате.
     */
    [[nodiscard]] uint16_t getFieldsCount() const;

    /**
     * @return Количество строк в результате.
     */
    [[nodiscard]] int getRowsCount() const;
    
    /**
     * @param fieldIndex Номер колонки.
     * @return Значение указанной колонки в текущей строке. Поменять значение текущей строки можно с помощью методов next() и previous().
     */
    [[nodiscard]] SqlValue value(int fieldIndex) const;
    
    /**
     * @param fieldIndex Наименование колонки.
     * @return Значение указанной колонки в текущей строке. Поменять значение текущей строки можно с помощью методов next() и previous().
     */
    [[nodiscard]] SqlValue value(std::string_view fieldName) const;
    
    /**
     * @return Список наименований колонок.
     */
    [[nodiscard]] std::vector<const char *> getFieldNames() const;
    
    /**
     * @return Есть ли в результате хоть 1 строка.
     */
    [[nodiscard]] bool any() const;
    
    /**
     * Перевести указатель на следующую строку.
     * @return Удалось передвинуть указатель.
     */
    bool next();
    
    /**
     * Перевести указатель на предыдущую строку.
     * @return Удалось передвинуть указатель.
     */
    bool previous();
    
private:
    PGresult *_result;
    int _rowIdx;
};

}

#endif //ENERGO_SQLQUERY_H
