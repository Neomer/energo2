//
// Created by kir on 02.01.2020.
//

#ifndef ENERGO_DYNAMICSIZEQUEUE_H
#define ENERGO_DYNAMICSIZEQUEUE_H

#include <cinttypes>
#include <algorithm>

#define DEFAULT_ALLOCATED        8

namespace energo::types {

template<typename TElement>
class DynamicSizeQueue {
    TElement *_data, *_readPtr, *_writePtr, *_endPtr;

public:
    explicit DynamicSizeQueue() :
            _data{ new TElement[DEFAULT_ALLOCATED] },
            _readPtr{_data},
            _writePtr{_data},
            _endPtr{_data + DEFAULT_ALLOCATED}
    {

    }

    explicit DynamicSizeQueue(size_t count)
    {
        auto formattedSize = (static_cast<size_t>(count / DEFAULT_ALLOCATED) + 1) * DEFAULT_ALLOCATED;
        _data = new TElement[formattedSize];
        _readPtr = _writePtr = _data;
        _endPtr = _data + formattedSize;
    }

    /**
     * @return максимальное количество элементов, котороые способен вместить очередь.
     */
    [[nodiscard]] inline size_t size() const {
        return _endPtr - _data;
    }

    /**
     * @return фактическое количество элементов, записанное в очередь.
     */
    [[nodiscard]] inline size_t available() const {
        return _writePtr - _readPtr;
    }

    /**
     * @return пуста ли очередь.
     */
    [[nodiscard]] inline bool empty() const {
        return _writePtr == _readPtr;
    }

    /**
     * @return полна ли очередь.
     */
    [[nodiscard]] inline bool full() const {
        return _writePtr == _endPtr;
    }

    /**
     * Читает в element значение элемента, на котором в текущий момент находится указатель для чтения.
     * @param element Элемент, в который необходимо записать значение.
     * @return Удалось ли прочитать значение.
     */
    [[nodiscard]] bool read(TElement &element) {
        if (_readPtr == _writePtr) {
            return false;
        }
        element = *_readPtr++;
        defragmentation();
        return true;
    }

    [[nodiscard]] size_t readAll(TElement *buffer, size_t size) {
        auto actuallyRead = std::min<size_t>(size, available());
        auto endPtr = _readPtr + actuallyRead;
        std::copy(_readPtr, endPtr, buffer);
        defragmentation();
        return actuallyRead;
    }

    /**
     * Резервирует место в очередье для того, чтобы он вместил по меньшей мере size элементов. Если в очередь до этого уже были записаны данные, они будут скопированы.
     * @param size Количество элементов, которое точно будет размещаться в очередь.
     */
    void reserve(size_t size) {
        auto formattedSize = (static_cast<size_t>(size / DEFAULT_ALLOCATED) + 1) * DEFAULT_ALLOCATED;
        if (void *mem = std::realloc(_data, size)) {
            auto tmp = static_cast<TElement *>(mem);
            std::copy(_readPtr, _writePtr, tmp + _readPtr - _data);
            _readPtr = tmp + _readPtr - _data;
            _writePtr = tmp + _writePtr - _data;
            _data = tmp;
        } else {
            throw std::bad_alloc();
        }
    }

    /**
     * Записывает в очередь значение
     * @param element значение, которое необходимо записать.
     * @throws std::bad_alloc не удалось выделить память для добавления элемента.
     */
    void write(const TElement &element) {
        if (full()) {
            reserve(size() * 2);
        }
        *_writePtr++ = element;
    }

    /**
     * Записывает в очередь массив элементов.
     * @param data Массив элементов, которые необходимо записать в очередь.
     * @param size Количество элементов в исходном массиве.
     * @throws std::bad_alloc не удалось выделить память для добавления элементов.
     */
    void writeAll(const TElement *data, size_t size) {
        if (_endPtr - _writePtr < size) {
            reserve(this->size() + size);
        }
        auto endPtr = data + size;
        std::copy(data, endPtr, _writePtr);
    }

private:
    inline void defragmentation() {
        if (empty()) {
            _writePtr = _readPtr = _data;
        }
    }
};

}

#undef DEFAULT_PREALLOCATED


#endif //ENERGO_DYNAMICSIZEQUEUE_H
