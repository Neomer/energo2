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

public:
    explicit MetaClass(const energo::types::Uuid &typeUid);

    virtual ~MetaClass() = default;

    [[nodiscard]] const types::Uuid &getTypeUid() const;
};

}

#endif //ENERGO_METACLASS_H
