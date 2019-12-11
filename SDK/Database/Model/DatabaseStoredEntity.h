//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_DATABASESTOREDENTITY_H
#define ENERGO_DATABASESTOREDENTITY_H

#include "../SqlQueryReader.h"
#include "../../Metadata/MetaClass.h"

namespace energo::db::entity {

class DatabaseStoredEntity : public meta::MetaClass {
public:
    explicit DatabaseStoredEntity(const types::Uuid &typeUid);

    virtual void fromSql(const SqlQueryReader &reader) = 0;
};

}


#endif //ENERGO_DATABASESTOREDENTITY_H
