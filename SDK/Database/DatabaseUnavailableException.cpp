//
// Created by kir on 07.12.2019.
//

#include "DatabaseUnavailableException.h"

using namespace std;
using namespace energo::db;
using namespace energo::exceptions;

const DatabaseConnectionSettings &DatabaseUnavailableException::getSettings() const {
    return _settings;
}

DatabaseUnavailableException::DatabaseUnavailableException(energo::db::DatabaseConnectionSettings &settings) :
    runtime_error{""},
    _settings{settings}
{

}
