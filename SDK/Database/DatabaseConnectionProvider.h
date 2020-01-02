//
// Created by kir on 11.12.2019.
//

#ifndef ENERGO_DATABASECONNECTIONPROVIDER_H
#define ENERGO_DATABASECONNECTIONPROVIDER_H

#include <vector>
#include "../Metadata/TypeMetadata.h"
#include "DatabaseConnection.h"
#include "../Metadata/MetadataProvider.h"

namespace energo::db {

class EXPORTS DatabaseConnectionProvider {
    std::vector<std::shared_ptr<DatabaseConnection>> _connections;
    std::random_device _randomDevice;
    const DatabaseConnectionSettings _connectionSettings;
    
public:
    static DatabaseConnectionProvider *GetFromMetadata(const meta::MetadataProvider &metadataProvider);
    
    explicit DatabaseConnectionProvider(const DatabaseConnectionSettings &connectionSettings, const types::Uuid &typeUid);
    
    virtual ~DatabaseConnectionProvider() = default;
    
    void initialize(size_t defaultConnectionCount);
    
    void release();
    
    [[nodiscard]] const DatabaseConnection *getConnection() const;
    
protected:
    [[nodiscard]] virtual DatabaseConnection *createConnection(std::random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) = 0;
};

}


#endif //ENERGO_DATABASECONNECTIONPROVIDER_H
