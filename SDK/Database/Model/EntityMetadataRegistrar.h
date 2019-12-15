//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_ENTITYMETADATAREGISTRAR_H
#define ENERGO_ENTITYMETADATAREGISTRAR_H

#include "../../Metadata/MetadataProvider.h"
#include "../DatabaseConnectionProvider.h"

namespace energo::db::entity {

class EXPORTS EntityMetadataRegistrar {
    EntityMetadataRegistrar() = default;
    ~EntityMetadataRegistrar() = default;

public:
    static void RegisterEntityTypes(meta::MetadataProvider &provider);
    
    static void RegisterEntityManagers(meta::MetadataProvider &metadataProvider,
            const DatabaseConnectionProvider &databaseConnectionProvider);
};

}

#endif //ENERGO_ENTITYMETADATAREGISTRAR_H
