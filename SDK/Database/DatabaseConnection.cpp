//
// Created by kir on 07.12.2019.
//

#include <fmt/format.h>
#include "DatabaseConnection.h"
#include "DatabaseUnavailableException.h"
#include "DatabaseConnectionIsClosedException.h"
#include "SqlQueryBadResultException.h"

using namespace std;
using namespace energo::db;
using namespace energo::types;
using namespace energo::exceptions;

DatabaseConnection::DatabaseConnection(std::random_device &randomDevice, energo::db::DatabaseConnectionSettings &settings) :
    _connectionSettings{settings},
    _open{false},
    _connection{nullptr},
    _uid{Uuid::Random(randomDevice)}
{

}

void DatabaseConnection::open() {
    if (_open) {
        return;
    }
    _connection = PQsetdbLogin(
            _connectionSettings.getHost().data(),
            to_string(_connectionSettings.getPort()).c_str(),
            nullptr,
            nullptr,
            _connectionSettings.getDatabase().data(),
            _connectionSettings.getUser().data(),
            _connectionSettings.getPassword().data());
    
    auto status = PQstatus(_connection);
    if (status != CONNECTION_OK) {
        throw DatabaseUnavailableException(_connectionSettings);
    }
    _open = true;
}

void DatabaseConnection::close() {
    if (!_open) {
        return;
    }
    PQfinish(_connection);
    _open = false;
}

bool DatabaseConnection::isOpen() const {
    return _open.load();
}

const energo::types::Uuid &DatabaseConnection::getUid() const {
    return _uid;
}

SqlQuery DatabaseConnection::exec(std::string_view sql) const {
    if (!_open) {
        throw DatabaseConnectionIsClosedException();
    }
    
    SqlQuery query(PQexec(
            _connection,
            sql.data()));
    
    if (!query.isValid()) {
        throw SqlQueryBadResultException(PQerrorMessage(_connection));
    }
    return query;
}
