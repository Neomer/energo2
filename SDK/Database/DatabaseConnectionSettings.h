//
// Created by kir on 07.12.2019.
//

#ifndef ENERGO_DATABASECONNECTIONSETTINGS_H
#define ENERGO_DATABASECONNECTIONSETTINGS_H

#include <string>
#include <string_view>
#include <cinttypes>
#include "../os.h"

namespace energo::db {

/**
 * Настройки подключения к базе данных.
 */
class DatabaseConnectionSettings {
public:
    /**
     * @return Порт подключения к базе данных.
     */
    [[nodiscard]] uint16_t getPort() const;
    
    /**
     * Установить порт подключения к базе данных.
     * @param port  Порт подключения к базе данных.
     */
    void setPort(uint16_t port);
    
    /**
     * @return Адрес сервера базы данных.
     */
    [[nodiscard]] std::string_view getHost() const;

    /**
     * Установить адрес сервера базы данных.
     * @param host Адрес сервера базы данных.
     */
    void setHost(std::string_view host);
    
    /**
     * @return Имя пользователя базы данных.
     */
    [[nodiscard]] std::string_view getUser() const;
    
    /**
     * Установить имя пользователя базы данных.
     * @param user Имя пользователя базы данных.
     */
    void setUser(std::string_view user);
    
    /**
     * @return Пароль пользователя.
     */
    [[nodiscard]] std::string_view getPassword() const;
    
    /**
     * Установить пароль пользователя.
     * @param password Пароль пользователя.
     */
    void setPassword(std::string_view password);
    
    /**
     * @return Наименование базы данных.
     */
    [[nodiscard]] std::string_view getDatabase() const;
    
    /**
     * Установить наименование базы данных.
     * @param database Наименование базы данных.
     */
    void setDatabase(std::string_view database);

private:
    uint16_t _port;
    std::string _host, _user, _password, _database;
};

}

#endif //ENERGO_DATABASECONNECTIONSETTINGS_H
