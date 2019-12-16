//
// Created by kir on 15.12.2019.
//

#ifndef ENERGO_PLUGIN_H
#define ENERGO_PLUGIN_H

#include "../Types/Uuid.h"
#include "../Types/Version.h"
#include "PluginInfo.h"

namespace energo::plugin {

class Plugin {
    const types::Uuid _pluginUid;
    const types::Version _version;
    std::string _name;
    PluginType _type;
    void *_handle;
    
public:
    explicit Plugin(const PluginInfo &pluginInfo, void *pluginHandle);
    
    [[nodiscard]] const types::Uuid &getPluginUid() const;
    
    [[nodiscard]] const types::Version &getVersion() const;
    
    [[nodiscard]] const std::string &getName() const;
    
    [[nodiscard]] PluginType getType() const;
    
    void *getHandle() const;
};

}

#endif //ENERGO_PLUGIN_H
