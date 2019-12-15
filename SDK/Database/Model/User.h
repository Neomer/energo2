//
// Created by vinokurov on 09.12.2019.
//

#ifndef ENERGO_USER_H
#define ENERGO_USER_H

#include <cinttypes>
#include <string>
#include <string_view>
#include "../../Metadata/EntityMetadata.h"
#include "IdentifiedEntity.h"


namespace energo::db::entity {

class EXPORTS User : public IdentifiedEntity {
    std::string _username, _firstName, _secondName;

public:
    User();
    
    explicit User(const types::Uuid &uid);

    [[nodiscard]] std::string_view getUsername() const;

    void setUsername(std::string_view username);

    [[nodiscard]] std::string_view getFirstName() const;

    void setFirstName(std::string_view firstName);

    [[nodiscard]] std::string_view getSecondName() const;

    void setSecondName(std::string_view secondName);
    
public:
    void fromSql(const SqlQueryReader &reader) override;
    
    void toSqlValues(DatabaseStoredEntity::TFieldValuePairList &fieldValueList, const TransformationProvider &transformationProvider) const override;
    
    [[nodiscard]] std::string getFieldValue(size_t fieldHash, const TransformationProvider &transformationProvider) const override;
};

class UserMetadata : public meta::EntityMetadata {
public:
    UserMetadata();

    [[nodiscard]] void *createInstance() const override {
        return new User();
    }

    [[nodiscard]] std::string_view getTypeName() const override {
        return "User";
    }
    
    [[nodiscard]] std::string_view getTableName() const override {
        return "Users";
    }
};

}

#endif //ENERGO_USER_H
