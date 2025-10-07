//
// Created by Ko-chieh Yin on 10/6/25.
//


#include "gtest/gtest.h"
#include "BinaryHeap.h"

template<class T>
class CustomComparator {
public:
    bool operator()(T& a, T& b) const {
        return a > b;
    }
};


class TestBinaryHeap : public ::testing::Test {
protected:
    MaxBinaryHeap<int> maxHeap;
    MinBinaryHeap<int> minHeap;
    BinaryHeap<int,CustomComparator<int>> customHeap;

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

        customHeap.push(3);
        customHeap.push(2);
        customHeap.push(10);
        customHeap.push(1);
        customHeap.push(5);

    }
};

TEST_F(TestBinaryHeap, testEmpty) {
    EXPECT_FALSE(maxHeap.empty());
    EXPECT_FALSE(minHeap.empty());

    maxHeap.clear();
    EXPECT_ANY_THROW(maxHeap.top());
}

TEST_F(TestBinaryHeap, testDepth) {
    EXPECT_EQ(maxHeap.depth(),3);
    EXPECT_EQ(minHeap.depth(),3);
}

TEST_F(TestBinaryHeap, testPop) {
    EXPECT_EQ(maxHeap.top(),10);
    EXPECT_EQ(minHeap.top(),1);
}

TEST_F(TestBinaryHeap, testClear) {
    maxHeap.clear();
    minHeap.clear();
    EXPECT_EQ(maxHeap.size(),0);
    EXPECT_EQ(minHeap.size(),0);
}

TEST_F(TestBinaryHeap, testCustomComparator) {
    EXPECT_EQ(customHeap.size(),5);
    EXPECT_EQ(customHeap.depth(),3);
    EXPECT_EQ(customHeap.top(),10);
}




