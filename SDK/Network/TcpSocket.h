//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_TCPSOCKET_WIN_H
#define ENERGO_TCPSOCKET_WIN_H

#include "../global.h"
#include "../os.h"
#include <cinttypes>
#include <string_view>
#include "../IO/AsyncIODevice.h"

namespace energo::net {

class EXPORTS TcpSocket : public io::AsyncIODevice<char> {
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

    bool open(OpenMode openMode) override;

    void close() override;

};

}

#endif //ENERGO_TCPSOCKET_WIN_H
