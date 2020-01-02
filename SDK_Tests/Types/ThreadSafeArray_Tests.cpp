#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by vinokurov on 24.12.2019.
//

#include "ThreadSafeArray_Tests.h"

using namespace std;
using namespace energo::types;

TEST_F(ThreadSafeArray_Tests, ArrraySizeMustBeEqualsTemplateSize) {
    const int size = 5;
    ThreadSafeArray<int, size> array;
    EXPECT_EQ(array.size(), size);
}

TEST_F(ThreadSafeArray_Tests, ArrayGetMustEqualsSet) {
    const int size = 5;
    ThreadSafeArray<int, size> array;
    array.set(0, 4);
    EXPECT_EQ(array.get(0), 4);
}

TEST_F(ThreadSafeArray_Tests, SetValueWithIndexOutOfRangeMustThrowsException)
{
    ThreadSafeArray<int, 4> array;
    EXPECT_THROW(array.set(5, 3), range_error);
}

TEST_F(ThreadSafeArray_Tests, GetValueWithIndexOutOfRangeMustThrowsException)
{
    ThreadSafeArray<int, 4> array;
    EXPECT_THROW(array.get(5), range_error);
}

TEST_F(ThreadSafeArray_Tests, SetValueWithNegativeIndexMustThrowsException)
{
    ThreadSafeArray<int, 4> array;
    EXPECT_THROW(array.set(-1, 3), range_error);
}

TEST_F(ThreadSafeArray_Tests, GetValueWithNegativeIndexMustThrowsException)
{
    ThreadSafeArray<int, 4> array;
    EXPECT_THROW(array.get(-1), range_error);
}

TEST_F(ThreadSafeArray_Tests, InitializerList)
{
    ThreadSafeArray<int, 4> array{ 1, 2, 3, 4 };
    EXPECT_EQ(array.get(0), 1);
    EXPECT_EQ(array.get(1), 2);
    EXPECT_EQ(array.get(2), 3);
    EXPECT_EQ(array.get(3), 4);
}

TEST_F(ThreadSafeArray_Tests, ClearMustSetAllToZero)
{
    ThreadSafeArray<int, 4> array{ 1, 2, 3, 4 };
    array.clear();
    EXPECT_EQ(array.get(0), 0);
    EXPECT_EQ(array.get(1), 0);
    EXPECT_EQ(array.get(2), 0);
    EXPECT_EQ(array.get(3), 0);
}

TEST_F(ThreadSafeArray_Tests, CopyFromRawArray) {
    int src[3] = { 1, 2, 3 };
    ThreadSafeArray<int, 3> array;
    array.copyFrom(src, 0, 0, 3);
    EXPECT_EQ(array.get(0), 1);
    EXPECT_EQ(array.get(1), 2);
    EXPECT_EQ(array.get(2), 3);
}

TEST_F(ThreadSafeArray_Tests, CopyToRawArray) {
    int src[3];
    ThreadSafeArray<int, 3> array{ 1, 2, 3 };
    array.copyTo(src, 0, 0, 3);
    EXPECT_EQ(src[0], 1);
    EXPECT_EQ(src[1], 2);
    EXPECT_EQ(src[2], 3);
}


TEST_F(ThreadSafeArray_Tests, CopyToOtherArray) {
    ThreadSafeArray<int, 3> array{ 1, 2, 3 }, targetArray;
    array.copyTo(targetArray, 0, 0, 3);
    EXPECT_EQ(targetArray.get(0), 1);
    EXPECT_EQ(targetArray.get(1), 2);
    EXPECT_EQ(targetArray.get(2), 3);
}

TEST_F(ThreadSafeArray_Tests, CopyFromRawArrayTooManyItemsMustThrowsException) {
    int src[3] = { 1, 2, 3 };
    ThreadSafeArray<int, 2> array;
    EXPECT_THROW(array.copyFrom(src, 0, 0, 3), range_error);
}

#pragma clang diagnostic pop