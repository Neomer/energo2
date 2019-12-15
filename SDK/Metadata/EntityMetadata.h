//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_ENTITYMETADATA_H
#define ENERGO_ENTITYMETADATA_H

#include <utility>
#include <vector>
#include <string_view>
#include "ClassMetadata.h"

namespace energo::meta {

/**
 * Метаданные сущности.
 */
class EntityMetadata : public ClassMetadata {
public:
    using TFieldWithHashList = std::vector<std::pair<std::string_view, size_t>>;

private:
    TFieldWithHashList _fieldNames;

public:
    EntityMetadata(const types::Uuid &typeUid,
            const types::Uuid &parentTypeUid,
            const std::vector<std::string_view>& fieldNames);
    
    [[nodiscard]] virtual std::string_view getTableName() const = 0;
    
    [[nodiscard]] const TFieldWithHashList &getFieldNames() const;
};

}


#endif //ENERGO_ENTITYMETADATA_H
