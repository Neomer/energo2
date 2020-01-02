//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_METADATAPROVIDER_H
#define ENERGO_METADATAPROVIDER_H

#include <vector>
#include <memory>
#include <functional>
#include "TypeMetadata.h"

namespace energo::meta {

/**
 * Контейнер зарегистрированных метаданных типов.
 */
class EXPORTS MetadataProvider {
    std::vector<const meta::TypeMetadata *> _metadataVector;

public:
    static MetadataProvider *GetStatic();
    
    /**
     * Зарегистрировать в контейнере метаданные для типа.
     * @param metadata Метаданные типа.
     */
    void registerMetadata(const TypeMetadata *metadata);

    /**
     * Найти метаданные для указанного идентификатора типа.
     * @param typeUid Идентификатор типа.
     * @return Метаданные типа, либо nullptr, если тип с указанным иденгтификатором не зарегистрирован.
     */
    [[nodiscard]] const TypeMetadata* find(const energo::types::Uuid &typeUid) const;
    
    /**
     * Найти метаданные для указанного идентификатора типа.
     * @param comparator Метод для поиска подходящего варианта.
     * @return Метаданные типа, либо nullptr, если тип с указанным иденгтификатором не зарегистрирован.
     */
    [[nodiscard]] const TypeMetadata* find(const std::function<bool(const meta::TypeMetadata *)> &comparator) const;
};

}


#define META_TYPE(className)    metadataProvider.registerMetadata(new className());

#endif //ENERGO_METADATAPROVIDER_H
