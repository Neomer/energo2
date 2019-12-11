//
// Created by kir on 11.12.2019.
//

#include "EntityMetadata.h"

using namespace energo::meta;
using namespace energo::types;

EntityMetadata::EntityMetadata(const Uuid &typeUid, const Uuid &parentTypeUid) :
    ClassMetadata(typeUid, parentTypeUid)
{

}
