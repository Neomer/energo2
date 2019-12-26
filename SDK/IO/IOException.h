//
// Created by kir on 26.12.2019.
//

#ifndef ENERGO_IOEXCEPTION_H
#define ENERGO_IOEXCEPTION_H

#include "../global.h"
#include <string_view>
#include <stdexcept>

namespace energo::exceptions {

class EXPORTS IOException : public std::runtime_error {
public:
    explicit IOException(std::string_view message);
};

}

#endif //ENERGO_IOEXCEPTION_H
