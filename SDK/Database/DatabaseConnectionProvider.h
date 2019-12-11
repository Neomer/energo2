//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_DATABASECONNECTIONPROVIDER_H
#define ENERGO_DATABASECONNECTIONPROVIDER_H

#include <vector>
#include "DatabaseConnection.h"

namespace energo::db {

class DatabaseConnectionProvider {
    std::vector<std::shared_ptr<DatabaseConnection>> _connections;
    std::random_device _randomDevice;
    const DatabaseConnectionSettings _connectionSettings;
    
public:
    explicit DatabaseConnectionProvider(const DatabaseConnectionSettings &connectionSettings);
    
    void initialize(size_t defaultConnectionCount);
    
    void release();
    
    [[nodiscard]] const DatabaseConnection *getConnection() const;

protected:
    [[nodiscard]] virtual DatabaseConnection *createConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) = 0;
};

}


#endif //ENERGO_DATABASECONNECTIONPROVIDER_H
