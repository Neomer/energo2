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
    int64_t;
#else
    int32_t ;
#endif

protected:
    SocketDescriptorType _socketDescriptor;

private:
    std::optional<std::function<void(io::IOStream<char> &)>> _dataListener;
    std::atomic_bool _run;
    io::IOStream<char> _inputStream;
    net::ConnectionPoint _remotePoint;
    io::Device::OpenMode _mode;

public:
    [[nodiscard]] static bool IsValid(SocketDescriptorType descriptor);
    
    TcpSocket(SocketDescriptorType descriptor, ConnectionPoint remoteConnectionPoint);
    
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
    
    [[nodiscard]] bool valid() const;

protected:
    void readProc();
    
    void writeProc();
    
};

}

#endif //ENERGO_TCPSOCKET_WIN_H
