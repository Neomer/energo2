//
// Created by kir on 10.12.2019.
//

#include "IdentifiedEntity.h"

using namespace std;
using namespace energo::types;
using namespace energo::db::entity;
using namespace energo::db;

IdentifiedEntity::IdentifiedEntity(const Uuid &typeUid) :
    DatabaseStoredEntity(typeUid)
{

}

void IdentifiedEntity::fromSql(const SqlQueryReader &reader) {
    _uid = reader.value("Uid").asUuid();
}

const Uuid &IdentifiedEntity::getUid() const {
    return _uid;
}

void IdentifiedEntity::setUid(const Uuid &uid) {
    _uid = uid;
}

