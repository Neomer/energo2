//
// Created by kir on 11.12.2019.
//

#include <algorithm>
#include "DatabaseConnectionProvider.h"

using namespace std;
using namespace energo::db;

DatabaseConnectionProvider::DatabaseConnectionProvider(const DatabaseConnectionSettings &connectionSettings) :
    _connectionSettings{connectionSettings},
    _randomDevice{}
{

}

void DatabaseConnectionProvider::initialize(size_t defaultConnectionCount) {
    while (defaultConnectionCount--) {
        auto connection = createConnection(_randomDevice, _connectionSettings);
        connection->open();
        _connections.emplace_back(connection);
    }
}

const DatabaseConnection *DatabaseConnectionProvider::getConnection() const {
    auto it = find_if(_connections.begin(), _connections.end(),
                [](std::shared_ptr<DatabaseConnection> connection) {
                    return connection->isOpen();
                });
    return it != _connections.end() ? (*it).get() : nullptr;
}

void DatabaseConnectionProvider::release() {
    for_each(_connections.begin(), _connections.end(),
            [](std::shared_ptr<DatabaseConnection> connection) {
                connection->close();
            });
}


