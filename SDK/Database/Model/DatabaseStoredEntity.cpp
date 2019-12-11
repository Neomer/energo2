//
// Created by vinokurov on 09.12.2019.
//

#include "DatabaseStoredEntity.h"

using namespace energo::types;
using namespace energo::db::entity;

DatabaseStoredEntity::DatabaseStoredEntity(const Uuid &typeUid) :
    MetaClass(typeUid)
{

}
