//
// Created by kir on 10.12.2019.
//

#include "../../DatabaseUnavailableException.h"
#include "../../SqlQueryBadResultException.h"
#include "../../DatabaseConnectionIsClosedException.h"
#include "PostgreSqlConnectionAdapter.h"
#include "PostgreSqlResultAdapter.h"
#include "PostgreSqlTransformationProvider.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;
using namespace energo::exceptions;

PostgreSqlConnectionAdapter::PostgreSqlConnectionAdapter(random_device &randomDevice, const DatabaseConnectionSettings &settings) :
    DatabaseConnection(randomDevice, settings),
    _transformationProvider{},
    _queryBuilder{_transformationProvider}
{

}

void PostgreSqlConnectionAdapter::open() {
    if (isOpen()) {
        return;
    }
    
    DatabaseConnection::open();
    _connection = PQsetdbLogin(
            _connectionSettings.getHost().data(),
            to_string(_connectionSettings.getPort()).c_str(),
            nullptr,
            nullptr,
            _connectionSettings.getDatabase().data(),
            _connectionSettings.getUser().data(),
            _connectionSettings.getPassword().data());
    
    auto status = PQstatus(_connection);
    if (status != CONNECTION_OK) {
        throw DatabaseUnavailableException(_connectionSettings);
    }
}

void PostgreSqlConnectionAdapter::close() {
    if (!isOpen()) {
        return;
    }
    PQfinish(_connection);
    DatabaseConnection::close();
}

unique_ptr<SqlQuery> PostgreSqlConnectionAdapter::exec(std::string_view sql) const {
    if (!isOpen()) {
        throw DatabaseConnectionIsClosedException();
    }
    
    unique_ptr<DatabaseResultAdapter> adapter(new PostgreSqlResultAdapter(PQexec(_connection,sql.data()), _transformationProvider));
    std::unique_ptr<SqlQuery> result(new SqlQuery(move(adapter)));
    
    if (!result->isValid()) {
        throw SqlQueryBadResultException(PQerrorMessage(_connection));
    }
    return std::move(result);
}

const DatabaseQueryBuilder *PostgreSqlConnectionAdapter::queryBuilder() const {
    return &_queryBuilder;
}
