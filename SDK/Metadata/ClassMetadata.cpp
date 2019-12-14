//
// Created by vinokurov on 11.12.2019.
//

#include "MetadataProvider.h"
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

bool ClassMetadata::isDerived(const Uuid &typeUid) const {
    if (typeUid.isEmpty()) {
        return false;
    }
    return _parentTypeUid.equals(typeUid);
}

bool ClassMetadata::isDerived(const Uuid &typeUid, const MetadataProvider &metadataProvider) const {
    if (isDerived(typeUid)) {
        return true;
    }
    if (_parentTypeUid.isEmpty()) {
        return false;
    }
    auto parentClassMetadata = dynamic_cast<const ClassMetadata*>(metadataProvider.find(_parentTypeUid));
    if (parentClassMetadata != nullptr) {
        return parentClassMetadata->isDerived(typeUid, metadataProvider);
    }
    return false;
}
