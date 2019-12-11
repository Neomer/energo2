//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_CLASSMETADATA_H
#define ENERGO_CLASSMETADATA_H

#include "TypeMetadata.h"
#include "MetaClass.h"

namespace energo::meta {

class ClassMetadata: public TypeMetadata {
    energo::types::Uuid _parentTypeUid;

public:
    ClassMetadata(const types::Uuid &typeUid, const types::Uuid &parentTypeUid);

    [[nodiscard]] const types::Uuid &getParentTypeUid() const;

    [[nodiscard]] virtual MetaClass *createInstance() const = 0;
};

}

#endif //ENERGO_CLASSMETADATA_H
