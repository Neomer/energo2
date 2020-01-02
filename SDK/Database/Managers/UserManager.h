//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_USERMANAGER_H
#define ENERGO_USERMANAGER_H

#include "EntityManager.h"
#include "../../Metadata/SingletonClassMetadata.h"

namespace energo::db::managers {

class EXPORTS UserManager : public EntityManager {
public:
    UserManager(const DatabaseConnectionProvider &provider,
                const meta::MetadataProvider &metadataProvider);
    
};

class EXPORTS UserManagerMetadata : public EntityManagerMetadata, public meta::SingletonClassMetadata {
public:
    UserManagerMetadata();

protected:
    void *createInstanceInternal() const override;

public:
    
    [[nodiscard]] std::string_view getTypeName() const override;
};

}

#endif //ENERGO_USERMANAGER_H
