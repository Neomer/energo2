//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>

#include <BenchmarkTimer.h>
#include <Database/DatabaseUnavailableException.h>
#include <Database/Model/EntityMetadataRegistrar.h>
#include <Metadata/MetadataProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.h>
#include <Database/Model/User.h>
#include <Metadata/TypeUids.h>
#include <Database/Managers/EntityManager.h>
#include <Plugin/PluginLoader.h>

using namespace std;
using namespace energo::benchmark;
using namespace energo::db;
using namespace energo::db::entity;
using namespace energo::meta;
using namespace energo::db::managers;
using namespace energo::types;

using namespace energo::plugin;

int main(int argv, char **argc) {
    random_device rd;
    BenchmarkTimer timer("Configurator app", cout);
    
    Plugin *plugin;
    if (PluginLoader::tryLoadPlugin("../Plugins/TestPlugin/libTestPlugin.dll", &plugin)) {
        cout << "Loading plugin...\n";
    }

    DatabaseConnectionSettings settings;
    settings.setHost("localhost");
    settings.setPort(5432);
    settings.setUser("postgres");
    settings.setPassword("123456");
    settings.setDatabase("energo2");
    
    adapters::PostgreSqlConnectionProvider connectionProvider{settings};
    connectionProvider.initialize(1);
    timer.lap("connection ready");
    
    MetadataProvider metadataProvider;
    EntityMetadataRegistrar::RegisterEntityTypes(metadataProvider);
    EntityMetadataRegistrar::RegisterEntityManagers(metadataProvider, connectionProvider);
    timer.lap("initialization finished");

    auto manager = dynamic_cast<const EntityManager *>(metadataProvider.find(USERMANAGER_TYPE_UID));
    auto entity = manager->get(Uuid::Parse("4635efb6-1466-414b-97ca-5068d808032b"));
    if (entity == nullptr) {
        cout << "User not found.\n";
    } else {
        auto user = dynamic_cast<User *>(entity.get());
        cout << "User found!\n"
             << "   " << user->getFirstName() << " [" << user->getUid() << "]\n";
        
        user->setFirstName("Администратор");
        manager->update(*user);
    }
    connectionProvider.release();

    return 0;
}

