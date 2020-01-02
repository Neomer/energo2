//
// Created by kir on 26.12.2019.
//

#ifndef ENERGO_IOSTREAM_H
#define ENERGO_IOSTREAM_H

#include <iostream>
#include "IOException.h"
#include "../Types/ThreadSafeQueue.h"

#ifndef IOSTREAM_BUFFER_SIZE
#define IOSTREAM_BUFFER_SIZE            102400
#endif

namespace energo::io {

template<typename TDataType>
class IOStream {
    types::ThreadSafeQueue<TDataType, IOSTREAM_BUFFER_SIZE> _queue;

public:
    IOStream() = default;

    ~IOStream() = default;
    
    void put(TDataType data) {
        _queue.push(data);
    }
    
    [[nodiscard]] TDataType get() {
        TDataType result;
        if (!_queue.take(result)) {
            throw exceptions::IOException{"Поток ввода-вывода пуст."};
        }
        return result;
    }
    
    [[nodiscard]] bool any() const {
        return _queue.any();
    }
    
    [[nodiscard]] size_t read(TDataType *buffer, size_t size) {
        size_t readSize;
        if (!_queue.take(buffer, size, readSize)) {
            throw exceptions::IOException{"Не удалось прочитать из буфера."};
        }
        return readSize;
    }
    
    [[nodiscard]] size_t write(const TDataType *buffer, size_t size) {
        size_t write;
        if (!_queue.push(buffer, size, write)) {
            throw exceptions::IOException{"Буффер переполнен."};
        }
        return write;
    }
    
    [[nodiscard]] size_t count() const {
        return _queue.count();
    }
};

}

#endif //ENERGO_IOSTREAM_H
