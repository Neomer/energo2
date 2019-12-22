//
// Created by kir on 11.12.2019.
//

#include <algorithm>
#include "../Metadata/TypeUids.h"
#include "DatabaseConnectionProvider.h"
#include "../Metadata/ClassMetadata.h"

using namespace std;
using namespace energo::db;

DatabaseConnectionProvider::DatabaseConnectionProvider(const DatabaseConnectionSettings &connectionSettings, const types::Uuid &typeUid) :
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

DatabaseConnectionProvider *DatabaseConnectionProvider::GetFromMetadata(const meta::MetadataProvider &metadataProvider) {
    auto providerMetadata = metadataProvider.find(
            [](const meta::TypeMetadata *metadata) {
                auto classMetadata = dynamic_cast<const meta::ClassMetadata *>(metadata);
                return classMetadata != nullptr && classMetadata->getParentTypeUid() == DATABASEPROVIDER_TYPE_UID;
            });
    return reinterpret_cast<DatabaseConnectionProvider *>(dynamic_cast<const meta::ClassMetadata *>(providerMetadata)->createInstance());
}
