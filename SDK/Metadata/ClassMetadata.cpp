//
// Created by vinokurov on 11.12.2019.
//

#include "ClassMetadata.h"

using namespace energo::meta;
using namespace energo::types;

ClassMetadata::ClassMetadata(const Uuid &typeUid, const Uuid &parentTypeUid) :
    TypeMetadata(typeUid),
    _parentTypeUid(parentTypeUid)
{

}

const Uuid &ClassMetadata::getParentTypeUid() const {
    return _parentTypeUid;
}
