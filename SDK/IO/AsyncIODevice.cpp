//
// Created by vinokurov on 23.12.2019.
//

#include "AsyncIODevice.h"

using namespace std;
using namespace energo::io;

AsyncIODevice::AsyncIODevice(const std::function<void(void)> &openFunc,
        const std::function<void(void)> &closeFunc,
        const std::function<size_t(std::string_view)> &writeFunc,
        const std::function<size_t(char *, size_t)> &readFunc) :

        _openFunc{openFunc},
        _closeFunc{closeFunc},
        _writeFunc{writeFunc},
        _readFunc{readFunc},
        _run{true},
        _readThread{bind(&AsyncIODevice::readProc, this)}
{

}


AsyncIODevice::~AsyncIODevice() {
    _run = false;
}

bool AsyncIODevice::open(IODevice::OpenMode openMode) {
    return false;
}

void AsyncIODevice::close() {

}

std::future<size_t> AsyncIODevice::read(char *buffer, size_t length) {
    std::packaged_task<size_t(char *, size_t)> task{_readFunc};
    auto future = task.get_future();
    thread thread{move(task), buffer, length};
    thread.detach();
    return future;
}

future<size_t> AsyncIODevice::write(string_view data, function<void(exception &)> &onErrorCallback, optional<function<void(size_t)>> &onSuccessCallback) {
    return future<std::size_t>{};
}

void AsyncIODevice::readProc() {
    while (_run) {

    }
}
