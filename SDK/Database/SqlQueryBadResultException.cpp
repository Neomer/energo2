//
// Created by kir on 08.12.2019.
//

#include "SqlQueryBadResultException.h"

using namespace energo::exceptions;

SqlQueryBadResultException::SqlQueryBadResultException(std::string_view message) :
    std::runtime_error{message.data()}
{

}
