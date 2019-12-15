//
// Created by kir on 11.12.2019.
//

#include "../../BenchmarkTimer.h"
#include <stdexcept>
#include "../DatabaseConnectionIsClosedException.h"
#include "../SqlConditionBuilder.h"
#include "EntityManager.h"
#include "../../Metadata/TypeUids.h"

using namespace std;
using namespace std::string_literals;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::db::managers;
using namespace energo::types;
using namespace energo::meta;
using namespace energo::exceptions;
using namespace energo::benchmark;

managers::EntityManager::EntityManager(const energo::db::DatabaseConnectionProvider &provider,
                                       const energo::types::Uuid &typeUid,
                                       const energo::types::Uuid &entityTypeUid,
                                       const energo::meta::MetadataProvider &metadataProvider) :
        ClassMetadata{typeUid, Uuid::Empty()},
        _connectionProvider{provider},
        _entityTypeUid{entityTypeUid},
        _metadataProvider{metadataProvider},
        _entityMetadata{nullptr}

{
    auto typeMetadata = _metadataProvider.find(entityTypeUid);
    if (typeMetadata == nullptr) {
        throw runtime_error("Метаданные для типа "s + entityTypeUid.toString() + " не зарегистрированы.");
    }
    _entityMetadata = dynamic_cast<const EntityMetadata *>(typeMetadata);
    if (_entityMetadata == nullptr) {
        throw runtime_error("Метаданные для типа "s + entityTypeUid.toString() + " не являются метаданными сущности.");
    }
}

std::shared_ptr<energo::db::entity::DatabaseStoredEntity> managers::EntityManager::get(const energo::types::Uuid &uid) const {
    BenchmarkTimer timer("entity get");
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    auto sql = connection
            ->queryBuilder()
            ->createSelectQueryBuilder(_entityMetadata->getTableName())
            ->where(
                    SqlConditionBuilder::Eq(
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
    auto entity = reinterpret_cast<DatabaseStoredEntity *>(instance);
    timer.lap("entity instance created");
    entity->fromSql(result->getReader());
    timer.lap("entity deserialized");

    return shared_ptr<DatabaseStoredEntity>(entity);
}


void managers::EntityManager::all(std::vector<std::shared_ptr<energo::db::entity::DatabaseStoredEntity>> &result) const {
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
        auto entity = reinterpret_cast<DatabaseStoredEntity *>(instance);
        entity->fromSql(queryResult->getReader());
        result.emplace_back(shared_ptr<DatabaseStoredEntity>(entity));
    }
    while (queryResult->next());
}

void managers::EntityManager::remove(energo::db::entity::IdentifiedEntity &&entity) const {
    remove(entity.getUid());
    entity.setUid(Uuid::Empty());
}

void managers::EntityManager::remove(const energo::types::Uuid &uid) const {
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    auto sql = connection
            ->queryBuilder()
            ->createDeleteQueryBuilder(_entityMetadata->getTableName())
            ->where(
                    SqlConditionBuilder::Eq(
                        connection->transformationProvider().escapeFieldNameIfNeeded("Uid"),
                        connection->transformationProvider().formatValue(uid)
            ))
            .build();
    auto queryResult = connection->exec(sql);
}

const Uuid &managers::EntityManager::getEntityTypeUid() const {
    return _entityTypeUid;
}

void managers::EntityManager::update(const IdentifiedEntity &entity) const {
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    entity::DatabaseStoredEntity::TFieldValuePairList fieldValues;
    entity.toSqlValues(fieldValues, connection->transformationProvider());
    
    auto sql = connection
            ->queryBuilder()
            ->createUpdateQueryBuilder(_entityMetadata->getTableName())
            ->where(
                    SqlConditionBuilder::Eq(
                            connection->transformationProvider().escapeFieldNameIfNeeded("Uid"),
                            connection->transformationProvider().formatValue(entity.getUid())
            ))
            .values(fieldValues)
            .build();
    
    auto result = connection->exec(sql);
}

void managers::EntityManager::save(const entity::IdentifiedEntity &entity) const {
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    entity::DatabaseStoredEntity::TFieldValuePairList fieldValues;
    entity.toSqlValues(fieldValues, connection->transformationProvider());
    
    vector<string> fields, values;
    for_each(fieldValues.begin(), fieldValues.end(),
            [&fields, &values](const pair<string, string> &item) {
                fields.emplace_back(item.first);
                values.emplace_back(item.second);
            });
    
    auto sql = connection
            ->queryBuilder()
            ->createInsertQueryBuilder(_entityMetadata->getTableName())
            ->fields(fields)
            .values(values)
            .build();
    
    auto result = connection->exec(sql);
}

void managers::EntityManager::saveAll(const std::vector<const entity::IdentifiedEntity *> &entities) const {
    auto connection = _connectionProvider.getConnection();
    if (connection == nullptr) {
        throw DatabaseConnectionIsClosedException();
    }
    
    auto queryBuilder = connection
            ->queryBuilder()
            ->createInsertQueryBuilder(_entityMetadata->getTableName());
    auto fieldNames = _entityMetadata->getFieldNames();
    vector<string> fields;
    fields.reserve(fieldNames.size());
    for (auto field : fieldNames) {
        fields.emplace_back(field.first);
    }
    queryBuilder->fields(fields);
    
    for_each(entities.begin(), entities.end(),
                [&connection, &queryBuilder, &fieldNames](const IdentifiedEntity *entity) {
                    vector<string> values;
                    values.reserve(fieldNames.size());
                    for (auto field : fieldNames) {
                        values.push_back(entity->getFieldValue(field.second, connection->transformationProvider()));
                    }
                    queryBuilder->values(values);
                });
    
    auto sql = queryBuilder->build();
    auto result = connection->exec(sql);
}