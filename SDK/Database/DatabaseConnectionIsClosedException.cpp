//
// Created by kir on 07.12.2019.
//

#include "DatabaseConnectionIsClosedException.h"

using namespace energo::exceptions;

DatabaseConnectionIsClosedException::DatabaseConnectionIsClosedException() :
    std::runtime_error("")
{

}
