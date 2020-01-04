//
// Created by kir on 03.01.2020.
//

#ifndef ENERGO_THREADPOOL_H
#define ENERGO_THREADPOOL_H

#include <memory>
#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <condition_variable>
#include <atomic>
#include "../Types/ThreadSafeDynamicQueue.h"
#include "../Metadata/SingletonClassMetadata.h"

namespace energo::threads {

class ThreadPool {
    std::vector<std::thread> _threads;
    types::ThreadSafeDynamicQueue<std::function<void()>> _taskQueue;
    std::mutex _condMtx;
    std::condition_variable _conditional;
    std::atomic_bool _run{true};

public:
    class Worker {
        ThreadPool *_pool;
    
    public:
        explicit Worker(ThreadPool *pool);
    
        void operator()();
    };
    
    explicit ThreadPool(size_t threads);
    
    void init();
    
    ~ThreadPool();
    
    template<typename F, typename...Args>
    auto execute(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        
        std::function<void()> wrapper_func = [task_ptr]() {
            (*task_ptr)();
        };
        
        _taskQueue.enqueue(wrapper_func);
        _conditional.notify_one();
        
        return task_ptr->get_future();
    }
};

class ThreadPoolMetadata : public meta::SingletonClassMetadata {
protected:
    [[nodiscard]] void *createInstanceInternal() const override;

public:
    ThreadPoolMetadata();
    
    [[nodiscard]] std::string_view getTypeName() const override;
};

}

#endif //ENERGO_THREADPOOL_H
