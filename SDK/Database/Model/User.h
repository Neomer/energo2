//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_USER_H
#define ENERGO_USER_H

#include <cinttypes>
#include <string>
#include <string_view>
#include "../../Metadata/ClassMetadata.h"
#include "IdentifiedEntity.h"

namespace energo::db::entity {

class User : public IdentifiedEntity {
    std::string _username, _firstName, _secondName;

public:
    User();

    [[nodiscard]] std::string_view getUsername() const;

    void setUsername(std::string_view username);

    [[nodiscard]] std::string_view getFirstName() const;

    void setFirstName(std::string_view firstName);

    [[nodiscard]] std::string_view getSecondName() const;

    void setSecondName(std::string_view secondName);

public:
    void fromSql(const SqlQueryReader &reader) override;
};

class UserMetadata : public meta::ClassMetadata {
public:
    UserMetadata();

    [[nodiscard]] meta::MetaClass *createInstance() const override;

    std::string_view getTypeName() const override;
};

}

#endif //ENERGO_USER_H
