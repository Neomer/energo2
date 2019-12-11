//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_METADATAPROVIDER_H
#define ENERGO_METADATAPROVIDER_H

#include <vector>
#include <memory>
#include "TypeMetadata.h"

namespace energo::meta {

/**
 * Контейнер зарегистрированных метаданных типов.
 */
class MetadataProvider {
    std::vector<std::shared_ptr<TypeMetadata>> _metadataVector;

public:
    /**
     * Зарегистрировать в контейнере метаданные для типа.
     * @param metadata Метаданные типа.
     */
    void registerMetadata(std::shared_ptr<TypeMetadata> metadata);

    /**
     * Найти метаданные для указанного идентификатора типа.
     * @param typeUid Идентификатор типа.
     * @return Метаданные типа, либо nullptr, если тип с указанным иденгтификатором не зарегистрирован.
     */
    [[nodiscard]] const TypeMetadata* find(const energo::types::Uuid &typeUid) const;
};

}

#endif //ENERGO_METADATAPROVIDER_H
