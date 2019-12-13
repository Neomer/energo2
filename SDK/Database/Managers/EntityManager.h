//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_ENTITYMANAGER_H
#define ENERGO_ENTITYMANAGER_H

#include "../../Types/Uuid.h"
#include "../Model/DatabaseStoredEntity.h"
#include "../DatabaseConnectionProvider.h"
#include "../../Metadata/MetadataProvider.h"
#include "../../Metadata/EntityMetadata.h"

namespace energo::db::managers {

/**
 * Менеджер сущности. Используется для базовой работы с записями в базе данных.
 */
class EntityManager {
protected:
    const energo::db::DatabaseConnectionProvider &_connectionProvider;
    const energo::types::Uuid &_typeUid;
    const energo::meta::MetadataProvider &_metadataProvider;
    const energo::meta::EntityMetadata *_entityMetadata;
    
public:
    /**
     * Создает менеджер сущности.
     * @param provider Провайдер подключений к базе данных.
     * @param typeUid Идентификатор типа, с которой работает данный менеджер сущностей.
     * @param metadataProvider Инициализированный провайдер метаданных.
     * @throws std::runtime_error Невозможно получить метаданные для сущности указанного типа.
     */
    explicit EntityManager(
            const energo::db::DatabaseConnectionProvider &provider,
            const energo::types::Uuid &typeUid,
            const energo::meta::MetadataProvider &metadataProvider);
    
    /**
     * Возвращает Сущность с указанным идентификатором.
     * @param uid Идентификатор сущности.
     * @return Сущность с указанным идентификатором.
     * @throws energo::exceptions::DatabaseConnectionIsClosedException Не удалось получить активное подключение.
     */
    [[nodiscard]] virtual std::shared_ptr<energo::db::entity::DatabaseStoredEntity> get(const energo::types::Uuid &uid) const;
    
    /**
     * Заполняет вектор всеми сущностями, хранящимися в базе данных.
     * @param result
     * @throws energo::exceptions::DatabaseConnectionIsClosedException Не удалось получить активное подключение.
     */
    virtual void all(std::vector<std::shared_ptr<energo::db::entity::DatabaseStoredEntity>> &result) const;
};

}

#endif //ENERGO_ENTITYMANAGER_H