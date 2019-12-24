//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_ASYNCIODEVICE_H
#define ENERGO_ASYNCIODEVICE_H

#include <mutex>
#include <future>
#include <thread>
#include <functional>
#include <atomic>
#include <optional>
#include "IODevice.h"
#include "../Types/ThreadSafeQueue.h"

namespace energo::io {

class EXPORTS AsyncIODevice {
    using TWriteTask = std::packaged_task<size_t(std::string_view, std::function<void(std::exception &)> &, std::optional<std::function<void(size_t)>> &)>;

    const std::function<void(void)> &_openFunc;
    const std::function<void(void)> &_closeFunc;
    const std::function<size_t(std::string_view)> &_writeFunc;
    const std::function<size_t(char *, size_t)> &_readFunc;
    std::atomic_bool _run;
    std::thread _readThread, _writeThread;
    energo::types::ThreadSafeQueue<TWriteTask, 50> _writeTasks;

public:
    AsyncIODevice(const std::function<void(void)> &openFunc,
            const std::function<void(void)> &closeFunc,
            const std::function<size_t(std::string_view)> &writeFunc,
            const std::function<size_t(char *, size_t)> &readFunc);

    virtual ~AsyncIODevice();

    bool open(IODevice::OpenMode openMode);

    void close();

    std::future<size_t> write(std::string_view data, std::function<void(std::exception &)> &onErrorCallback, std::optional<std::function<void(size_t)>> &onSuccessCallback);

    std::future<size_t> read(char *buffer, size_t length);

private:
    void readProc();
};

}

#endif //ENERGO_ASYNCIODEVICE_H
