//
// Created by vinokurov on 11.12.2019.
//

#include <algorithm>
#include <stdexcept>
#include "MetadataProvider.h"

using namespace std;
using namespace energo::meta;
using namespace std::string_literals;

void MetadataProvider::registerMetadata(const TypeMetadata* metadata) {
    auto storedMetadata = find(metadata->getTypeUid());
    if (storedMetadata != nullptr) {
        throw runtime_error("Не удалось зарегистрировать метаданные для типа "s +
            metadata->getTypeName().data() +
            ". Идентификатор "s + metadata->getTypeUid().toString() +
            " уже зарегистрированы для типа " + storedMetadata->getTypeName().data() + ".");
    }
    _metadataVector.push_back(metadata);
}

const TypeMetadata *MetadataProvider::find(const energo::types::Uuid &typeUid) const {
    std::vector<const TypeMetadata *>::const_iterator it;
    for (it = _metadataVector.begin(); it != _metadataVector.end(); ++it) {
        if ((*it)->getTypeUid().equals(typeUid)) {
            break;
        }
    }
    return (it != _metadataVector.end()) ? *it : nullptr;
}

const TypeMetadata *MetadataProvider::find(const function<bool(const meta::TypeMetadata *)>& comparator) const {
    std::vector<const TypeMetadata *>::const_iterator it;
    for (it = _metadataVector.begin(); it != _metadataVector.end(); ++it) {
        if (comparator(*it)) {
            break;
        }
    }
    return (it != _metadataVector.end()) ? *it : nullptr;
}

MetadataProvider *MetadataProvider::GetStatic() {
    static auto staticMetadataProvider = new MetadataProvider{};
    return staticMetadataProvider;
}
