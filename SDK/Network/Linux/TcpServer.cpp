//
// Created by kir on 29.12.2019.
//

#include "../../os.h"

#ifdef OS_LINUX

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../TcpServer.h"
#include "../NetException.h"

using namespace std;
using namespace energo::net;

bool TcpServer::bind(const ConnectionPoint &connectionPoint) {
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
        cout << strerror(errno) << endl;
    }
    return result >= 0;
}

void TcpServer::listen() {
    ::listen(_socketDescriptor, 0);
}

#endif