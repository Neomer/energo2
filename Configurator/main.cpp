//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>

#include <BenchmarkTimer.h>
#include <Database/DatabaseUnavailableException.h>
#include <Metadata/MetadataProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.h>
#include <Database/Model/User.h>
#include <Metadata/TypeUids.h>
#include <Database/Managers/EntityManager.h>
#include <Plugin/PluginLoader.h>
#include <Metadata/MetadataRegistrar.h>

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
    
    auto staticMetadataProvider = MetadataProvider::GetStatic();
    
    timer.lap("Loading metadata...");
    MetadataRegistrar::RegisterMetaTypes(*staticMetadataProvider);
    
    DatabaseConnectionSettings settings;
    settings.setHost("localhost");
    settings.setPort(5432);
    settings.setUser("postgres");
    settings.setPassword("123456");
    settings.setDatabase("energo2");
    
    DatabaseConnectionProvider *connectionProvider = nullptr;
    Plugin *plugin;
    if (PluginLoader::tryLoadPlugin("../Plugins/TestPlugin/libTestPlugin.dll", &plugin)) {
        cout << "Loading plugin...\n";
        switch (plugin->getType()) {
            case PluginType::DatabaseAdapter:
            {
                connectionProvider = PluginLoader::createDatabaseProvider(plugin, settings);
                break;
            }
            case PluginType::DatabasePatch:
                break;
        }
    }
    
    if (connectionProvider == nullptr) {
        auto databaseProvider = dynamic_cast<const adapters::PostgreSqlConnectionProviderMetadata *>(
                staticMetadataProvider->find([](const TypeMetadata *metadata) -> bool {
                    return dynamic_cast<const adapters::PostgreSqlConnectionProviderMetadata *>(metadata) != nullptr;
                }));
        const_cast<adapters::PostgreSqlConnectionProviderMetadata *>(databaseProvider)->setInstance(
                        new adapters::PostgreSqlConnectionProvider{settings});
        connectionProvider = reinterpret_cast<DatabaseConnectionProvider *>(databaseProvider->createInstance());
    }
    timer.lap("metadata prepared");
    
    connectionProvider->initialize(1);
    timer.lap("all connections are open");

    auto manager = EntityManager::GetEntityManager(USER_TYPE_UID);
    timer.lap("manager found");
    if (manager == nullptr) {
        cout << "Manager not found!\n";
    } else {
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
    }
    timer.lap("all work is done.");

    connectionProvider->release();
    delete connectionProvider;

    return 0;
}

