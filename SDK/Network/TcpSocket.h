//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_TCPSOCKET_WIN_H
#define ENERGO_TCPSOCKET_WIN_H

#include "../global.h"
#include "../os.h"
#include <cinttypes>
#include <string_view>
#include <functional>
#include <optional>
#include "../IO/AsyncIODevice.h"

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
    std::optional<std::function<void(io::IOStream<char> &)>> _dataListener;

public:
    TcpSocket(SocketDescriptorType descriptor);
    
    TcpSocket();
    
    virtual ~TcpSocket();
    
    std::future<size_t> write(io::IOStream<char> &stream);
    
    TcpSocket &onBytesAvailable(std::function<void(io::IOStream<char> &)> &dataListener);
    
};

}

#endif //ENERGO_TCPSOCKET_WIN_H
