#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 24.12.2019.
//

#include "ThreadSafeQueue_Tests.h"

using namespace std;
using namespace energo::types;

TEST_F(ThreadSafeQueue_Tests, ReadEmptyQueueMustReturnsFalse) {
    ThreadSafeQueue<int, 5> queue;
    int value;
    EXPECT_FALSE(queue.take(value));
}

TEST_F(ThreadSafeQueue_Tests, FullQueueMuReturnFalseOnInsert) {
    ThreadSafeQueue<int, 1> queue;
    EXPECT_TRUE(queue.push(1));
    EXPECT_FALSE(queue.push(2));
}

TEST_F(ThreadSafeQueue_Tests, SecondReadMustReturnFalseIfQueueHasOnlyOneValue) {
    ThreadSafeQueue<int, 4> queue;
    int value;
    EXPECT_TRUE(queue.push(1));
    EXPECT_TRUE(queue.take(value));
    EXPECT_FALSE(queue.take(value));
}


#pragma clang diagnostic pop