//
// Created by kir on 15.12.2019.
//

#include "../os.h"

#ifdef OS_LINUX

#include <iostream>

#include <dlfcn.h>
#include "PluginLoader.h"
#include "PluginInfo.h"

using namespace std;
using namespace energo::plugin;
using namespace energo::db;


bool PluginLoader::tryLoadPlugin(string_view path, class Plugin **plugin) {
    auto libraryHandle = dlopen(path.data(), RTLD_NOW);
    if (libraryHandle == nullptr) {
        return false;
    }
    auto libraryPluginInfoFunc = reinterpret_cast<PluginInfoFunc>(dlsym(libraryHandle, "plugin_info"));
    if (libraryPluginInfoFunc == nullptr) {
        return false;
    }
    try{
        *plugin = new Plugin(libraryPluginInfoFunc(), libraryHandle);
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        return false;
    }
    return true;
}

DatabaseConnectionProvider *PluginLoader::createDatabaseProvider(const Plugin *plugin, const DatabaseConnectionSettings &settings) {
    auto libraryPluginInfoFunc = reinterpret_cast<DatabaseConnectionProvider *(*)(const DatabaseConnectionSettings &)>(dlsym(plugin->getHandle(), "create_provider"));
    if (libraryPluginInfoFunc == nullptr) {
        return nullptr;
    }
    try{
        return libraryPluginInfoFunc(settings);
    }
    catch (exception &ex) {
        cout << ex.what() << endl;
        return nullptr;
    }
}


#endif // OS_LINUX