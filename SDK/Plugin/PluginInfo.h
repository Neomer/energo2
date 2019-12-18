//
// Created by kir on 15.12.2019.
//

#ifndef ENERGO_PLUGININFO_H
#define ENERGO_PLUGININFO_H

namespace energo::plugin {

enum class PluginType {
    DatabaseAdapter,
    DatabasePatch
};

extern "C" struct PluginInfo {
    PluginType type;
    const char *uid;
    const char *name;
    const char *version;
};

typedef PluginInfo (*PluginInfoFunc)();


}



#endif //ENERGO_PLUGININFO_H
