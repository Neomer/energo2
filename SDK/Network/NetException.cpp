//
// Created by kir on 29.12.2019.
//

#include "NetException.h"

energo::exceptions::NetException::NetException(std::string_view message) :
    std::runtime_error{message.data()}
{

}
