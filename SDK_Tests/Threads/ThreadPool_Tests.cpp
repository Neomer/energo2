//
// Created by kir on 03.01.2020.
//

#include <functional>
#include <chrono>
#include <thread>
#include "ThreadPool_Tests.h"

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace energo::threads;

TEST_F(ThreadPool_Tests, DynamicThreadInstantiation) {
    auto func = [](const int a, const int b) -> int {
        return a + b;
    };
    ThreadPool pool{2};
    pool.init();
    auto future = pool.execute(func, 2, 3);
    
    EXPECT_EQ(future.get(), 5);
}