//
// Created by Ko-chieh Yin on 10/6/25.
//

#include "BinaryHeap.h"
#include "gtest/gtest.h"
#include "BinaryHeapUtil.h"

class TestBinaryHeapUtil : public ::testing::Test {
protected:
    MaxBinaryHeap<int> maxHeap;
    MinBinaryHeap<int> minHeap;

    void SetUp() override {
        maxHeap.push(3);
        maxHeap.push(2);
        maxHeap.push(10);
        maxHeap.push(1);
        maxHeap.push(5);


        minHeap.push(3);
        minHeap.push(2);
        minHeap.push(10);
        minHeap.push(1);
        minHeap.push(5);
    }
};

TEST_F(TestBinaryHeapUtil,测试最大堆的获取第n个元素) {
    EXPECT_EQ(getValueWithOrderPriority(maxHeap,3),3);
    EXPECT_EQ(getValueWithOrderPriority(maxHeap,2),5);
    EXPECT_EQ(getValueWithOrderPriority(maxHeap,1),10);
    EXPECT_ANY_THROW(getValueWithOrderPriority(maxHeap,0));
    EXPECT_ANY_THROW(getValueWithOrderPriority(maxHeap,6));
}
