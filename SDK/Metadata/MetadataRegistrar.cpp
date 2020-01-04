//
// Created by kir on 18.12.2019.
//

#include "MetadataProvider.h"
#include "MetadataRegistrar.h"

using namespace energo::meta;

#include "../Database/Model/User.h"
#include "../Database/Managers/UserManager.h"
#include "../Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.h"
#include "../Database/Adapters/PostgreSql/Patches/InitialPatch.h"
#include "../Threads/ThreadPool.h"

void MetadataRegistrar::RegisterMetaTypes(MetadataProvider &metadataProvider) {
    metadataProvider.registerMetadata(new db::entity::UserMetadata{});
    metadataProvider.registerMetadata(new db::managers::UserManagerMetadata{});
    
    /**
     * PostgreSql
     */
    metadataProvider.registerMetadata(new db::adapters::PostgreSqlConnectionProviderMetadata{});
    metadataProvider.registerMetadata(new db::patch::InitialPatchMetadata{});
    
    metadataProvider.registerMetadata(new threads::ThreadPoolMetadata{});
}
