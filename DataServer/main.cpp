//
// Created by vinokurov on 04.12.2019.
//

#include <iostream>

#include <BenchmarkTimer.h>
#include <Database/DatabaseUnavailableException.h>
#include <Metadata/MetadataProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.h>
#include <Plugin/PluginLoader.h>
#include <Metadata/MetadataRegistrar.h>
#include <Network/TcpServer.h>

using namespace std;
using namespace energo;
using namespace energo::benchmark;
using namespace energo::db;
using namespace energo::types;
using namespace energo::plugin;

int main(int argv, char **argc) {
    random_device rd;
    BenchmarkTimer timer("DataServer app", cout);
    
    auto staticMetadataProvider = meta::MetadataProvider::GetStatic();
    
    timer.lap("Loading metadata...");
    meta::MetadataRegistrar::RegisterMetaTypes(*staticMetadataProvider);
    
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
                staticMetadataProvider->find([](const meta::TypeMetadata *metadata) -> bool {
                    return dynamic_cast<const adapters::PostgreSqlConnectionProviderMetadata *>(metadata) != nullptr;
                }));
        const_cast<adapters::PostgreSqlConnectionProviderMetadata *>(databaseProvider)->setInstance(
                        new adapters::PostgreSqlConnectionProvider{settings});
        connectionProvider = reinterpret_cast<DatabaseConnectionProvider *>(databaseProvider->createInstance());
    }
    timer.lap("metadata prepared");
    
    connectionProvider->initialize(1);
    timer.lap("all connections are open");

    net::TcpServer server;
    if (!server.bind(net::ConnectionPoint{"0.0.0.0", 5551})) {
        throw runtime_error{"Не удалось связать сервер с портом."};
    }
    server.onConnectionReadyListener(
            [](std::shared_ptr<net::TcpSocket> socket) {
                cout << "Новое подключение!\n";
                socket->close();
            });
    server.listen();
    
    getchar();
    
    server.close();
    connectionProvider->release();
    delete connectionProvider;


    return 0;
}

