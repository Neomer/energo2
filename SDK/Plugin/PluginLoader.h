//
// Created by kir on 15.12.2019.
//

#ifndef ENERGO_PLUGINLOADER_H
#define ENERGO_PLUGINLOADER_H

#include <string_view>
#include "Plugin.h"

namespace energo::plugin {

class PluginLoader {
public:
    static bool tryLoadPlugin(std::string_view path, Plugin **plugin);
};

}

#endif //ENERGO_PLUGINLOADER_H
