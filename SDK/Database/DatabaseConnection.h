//
// Created by kir on 07.12.2019.
//

#ifndef ENERGO_DATABASECONNECTION_H
#define ENERGO_DATABASECONNECTION_H

#include <atomic>
#include <string_view>
#include <memory>
#include "DatabaseConnectionSettings.h"
#include "../Types/Uuid.h"
#include "SqlQuery.h"
#include "SqlQueryBuilder.h"

namespace energo::db {

/**
 * Одиночное подключение к базе данных.
 */
class EXPORTS DatabaseConnection {
public:
    /**
     * Подготавливает новое подключение к базе данных. Для соединения необходимо вызвать метод DatabaseConnection::open().
     * @param settings Настройки подключения к базе данных.
     */
    explicit DatabaseConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &settings);
    
    /**
     * Открывает новое подключение к базе данных. Если оно было открыто до этого, то ничего не произойдет.
     * @throw DatabaseUnavailableException Не удалось подключиться к базе данных.
     */
    virtual void open();
    
    /**
     * Закрывает подключение к базе данных. Если оно не было открыто, то ничего не произойдет.
     */
    virtual void close();
    
    /**
     * @return Открыто ли подлючение к базе данных.
     */
    [[nodiscard]] bool isOpen() const;
    
    /**
     * @return Уникальный идентификатор подключения.
     */
    [[nodiscard]] const energo::types::Uuid &getUid() const;
    
    /**
     * @return Билдер SQL-запросов для текущего адаптера базы данных.
     */
    [[nodiscard]] virtual const SqlQueryBuilder *queryBuilder() const = 0;
    
    /**
     * Выполняет SQL-запрос к базе данных.
     * @param sql SQL-запрос.
     * @return SqlQuery, представляющий результат выполнения запроса.
     * @throws DatabaseConnectionIsClosedException Попытка выполнить запрос при закрытом соединении.
     * @throws SqlQueryBadResultException выполнение запроса завершилось с ошибкой.
     */
    [[nodiscard]] virtual std::unique_ptr<SqlQuery> exec(std::string_view sql) const = 0;
    
private:
    std::atomic_bool _open;
    energo::types::Uuid _uid;

protected:
    DatabaseConnectionSettings _connectionSettings;
};

}

#endif //ENERGO_DATABASECONNECTION_H
