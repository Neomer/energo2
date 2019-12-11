//
// Created by vinokurov on 11.12.2019.
//

#include "MetaClass.h"

using namespace energo::meta;
using namespace energo::types;

MetaClass::MetaClass(const energo::types::Uuid &typeUid) :
    _typeUid{typeUid},
    _parentTypeUid{}
{

}

MetaClass::MetaClass(const energo::types::Uuid &typeUid, const energo::types::Uuid &parentTypeUid) :
    _typeUid{typeUid},
    _parentTypeUid{parentTypeUid}
{

}

const Uuid &MetaClass::getTypeUid() const {
    return _typeUid;
}

const Uuid &MetaClass::getParentTypeUid() const {
    return _parentTypeUid;
}

