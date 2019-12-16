//
// Created by kir on 15.12.2019.
//

#include "Plugin.h"

using namespace std;
using namespace energo;
using namespace energo::plugin;

const energo::types::Uuid &Plugin::getPluginUid() const {
    return _pluginUid;
}

Plugin::Plugin(const PluginInfo &pluginInfo, void *pluginHandle) :
    _pluginUid{types::Uuid::Parse(pluginInfo.uid)},
    _version{types::Version::Parse(pluginInfo.version)},
    _name{pluginInfo.name},
    _type{pluginInfo.type},
    _handle{pluginHandle}
{

}

const types::Version &Plugin::getVersion() const {
    return _version;
}

const string &Plugin::getName() const {
    return _name;
}

PluginType Plugin::getType() const {
    return _type;
}

void *Plugin::getHandle() const {
    return _handle;
}
