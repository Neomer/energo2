//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_TCPSOCKET_WIN_H
#define ENERGO_TCPSOCKET_WIN_H

#include "../global.h"
#include "../os.h"
#include <cinttypes>
#include <string_view>

namespace energo::net {

class EXPORTS TcpSocket {
public:
    using SocketDescriptorType =
#ifdef ENVIRONMENT64
    uint64_t;
#else
    uint32_t ;
#endif

private:
    SocketDescriptorType _socketDescriptor;

public:
    TcpSocket(SocketDescriptorType descriptor);

    void write(std::string_view data) const;

    size_t read(char *buffer, size_t length) const;

    void close();
};

}

#endif //ENERGO_TCPSOCKET_WIN_H
