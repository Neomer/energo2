//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_IODEVICE_H
#define ENERGO_IODEVICE_H

#include "../global.h"
#include "../os.h"
#include <string_view>

namespace energo::io {

class EXPORTS IODevice {
public:
    enum class OpenMode {
        ReadOnly,
        WriteOnly,
        ReadWrite
    };

    IODevice() = default;
    virtual ~IODevice() = default;

    virtual bool open(OpenMode openMode) = 0;
    virtual void close() = 0;

    virtual size_t write(std::string_view data) = 0;
    virtual size_t read(char *buffer, size_t length) = 0;

};

}

#endif //ENERGO_IODEVICE_H
