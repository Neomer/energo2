//
// Created by kir on 11.12.2019.
//

#include "EntityMetadata.h"

#include <utility>

using namespace std;
using namespace energo::meta;
using namespace energo::types;

EntityMetadata::EntityMetadata(const Uuid &typeUid, const Uuid &parentTypeUid, const vector<string_view>& fieldNames) :
    ClassMetadata(typeUid, parentTypeUid)
{
    hash<string_view> sHash;
    
    for (auto item : fieldNames) {
        _fieldNames.emplace_back(item, sHash(item));
    }
}

const EntityMetadata::TFieldWithHashList &EntityMetadata::getFieldNames() const {
    return _fieldNames;
}
