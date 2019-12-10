//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_USER_H
#define ENERGO_USER_H

#include <cinttypes>
#include <string>
#include <string_view>
#include "DatabaseStoredEntity.h"

namespace energo::db::entity {

class User : public DatabaseStoredEntity {
    std::string _username, _firstName, _secondName;

public:
    [[nodiscard]] std::string_view getUsername() const;

    void setUsername(std::string_view username);

    [[nodiscard]] std::string_view getFirstName() const;

    void setFirstName(std::string_view firstName);

    [[nodiscard]] std::string_view getSecondName() const;

    void setSecondName(std::string_view secondName);

public:
    void fromSql(const SqlQueryReader &reader) override;
};

}

#endif //ENERGO_USER_H
