//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>

#include <BenchmarkTimer.h>
#include <Database/DatabaseUnavailableException.h>
#include <Database/Model/EntityMetadataRegistrar.h>
#include <Metadata/MetadataProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.h>
#include <Database/Managers/UserManager.h>
#include <Database/Model/User.h>

using namespace std;
using namespace energo::benchmark;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::meta;
using namespace energo::db::managers;
using namespace energo::types;
using namespace std::string_literals;

int main(int argv, char **argc) {
    BenchmarkTimer timer("Configurator app", cout);

    MetadataProvider metadataProvider;
    EntityMetadataRegistrar::RegisterEntityTypes(metadataProvider);
    timer.lap("metadata registered");

    DatabaseConnectionSettings settings;
    settings.setHost("localhost");
    settings.setPort(5432);
    settings.setUser("postgres");
    settings.setPassword("123456");
    settings.setDatabase("energo2");
    
    adapters::PostgreSqlConnectionProvider connectionProvider{settings};
    connectionProvider.initialize(1);
    UserManager manager{connectionProvider, metadataProvider};
    timer.lap("initialization finished");

    auto entity = manager.get(Uuid::Parse("b3b756eb-99ad-4300-a4e0-c2ffe0925c0d"));
    if (entity == nullptr) {
        cout << "User not found.\n";
    } else {
        auto user = dynamic_cast<User *>(entity.get());
        cout << "User found!\n"
             << "   " << user->getFirstName() << " [" << user->getUid() << "]\n";
    }
    
    connectionProvider.release();

    return 0;
}

