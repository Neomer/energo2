//
// Created by vinokurov on 11.12.2019.
//

#include "TypeMetadata.h"

using namespace energo::meta;
using namespace energo::types;

TypeMetadata::TypeMetadata(const Uuid &typeUid) :
    _typeUid(typeUid)
{

}

const Uuid &TypeMetadata::getTypeUid() const {
    return _typeUid;
}
