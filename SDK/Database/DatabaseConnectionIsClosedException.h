//
// Created by kir on 07.12.2019.
//

#ifndef ENERGO_DATABASECONNECTIONISCLOSEDEXCEPTION_H
#define ENERGO_DATABASECONNECTIONISCLOSEDEXCEPTION_H

#include <stdexcept>
#include "../global.h"

namespace energo::exceptions {

/**
 * Попытка работать с закрытым подключением к базе данных.
 */
class EXPORTS DatabaseConnectionIsClosedException : public std::runtime_error {
public:
    /**
     * Попытка работать с закрытым подключением к базе данных.
     */
    explicit DatabaseConnectionIsClosedException();

};

}

#endif //ENERGO_DATABASECONNECTIONISCLOSEDEXCEPTION_H
