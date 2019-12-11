//
// Created by kir on 11.12.2019.
//

#include <stdexcept>
#include "../DatabaseConnectionIsClosedException.h"
#include "EntityManager.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::db::managers;
using namespace energo::types;
using namespace energo::meta;
using namespace energo::exceptions;

EntityManager::EntityManager(const DatabaseConnectionProvider &provider, const Uuid &typeUid, const MetadataProvider &metadataProvider) :
    _connectionProvider{provider},
    _typeUid{typeUid},
    _metadataProvider{metadataProvider},
    _entityMetadata{nullptr}
{
    auto typeMetadata = _metadataProvider.find(_typeUid);
    if (typeMetadata == nullptr) {
        throw runtime_error("Метаданные для типа "s + _typeUid.toString() + " не зарегистрированы.");
    }
    _entityMetadata = dynamic_cast<const EntityMetadata *>(typeMetadata);
    if (_entityMetadata == nullptr) {
        throw runtime_error("Метаданные для типа "s + _typeUid.toString() + " не являются метаданными сущности.");
    }
}

shared_ptr<DatabaseStoredEntity> EntityManager::get(const Uuid &uid) const {
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    auto sql = connection
            ->queryBuilder()
            ->createSelectQueryBuilder(_entityMetadata->getTableName())
            ->where(R"("Uid"=')" + uid.toString() + "'")
            .limit(1)
            .build();
    
    auto result = connection->exec(sql);
    if (!result->any()) {
        return shared_ptr<DatabaseStoredEntity>(nullptr);
    }
    auto instance = _entityMetadata->createInstance();
    auto entity = dynamic_cast<DatabaseStoredEntity *>(instance);
    entity->fromSql(result->getReader());
    
    return shared_ptr<DatabaseStoredEntity>(entity);
}

void EntityManager::all(vector<shared_ptr<DatabaseStoredEntity>> &result) const {

}
