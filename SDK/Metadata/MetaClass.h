//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_METACLASS_H
#define ENERGO_METACLASS_H

#include <string_view>
#include "../Types/Uuid.h"

namespace energo::meta {

/**
 * Базовый класс для дргих классов, которые имеют метаданные и хранятся в контейнере метаданных.
 */
class EXPORTS MetaClass {
    energo::types::Uuid _typeUid;
    energo::types::Uuid _parentTypeUid;

public:
    explicit MetaClass(const energo::types::Uuid &typeUid);

    explicit MetaClass(const energo::types::Uuid &typeUid, const energo::types::Uuid &parentTypeUid);

    virtual ~MetaClass() = default;

    [[nodiscard]] const types::Uuid &getTypeUid() const;

    [[nodiscard]] const types::Uuid &getParentTypeUid() const;
};

}

#endif //ENERGO_METACLASS_H
