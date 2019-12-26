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

TEST_F(ThreadSafeQueue_Tests, ReadToArray) {
    ThreadSafeQueue<int, 10> queue{ 1, 2, 3, 4 };
    EXPECT_EQ(queue.getReadIdx(), 0);
    EXPECT_EQ(queue.getWriteIdx(), 4);
    int b[2];
    size_t read;
    EXPECT_TRUE(queue.take(b, 2, read));
    EXPECT_EQ(read, 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(queue.getReadIdx(), 2);
    EXPECT_EQ(queue.getWriteIdx(), 4);
}

TEST_F(ThreadSafeQueue_Tests, InitializeFullQueueWritePointerMustSetToZero) {
    ThreadSafeQueue<int, 5> queue{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(queue.getReadIdx(), 0);
    EXPECT_EQ(queue.getWriteIdx(), 0);
}

TEST_F(ThreadSafeQueue_Tests, ReadToArrayWithSwapReadPointerToBegin) {
    ThreadSafeQueue<int, 5> queue{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(queue.getReadIdx(), 0);
    EXPECT_EQ(queue.getWriteIdx(), 0);
    int b[2];
    size_t read;
    EXPECT_TRUE(queue.take(b, 2, read));
    EXPECT_EQ(read, 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(queue.getReadIdx(), 2);
    EXPECT_EQ(queue.getWriteIdx(), 4);
}



#pragma clang diagnostic pop
