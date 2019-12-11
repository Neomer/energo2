//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_IDENTIFIEDENTITY_H
#define ENERGO_IDENTIFIEDENTITY_H

#include "../../Types/Uuid.h"
#include "DatabaseStoredEntity.h"

namespace energo::db::entity {

class IdentifiedEntity : public DatabaseStoredEntity {
    energo::types::Uuid _uid;
    
public:
    explicit IdentifiedEntity(const types::Uuid &typeUid);

    void fromSql(const SqlQueryReader &reader) override;
    
    [[nodiscard]] const types::Uuid &getUid() const;
    
    void setUid(const types::Uuid &uid);
};

}

#endif //ENERGO_IDENTIFIEDENTITY_H
