//
// Created by kir on 08.12.2019.
//

#ifndef ENERGO_DATA_H
#define ENERGO_DATA_H

#include "DatabaseStoredEntity.h"

namespace energo::db::entity {

class EXPORTS Data : public DatabaseStoredEntity {
public:
    void fromSql(const SqlQueryReader &reader) override;
};

}

#endif //ENERGO_DATA_H
