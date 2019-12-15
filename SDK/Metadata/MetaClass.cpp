//
// Created by vinokurov on 11.12.2019.
//

#include "MetaClass.h"

using namespace energo::meta;
using namespace energo::types;

MetaClass::MetaClass(const energo::types::Uuid &typeUid) :
    _typeUid{typeUid}
{

}

const Uuid &MetaClass::getTypeUid() const {
    return _typeUid;
}
