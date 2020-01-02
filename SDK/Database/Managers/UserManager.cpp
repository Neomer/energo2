//
// Created by kir on 11.12.2019.
//

#include "../../Metadata/TypeUids.h"
#include "UserManager.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::db::managers;
using namespace energo::types;
using namespace energo::meta;


managers::UserManager::UserManager(const DatabaseConnectionProvider &provider,
                                   const MetadataProvider &metadataProvider)  :
        EntityManager{provider, USERMANAGER_TYPE_UID, USER_TYPE_UID, metadataProvider}
{

}

managers::UserManagerMetadata::UserManagerMetadata() :
        EntityManagerMetadata{ USER_TYPE_UID },
        SingletonClassMetadata{ USERMANAGER_TYPE_UID, ENTITYMANAGER_TYPE_UID }
{

}

string_view managers::UserManagerMetadata::getTypeName() const {
    return "UserManagerMetadata";
}

void *managers::UserManagerMetadata::createInstanceInternal() const {
    auto databaseProvider = DatabaseConnectionProvider::GetFromMetadata(*MetadataProvider::GetStatic());
    return new UserManager{*databaseProvider, *MetadataProvider::GetStatic()};
}
