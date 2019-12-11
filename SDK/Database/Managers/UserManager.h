//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_USERMANAGER_H
#define ENERGO_USERMANAGER_H

#include "EntityManager.h"

namespace energo::db::managers {

class UserManager : public EntityManager {
public:
    UserManager(const DatabaseConnectionProvider &provider,
                const meta::MetadataProvider &metadataProvider);
    
};

}

#endif //ENERGO_USERMANAGER_H
