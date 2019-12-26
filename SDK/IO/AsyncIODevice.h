//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_ASYNCIODEVICE_H
#define ENERGO_ASYNCIODEVICE_H

#include <vector>
#include "../global.h"
#include "IODevice.h"
#include "../Types/ThreadSafeArray.h"

#ifndef ASYNC_DEVICE_BUFFER_SIZE
#define ASYNC_DEVICE_BUFFER_SIZE            10240
#endif

namespace energo::io {

template<typename TDataType>
class EXPORTS AsyncIODevice : public IODevice<TDataType> {
    types::ThreadSafeArray<TDataType, ASYNC_DEVICE_BUFFER_SIZE> _data;
    std::vector<TDataType> _dynamicBuffer;
    size_t _pointer;

public:
    AsyncIODevice() :
        _pointer{0}
    {
        _dynamicBuffer.reserve(ASYNC_DEVICE_BUFFER_SIZE);
    }

    ~AsyncIODevice() override = default;

protected:
    [[nodiscard]] virtual bool isDataCorrect() const = 0;

    virtual void onDataReady() const = 0;
};

}

#endif //ENERGO_ASYNCIODEVICE_H
