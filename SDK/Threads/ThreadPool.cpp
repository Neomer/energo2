//
// Created by kir on 03.01.2020.
//

#include "ThreadPool.h"

using namespace std;
using namespace energo::threads;

ThreadPool::ThreadPool(size_t threads) :
    _run{true},
    _threads{threads}
{

}

ThreadPool::~ThreadPool() {
    _run = false;
    _conditional.notify_all();
}

void ThreadPool::init() {
    for (auto idx = 0; idx < _threads.size(); ++idx) { // NOLINT(modernize-loop-convert)
        _threads[idx] = std::thread{Worker{this}};
        _threads[idx].detach();
    }
}

ThreadPool::Worker::Worker(ThreadPool *pool) :
    _pool{pool}
{

}

void ThreadPool::Worker::operator()() {
    std::function<void()> func;
    bool dequeued;
    while (_pool->_run) {
        {
            std::unique_lock<std::mutex> lock(_pool->_condMtx);
            if (_pool->_taskQueue.empty()) {
                _pool->_conditional.wait(lock);
            }
            if (!_pool->_run) {
                return;
            }
            dequeued = _pool->_taskQueue.dequeue(func);
        }
        if (dequeued) {
            func();
        }
    }
}
