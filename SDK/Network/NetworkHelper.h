//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_NETWORKHELPER_H
#define ENERGO_NETWORKHELPER_H

#include "../classes.h"
#include "../global.h"

namespace energo::net {

class EXPORTS NetworkHelper {
    STATIC_CLASS(NetworkHelper)

public:
    static void Initialize();

    static void Release();
};

}

#endif //ENERGO_NETWORKHELPER_H
