//
// Created by vinokurov on 16.12.2019.
//

#include "../os.h"

#ifdef OS_WIN

#include <iostream>
#include <windows.h>

#include "PluginLoader.h"
#include "PluginInfo.h"

using namespace std;
using namespace energo::plugin;


bool PluginLoader::tryLoadPlugin(string_view path, class Plugin **plugin) {
    auto libraryHandle = LoadLibrary(path.data());
    if (libraryHandle == nullptr) {
        return false;
    }
    auto libraryPluginInfoFunc = reinterpret_cast<PluginInfoFunc>(GetProcAddress(libraryHandle, "plugin_info"));
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


#endif // OS_WIN