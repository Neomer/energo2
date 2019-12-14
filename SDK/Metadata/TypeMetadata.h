//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_TYPEMETADATA_H
#define ENERGO_TYPEMETADATA_H

#include <string_view>
#include "../Types/Uuid.h"

namespace energo::meta {

/**
 * Метаданные типа.
 */
class EXPORTS TypeMetadata {
    energo::types::Uuid _typeUid;

public:
    explicit TypeMetadata(const types::Uuid &typeUid);

    [[nodiscard]] const types::Uuid &getTypeUid() const;

    [[nodiscard]] virtual std::string_view getTypeName() const = 0;
};

}

#endif //ENERGO_TYPEMETADATA_H
