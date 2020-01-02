//
// Created by vinokurov on 23.12.2019.
//

#include "../../os.h"

#ifdef  OS_WIN

#include <stdexcept>

#include "../TcpSocket.h"
#include <winsock2.h>

using namespace std;
using namespace energo::net;

TcpSocket::TcpSocket(SocketDescriptorType descriptor) :
    _socketDescriptor{descriptor}
{

}

TcpSocket::TcpSocket() {

}

TcpSocket::~TcpSocket() {

}

std::future<size_t> TcpSocket::write(energo::io::IOStream<char> &stream) {
    return std::future<size_t>();
}

TcpSocket &TcpSocket::onBytesAvailable(function<void(io::IOStream<char> &)> &dataListener) {
    return *this;
}

#endif
