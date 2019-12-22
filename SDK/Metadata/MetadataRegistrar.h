//
// Created by kir on 18.12.2019.
//

#ifndef ENERGO_METADATAREGISTRAR_H
#define ENERGO_METADATAREGISTRAR_H

#include "../classes.h"
#include "../global.h"

namespace energo::meta {

class EXPORTS MetadataRegistrar final {
    STATIC_CLASS(MetadataRegistrar)

public:
    static void RegisterMetaTypes(MetadataProvider &metadataProvider);
};

}

#endif //ENERGO_METADATAREGISTRAR_H
