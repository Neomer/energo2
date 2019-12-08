//
// Created by kir on 07.12.2019.
//

#ifndef ENERGO_DATABASEUNAVAILABLEEXCEPTION_H
#define ENERGO_DATABASEUNAVAILABLEEXCEPTION_H

#include <stdexcept>
#include "DatabaseConnectionSettings.h"

namespace energo::exceptions {

/**
 * Не удалось подключиться к базе данных.
 */
class DatabaseUnavailableException : public std::runtime_error {
public:
    /**
     * Не удалось подключиться к базе данных.
     * @param settings Используемые настройки для подключения к базе данных.
     */
    explicit DatabaseUnavailableException(energo::db::DatabaseConnectionSettings &settings);
    
    /**
     * @return  Используемые настройки для подключения к базе данных.
     */
    [[nodiscard]] const db::DatabaseConnectionSettings &getSettings() const;

private:
    energo::db::DatabaseConnectionSettings &_settings;
};

}

#endif //ENERGO_DATABASEUNAVAILABLEEXCEPTION_H
