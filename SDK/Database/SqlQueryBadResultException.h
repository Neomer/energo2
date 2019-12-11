//
// Created by kir on 08.12.2019.
//

#ifndef ENERGO_SQLQUERYBADRESULTEXCEPTION_H
#define ENERGO_SQLQUERYBADRESULTEXCEPTION_H

#include <stdexcept>
#include <string_view>
#include "../global.h"

namespace energo::exceptions {

class EXPORTS SqlQueryBadResultException : public std::runtime_error {
public:
    explicit SqlQueryBadResultException(std::string_view message);
};

}

#endif //ENERGO_SQLQUERYBADRESULTEXCEPTION_H
