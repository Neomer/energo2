//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_TCPSOCKET_WIN_H
#define ENERGO_TCPSOCKET_WIN_H

#include "../os.h"
#include <cinttypes>
#include <string_view>
#include <functional>
#include <optional>
#include <thread>
#include <atomic>
#include "../IO/AsyncIODevice.h"
#include "ConnectionPoint.h"

namespace energo::net {

class EXPORTS TcpSocket : public io::IODevice<char> {
public:
    using SocketDescriptorType =
#ifdef ENVIRONMENT64
    uint64_t;
#else
    uint32_t ;
#endif

protected:
    SocketDescriptorType _socketDescriptor;

private:
    std::optional<std::function<void(io::IOStream<char> &)>> _dataListener;
    std::thread _readThread;
    std::atomic_bool _run;
    io::IOStream<char> _inputStream;
    net::ConnectionPoint _remotePoint;
    io::Device::OpenMode _mode;

public:
    TcpSocket(SocketDescriptorType descriptor);
    
    TcpSocket();
    
    virtual ~TcpSocket();
    
    [[nodiscard]] bool open(io::Device::OpenMode openMode) override;
    
    /**
     * Подключает сокет к удаленному хосту.
     * @param connectionPoint Точка подключения к удаленному хосту.
     * @return Удалось ли подключниться.
     * @throws enrgo::exceptions::NetException некорректная точка подключения.
     */
    [[nodiscard]] bool connect(const net::ConnectionPoint &connectionPoint);
    
    void close() override;
    
    std::future<size_t> read(io::IOStream<char> &stream) override;
    
    std::future<size_t> write(io::IOStream<char> &stream) override;
    
    TcpSocket &onBytesAvailable(std::function<void(io::IOStream<char> &)> &dataListener);

protected:
    void readProc();
    
};

}

#endif //ENERGO_TCPSOCKET_WIN_H
