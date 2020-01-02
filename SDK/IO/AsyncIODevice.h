//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_ASYNCIODEVICE_H
#define ENERGO_ASYNCIODEVICE_H

#include <vector>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>
#include "../global.h"
#include "IODevice.h"
#include "../Types/ThreadSafeArray.h"

namespace energo::io {

template<typename TDataType>
class AsyncIODevice : public IODevice<TDataType> {
    std::atomic_bool _run;
    IOStream<TDataType> _stream;

public:
    AsyncIODevice() :
        _run{true}
    {
    
    }

    ~AsyncIODevice() override
    {
        _run = false;
    }
    
};

}

#endif //ENERGO_ASYNCIODEVICE_H
