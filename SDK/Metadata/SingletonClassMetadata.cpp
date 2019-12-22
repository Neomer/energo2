//
// Created by kir on 18.12.2019.
//

#include "SingletonClassMetadata.h"

using namespace energo::meta;

SingletonClassMetadata::SingletonClassMetadata(const energo::types::Uuid &typeUid, const energo::types::Uuid &parentTypeUid) :
    ClassMetadata(typeUid, parentTypeUid),
    _instance{nullptr}
{

}

void energo::meta::SingletonClassMetadata::setInstance(void *instance) {
    _instance = instance;
}


void *SingletonClassMetadata::createInstance() {
    if (_instance == nullptr) {
        _instance = createInstanceInternal();
    }
    return _instance;
}

void *energo::meta::SingletonClassMetadata::createInstance() const {
    return _instance;
}

bool SingletonClassMetadata::isReady() const {
    return _instance != nullptr;
}
