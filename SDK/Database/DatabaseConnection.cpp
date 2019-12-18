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

DatabaseConnection::DatabaseConnection(random_device &randomDevice, const DatabaseConnectionSettings &settings) :
    _connectionSettings{settings},
    _open{false},
    _uid{Uuid::Random(randomDevice)}
{

}

void DatabaseConnection::open() {
    _open = true;
}

void DatabaseConnection::close() {
    _open = false;
}

bool DatabaseConnection::isOpen() const {
    return _open.load();
}

const energo::types::Uuid &DatabaseConnection::getUid() const {
    return _uid;
}

void DatabaseConnection::beginTransaction(IsolationLevel isolationLevel) {
    _transaction = true;
}

bool DatabaseConnection::inTransaction() const {
    return _transaction.load();
}

void DatabaseConnection::commit() {
    _transaction = false;
}

void DatabaseConnection::rollback() {
    _transaction = false;
}
