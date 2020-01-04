//
// Created by kir on 04.01.2020.
//

#ifndef ENERGO_THREADSAFEDYNAMICQUEUE_H
#define ENERGO_THREADSAFEDYNAMICQUEUE_H

#include <mutex>
#include <queue>

namespace energo::types {

template<typename TElement>
class ThreadSafeDynamicQueue {
    std::queue<TElement> _queue;
    std::mutex _mtx;
    
public:
    ThreadSafeDynamicQueue() = default;
    ThreadSafeDynamicQueue(std::initializer_list<TElement> args) : _queue{args} {
    
    }
    ~ThreadSafeDynamicQueue() {
        std::unique_lock<std::mutex> lock(_mtx);
    }
    
    [[nodiscard]] bool empty() {
        std::unique_lock<std::mutex> lock(_mtx);
        return _queue.empty();
    }
    
    void enqueue(TElement& t) {
        std::unique_lock<std::mutex> lock(_mtx);
        _queue.push(t);
    }
    
    [[nodiscard]] bool dequeue(TElement &element) {
        std::unique_lock<std::mutex> lock(_mtx);
        if (_queue.empty()) {
            return false;
        }
        element = std::move(_queue.front());
        _queue.pop();
        return true;
    }
};

}

#endif //ENERGO_THREADSAFEDYNAMICQUEUE_H
