//
// Created by vinokurov on 11.12.2019.
//

#include <algorithm>
#include <stdexcept>
#include "MetadataProvider.h"

using namespace std;
using namespace energo::meta;
using namespace std::string_literals;

void MetadataProvider::registerMetadata(std::shared_ptr<TypeMetadata> metadata) {
    auto storedMetadata = find(metadata->getTypeUid());
    if (storedMetadata != nullptr) {
        throw runtime_error("Не удалось зарегистрировать метаданные для типа "s +
            metadata->getTypeName().data() +
            ". Идентификатор "s + metadata->getTypeUid().toString() +
            " уже зарегистрированы для типа " + storedMetadata->getTypeName().data() + ".");
    }
    _metadataVector.emplace_back(metadata);
}

const TypeMetadata *MetadataProvider::find(const energo::types::Uuid &typeUid) const {
    std::vector<std::shared_ptr<TypeMetadata>>::const_iterator it;
    for (it = _metadataVector.begin(); it != _metadataVector.end(); ++it) {
        if ((*it)->getTypeUid().equals(typeUid)) {
            break;
        }
    }
    return (it != _metadataVector.end()) ? it->get() : nullptr;
}