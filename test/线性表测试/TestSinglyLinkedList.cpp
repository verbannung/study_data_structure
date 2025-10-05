#include "../../线性表/SinglyLinkedList.h"
#include "gtest/gtest.h"

class SinglyLinkedListTest : public ::testing::Test {
protected:
    SinglyLinkedList<int> list;

    void SetUp() override {
        list.insert(0, 1);
        list.insert(1, 2);
        list.insert(2, 3);
    }
};

TEST_F(SinglyLinkedListTest, SizeShouldBeThree) {
    EXPECT_EQ(list.size(), 3);
}

TEST_F(SinglyLinkedListTest, GetShouldReturnCorrectElement) {
    EXPECT_EQ(list.get(0), 1);
    EXPECT_EQ(list.get(1), 2);
    EXPECT_EQ(list.get(2), 3);
}

TEST_F(SinglyLinkedListTest, IndexOfShouldFindCorrectIndex) {
    EXPECT_EQ(list.indexOf(2).value(), 1);
    EXPECT_EQ(list.indexOf(3).value(), 2);
    EXPECT_FALSE(list.indexOf(4).has_value());
}

TEST_F(SinglyLinkedListTest, EraseShouldRemoveElement) {
    list.erase(1);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.get(1), 3);
}

TEST_F(SinglyLinkedListTest, InsertShouldAddElementAtCorrectPosition) {
    list.insert(1, 99);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.get(1), 99);
    EXPECT_EQ(list.get(2), 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}