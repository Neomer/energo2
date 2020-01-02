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
#include <zmq.h>

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

    auto context = zmq_ctx_new();
    zmq_ctx_set(context, ZMQ_IO_THREADS, 4);
    auto socket = zmq_socket(context, ZMQ_PUB);
    zmq_connect(socket, "tcp://lib.ru:80");
    zmq_setsockopt(socket, ZMQ_IDENTITY, nullptr, 0);
    
    zmq_send(socket, nullptr, 0, ZMQ_NOBLOCK);
    
    zmq_close (socket);
    zmq_ctx_destroy (context);

    connectionProvider->release();
    delete connectionProvider;


    return 0;
}

