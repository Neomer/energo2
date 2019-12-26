//
// Created by kir on 26.12.2019.
//

#include "../../os.h"

#ifdef OS_LINUX

#include <sys/socket.h>
#include "../TcpSocket.h"

using namespace std;
using namespace energo::net;
using namespace energo::io;

TcpSocket::TcpSocket(TcpSocket::SocketDescriptorType descriptor) :
    _socketDescriptor{descriptor},
    _dataListener{nullopt}
{

}

TcpSocket::TcpSocket() :
    _socketDescriptor{0},
    _dataListener{nullopt}
{

}

TcpSocket::~TcpSocket() {
    if (_socketDescriptor != 0) {
        shutdown(_socketDescriptor, 0);
    }
}

future<size_t> TcpSocket::write(IOStream<char> &stream) {
    auto future = async(launch::async,
                        [&stream, this]() -> size_t {
                                char buffer[10240];
                                size_t sent = 0;
                                while (stream.count()) {
                                    auto read = stream.read(buffer, 10240);
                                    sent += read;
                                    while ((read -= send(_socketDescriptor, buffer, read, 0)) > 0);
                                }
                                return sent;
                            });
    
    return future;
}

TcpSocket &TcpSocket::onBytesAvailable(function<void(io::IOStream<char> &)> &dataListener) {
    _dataListener = dataListener;
    return *this;
}


#endif