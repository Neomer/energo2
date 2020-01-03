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

TEST_F(ThreadSafeQueue_Tests, FullQueueMustReturnFalseOnInsert) {
    ThreadSafeQueue<int, 1> queue;
    EXPECT_TRUE(queue.push(1));
    EXPECT_EQ(queue.count(), 1);
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
    EXPECT_EQ(queue.getWriteIdx(), 0);
}

TEST_F(ThreadSafeQueue_Tests, WriteToFullQueueAfterOnReadingMustReturnsFalse) {
    ThreadSafeQueue<int, 5> queue{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(queue.getReadIdx(), 0);
    EXPECT_EQ(queue.getWriteIdx(), 0);
    int val = 0;
    EXPECT_TRUE(queue.take(val));
    EXPECT_EQ(val, 1);
    EXPECT_TRUE(queue.push(5));
    EXPECT_FALSE(queue.push(6));
}

TEST_F(ThreadSafeQueue_Tests, AfterReadingAllDataReadAndWriteIndexesMustSetToZero) {
    ThreadSafeQueue<int, 3> queue{ 1, 2, 3 };
    EXPECT_EQ(queue.getReadIdx(), 0);
    EXPECT_EQ(queue.getWriteIdx(), 0);
    int val = 0;
    EXPECT_TRUE(queue.take(val));
    EXPECT_EQ(val, 1);
    EXPECT_TRUE(queue.push(5));
    int buf[5];
    size_t read = 0;
    EXPECT_TRUE(queue.take(buf, 3, read));
    EXPECT_EQ(buf[0], 2);
    EXPECT_EQ(buf[1], 3);
    EXPECT_EQ(buf[2], 5);
    EXPECT_EQ(queue.getReadIdx(), 0);
    EXPECT_EQ(queue.getWriteIdx(), 0);
}


TEST_F(ThreadSafeQueue_Tests, PushTooLongArrayMustWriteAtLeastQueueSizeItems) {
    ThreadSafeQueue<int, 3> queue;
    int b[] = {1, 2, 3, 4, 5};
    size_t written = 0;
    EXPECT_TRUE(queue.push(b, 5, written));
    EXPECT_EQ(written, queue.size());
    EXPECT_EQ(written, queue.count());
    EXPECT_TRUE(queue.full());
}

TEST_F(ThreadSafeQueue_Tests, WriteString) {
    ThreadSafeQueue<char, 10> queue;
    size_t written;
    EXPECT_TRUE(queue.push("Hello", 6, written));
    EXPECT_EQ(written, 6);
    EXPECT_EQ(queue.getWriteIdx(), 6);
}


TEST_F(ThreadSafeQueue_Tests, ReadShortString) {
    ThreadSafeQueue<char, 10> queue{ 'H', 'e', 'l', 'l', 'o', 0 };
    char buf[256];
    size_t read;
    EXPECT_TRUE(queue.take(buf, 256, read));
    EXPECT_EQ(read, 6);
    EXPECT_EQ(strcmp(buf, "Hello"), 0);
}



#pragma clang diagnostic pop
