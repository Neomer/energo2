//
// Created by kir on 29.12.2019.
//

#include "../../os.h"

#ifdef OS_LINUX

#include <thread>
#include <functional>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../TcpServer.h"
#include "../NetException.h"

using namespace std;
using namespace energo::net;

TcpServer::TcpServer() :
    _run{false},
    _connectionReadyListener{nullopt}
{
}

TcpServer::~TcpServer() {
    TcpServer::close();
}

bool TcpServer::bind(const ConnectionPoint &connectionPoint) {
    if (!TcpSocket::open(io::Device::OpenMode::None)) {
        cout << "Ошибка создания сокета: " << strerror(errno) << endl;
        return false;
    }
    
    struct sockaddr_in remoteAddr{};
    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(connectionPoint.getPort()); // NOLINT(hicpp-signed-bitwise)
    if (inet_pton(AF_INET, connectionPoint.getIp4Address().data(), &remoteAddr.sin_addr) <= 0)
    {
        throw exceptions::NetException{"Не удалось преобразовать имя хоста в корректный ip-адрес."};
    }
    auto result = ::bind(_socketDescriptor, (struct sockaddr *)&remoteAddr, sizeof(remoteAddr));
    if (result < 0) {
        cout << "Ошибка связывания сокета: " << strerror(errno) << endl;
    }
    return result >= 0;
}

void TcpServer::listen() {
    if (_run) {
        return;
    }
    _run = true;
    thread listenThread{std::bind(&TcpServer::listenProc, this)};
    listenThread.detach();
}

void TcpServer::listenProc() {
    ::listen(_socketDescriptor, 0);

    if (!_connectionReadyListener.has_value()) {
        throw  exceptions::NetException{"Не установлен метод для обработки новых подключений."};
    }
    struct sockaddr_in remoteAddr{};
    socklen_t addrSize;
    while (_run) {
        auto socket = accept(_socketDescriptor, (struct sockaddr *)&remoteAddr, &addrSize);
        if (TcpSocket::IsValid(socket)) {
            _connectionReadyListener.value()(make_shared<TcpSocket>(
                    static_cast<TcpSocket::SocketDescriptorType>(socket),
                    move(ConnectionPoint{"", 0})));
        }
    }
}

void TcpServer::onConnectionReadyListener(const optional<function<void(shared_ptr<TcpSocket>)>> &listener) {
    _connectionReadyListener = listener;
}

void TcpServer::close() {
    if (!_run) {
        return;
    }
    _run = false;
    TcpSocket::close();
}


#endif