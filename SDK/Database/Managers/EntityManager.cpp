//
// Created by kir on 11.12.2019.
//

#include "../../BenchmarkTimer.h"
#include <stdexcept>
#include "../DatabaseConnectionIsClosedException.h"
#include "../SqlComparisonBuilder.h"
#include "EntityManager.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::db::managers;
using namespace energo::types;
using namespace energo::meta;
using namespace energo::exceptions;
using namespace energo::benchmark;

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
    BenchmarkTimer timer("entity get");
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    auto sql = connection
            ->queryBuilder()
            ->createSelectQueryBuilder(_entityMetadata->getTableName())
            ->where(
                    SqlComparisonBuilder::Eq(
                            connection->transformationProvider().escapeFieldNameIfNeeded("Uid"),
                            connection->transformationProvider().formatValue(uid)))
            .limit(1)
            .build();
    timer.lap("SQL query ready");

    auto result = connection->exec(sql);
    timer.lap("SQL execution");
    if (!result->any()) {
        return shared_ptr<DatabaseStoredEntity>(nullptr);
    }
    auto instance = _entityMetadata->createInstance();
    auto entity = dynamic_cast<DatabaseStoredEntity *>(instance);
    timer.lap("entity instance created");
    entity->fromSql(result->getReader());
    timer.lap("entity deserialized");

    return shared_ptr<DatabaseStoredEntity>(entity);
}

void EntityManager::all(vector<shared_ptr<DatabaseStoredEntity>> &result) const {
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    auto sql = connection
            ->queryBuilder()
            ->createSelectQueryBuilder(_entityMetadata->getTableName())
            ->build();

    auto queryResult = connection->exec(sql);
    if (!queryResult->any()) {
        return;
    }
    do
    {
        auto instance = _entityMetadata->createInstance();
        auto entity = dynamic_cast<DatabaseStoredEntity *>(instance);
        entity->fromSql(queryResult->getReader());
        result.emplace_back(shared_ptr<DatabaseStoredEntity>(entity));
    }
    while (queryResult->next());
}
