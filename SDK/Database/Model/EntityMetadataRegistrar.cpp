//
// Created by vinokurov on 11.12.2019.
//

#include "EntityMetadataRegistrar.h"

using namespace std;
using namespace energo::db::entity;
using namespace energo::meta;
using namespace energo::types;

#include "User.h"

void EntityMetadataRegistrar::RegisterEntityTypes(MetadataProvider &provider) {
    provider.registerMetadata(shared_ptr<TypeMetadata>(new UserMetadata()));
}
