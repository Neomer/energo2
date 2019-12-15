//
// Created by vinokurov on 09.12.2019.
//

#include <iostream>
#include "User.h"
#include "../../Metadata/TypeUids.h"
#include "../TransformationProvider.h"

using namespace std;
using namespace energo::db;
using namespace energo::types;
using namespace energo::db::entity;

User::User()
{

}

[[nodiscard]] std::string_view User::getUsername() const {
    return _username;
}

void User::setUsername(std::string_view username) {
    _username = username;
}

[[nodiscard]] std::string_view User::getFirstName() const {
    return _firstName;
}

void User::setFirstName(std::string_view firstName) {
    _firstName = firstName;
}

[[nodiscard]] std::string_view User::getSecondName() const {
    return _secondName;
}

void User::setSecondName(std::string_view secondName) {
    _secondName = secondName;
}

void User::fromSql(const SqlQueryReader &reader) {
    IdentifiedEntity::fromSql(reader);
    _username = reader.value("Username").asString();
    _firstName = reader.value("FirstName").asString();
    _secondName = reader.value("SecondName").asString();
}

void User::toSqlValues(DatabaseStoredEntity::TFieldValuePairList &fieldValueList, const TransformationProvider &transformationProvider) const {
    IdentifiedEntity::toSqlValues(fieldValueList, transformationProvider);
    fieldValueList.emplace_back("Username", transformationProvider.formatValue(_username));
    fieldValueList.emplace_back("FirstName", transformationProvider.formatValue(_firstName));
    fieldValueList.emplace_back("SecondName", transformationProvider.formatValue(_secondName));
}

User::User(const Uuid &uid) : IdentifiedEntity(uid) {

}

#define USERNAME_HASH       1647932740699693284
#define FIRSTNAME_HASH      8008681739169510336
#define SECONDNAME_HASH     13844251714853448021ull

string User::getFieldValue(size_t fieldHash, const TransformationProvider &transformationProvider) const {
    
    hash<string_view> sHash;
    
    switch (fieldHash) {
        case USERNAME_HASH: return transformationProvider.formatValue(_username);
        case FIRSTNAME_HASH: return transformationProvider.formatValue(_firstName);
        case SECONDNAME_HASH: return transformationProvider.formatValue(_secondName);
        default: return IdentifiedEntity::getFieldValue(fieldHash, transformationProvider);
    }
}

#undef USERNAME_HASH
#undef FIRSTNAME_HASH
#undef SECONDNAME_HASH

UserMetadata::UserMetadata() :
    EntityMetadata{
            USER_TYPE_UID,
            Uuid::Empty(),
            {
                    "Uid", "Username", "FirstName", "SecondName"
            }
    }
{

}
