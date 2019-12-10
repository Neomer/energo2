//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_DATABASESTOREDENTITY_H
#define ENERGO_DATABASESTOREDENTITY_H

#include "../SqlQueryReader.h"

namespace energo::db::entity {

class DatabaseStoredEntity {
public:
    DatabaseStoredEntity() = default;
    virtual ~DatabaseStoredEntity() = default;

    virtual void fromSql(const SqlQueryReader &reader) = 0;
};

}


#endif //ENERGO_DATABASESTOREDENTITY_H
