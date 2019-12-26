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

bool TcpSocket::open(energo::io::IODevice<char>::OpenMode openMode) {
    return false;
}

void TcpSocket::close() {
    closesocket(static_cast<SOCKET>(_socketDescriptor));
}

#endif
