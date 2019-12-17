//
// Created by kir on 16.12.2019.
//

#include <iostream>
#include "FakeConnectionProvider.h"
#include "FakeDatabaseAdapter.h"

using namespace std;
using namespace energo::db;
using namespace energo::db::adapters;

FakeConnectionProvider::FakeConnectionProvider(const DatabaseConnectionSettings &connectionSettings) :
    DatabaseConnectionProvider(connectionSettings)
{
    cout << "Provider constructed.\n";
}

DatabaseConnection *FakeConnectionProvider::createConnection(random_device &randomDevice, const DatabaseConnectionSettings &connectionSettings) {
    return new FakeDatabaseAdapter(randomDevice, connectionSettings);
}

FakeConnectionProvider::~FakeConnectionProvider() {
    cout << "Provider destructed.\n";
}


extern "C" DatabaseConnectionProvider * EXPORTS create_provider(const DatabaseConnectionSettings &connectionSettings) {
    return new FakeConnectionProvider(connectionSettings);
}