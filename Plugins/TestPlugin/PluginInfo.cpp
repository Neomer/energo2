//
// Created by kir on 15.12.2019.
//

#include "../../SDK/global.h"
#include "../../SDK/Plugin/PluginInfo.h"

namespace energo::plugin {

extern "C" PluginInfo EXPORTS plugin_info() {
    return {
            PluginType::DatabaseAdapter,
            "180bc317-0e2b-4296-8e2b-33edb9b8a605",
            "TestPlugin",
            "1.0.0"
    };
}

}