//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_POSTGRESQLCONNECTIONPROVIDER_H
#define ENERGO_POSTGRESQLCONNECTIONPROVIDER_H

#include "../../../Metadata/SingletonClassMetadata.h"
#include "../../DatabaseConnectionProvider.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlConnectionProvider : public DatabaseConnectionProvider {
public:
    explicit PostgreSqlConnectionProvider(const DatabaseConnectionSettings &connectionSettings);

protected:
    DatabaseConnection *
    createConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) override;
};

class EXPORTS PostgreSqlConnectionProviderMetadata : public meta::SingletonClassMetadata {
public:
    PostgreSqlConnectionProviderMetadata();
    
    [[nodiscard]] std::string_view getTypeName() const override;

protected:
    void *createInstanceInternal() const override;
};

}

#endif //ENERGO_POSTGRESQLCONNECTIONPROVIDER_H
