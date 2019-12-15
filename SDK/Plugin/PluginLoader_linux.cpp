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
}


#endif // OS_LINUX