//
// Created by kir on 16.12.2019.
//

#ifndef ENERGO_FAKECONNECTIONPROVIDER_H
#define ENERGO_FAKECONNECTIONPROVIDER_H

#include "../../SDK/Database/DatabaseConnectionProvider.h"

namespace energo::db::adapters {

class FakeConnectionProvider : public DatabaseConnectionProvider {
public:
    explicit FakeConnectionProvider(const DatabaseConnectionSettings &connectionSettings);

protected:
    DatabaseConnection *
    createConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) override;
};

}


#endif //ENERGO_FAKECONNECTIONPROVIDER_H
