//
// Created by vinokurov on 24.12.2019.
//

#ifndef ENERGO_THREADSAFEQUEUE_H
#define ENERGO_THREADSAFEQUEUE_H

#include "ThreadSafeArray.h"

namespace energo::types {

template<typename TElement, size_t NElements>
class ThreadSafeQueue {
    ThreadSafeArray<TElement, NElements> _queue;
    size_t _readIdx, _writeIdx;

    inline void assertIndex(size_t index) {
        if (index >= NElements) {
            throw std::range_error("Индекс элемента выходит за границы допустимых значений.");
        }
    }

public:
    ThreadSafeQueue() :
        _readIdx{0}, _writeIdx{0}
    {

    }

    ThreadSafeQueue(std::initializer_list<TElement> args) :
        _queue{args}, _readIdx{0}, _writeIdx{0}
    {

    }

    [[nodiscard]] inline size_t count() const noexcept {
        return _writeIdx - _readIdx;
    }

    [[nodiscard]] inline size_t size() const noexcept {
        return NElements;
    }

    [[nodiscard]] inline bool any() const {
        return _writeIdx != _readIdx;
    }

    [[nodiscard]] bool push(const TElement &element) {
        if (_writeIdx == size()) {
            if (_readIdx != 0) {
                _writeIdx = 0;
            } else {
                return false;
            }
        }
        _queue.set(_writeIdx++, element);
        return true;
    }

    [[nodiscard]] bool take(TElement &element) {
        if (_writeIdx == _readIdx) {
            return false;
        }
        if (_readIdx == size()) {
            _readIdx == 0;
        }
        element = _queue.get(_readIdx++);
        return true;
    }

    [[nodiscard]] inline size_t getReadIdx() const {
        return _readIdx;
    }

    [[nodiscard]] inline size_t getWriteIdx() const {
        return _writeIdx;
    }
};

}

#endif //ENERGO_THREADSAFEQUEUE_H
