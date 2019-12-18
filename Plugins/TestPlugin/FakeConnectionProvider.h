//
// Created by kir on 16.12.2019.
//

#ifndef ENERGO_FAKECONNECTIONPROVIDER_H
#define ENERGO_FAKECONNECTIONPROVIDER_H

#include "../../SDK/Database/DatabaseConnectionProvider.h"

namespace energo::db::adapters {

class EXPORTS FakeConnectionProvider : public DatabaseConnectionProvider {
public:
    explicit FakeConnectionProvider(const DatabaseConnectionSettings &connectionSettings);

    ~FakeConnectionProvider() override;

protected:
    DatabaseConnection *
    createConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) override;

public:
    std::string_view getTypeName() const override;
};

}


#endif //ENERGO_FAKECONNECTIONPROVIDER_H
