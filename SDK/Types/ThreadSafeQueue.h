//
// Created by vinokurov on 24.12.2019.
//

#ifndef ENERGO_THREADSAFEQUEUE_H
#define ENERGO_THREADSAFEQUEUE_H

#include <algorithm>
#include <mutex>
#include "ThreadSafeArray.h"

namespace energo::types {

template<typename TElement, size_t NElements>
class ThreadSafeQueue {
    ThreadSafeArray<TElement, NElements> _queue;
    size_t _readIdx, _writeIdx;
    std::mutex _mtx;
    bool _rounded;

public:
    ThreadSafeQueue() :
        _readIdx{0}, _writeIdx{0}, _rounded{false}
    {

    }

    ThreadSafeQueue(std::initializer_list<TElement> args) :
        _queue{args}, _readIdx{0}, _writeIdx{args.size()}
    {
        if (_writeIdx == size()) {
            _writeIdx = 0;
            _rounded = true;
        } else {
            _rounded = false;
        }
    }

    [[nodiscard]] inline size_t count() const noexcept {
        return _rounded ? NElements - _readIdx + _writeIdx : _writeIdx - _readIdx;
    }

    [[nodiscard]] inline size_t size() const noexcept {
        return NElements;
    }

    [[nodiscard]] inline bool full() const noexcept {
        return count() == size();
    }

    [[nodiscard]] inline bool any() const {
        return _writeIdx != _readIdx || _rounded;
    }

    [[nodiscard]] bool push(const TElement &element) {
        std::lock_guard grd{_mtx};
        if (full()) {
            return false;
        }
        _queue.set(_writeIdx++, element);
        if (_writeIdx == size()) {
            _rounded = true;
            _writeIdx = 0;
        }
        return true;
    }
    
    [[nodiscard]] bool push(const TElement *data, size_t size, size_t &actualPushed) {
        std::lock_guard grd{_mtx};
        actualPushed = std::min<size_t>(size, this->size() - count());
        if (!actualPushed) {
            return false;
        }
        auto available = _rounded ? _readIdx - _writeIdx : this->size() - _writeIdx;
        _queue.copyFrom(data, 0, _writeIdx, available);
        _writeIdx += available;
        if (_writeIdx == this->size()) {
            auto remain = actualPushed - available;
            if (remain) {
                _queue.copyFrom(data, 0, available, remain);
            }
            _writeIdx = remain;
            _rounded = true;
        }
        return true;
    }
    
    [[nodiscard]] bool take(TElement &element) {
        std::lock_guard grd{_mtx};
        if (!any()) {
            return false;
        }
        element = _queue.get(_readIdx++);
        if (_readIdx == size()) {
            _readIdx == 0;
            _rounded = false;
        }
        defragmentation();
        return true;
    }
    
    [[nodiscard]] bool take(TElement *buffer, size_t size, size_t &actualSize) {
        std::lock_guard grd{_mtx};
        if (!any()) {
            return false;
        }
        actualSize = std::min<size_t>(size, NElements - _readIdx);
        _queue.copyTo(buffer, _readIdx, 0, actualSize);
        auto remain = size - actualSize;
        if (remain > 0 && _writeIdx > 0) {
            remain = std::min<size_t>(remain, _writeIdx);
            _queue.copyTo(buffer, 0, actualSize, remain);
            actualSize += remain;
            _readIdx = remain;
        } else {
            _readIdx += actualSize;
        }
        defragmentation();
        return true;
    }

    [[nodiscard]] inline size_t getReadIdx() const {
        return _readIdx;
    }

    [[nodiscard]] inline size_t getWriteIdx() const {
        return _writeIdx;
    }
    
private:
    inline void defragmentation() {
        if (_readIdx == _writeIdx) {
            _readIdx = 0;
            _writeIdx = 0;
            _rounded = false;
        }
    }
};

}

#endif //ENERGO_THREADSAFEQUEUE_H
