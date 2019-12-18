//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_POSTGRESQLCONNECTIONPROVIDER_H
#define ENERGO_POSTGRESQLCONNECTIONPROVIDER_H

#include "../../DatabaseConnectionProvider.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlConnectionProvider : public DatabaseConnectionProvider {
public:
    explicit PostgreSqlConnectionProvider(const DatabaseConnectionSettings &connectionSettings);

protected:
    DatabaseConnection *
    createConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) override;

public:
    std::string_view getTypeName() const override;
};

}

#endif //ENERGO_POSTGRESQLCONNECTIONPROVIDER_H
