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
    provider.registerMetadata(new UserMetadata());
}

#include "../Managers/UserManager.h"

using namespace energo::db::managers;

void EntityMetadataRegistrar::RegisterEntityManagers(MetadataProvider &metadataProvider,
                                                     const energo::db::DatabaseConnectionProvider &databaseConnectionProvider)
{
    metadataProvider.registerMetadata(new UserManager{databaseConnectionProvider, metadataProvider});
}
