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


UserManager::UserManager(const DatabaseConnectionProvider &provider, const MetadataProvider &metadataProvider) :
    EntityManager(provider, USER_TYPE_UID, metadataProvider)
{

}
