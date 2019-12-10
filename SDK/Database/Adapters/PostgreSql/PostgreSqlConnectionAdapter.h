//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLCONNECTIONADAPTER_H
#define ENERGO_POSTGRESQLCONNECTIONADAPTER_H

#include <libpq-fe.h>
#include "../../DatabaseConnection.h"
#include "PostgreSqlTransformationProvider.h"

namespace energo::db::adapters {

class EXPORTS PostgreSqlConnectionAdapter: public DatabaseConnection {
    PGconn *_connection;
    PostgreSqlTransformationProvider _transformationProvider;

public:
    PostgreSqlConnectionAdapter(std::random_device &randomDevice, const energo::db::DatabaseConnectionSettings &settings);
    
    void open() override;
    
    void close() override;
    
    std::unique_ptr<SqlQuery> exec(std::string_view sql) const override;
};

}

#endif //ENERGO_POSTGRESQLCONNECTIONADAPTER_H
