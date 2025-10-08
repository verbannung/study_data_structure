//
// Created by Ko-chieh Yin on 10/8/25.
//

#include <gtest/gtest.h>
#include "LeftistHeap.h"

// 定义一个测试夹具（fixture）
class TestLeftistHeap : public ::testing::Test {
protected:
    LeftistHeap<int> heap;

    void SetUp() override {
        heap.push(5);
        heap.push(2);
        heap.push(8);
        heap.push(1);
    }

    void TearDown() override {
        heap.clear();
    }
};

TEST_F(TestLeftistHeap, PushAndTop) {
    EXPECT_FALSE(heap.empty());
    EXPECT_EQ(heap.size(), 4);
    EXPECT_EQ(heap.top(), 1);
}

TEST_F(TestLeftistHeap, PopRemovesMin) {
    heap.pop();
    EXPECT_EQ(heap.top(), 2);
    EXPECT_EQ(heap.size(), 3);
}

TEST_F(TestLeftistHeap, ClearEmptiesHeap) {
    heap.clear();
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
    EXPECT_THROW(heap.top(), std::runtime_error);
}

TEST_F(TestLeftistHeap, MergeTwoHeaps) {
    LeftistHeap<int> other;
    other.push(7);
    other.push(3);
    other.push(6);

    heap.merge(other);

    // other 应为空
    EXPECT_TRUE(other.empty());
    EXPECT_EQ(heap.size(), 7);
    EXPECT_EQ(heap.top(), 1);
}

TEST_F(TestLeftistHeap, MergeMaintainsHeapOrder) {
    LeftistHeap<int> other;
    other.push(0);
    other.push(9);

    heap.merge(other);
    EXPECT_EQ(heap.top(), 0);

    heap.pop();
    EXPECT_EQ(heap.top(), 1);
    heap.pop();
    EXPECT_EQ(heap.top(), 2);
}

TEST_F(TestLeftistHeap, PopOnEmptyThrows) {
    heap.clear();
    EXPECT_THROW(heap.pop(), std::runtime_error);
}


TEST_F(TestLeftistHeap, MaxHeapCompare) {
    LeftistHeap<int, std::greater<>> maxHeap;
    maxHeap.push(5);
    maxHeap.push(10);
    maxHeap.push(1);
    maxHeap.push(8);

    EXPECT_EQ(maxHeap.top(), 10);
    maxHeap.pop();
    EXPECT_EQ(maxHeap.top(), 8);
}


TEST_F(TestLeftistHeap, DepthCalculation) {
    std::size_t d = heap.depth();
    EXPECT_GE(d, 2);
    EXPECT_LE(d, heap.size());
}