//
// Created by vinokurov on 23.12.2019.
//

#ifndef ENERGO_IODEVICE_H
#define ENERGO_IODEVICE_H

#include "../global.h"
#include "../os.h"
#include <string_view>
#include <future>
#include "IOStream.h"
#include "Device.h"

namespace energo::io {

/**
 * Абстрактный класс для устройств ввода-вывода данных.
 * @tparam TDataType Тип элемента массива данных.
 */
template<typename TDataType>
class EXPORTS IODevice : Device {
public:
    virtual std::future<size_t> write(IOStream<TDataType> &stream) = 0;
    
    virtual std::future<size_t> read(IOStream<TDataType> &stream) = 0;

};

}

#endif //ENERGO_IODEVICE_H
