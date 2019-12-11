//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_ENTITYMETADATAREGISTRAR_H
#define ENERGO_ENTITYMETADATAREGISTRAR_H

#include "../../Metadata/MetadataProvider.h"

namespace energo::db::entity {

class EXPORTS EntityMetadataRegistrar {
    EntityMetadataRegistrar() = default;
    ~EntityMetadataRegistrar() = default;

public:
    static void RegisterEntityTypes(meta::MetadataProvider &provider);
};

}

#endif //ENERGO_ENTITYMETADATAREGISTRAR_H
