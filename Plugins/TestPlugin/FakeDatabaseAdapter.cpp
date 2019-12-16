//
// Created by kir on 16.12.2019.
//

#include <iostream>
#include "FakeDatabaseAdapter.h"

using namespace std;
using namespace energo::db;

adapters::FakeDatabaseAdapter::FakeDatabaseAdapter(random_device &randomDevice, const DatabaseConnectionSettings &settings) :
    DatabaseConnection(randomDevice, settings)
{

}

void adapters::FakeDatabaseAdapter::open() {
    cout << "Fake connection ready." << endl;
    DatabaseConnection::open();
}

void adapters::FakeDatabaseAdapter::close() {
    DatabaseConnection::close();
    cout << "Fake connection is closed." << endl;
}

const SqlQueryBuilder *adapters::FakeDatabaseAdapter::queryBuilder() const {
    return nullptr;
}

unique_ptr<SqlQuery> adapters::FakeDatabaseAdapter::exec(std::string_view sql) const {
    return std::unique_ptr<SqlQuery>(nullptr);
}

const TransformationProvider &adapters::FakeDatabaseAdapter::transformationProvider() const {
    return _transformationProvider;
}

