//
// Created by vinokurov on 09.12.2019.
//

#include <iostream>
#include "User.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::entity;

void User::fromSql(const SqlQueryReader &reader) {
    IdentifiedEntity::fromSql(reader);
    _username = reader.value("Username").asString();
    _firstName = reader.value("FirstName").asString();
    _secondName = reader.value("SecondName").asString();
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
