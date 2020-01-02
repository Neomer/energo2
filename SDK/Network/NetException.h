//
// Created by kir on 29.12.2019.
//

#ifndef ENERGO_NETEXCEPTION_H
#define ENERGO_NETEXCEPTION_H

#include <stdexcept>
#include <string_view>

namespace energo::exceptions {

class NetException  : public std::runtime_error {
public:
    explicit NetException(std::string_view message);
};

}


#endif //ENERGO_NETEXCEPTION_H
