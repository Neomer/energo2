//
// Created by kir on 10.12.2019.
//

#include <stdexcept>
#include "IdentifiedEntity.h"

using namespace std;
using namespace energo::types;
using namespace energo::db::entity;
using namespace energo::db;


void IdentifiedEntity::fromSql(const SqlQueryReader &reader) {
    _uid = reader.value("Uid").asUuid();
}

const Uuid &IdentifiedEntity::getUid() const {
    return _uid;
}

void IdentifiedEntity::setUid(const Uuid &uid) {
    _uid = uid;
}

void IdentifiedEntity::toSqlValues(
        DatabaseStoredEntity::TFieldValuePairList &fieldValueList,
        const TransformationProvider &transformationProvider) const
{
    fieldValueList.emplace_back("Uid", transformationProvider.formatValue(_uid));
}

IdentifiedEntity::IdentifiedEntity(const Uuid &uid) :
    _uid{uid}
{

}

#define UID_HASH    4683115637787579149

string IdentifiedEntity::getFieldValue(size_t fieldHash, const TransformationProvider &transformationProvider) const {
    if (fieldHash == UID_HASH) {
        return transformationProvider.formatValue(_uid);
    } else {
        throw invalid_argument("Поля с указанным хэшем не найдено.");
    }
}

#undef UID_HASH

