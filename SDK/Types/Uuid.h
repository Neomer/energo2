//
// Created by vinokurov on 04.12.2019.
//

#ifndef ENERGO_UUID_H
#define ENERGO_UUID_H

#include "../global.h"

namespace energo::types {

class EXPORTS Uuid final {
public:
    Uuid();

    bool equals(const Uuid &other) const;

    bool operator==(const Uuid &other) const;

private:

};

}

#endif //ENERGO_UUID_H
