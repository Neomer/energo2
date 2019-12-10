//
// Created by kir on 07.12.2019.
//

#ifndef ENERGO_SQLQUERY_H
#define ENERGO_SQLQUERY_H

#include <memory>
#include "DatabaseResultAdapter.h"
#include "SqlQueryReader.h"

namespace energo::db {

/**
 * Результат выполнения SQL-запроса.
 * Представляет собой итерратор для прохода по строкам результата запроса.
 * Для чтения результатов выборки необходимо вызвать методы getReader() или getReader(int row).
 */
class EXPORTS SqlQuery final {
    std::shared_ptr<DatabaseResultAdapter> _adapter;
    int _rowIdx;

public:
    explicit SqlQuery(std::unique_ptr<DatabaseResultAdapter> adapter);
    ~SqlQuery() = default;
    
    /**
     * @return Выполнение запроса прошло без ошибок.
     */
    [[nodiscard]] bool isValid() const;
    
    /**
     * @return Количество строк в результате.
     */
    [[nodiscard]] int getRowsCount() const;

    /**
     * @return Есть ли в результате хоть 1 строка.
     */
    [[nodiscard]] bool any() const;

    /**
     * @return Ридер для текущей строки результата запроса.
     */
    [[nodiscard]] SqlQueryReader getReader() const;

    /**
     * @param row Номер строки.
     * @return Ридер для указанной строки результата запроса.
     * @throws std::range_error Указанная строка выходит за диапазон допустимых значений.
     */
    [[nodiscard]] SqlQueryReader getReader(int row) const;

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
    
};

}

#endif //ENERGO_SQLQUERY_H
