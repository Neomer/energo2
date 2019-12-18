//
// Created by kir on 11.12.2019.
//

#include "../../../Metadata/TypeUids.h"
#include "PostgreSqlConnectionAdapter.h"
#include "PostgreSqlConnectionProvider.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;


PostgreSqlConnectionProvider::PostgreSqlConnectionProvider(const DatabaseConnectionSettings &connectionSettings) :
    DatabaseConnectionProvider{connectionSettings, POSTGRESQLPROVIDER_TYPE_UID}
{

}

DatabaseConnection *PostgreSqlConnectionProvider::createConnection(random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) {
    return new PostgreSqlConnectionAdapter(randomDevice, connectionSettings);
}

string_view PostgreSqlConnectionProvider::getTypeName() const {
    return "PostgreSqlConnectionProvider";
}
