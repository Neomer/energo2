//
// Created by kir on 26.12.2019.
//

#include "../../os.h"

#ifdef OS_LINUX

#define BUFFER_SIZE     10240

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>
#include "../TcpSocket.h"
#include "../NetException.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace energo::net;
using namespace energo::io;

TcpSocket::TcpSocket(TcpSocket::SocketDescriptorType descriptor) :
    _socketDescriptor{descriptor},
    _dataListener{nullopt},
    _run{true},
    _readThread{bind(&TcpSocket::readProc, this)}
{
    _readThread.detach();
}

TcpSocket::TcpSocket() :
    _socketDescriptor{0},
    _dataListener{nullopt},
    _readThread{bind(&TcpSocket::readProc, this)}
{
    _readThread.detach();
}

TcpSocket::~TcpSocket() {
    if (_socketDescriptor != 0) {
        shutdown(_socketDescriptor, 0);
    }
}

future<size_t> TcpSocket::write(IOStream<char> &stream) {
    // TODO: вынести общую логику для асинхронных устройств ввода-вывода в базовый класс.
    auto future = async(launch::async,
                        [&stream, this]() -> size_t {
                                char buffer[BUFFER_SIZE];
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

void TcpSocket::readProc() {
    char buffer[BUFFER_SIZE];
    while (_run) {
        try
        {
            if (!_dataListener.has_value()) {
                this_thread::sleep_for(1s);
                continue;
            }
            auto read = recv(_socketDescriptor, buffer, BUFFER_SIZE, 0);
            if (read) {
                //TODO: обработка кейса, когда не удалось положить все данные в поток.
                auto written = _inputStream.write(buffer, read);
                _dataListener.value()(_inputStream);
            } else {
                _run = false;
                break;
            }
        } catch (exception &ex) {
            cout << ex.what() << endl;
        }
    }
}

bool TcpSocket::open(io::Device::OpenMode openMode) {
    _mode = openMode;
    _socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    return _socketDescriptor > 0;
}

void TcpSocket::close() {
    if (_socketDescriptor != 0) {
        shutdown(_socketDescriptor, 0);
        _socketDescriptor = 0;
    }
}

future<size_t> TcpSocket::read(IOStream<char> &stream) {
    return std::future<size_t>();
}

bool TcpSocket::connect(const ConnectionPoint &connectionPoint) {
    _remotePoint = connectionPoint;
    struct sockaddr_in remoteAddr{};
    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(connectionPoint.getPort()); // NOLINT(hicpp-signed-bitwise)
    if (inet_pton(AF_INET, connectionPoint.getIp4Address().data(), &remoteAddr.sin_addr) <= 0)
    {
        throw exceptions::NetException{"Не удалось преобразовать имя хоста в корректный ip-адрес."};
    }
    auto result = ::connect(_socketDescriptor, (struct sockaddr *) &remoteAddr, sizeof(remoteAddr));
    if (result < 0) {
        cout << strerror(errno) << endl;
    }
    return result >= 0;
}

#undef BUFFER_SIZE


#endif