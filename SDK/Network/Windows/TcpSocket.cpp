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

void energo::net::TcpSocket::close() {
    closesocket(static_cast<SOCKET>(_socketDescriptor));
}

void TcpSocket::write(string_view data) const {
    auto sent = send(static_cast<SOCKET>(_socketDescriptor), data.data(), data.size(), 0);
    if (sent != data.size()) {
        throw runtime_error("Не все данные были отправлены.");
    }
}

size_t TcpSocket::read(char *buffer, size_t length) const {
    return recv(static_cast<SOCKET>(_socketDescriptor), buffer, length, 0);
}

#endif
