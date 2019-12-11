//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_ENTITYMETADATA_H
#define ENERGO_ENTITYMETADATA_H

#include <string_view>
#include "ClassMetadata.h"

namespace energo::meta {

class EntityMetadata : public ClassMetadata {
public:
    EntityMetadata(const types::Uuid &typeUid, const types::Uuid &parentTypeUid);
    
    [[nodiscard]] virtual std::string_view getTableName() const = 0;
};

}


#endif //ENERGO_ENTITYMETADATA_H
