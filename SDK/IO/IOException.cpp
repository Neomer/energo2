//
// Created by kir on 26.12.2019.
//

#include "IOException.h"

energo::exceptions::IOException::IOException(std::string_view message) :
    std::runtime_error{message.data()}
{

}
