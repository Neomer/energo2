//
// Created by kir on 26.12.2019.
//

#include "../../os.h"

#ifdef OS_LINUX

#define INVALID_SOCKET      (-1)
#define BUFFER_SIZE         10240

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>
#include <utility>
#include "../TcpSocket.h"
#include "../NetException.h"
#include "../../Metadata/MetadataProvider.h"
#include "../../Metadata/TypeUids.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace energo::net;
using namespace energo::io;

TcpSocket::TcpSocket(TcpSocket::SocketDescriptorType descriptor, ConnectionPoint remoteConnectionPoint) :
    _socketDescriptor{descriptor},
    _dataListener{nullopt},
    _run{false},
    _mode{io::Device::OpenMode::None},
    _remotePoint{std::move(remoteConnectionPoint)}
{
    auto metadataProvider = meta::MetadataProvider::GetStatic();
    auto threadPoolMetadata = const_cast<meta::SingletonClassMetadata *>(dynamic_cast<const meta::SingletonClassMetadata *>(metadataProvider->find(THREADPOOL_TYPE_UID)));
    _threadPool = reinterpret_cast<threads::ThreadPool *>(threadPoolMetadata->createInstance());
}

TcpSocket::TcpSocket() :
    _socketDescriptor{socket(AF_INET, SOCK_STREAM, 0)},
    _dataListener{nullopt},
    _run{false},
    _mode{io::Device::OpenMode::None}
{
    auto metadataProvider = meta::MetadataProvider::GetStatic();
    auto threadPoolMetadata = const_cast<meta::SingletonClassMetadata *>(dynamic_cast<const meta::SingletonClassMetadata *>(metadataProvider->find(THREADPOOL_TYPE_UID)));
    _threadPool = reinterpret_cast<threads::ThreadPool *>(threadPoolMetadata->createInstance());
}

TcpSocket::~TcpSocket() {
    TcpSocket::close();
}

future<size_t> TcpSocket::write(IOStream<char> &stream) {
    if (_mode != io::Device::OpenMode::WriteOnly && _mode != io::Device::OpenMode::ReadWrite) {
        throw exceptions::IOException{"Устройство не открыто для записи."};
    }
    // TODO: вынести общую логику для асинхронных устройств ввода-вывода в базовый класс.
    auto future = _threadPool->execute([&stream, this]() -> size_t {
                                char buffer[BUFFER_SIZE];
                                size_t sent = 0;
                                while (stream.count()) {
                                    auto read = stream.read(buffer, 10240);
                                    sent += read;
                                    size_t written = 0;
                                    while ((written += send(_socketDescriptor, buffer + written, read - written, 0)) < read);
                                }
                                return sent;
                            });
    
    return future;
}

TcpSocket &TcpSocket::onBytesAvailable(function<void(io::IOStream<char> &)> &dataListener) {
    _dataListener = dataListener;
    return *this;
}

bool TcpSocket::open(io::Device::OpenMode openMode) {
    _mode = openMode;

    return _socketDescriptor != INVALID_SOCKET;
}

void TcpSocket::close() {
    if (_socketDescriptor != INVALID_SOCKET) {
        shutdown(_socketDescriptor, 0);
        _socketDescriptor = INVALID_SOCKET;
    }
}

future<size_t> TcpSocket::read(IOStream<char> &stream) {
    if (_mode != io::Device::OpenMode::ReadOnly && _mode != io::Device::OpenMode::ReadWrite) {
        throw exceptions::IOException{"Устройство не открыто для чтения."};
    }
    return std::future<size_t>();
}

bool TcpSocket::connect(const ConnectionPoint &connectionPoint) {
    if (_socketDescriptor == INVALID_SOCKET) {
        throw exceptions::NetException{"Сокет не был открыт."};
    }
    
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

bool TcpSocket::valid() const {
    return _socketDescriptor != INVALID_SOCKET;
}

bool TcpSocket::IsValid(SocketDescriptorType descriptor) {
    return descriptor != INVALID_SOCKET;
}

void TcpSocket::writeProc() {

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
                if (written < read) {
                    throw exceptions::NetException{"Не все данные были отправлены."};
                }
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

void TcpSocket::changeDataProcessMode(TcpSocket::DataProcessMode mode) {
    if (mode == DataProcessMode::Synchronous) {
        _run = false;
    } else {
        _run = true;
        if (static_cast<uint8_t>(_mode) & static_cast<uint8_t>(io::Device::OpenMode::ReadOnly)) {
            thread readThread{bind(&TcpSocket::readProc, this)};
            readThread.detach();
        }
    
        if (static_cast<uint8_t>(_mode) & static_cast<uint8_t>(io::Device::OpenMode::WriteOnly)) {
            thread writeThread{bind(&TcpSocket::writeProc, this)};
            writeThread.detach();
        }
    }
}

#undef INVALID_SOCKET
#undef BUFFER_SIZE


#endif