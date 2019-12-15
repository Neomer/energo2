//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_IDENTIFIEDENTITY_H
#define ENERGO_IDENTIFIEDENTITY_H

#include <functional>
#include "../../Types/Uuid.h"
#include "DatabaseStoredEntity.h"

namespace energo::db::entity {

class EXPORTS IdentifiedEntity : public DatabaseStoredEntity {
    energo::types::Uuid _uid;
    
public:
    IdentifiedEntity() = default;
    
    explicit IdentifiedEntity(const types::Uuid &uid);

    void fromSql(const SqlQueryReader &reader) override;
    
    [[nodiscard]] const types::Uuid &getUid() const;
    
    void setUid(const types::Uuid &uid);
    
    void toSqlValues(DatabaseStoredEntity::TFieldValuePairList &fieldValueList, const TransformationProvider &transformationProvider ) const override;
    
    [[nodiscard]] std::string getFieldValue(size_t fieldHash, const TransformationProvider &transformationProvider) const override;
};

}

#endif //ENERGO_IDENTIFIEDENTITY_H
